// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Texture/D12Cubemap.hpp>

#include <Device/D12Device.hpp>
#include <D12ResourceInitializer.hpp>
#include <Buffers/D12Buffer.hpp>

namespace SA::RND::DX12
{
	void Cubemap::Create(const Device& _device, ResourceInitializer& _init, const RawCubemap& _raw)
	{
		const DXGI_FORMAT dxTextureFormat = API_GetFormat(_raw.texture.format);
		const DXGI_FORMAT dxIrradianceFormat = API_GetFormat(_raw.irradiance.format);

		// Create resources
		{
			const D3D12_HEAP_PROPERTIES heap{
				.Type = D3D12_HEAP_TYPE_DEFAULT,
				.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
				.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
				.CreationNodeMask = 1,
				.VisibleNodeMask = 1,
			};

			// Texture
			{
				const D3D12_RESOURCE_DESC desc{
					.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
					.Alignment = 0u,
					.Width = _raw.texture.extents.x,
					.Height = _raw.texture.extents.y,
					.DepthOrArraySize = 1,
					.MipLevels = static_cast<UINT16>(_raw.texture.mipLevels),
					.Format = dxTextureFormat,
					.SampleDesc = DXGI_SAMPLE_DESC{
						.Count = 1,
						.Quality = 0,
					},
					.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN,
					.Flags = D3D12_RESOURCE_FLAG_NONE,
				};

				SA_DX12_API(_device->CreateCommittedResource(&heap, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&mTexture)));
			}

			// Irradiance
			{
				const D3D12_RESOURCE_DESC desc{
					.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
					.Alignment = 0u,
					.Width = _raw.irradiance.extents.x,
					.Height = _raw.irradiance.extents.y,
					.DepthOrArraySize = 1,
					.MipLevels = static_cast<UINT16>(_raw.irradiance.mipLevels),
					.Format = dxIrradianceFormat,
					.SampleDesc = DXGI_SAMPLE_DESC{
						.Count = 1,
						.Quality = 0,
					},
					.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN,
					.Flags = D3D12_RESOURCE_FLAG_NONE,
				};

				SA_DX12_API(_device->CreateCommittedResource(&heap, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&mIrradiance)));
			}
		}


		// Copy data to GPU
		{
			// Texture
			{
				Buffer& staging = _init.CreateStagingBuffer(_device, _raw.texture.data.size(), _raw.texture.data.data());

				uint64_t offset = 0u;
				Vec2ui extents = _raw.texture.extents;
				const uint32_t channelNum = API_GetChannelNum(_raw.texture.format);

				for (uint32_t currMipLevel = 0u; currMipLevel < _raw.texture.mipLevels; ++currMipLevel)
				{
					const D3D12_TEXTURE_COPY_LOCATION src{
						.pResource = staging.Get(),
						.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
						.PlacedFootprint = D3D12_PLACED_SUBRESOURCE_FOOTPRINT{
							.Offset = offset,
							.Footprint = D3D12_SUBRESOURCE_FOOTPRINT{
								.Format = dxTextureFormat,
								.Width = extents.x,
								.Height = extents.y,
								.Depth = 1,
								.RowPitch = extents.x * channelNum,
							}
						}
					};

					const D3D12_TEXTURE_COPY_LOCATION dst{
						.pResource = mTexture.Get(),
						.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX,
						.SubresourceIndex = currMipLevel
					};

					_init.cmd->CopyTextureRegion(&dst, 0u, 0u, 0u, &src, nullptr);
				}
			}

			// Irradiance
			{
				Buffer& staging = _init.CreateStagingBuffer(_device, _raw.irradiance.data.size(), _raw.irradiance.data.data());

				uint64_t offset = 0u;
				Vec2ui extents = _raw.irradiance.extents;
				const uint32_t channelNum = API_GetChannelNum(_raw.irradiance.format);

				for (uint32_t currMipLevel = 0u; currMipLevel < _raw.irradiance.mipLevels; ++currMipLevel)
				{
					const D3D12_TEXTURE_COPY_LOCATION src{
						.pResource = staging.Get(),
						.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
						.PlacedFootprint = D3D12_PLACED_SUBRESOURCE_FOOTPRINT{
							.Offset = offset,
							.Footprint = D3D12_SUBRESOURCE_FOOTPRINT{
								.Format = dxIrradianceFormat,
								.Width = extents.x,
								.Height = extents.y,
								.Depth = 1,
								.RowPitch = extents.x * channelNum,
							}
						}
					};

					const D3D12_TEXTURE_COPY_LOCATION dst{
						.pResource = mIrradiance.Get(),
						.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX,
						.SubresourceIndex = currMipLevel
					};

					_init.cmd->CopyTextureRegion(&dst, 0u, 0u, 0u, &src, nullptr);
				}
			}
		}


		// Transitions Copy-Dst to Read-Only
		{
			const D3D12_RESOURCE_BARRIER barrier{
				.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
				.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
				.Transition = D3D12_RESOURCE_TRANSITION_BARRIER{
					.pResource = mTexture.Get(),
					.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
					.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST,
					.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
				}
			};

			D3D12_RESOURCE_BARRIER barriers[2]{ barrier, barrier };
			barriers[1].Transition.pResource = mIrradiance.Get();

			_init.cmd->ResourceBarrier(2, barriers);
		}
	}
	
	void Cubemap::Destroy(const Device& _device)
	{
		// Texture
		{
			SA_LOG_RAII(L"Cubemap texture destroyed.", Info, SA.Render.DX12, (L"Handle [%1]", mTexture.Get()));

			mTexture.Reset();
		}

		// Irradiance
		{
			SA_LOG_RAII(L"Cubemap irradiance destroyed.", Info, SA.Render.DX12, (L"Handle [%1]", mIrradiance.Get()));

			mIrradiance.Reset();
		}
	}
}

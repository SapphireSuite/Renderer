// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Texture/D12Texture.hpp>

#include <Device/D12Device.hpp>
#include <D12ResourceInitializer.hpp>
#include <Buffers/D12Buffer.hpp>

namespace SA::RND::DX12
{
	void Texture::Create(const Device& _device, ResourceInitializer& _init, const RawTexture& _raw)
	{
		const DXGI_FORMAT dxFormat = API_GetFormat(_raw.format);

		// Create resource
		{
			const D3D12_RESOURCE_DESC desc{
				.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
				.Alignment = 0u,
				.Width = _raw.extents.x,
				.Height = _raw.extents.y,
				.DepthOrArraySize = 1,
				.MipLevels = static_cast<UINT16>(_raw.mipLevels),
				.Format = dxFormat,
				.SampleDesc = DXGI_SAMPLE_DESC{
					.Count = 1,
					.Quality = 0,
				},
				.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN,
				.Flags = D3D12_RESOURCE_FLAG_NONE,
			};

			const D3D12_HEAP_PROPERTIES heap{
				.Type = D3D12_HEAP_TYPE_DEFAULT,
				.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
				.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
				.CreationNodeMask = 1,
				.VisibleNodeMask = 1,
			};

			SA_DX12_API(_device->CreateCommittedResource(&heap, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&mHandle)));
		}


		// Copy data to GPU
		{
			Buffer& staging = _init.CreateStagingBuffer(_device, _raw.data.size(), _raw.data.data());

			uint64_t offset = 0u;
			Vec2ui extents = _raw.extents;
			const uint32_t channelNum = API_GetChannelNum(_raw.format);

			for (uint32_t currMipLevel = 0u; currMipLevel < _raw.mipLevels; ++currMipLevel)
			{
				const D3D12_TEXTURE_COPY_LOCATION src{
					.pResource = staging.Get(),
					.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,
					.PlacedFootprint = D3D12_PLACED_SUBRESOURCE_FOOTPRINT{
						.Offset = offset,
						.Footprint = D3D12_SUBRESOURCE_FOOTPRINT{
							.Format = dxFormat,
							.Width = extents.x,
							.Height = extents.y,
							.Depth = 1,
							.RowPitch = extents.x * channelNum,
						}
					}
				};

				const D3D12_TEXTURE_COPY_LOCATION dst{
					.pResource = mHandle.Get(),
					.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX,
					.SubresourceIndex = currMipLevel
				};
				
				_init.cmd->CopyTextureRegion(&dst, 0u, 0u, 0u, &src, nullptr);
			}
		}


		// Transition Dst to Read-Only
		{
			const D3D12_RESOURCE_BARRIER barrier{
				.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
				.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
				.Transition = D3D12_RESOURCE_TRANSITION_BARRIER{
					.pResource = mHandle.Get(),
					.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
					.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST,
					.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
				}
			};

			_init.cmd->ResourceBarrier(1, &barrier);
		}

		SA_LOG(L"Texture created.", Info, SA.Render.DX12, (L"Handle [%1]", mHandle.Get()));
	}
	
	void Texture::Destroy()
	{
		SA_LOG_RAII(L"Texture destroyed.", Info, SA.Render.DX12, (L"Handle [%1]", mHandle.Get()));

		mHandle.Reset();
	}
}

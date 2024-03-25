// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <Pass/D12FrameBuffer.hpp>

#include <Device/D12Device.hpp>

namespace SA::RND::DX12
{
	namespace Intl
	{
		bool HasDepthAttachment(const RenderPassInfo& _info, const DX12::SubpassInfo& _subpass)
		{
			for (auto& attach : _subpass.attachments)
			{
				auto desc = _info.textureToDescriptorMap.at(attach.texture);

				if (desc.usage & D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL)
					return true;
			}

			return false;
		}
	}

	void FrameBuffer::Create(const Device& _device, const RenderPassInfo& _info)
	{
		mSubpassFrames.reserve(_info.subpasses.size());

		// Render Target view heap
		{
			uint32_t renderTargetNum = 0u;
			uint32_t depthStencilNum = 0u;

			for (auto& subpass : _info.subpasses)
			{
				for (auto& attach : subpass.attachments)
				{
					auto& desc = _info.textureToDescriptorMap.at(attach.texture);

					if (desc.usage & D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL)
						++depthStencilNum;
					else if (desc.usage & D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET)
						++renderTargetNum;
				}
			}

			if (renderTargetNum > 0)
			{
				D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
				rtvHeapDesc.NumDescriptors = renderTargetNum;
				rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
				rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

				SA_DX12_API(_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&mRenderTargetViewHeap)));
			}

			if (depthStencilNum > 0)
			{
				D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
				dsvHeapDesc.NumDescriptors = depthStencilNum;
				dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
				dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

				SA_DX12_API(_device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&mDepthStencilViewHeap)));
			}
		}


		mRTVDescriptorIncrementSize = _device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		mDSVDescriptorIncrementSize = _device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle(mRenderTargetViewHeap ? mRenderTargetViewHeap->GetCPUDescriptorHandleForHeapStart() : D3D12_CPU_DESCRIPTOR_HANDLE());
		D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle(mDepthStencilViewHeap ? mDepthStencilViewHeap->GetCPUDescriptorHandleForHeapStart() : D3D12_CPU_DESCRIPTOR_HANDLE());

		D3D12_HEAP_PROPERTIES heapProps = {};
		heapProps.Type = D3D12_HEAP_TYPE_DEFAULT;

		for (auto& subpass : _info.subpasses)
		{
			auto& subpassFrame = mSubpassFrames.emplace_back();
			subpassFrame.colorViewHeap = rtvHandle;
			subpassFrame.depthViewHeap = Intl::HasDepthAttachment(_info, subpass) ? dsvHandle : D3D12_CPU_DESCRIPTOR_HANDLE();
			subpassFrame.attachments.reserve(subpass.attachments.size());

			for (auto& attachInfo : subpass.attachments)
			{
				auto& desc = _info.textureToDescriptorMap.at(attachInfo.texture);

				Attachment attach;

				D3D12_RENDER_TARGET_VIEW_DESC viewDesc
				{
					.Format = desc.format,
					.ViewDimension = desc.sampling > 1 ? D3D12_RTV_DIMENSION_TEXTURE2DMS : D3D12_RTV_DIMENSION_TEXTURE2D,

					.Texture2D
					{
						.MipSlice = 0,
						.PlaneSlice = 0,
					}
				};

				// Resource
				{
					attach.texture = attachInfo.texture->Get();

					if (attachInfo.resolved)
						attach.resolved = attachInfo.resolved->Get();


					// Clear color
					{
						attach.clearValue.Format = desc.format;

						if (attachInfo.bClear)
						{
							if (desc.usage & D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL)
							{
								attach.clearValue.DepthStencil.Depth = desc.clearColor.r;
								attach.clearValue.DepthStencil.Stencil = static_cast<uint8_t>(desc.clearColor.g);
							}
							else
							{
								attach.clearValue.Color[0] = desc.clearColor.r;
								attach.clearValue.Color[1] = desc.clearColor.g;
								attach.clearValue.Color[2] = desc.clearColor.b;
								attach.clearValue.Color[3] = desc.clearColor.a;
							}
						}
						else
						{
							attach.clearValue.Color[0] = -1.0f;
						}
					}
				}

				// View.
				if (desc.usage & D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET)
				{
					_device->CreateRenderTargetView(attach.texture.Get(), &viewDesc, rtvHandle);
					rtvHandle.ptr += mRTVDescriptorIncrementSize;
				}
				else if (desc.usage & D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL)
				{
					_device->CreateDepthStencilView(attach.texture.Get(), nullptr, dsvHandle);
					dsvHandle.ptr += mDSVDescriptorIncrementSize;
				}

				subpassFrame.attachments.emplace_back(attach);
			}
		}

		SA_LOG("FrameBuffer created.", Info, SA.Render.DX12, (L"Handle [%1]", this))
	}

	void FrameBuffer::Destroy()
	{
		mSubpassFrames.clear();

		mRenderTargetViewHeap.Reset();
		mDepthStencilViewHeap.Reset();

		SA_LOG("FrameBuffer destroyed.", Info, SA.Render.DX12, (L"Handle [%1]", this))
	}

	uint32_t FrameBuffer::GetRTVDescriptorIncrementSize() const
	{
		return mRTVDescriptorIncrementSize;
	}

	uint32_t FrameBuffer::GetDSVDescriptorIncrementSize() const
	{
		return mDSVDescriptorIncrementSize;
	}


	uint32_t FrameBuffer::GetSubpassNum() const
	{
		return mSubpassFrames.size();
	}

	const FrameBuffer::SubpassFrame& FrameBuffer::GetSubpassFrame(uint32_t _subpassIndex) const
	{
		SA_ASSERT((OutOfArrayRange, _subpassIndex, mSubpassFrames), SA.Render.DX12);

		return mSubpassFrames[_subpassIndex];
	}
}

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/D12FrameBuffer.hpp>

#include <Device/D12Device.hpp>

#include "../Misc/D12Format.hpp"

namespace SA::RND::DX12
{
	void FrameBuffer::Create(const Device& _device, const RenderPassInfo& _info, MComPtr<ID3D12Resource> _presentImage)
	{
		/*
		mSubpassFrames.reserve(_info.subpasses.size());

		// Render Target view heap
		{
			uint32_t renderTargetNum = 0u;
			uint32_t depthStencilNum = 0u;

			for(auto& subpass : _info.subpasses)
			{
				for(auto& attach : subpass.attachments)
				{
					if(attach.type == AttachmentType::Color)
						++renderTargetNum;
					else if (attach.type == AttachmentType::Depth)
						++depthStencilNum;
				}
			}

			if(renderTargetNum > 0)
			{
				D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
				rtvHeapDesc.NumDescriptors = renderTargetNum;
				rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
				rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

				SA_DX12_API(_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&mRenderTargetViewHeap)));
			}

			if(depthStencilNum > 0)
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

		for(auto& subpass : _info.subpasses)
		{
			auto& subpassFrame = mSubpassFrames.emplace_back();
			subpassFrame.colorViewHeap = rtvHandle;
			subpassFrame.depthViewHeap = subpass.HasDepthAttachment() ? dsvHandle : D3D12_CPU_DESCRIPTOR_HANDLE();
			subpassFrame.attachments.reserve(subpass.attachments.size());

			for(auto& attachInfo : subpass.attachments)
			{
				Attachment attach;
				attach.clearValue.Format = attachInfo.format;

				D3D12_RENDER_TARGET_VIEW_DESC viewDesc
				{
					.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D,

					.Texture2D
					{
						.MipSlice = 0,
						.PlaneSlice = 0,
					}
				};

				// Resource
				{
					D3D12_RESOURCE_DESC desc{};
					desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
					desc.Width = attachInfo.extents.x;
					desc.Height = attachInfo.extents.y;
					desc.DepthOrArraySize = 1;
					desc.MipLevels = 1;
					desc.Format = attachInfo.format;
					desc.SampleDesc.Count = subpass.sampling;

					if (attachInfo.type == AttachmentType::Color)
					{
						attach.state = D3D12_RESOURCE_STATE_RENDER_TARGET;

						desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

						attach.clearValue.Color[0] = attachInfo.clearColor.r;
						attach.clearValue.Color[1] = attachInfo.clearColor.g;
						attach.clearValue.Color[2] = attachInfo.clearColor.b;
						attach.clearValue.Color[3] = attachInfo.clearColor.a;
					}
					else if (attachInfo.type == AttachmentType::Depth)
					{
						attach.state = D3D12_RESOURCE_STATE_DEPTH_WRITE;

						desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

						attach.clearValue.DepthStencil.Depth = attachInfo.clearColor.r;
						attach.clearValue.DepthStencil.Stencil = static_cast<uint8_t>(attachInfo.clearColor.g);
					}


					if (attachInfo.usage == AttachmentUsage::Present)
					{
						SA_ASSERT((Nullptr, _presentImage.Get()), SA.Render.DX12,
							L"Input present image handle must be valid with AttachmentUsage::Present");

						//attach.state = D3D12_RESOURCE_STATE_PRESENT;
	
						if (desc.SampleDesc.Count > 1)
						{
							viewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DMS;
							SA_DX12_API(_device->CreateCommittedResource(&heapProps,
								D3D12_HEAP_FLAG_NONE,
								&desc,
								attach.state,
								&attach.clearValue,
								IID_PPV_ARGS(&attach.imageBuffer)
							));

							attach.resolveImageBuffer = _presentImage;
						}
						else
						{
							attach.state = D3D12_RESOURCE_STATE_PRESENT;
							attach.imageBuffer = _presentImage;
						}
						
						viewDesc.Format = Intl::UNORMToSRGBFormat(_presentImage->GetDesc().Format);
					}
					else
					{
						// Create resource.

						SA_DX12_API(_device->CreateCommittedResource(&heapProps,
							D3D12_HEAP_FLAG_NONE,
							&desc,
							attach.state,
							&attach.clearValue,
							IID_PPV_ARGS(&attach.imageBuffer)
						));

						// Resolve resource.
						if (desc.SampleDesc.Count > 1 && 
							attachInfo.type == AttachmentType::Color) // DX12 does not support MSAA Depth resolve.
						{
							viewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DMS;
							desc.SampleDesc.Count = 1;

							SA_DX12_API(_device->CreateCommittedResource(&heapProps,
								D3D12_HEAP_FLAG_NONE,
								&desc,
								attach.state,
								&attach.clearValue,
								IID_PPV_ARGS(&attach.resolveImageBuffer)
							));
						}

						viewDesc.Format = attach.imageBuffer->GetDesc().Format;
					}
				}

				// View.
				if(attachInfo.type == AttachmentType::Color)
				{
					_device->CreateRenderTargetView(attach.imageBuffer.Get(), &viewDesc, rtvHandle);
					rtvHandle.ptr += mRTVDescriptorIncrementSize;

					subpassFrame.attachments.emplace_back(attach);
				}
				else if(attachInfo.type == AttachmentType::Depth)
				{
					_device->CreateDepthStencilView(attach.imageBuffer.Get(), nullptr, dsvHandle);
					dsvHandle.ptr += mDSVDescriptorIncrementSize;

					subpassFrame.depthAttachment = std::move(attach);
				}
			}
		}

		SA_LOG("FrameBuffer created.", Info, SA.Render.DX12, (L"Handle [%1]", this))
		*/
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


	FrameBuffer::SubpassFrame& FrameBuffer::GetSubpassFrame(uint32_t _subpassIndex)
	{
		SA_ASSERT((OutOfArrayRange, _subpassIndex, mSubpassFrames), SA.Render.DX12);

		return mSubpassFrames[_subpassIndex];
	}

	std::vector<FrameBuffer::Attachment>& FrameBuffer::GetSubpassAttachments(uint32_t _subpassIndex)
	{
		return GetSubpassFrame(_subpassIndex).attachments;
	}
}

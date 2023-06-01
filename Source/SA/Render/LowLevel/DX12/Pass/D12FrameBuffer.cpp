// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/D12FrameBuffer.hpp>

#include <Device/D12Device.hpp>

namespace SA::RND::DX12
{
	void FrameBuffer::Create(const Device& _device, const PassInfo& _info, MComPtr<ID3D12Resource> _presentImage)
	{
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
					else if(attach.type == AttachmentType::Depth)
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

			mImageBuffers.reserve(renderTargetNum + depthStencilNum);
		}


		const uint32_t rtvDescriptorSize = _device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		const uint32_t dsvDescriptorSize = _device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle(mRenderTargetViewHeap->GetCPUDescriptorHandleForHeapStart());
		D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle(mDepthStencilViewHeap->GetCPUDescriptorHandleForHeapStart());

		D3D12_HEAP_PROPERTIES heapProps = {};
		heapProps.Type = D3D12_HEAP_TYPE_DEFAULT;

		for(auto& subpass : _info.subpasses)
		{
			SubpassViewHeap& subpassHeap = mSubpassViewHeaps.emplace_back();
			subpassHeap.colorViewHeap = rtvHandle;
			subpassHeap.depthViewHeap = dsvHandle;

			for(auto& attach : subpass.attachments)
			{
				MComPtr<ID3D12Resource>& imgBuffer = mImageBuffers.emplace_back();

				// Resource
				if(attach.usage == AttachmentUsage::Present)
				{
					SA_ASSERT((Nullptr, _presentImage.Get()), SA.Render.DX12,
						L"Input present image handle must be valid with AttachmentUsage::Present");

					imgBuffer = _presentImage;
				}
				else
				{
					// Create resource.

					D3D12_RESOURCE_DESC desc{};
					desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
					desc.Width = attach.extents.x;
					desc.Height = attach.extents.y;
					desc.DepthOrArraySize = 1;
					desc.MipLevels = 1;
					desc.Format = attach.format;
					desc.SampleDesc.Count = subpass.sampling;

					D3D12_RESOURCE_STATES state = D3D12_RESOURCE_STATE_COMMON;
					D3D12_CLEAR_VALUE clearValue{attach.format};

					if(attach.type == AttachmentType::Color)
					{
						state = D3D12_RESOURCE_STATE_RENDER_TARGET;
						desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

						clearValue.Color[0] = attach.clearColor.r;
						clearValue.Color[1] = attach.clearColor.g;
						clearValue.Color[2] = attach.clearColor.b;
						clearValue.Color[3] = attach.clearColor.a;
					}
					else if(attach.type == AttachmentType::Depth)
					{
						state = D3D12_RESOURCE_STATE_DEPTH_WRITE;
						desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

						clearValue.DepthStencil.Depth = attach.clearColor.r;
						clearValue.DepthStencil.Stencil = static_cast<uint8_t>(attach.clearColor.g);
					}

					SA_DX12_API(_device->CreateCommittedResource(&heapProps,
						D3D12_HEAP_FLAG_NONE,
						&desc,
						state,
						&clearValue,
						IID_PPV_ARGS(&imgBuffer)
					));
				}


				// View.
				if(attach.type == AttachmentType::Color)
				{
					_device->CreateRenderTargetView(imgBuffer.Get(), nullptr, rtvHandle);
					rtvHandle.ptr += rtvDescriptorSize;
					++subpassHeap.colorRTNum;
				}
				else if(attach.type == AttachmentType::Depth)
				{
					_device->CreateDepthStencilView(imgBuffer.Get(), nullptr, dsvHandle);
					dsvHandle.ptr += dsvDescriptorSize;
				}
			}
		}

		SA_LOG("FrameBuffer created.", Info, SA.Render.DX12, (L"Handle [%1]", this))
	}

	void FrameBuffer::Destroy()
	{
		mSubpassViewHeaps.clear();
		mImageBuffers.clear();

		mRenderTargetViewHeap.Reset();
		mDepthStencilViewHeap.Reset();

		SA_LOG("FrameBuffer destroyed.", Info, SA.Render.DX12, (L"Handle [%1]", this))
	}


	void FrameBuffer::BindNextSubpass()
	{
		++mCurrSubpassIndex;

		SA_ASSERT((OutOfArrayRange, mCurrSubpassIndex, mSubpassViewHeaps), SA.Render.DX12, L"No more subpass to bind!");

		SubpassViewHeap& viewHeap = mSubpassViewHeaps[mCurrSubpassIndex];

		// _cmd->OMSetRenderTargets(viewHeap.num, &viewHeap.colorViewHeap, true, &viewHeap.depthViewHeap);
	}
}

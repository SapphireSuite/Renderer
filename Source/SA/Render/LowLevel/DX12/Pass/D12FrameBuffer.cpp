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

			for(auto& subpass : _info.subpasses)
				renderTargetNum += static_cast<uint32_t>(subpass.attachments.size());

			D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
			rtvHeapDesc.NumDescriptors = renderTargetNum;
			rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
			rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

			SA_DX12_API(_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&mRenderTargetViewHeap)));

			mImageBuffers.reserve(renderTargetNum);
		}


		const uint32_t rtvDescriptorSize = _device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle(mRenderTargetViewHeap->GetCPUDescriptorHandleForHeapStart());

		D3D12_HEAP_PROPERTIES heapProps = {};
		heapProps.Type = D3D12_HEAP_TYPE_DEFAULT;

		for(auto& subpass : _info.subpasses)
		{
			SubpassViewHeap& subpassHeap = mSubpassViewHeaps.emplace_back();
			subpassHeap.colorViewHeap = rtvHandle;
			subpassHeap.num = static_cast<uint32_t>(subpass.attachments.size());

			for(auto& attach : subpass.attachments)
			{
				MComPtr<ID3D12Resource>& imgBuffer = mImageBuffers.emplace_back();

				D3D12_RESOURCE_DESC desc{};
				desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
				desc.Width = attach.extents.x;
				desc.Height = attach.extents.y;
				desc.DepthOrArraySize = 1;
				desc.MipLevels = 1;
				desc.Format = attach.format;
				desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
				desc.SampleDesc.Count = subpass.sampling;

  				const D3D12_CLEAR_VALUE clearValue{attach.format,
					{{attach.clearColor.r, attach.clearColor.g, attach.clearColor.b, attach.clearColor.a}}};

				SA_DX12_API(_device->CreateCommittedResource(&heapProps,
					D3D12_HEAP_FLAG_NONE,
					&desc,
					D3D12_RESOURCE_STATE_RENDER_TARGET,
					&clearValue,
					IID_PPV_ARGS(imgBuffer.GetAddressOf())
				));


				if(attach.type == AttachmentType::Depth)
				{
					subpassHeap.depthViewHeap = rtvHandle;
				}


				if(attach.usage == AttachmentUsage::Present)
				{
					SA_ASSERT((Nullptr, _presentImage.Get()), SA.Render.DX12,
						L"Input present image handle must be valid with AttachmentUsage::Present");

					imgBuffer = _presentImage;
				}

				// View
				_device->CreateRenderTargetView(imgBuffer.Get(), nullptr, rtvHandle);
				rtvHandle.ptr += rtvDescriptorSize;
			}
		}
	}

	void FrameBuffer::Destroy()
	{
		mSubpassViewHeaps.clear();
		mImageBuffers.clear();

		mRenderTargetViewHeap.Reset();
	}


	void FrameBuffer::BindNextSubpass()
	{
		++mCurrSubpassIndex;

		SA_ASSERT((OutOfArrayRange, mCurrSubpassIndex, mSubpassViewHeaps), SA.Render.DX12, L"No more subpass to bind!");

		SubpassViewHeap& viewHeap = mSubpassViewHeaps[mCurrSubpassIndex];

		// _cmd->OMSetRenderTargets(viewHeap.num, &viewHeap.colorViewHeap, true, &viewHeap.depthViewHeap);
	}
}

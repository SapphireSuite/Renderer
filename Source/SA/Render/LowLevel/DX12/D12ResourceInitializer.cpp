// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <D12ResourceInitializer.hpp>

#include <Device/D12Device.hpp>
#include <Buffers/D12Buffer.hpp>

namespace SA::RND::DX12
{
	void ResourceInitializer::Create(const Device& _device)
	{
		if (_device.queueMgr.transfer.GetQueueNum())
			Create(_device, _device.queueMgr.transfer.GetQueue(0));
		else
			Create(_device, _device.queueMgr.graphics.GetQueue(0));
	}

	void ResourceInitializer::Create(const Device& _device, ID3D12CommandQueue* _queue)
	{
		mQueue = _queue;

		// Cmd
		{
			mCmdPool.Create(_device);

			cmd = mCmdPool.Allocate(_device);
			cmd.Begin();
		}

		// Synch
		{
			SA_DX12_API(_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence)));

			mFenceEvent = CreateEvent(nullptr, false, false, nullptr);
		}

		SA_LOG(L"Resource Initializer created.", Info, SA.Render.DX12);
	}

	void ResourceInitializer::Destroy()
	{
		mCmdPool.Destroy();

		// Clear remaining staging buffers
		for (auto& stagingBuffer : mStagingBuffers)
			stagingBuffer.Destroy();

		mStagingBuffers.clear();

		// Synch
		{
			mFence.Reset();
			CloseHandle(mFenceEvent);
		}

		SA_LOG(L"Resource Initializer destroyed.", Info, SA.Render.DX12);
	}

	Buffer& ResourceInitializer::CreateStagingBuffer(const Device& _device, uint64_t _size, const void* _data)
	{
		Buffer& stagingBuffer = mStagingBuffers.emplace_back();

		stagingBuffer.Create(_device,
			_size,
			D3D12_RESOURCE_STATE_COPY_SOURCE,
			D3D12_HEAP_TYPE_UPLOAD,
			_data
		);

		return stagingBuffer;
	}

	void ResourceInitializer::Submit()
	{
		cmd.End();


		// Submit commands.
		ID3D12CommandList* const cmdListHandle = static_cast<CommandList>(cmd).Get();
		mQueue->ExecuteCommandLists(1, &cmdListHandle);
		SA_DX12_API(mQueue->Signal(mFence.Get(), mFenceValue));


		// Synch
		SA_DX12_API(mFence->SetEventOnCompletion(mFenceValue, mFenceEvent));
		WaitForSingleObjectEx(mFenceEvent, INFINITE, FALSE);

		++mFenceValue;


		// Clear staging buffers
		for (auto& stagingBuffer : mStagingBuffers)
			stagingBuffer.Destroy();

		mStagingBuffers.clear();


		// Ready for new submit.
		cmd.Begin();
	}
}

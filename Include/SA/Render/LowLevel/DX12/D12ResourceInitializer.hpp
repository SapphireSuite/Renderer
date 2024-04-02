// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_D12_RESOURCE_INITIALIZER_GUARD
#define SAPPHIRE_RENDER_D12_RESOURCE_INITIALIZER_GUARD

#include <list>

#include <SA/Render/LowLevel/DX12/Device/Command/D12CommandPool.hpp>
#include <SA/Render/LowLevel/DX12/Buffers/D12Buffer.hpp>

namespace SA::RND::DX12
{
	class Device;

	class ResourceInitializer
	{
		CommandPool mCmdPool;
		ID3D12CommandQueue* mQueue = nullptr;

		std::list<Buffer> mStagingBuffers;

		HANDLE mFenceEvent;
		uint32_t mFenceValue = 1;
		MComPtr<ID3D12Fence> mFence;

	public:
		CommandBuffer cmd;

		void Create(const Device& _device);
		void Create(const Device& _device, ID3D12CommandQueue* _queue);
		void Destroy();

		Buffer& CreateStagingBuffer(const Device& _device, uint64_t _size, const void* _data = nullptr);

		void Submit();
	};
}

#endif // SAPPHIRE_RENDER_D12_RESOURCE_INITIALIZER_GUARD

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <VkResourceInitializer.hpp>

#include <SA/Collections/Debug>

#include <Device/VkDevice.hpp>
#include <Buffers/VkBuffer.hpp>

namespace SA::RND::VK
{
	void ResourceInitializer::Create(const Device& _device)
	{
		if (_device.queueMgr.transfer.GetQueueNum())
			Create(_device, _device.queueMgr.transfer.GetQueue(0));
		else
			Create(_device, _device.queueMgr.graphics.GetQueue(0));
	}

	void ResourceInitializer::Create(const Device& _device, const Queue& _queue)
	{
		mQueue = &_queue;
		mCmdPool.Create(_device, _queue.GetFamilyIndex());

		cmd = mCmdPool.Allocate(_device);
		cmd.Begin();

		SA_LOG(L"Resource Initializer created.", Info, SA.Render.Vulkan);
	}


	void ResourceInitializer::Destroy(const Device& _device)
	{
		mCmdPool.Destroy(_device);

		// Clear remaining staging buffers
		for (auto& stagingBuffer : mStagingBuffers)
			stagingBuffer.Destroy(_device);

		mStagingBuffers.clear();

		SA_LOG(L"Resource Initializer destroyed.", Info, SA.Render.Vulkan);
	}


	Buffer& ResourceInitializer::CreateStagingBuffer(const Device& _device, uint64_t _size, const void* _data)
	{
		Buffer& stagingBuffer = mStagingBuffers.emplace_back();

		stagingBuffer.Create(_device,
			_size,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			_data
		);

		return stagingBuffer;
	}


	void ResourceInitializer::Submit(const Device& _device)
	{
		cmd.End();


		// Submit commands.
		VkCommandBuffer vkCmd = cmd;
		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.pNext = nullptr;
		submitInfo.waitSemaphoreCount = 0u;
		submitInfo.pWaitSemaphores = nullptr;
		submitInfo.pWaitDstStageMask = nullptr;
		submitInfo.commandBufferCount = 1u;
		submitInfo.pCommandBuffers = &vkCmd;
		submitInfo.signalSemaphoreCount = 0u;
		submitInfo.pSignalSemaphores = nullptr;

		vkQueueSubmit(*mQueue, 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(*mQueue);


		// Clear staging buffers
		for (auto& stagingBuffer : mStagingBuffers)
			stagingBuffer.Destroy(_device);

		mStagingBuffers.clear();


		// Ready for new submit.
		cmd.Begin();
	}
}

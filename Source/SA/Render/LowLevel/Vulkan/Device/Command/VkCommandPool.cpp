// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Command/VkCommandPool.hpp>

#include <Device/VkDevice.hpp>

namespace SA::RND::VK
{
	void CommandPool::Create(const Device& _device, uint32_t _queueFamilyIndex)
	{
		VkCommandPoolCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		createInfo.pNext = nullptr;
		createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		createInfo.queueFamilyIndex = _queueFamilyIndex;

		SA_VK_API(vkCreateCommandPool(_device, &createInfo, nullptr, &mHandle), L"Failed to create command pool!");

		SA_LOG(L"Command pool created.", Info, SA.Render.Vulkan, ("Handle [%1]", mHandle));
	}
	
	void CommandPool::Destroy(const Device& _device)
	{
		SA_LOG_RAII(L"Command pool destroyed.", Info, SA.Render.Vulkan, ("Handle [%1]", mHandle))

		SA_VK_API(vkDestroyCommandPool(_device, mHandle, nullptr));
		mHandle = VK_NULL_HANDLE;
	}


	void CommandPool::Reset(const Device& _device)
	{
		SA_VK_API(vkResetCommandPool(_device, mHandle, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT));
	}


//{ Allocation

	CommandBuffer CommandPool::Allocate(const Device& _device, VkCommandBufferLevel _level)
	{
		CommandBuffer result;

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.pNext = nullptr;
		allocInfo.commandPool = mHandle;
		allocInfo.level = _level;
		allocInfo.commandBufferCount = 1u;

		SA_VK_API(vkAllocateCommandBuffers(_device, &allocInfo, &result.mHandle), L"Failed to allocate command buffers!");

		return result;
	}

	std::vector<CommandBuffer> CommandPool::AllocateMultiple(const Device& _device, uint32_t _num, VkCommandBufferLevel _level)
	{
		std::vector<CommandBuffer> result{ _num };
		std::vector<VkCommandBuffer> vkCommandBuffers{ _num };

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.pNext = nullptr;
		allocInfo.commandPool = mHandle;
		allocInfo.level = _level;
		allocInfo.commandBufferCount = _num;

		SA_VK_API(vkAllocateCommandBuffers(_device, &allocInfo, vkCommandBuffers.data()), L"Failed to allocate command buffers!");

		for (uint32_t i = 0; i < _num; ++i)
			result[i].mHandle = vkCommandBuffers[i];

		return result;
	}


	void CommandPool::Free(const Device& _device, CommandBuffer& _buffer)
	{
		SA_ASSERT((Default, _buffer.mHandle != VK_NULL_HANDLE), SA.Render.Vulkan, L"Destroy a null command buffer!")

		SA_VK_API(vkFreeCommandBuffers(_device, mHandle, 1u, &_buffer.mHandle));
		_buffer.mHandle = VK_NULL_HANDLE;
	}

	void CommandPool::FreeMultiple(const Device& _device, std::vector<CommandBuffer>& _buffers)
	{
		const uint32_t num = (uint32_t)_buffers.size();

		std::vector<VkCommandBuffer> vkCommandBuffers;
		vkCommandBuffers.resize(num);

		for (uint32_t i = 0; i < num; ++i)
		{
			SA_ASSERT((Default, _buffers[i].mHandle != VK_NULL_HANDLE), SA.Render.Vulkan, L"Destroy a null command buffer!")
			
			vkCommandBuffers[i] = _buffers[i].mHandle;
			_buffers[i].mHandle = VK_NULL_HANDLE;
		}

		SA_VK_API(vkFreeCommandBuffers(_device, mHandle, num, vkCommandBuffers.data()));
	}

//}


	CommandPool::operator VkCommandPool() const
	{
		return mHandle;
	}
}

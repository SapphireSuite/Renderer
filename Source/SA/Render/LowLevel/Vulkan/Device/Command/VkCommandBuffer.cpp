// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Command/VkCommandBuffer.hpp>

namespace SA::RND::VK
{
	void CommandBuffer::Begin()
	{
		SA_VK_API(vkResetCommandBuffer(mHandle, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT));

		// Start Command buffer record.
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.pNext = nullptr;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		beginInfo.pInheritanceInfo = nullptr;

		SA_VK_API(vkBeginCommandBuffer(mHandle, &beginInfo), L"Failed to begin command buffer!");
	}

	void CommandBuffer::End()
	{
		// End Command buffer record.
		SA_VK_API(vkEndCommandBuffer(mHandle), L"Failed to end command buffer!");
	}


	CommandBuffer::operator VkCommandBuffer() const
	{
		return mHandle;
	}
}

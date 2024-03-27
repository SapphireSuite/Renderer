// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Command/RHIVkCommandPool.hpp>

#include <Device/RHIVkDevice.hpp>
#include <Device/Command/RHIVkCommandBuffer.hpp>

#include <SA/Render/LowLevel/Vulkan/Device/VkDevice.hpp>

namespace SA::RND::RHI
{
	void VkCommandPool::Create(const Device* _device)
	{
		mVkDevice = &_device->API_Vulkan();

		// TODO: Clean
		mHandle.Create(*mVkDevice, mVkDevice->queueMgr.graphics[0].GetFamilyIndex());
	}
	
	void VkCommandPool::Destroy(const Device* _device)
	{
		SA_ASSERT((Equals, mVkDevice, &_device->API_Vulkan()), SA.Render.RHI, L"Device ptr should match to ensure correct destroy.");

		// Delete remaining command buffers.
		// Destroy is already handled by Vulkan API
		for (auto cmd : mCommandBuffers)
			delete cmd;

		mCommandBuffers.clear();
		//

		mHandle.Destroy(*mVkDevice);
		mVkDevice = nullptr;
	}


//{ Allocation

	CommandBuffer* VkCommandPool::Allocate()
	{
		RHI::VkCommandBuffer* const vkCmd = new RHI::VkCommandBuffer();

		vkCmd->mHandle = mHandle.Allocate(*mVkDevice);

		mCommandBuffers.emplace_back(vkCmd);

		return vkCmd;
	}
	
	std::vector<CommandBuffer*> VkCommandPool::Allocate(uint32_t _num)
	{
		std::vector<CommandBuffer*> result{ _num };

		std::vector<VK::CommandBuffer> vkCmds = mHandle.AllocateMultiple(*mVkDevice, _num);

		for (uint32_t i = 0; i < _num; ++i)
		{
			RHI::VkCommandBuffer* vkCmd = new RHI::VkCommandBuffer();
			mCommandBuffers.emplace_back(vkCmd);

			vkCmd->mHandle = vkCmds[i];
			
			result[i] = vkCmd;
		}

		return result;
	}

	
	void VkCommandPool::Free(CommandBuffer* _cmd)
	{
		if (std::erase(mCommandBuffers, _cmd))
		{
			mHandle.Free(*mVkDevice, _cmd->API_Vulkan());
			delete _cmd;
		}
		else
			SA_LOG((L"Try destroy CommandBuffer [%1] that does not belong to this CommandPool!", _cmd), Error, SA.Render.RHI);
	}
	
	void VkCommandPool::Free(std::vector<CommandBuffer*>& _cmds)
	{
		std::vector<VK::CommandBuffer> vkCmds;
		vkCmds.reserve(_cmds.size());

		for (size_t i = 0; i < _cmds.size(); ++i)
		{
			if (std::erase(mCommandBuffers, _cmds[i]))
			{
				vkCmds.emplace_back(_cmds[i]->API_Vulkan());
				delete _cmds[i];
			}
			else
				SA_LOG((L"Try destroy CommandBuffer [%1] that does not belong to this CommandPool!", _cmds[i]), Error, SA.Render.RHI);
		}

		mHandle.FreeMultiple(*mVkDevice, vkCmds);
	}

//}


	const VK::CommandPool& VkCommandPool::API_Vulkan() const
	{
		return mHandle;
	}
}

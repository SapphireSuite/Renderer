// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Command/D12CommandPool.hpp>

namespace SA::RND::DX12
{
	void CommandPool::Create(const Device& _device)
	{
		(void)_device;
	}
	
	void CommandPool::Destroy()
	{
	}


	CommandBuffer CommandPool::Allocate(const Device& _device, D3D12_COMMAND_LIST_TYPE _type)
	{
		CommandBuffer cmd;

		cmd.Create(_device, _type);

		return cmd;
	}

	std::vector<CommandBuffer> CommandPool::AllocateMultiple(const Device& _device, uint32_t _num, D3D12_COMMAND_LIST_TYPE _type)
	{
		std::vector<CommandBuffer> cmds{_num};

		for (auto& cmd : cmds)
			cmd.Create(_device, _type);

		return cmds;
	}


	void CommandPool::Free(CommandBuffer& _cmd)
	{
		_cmd.Destroy();
	}

	void CommandPool::FreeMultiple(std::vector<CommandBuffer>& _cmds)
	{
		for (auto& cmd : _cmds)
			cmd.Destroy();

		_cmds.clear();
	}
}

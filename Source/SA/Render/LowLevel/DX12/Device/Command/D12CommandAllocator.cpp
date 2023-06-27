// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Command/D12CommandAllocator.hpp>

#include <Device/D12Device.hpp>

namespace SA::RND::DX12
{
	void CommandAllocator::Create(const Device& _device, D3D12_COMMAND_LIST_TYPE _type)
	{
		SA_DX12_API(_device->CreateCommandAllocator(_type, IID_PPV_ARGS(&mHandle)));

		SA_LOG(L"Command Allocator created.", Info, SA.Render.DX12, ("Handle [%1]", mHandle.Get()));
	}

	void CommandAllocator::Destroy()
	{
		mHandle.Reset();

		SA_LOG(L"Command Allocator destroyed.", Info, SA.Render.DX12, ("Handle [%1]", mHandle.Get()));
	}


	CommandList CommandAllocator::Allocate(const Device& _device, D3D12_COMMAND_LIST_TYPE _type)
	{
		CommandList cmd;

		SA_DX12_API(_device->CreateCommandList(0, _type, mHandle.Get(), nullptr, IID_PPV_ARGS(&cmd.mHande)));

		return cmd;
	}

	std::vector<CommandList> CommandAllocator::AllocateMultiple(const Device& _device, uint32_t _num, D3D12_COMMAND_LIST_TYPE _type)
	{
		std::vector<CommandList> result{ _num };

		for (auto& cmd : result)
			SA_DX12_API(_device->CreateCommandList(0, _type, mHandle.Get(), nullptr, IID_PPV_ARGS(&cmd.mHande)));

		return result;
	}


	void CommandAllocator::Free(CommandList& _cmd)
	{
		_cmd.mHande.Reset();
	}

	void CommandAllocator::FreeMultiple(std::vector<CommandList>& _cmds)
	{
		for (auto& cmd : _cmds)
			cmd.mHande.Reset();

		_cmds.clear();
	}
}

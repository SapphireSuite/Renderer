// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Command/D12CommandPool.hpp>

#include <Device/D12Device.hpp>

namespace SA::RND::DX12
{
	void CommandPool::Create(const Device& _device, D3D12_COMMAND_LIST_TYPE _type)
	{
		SA_DX12_API(_device->CreateCommandAllocator(_type, IID_PPV_ARGS(&mHandle)));

		SA_LOG(L"Command pool created.", Info, SA.Render.DX12, ("Handle [%1]", mHandle.Get()));
	}

	void CommandPool::Destroy()
	{
		mHandle.Reset();

		SA_LOG(L"Command pool destroyed.", Info, SA.Render.DX12, ("Handle [%1]", mHandle.Get()));
	}


	CommandList CommandPool::Allocate(const Device& _device, D3D12_COMMAND_LIST_TYPE _type)
	{
		CommandList cmd;

		SA_DX12_API(_device->CreateCommandList(0, _type, mHandle.Get(), nullptr, IID_PPV_ARGS(&cmd.mHande)));

		return cmd;
	}

	void CommandPool::Free(CommandList& _cmd)
	{
		_cmd.mHande.Reset();
	}
}

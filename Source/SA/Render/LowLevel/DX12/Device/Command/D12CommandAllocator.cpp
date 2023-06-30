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
		SA_LOG_RAII(L"Command Allocator destroyed.", Info, SA.Render.DX12, ("Handle [%1]", mHandle.Get()));

		mHandle.Reset();
	}


	CommandList CommandAllocator::Allocate(const Device& _device, D3D12_COMMAND_LIST_TYPE _type)
	{
		CommandList cmd;

		SA_DX12_API(_device->CreateCommandList(0, _type, mHandle.Get(), nullptr, IID_PPV_ARGS(&cmd.mHandle)));

		cmd.mHandle->Close();

		return cmd;
	}

	void CommandAllocator::Free(CommandList& _cmdList)
	{
		_cmdList.mHandle.Reset();
	}


	ID3D12CommandAllocator* CommandAllocator::Get() const
	{
		return mHandle.Get();
	}

	ID3D12CommandAllocator* CommandAllocator::operator->() const
	{
		return mHandle.Get();
	}
}

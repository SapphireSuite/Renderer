// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Command/D12CommandBuffer.hpp>

namespace SA::RND::DX12
{
	void CommandBuffer::Create(const Device& _device, D3D12_COMMAND_LIST_TYPE _type)
	{
		mAllocator.Create(_device, _type);
		mCmdList = mAllocator.Allocate(_device, _type);

		SA_LOG(L"Command Buffer created.", Info, SA.Render.DX12, (L"List [%1] Allocator [%2]", mCmdList.Get(), mAllocator.Get()));
	}

	void CommandBuffer::Destroy()
	{
		SA_LOG_RAII(L"Command Buffer destroyed.", Info, SA.Render.DX12, (L"List [%1] Allocator [%2]", mCmdList.Get(), mAllocator.Get()));

		mAllocator.Free(mCmdList);
		mAllocator.Destroy();
	}


	void CommandBuffer::Begin()
	{
		mAllocator->Reset();
		mCmdList->Reset(mAllocator.Get(), nullptr);
	}
	
	void CommandBuffer::End()
	{
		mCmdList->Close();
	}


	void CommandBuffer::Draw(uint32_t _vertexNum, uint32_t _instanceNum, uint32_t _firstVertex, uint32_t _firstInstance)
	{
		SA_DX12_API(mCmdList->DrawInstanced(_vertexNum, _instanceNum, _firstVertex, _firstInstance));
	}


	const CommandList& CommandBuffer::GetCommandList() const
	{
		return mCmdList;
	}
}

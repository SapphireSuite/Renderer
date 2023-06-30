// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Command/RHID12CommandPool.hpp>

#include <Device/RHIDevice.hpp>

#include <Device/Command/RHID12CommandBuffer.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

namespace SA::RND::RHI
{
	void D12CommandPool::Create(const Device* _device)
	{
		mD12Device = &_device->API_DirectX12();

		mHandle.Create(*mD12Device);
	}
	
	void D12CommandPool::Destroy(const Device* _device)
	{
		SA_ASSERT((Equals, mD12Device, &_device->API_DirectX12()), SA.Render.RHI, L"Device ptr should match to ensure correct destroy.");

		// Delete remaining command buffers.
		// Destroy is already handled by DirectX12 API
		for (auto cmd : mCommandBuffers)
			delete cmd;

		mCommandBuffers.clear();
		//

		mHandle.Destroy();
		mD12Device = nullptr;
	}


//{ Allocation
		
	CommandBuffer* D12CommandPool::Allocate()
	{
		RHI::D12CommandBuffer* const d12Cmd = new RHI::D12CommandBuffer();

		d12Cmd->mHandle = mHandle.Allocate(*mD12Device);

		mCommandBuffers.emplace_back(d12Cmd);

		return d12Cmd;
	}
	
	std::vector<CommandBuffer*> D12CommandPool::Allocate(uint32_t _num)
	{
		std::vector<CommandBuffer*> result{ _num };

		std::vector<DX12::CommandBuffer> d12Cmds = mHandle.AllocateMultiple(*mD12Device, _num);

		for (uint32_t i = 0; i < _num; ++i)
		{
			RHI::D12CommandBuffer* d12Cmd = new RHI::D12CommandBuffer();
			mCommandBuffers.emplace_back(d12Cmd);

			d12Cmd->mHandle = d12Cmds[i];

			result[i] = d12Cmd;
		}

		return result;
	}

	
	void D12CommandPool::Free(CommandBuffer* _cmd)
	{
		if (std::erase(mCommandBuffers, _cmd))
		{
			mHandle.Free(_cmd->API_DirectX12());
			delete _cmd;
		}
		else
			SA_LOG((L"Try destroy CommandBuffer [%1] that does not belong to this CommandPool!", _cmd), Error, SA.Render.RHI);
	}
	
	void D12CommandPool::Free(std::vector<CommandBuffer*>& _cmds)
	{
		std::vector<DX12::CommandBuffer> d12Cmds;
		d12Cmds.reserve(_cmds.size());

		for (size_t i = 0; i < _cmds.size(); ++i)
		{
			if (std::erase(mCommandBuffers, _cmds[i]))
			{
				d12Cmds.emplace_back(_cmds[i]->API_DirectX12());
				delete _cmds[i];
			}
			else
				SA_LOG((L"Try destroy CommandBuffer [%1] that does not belong to this CommandPool!", _cmds[i]), Error, SA.Render.RHI);
		}

		mHandle.FreeMultiple(d12Cmds);
	}

//}


	const DX12::CommandPool& D12CommandPool::API_DirectX12() const
	{
		return mHandle;
	}
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL

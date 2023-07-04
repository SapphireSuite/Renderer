// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/RHID12Pipeline.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <Device/RHIDevice.hpp>
#include <Device/Command/RHID12CommandBuffer.hpp>

namespace SA::RND::RHI
{
	void D12Pipeline::Create(const Device* _device, const GraphicsPipelineInfo& _info)
	{
		auto gPipeline = new DX12::GraphicsPipeline();

		gPipeline->Create(_device->API_DirectX12(), _info.API_DirectX12());

		mHandle = gPipeline;
	}

	void D12Pipeline::Destroy(const Device* _device)
	{
		(void)_device;

		mHandle->Destroy();
		delete mHandle;
	}

	void D12Pipeline::Bind(const CommandBuffer* _cmd)
	{
		mHandle->Bind(_cmd->API_DirectX12().GetCommandList());
	}


	const DX12::Pipeline& D12Pipeline::API_DirectX12() const
	{
		return *mHandle;
	}
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL

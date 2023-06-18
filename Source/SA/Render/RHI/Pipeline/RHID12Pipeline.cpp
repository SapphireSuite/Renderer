// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/RHID12Pipeline.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <Device/RHIDevice.hpp>

namespace SA::RND::RHI
{
	void D12Pipeline::Create(const Device* _device, const GraphicsPipelineInfo& _info)
	{
		mHandle.Create(_device->API_DirectX12(), _info.API_DirectX12());
	}

	void D12Pipeline::Destroy(const Device* _device)
	{
		(void)_device;

		mHandle.Destroy();
	}


	const DX12::Pipeline& D12Pipeline::API_DirectX12() const
	{
		return mHandle;
	}
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL

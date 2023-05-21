// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <RHID12RenderInterface.hpp>

#include <Device/RHID12Device.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

namespace SA::RND::RHI
{
	void D12RenderInterface::Create()
	{
		mFactory.Create();
	}
	
	void D12RenderInterface::Destroy()
	{
		RenderInterface::Destroy();

		mFactory.Destroy();
	}

//{ Device

	Device* D12RenderInterface::InstantiateDeviceClass() const
	{
		return new D12Device();
	}

	std::vector<std::shared_ptr<DeviceInfo>> D12RenderInterface::QueryDeviceInfos() const
	{
		std::vector<DX12::DeviceInfo> d12Infos = mFactory.QueryDeviceInfos();

		std::vector<std::shared_ptr<DeviceInfo>> result;
		result.reserve(d12Infos.size());

		for(auto& d12Info : d12Infos)
			result.emplace_back(new D12DeviceInfo(std::move(d12Info)));

		return result;
	}

//}

	const DX12::Factory* D12RenderInterface::API_DirectX12() const
	{
		return &mFactory;
	}
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL

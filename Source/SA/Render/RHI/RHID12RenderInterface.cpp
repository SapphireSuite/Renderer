// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <RHID12RenderInterface.hpp>

#include <Device/RHID12Device.hpp>
#include <Surface/RHID12WindowSurface.hpp>
#include <Surface/RHID12Swapchain.hpp>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

namespace SA::RND::RHI
{
	void D12RenderInterface::Create(const IWindowInterface* _winIntf)
	{
		RenderInterface::Create(_winIntf);

		mFactory.Create();
	}
	
	void D12RenderInterface::Destroy()
	{
		RenderInterface::Destroy();

		mFactory.Destroy();
	}

//{ WindowSurface

	WindowSurface* D12RenderInterface::InstantiateWindowSurfaceClass() const
	{
		return new D12WindowSurface();
	}

//}


//{ Device

	Device* D12RenderInterface::InstantiateDeviceClass() const
	{
		return new D12Device();
	}

	std::vector<std::shared_ptr<DeviceInfo>> D12RenderInterface::QueryDeviceInfos(const DeviceRequirements& _reqs) const
	{
		std::vector<DX12::DeviceInfo> d12Infos = mFactory.QueryDeviceInfos(_reqs.API_DirectX12());

		std::vector<std::shared_ptr<DeviceInfo>> result;
		result.reserve(d12Infos.size());

		for(auto& d12Info : d12Infos)
			result.emplace_back(new D12DeviceInfo(std::move(d12Info)));

		return result;
	}

//}


//{ Swapchain

	Swapchain* D12RenderInterface::InstantiateSwapchainClass() const
	{
		return new D12Swapchain();
	}

//}


//{ ShaderCompiler

	ShaderCompileResult D12RenderInterface::CompileShader(const ShaderCompileInfo& _info)
	{
		return mShaderCompiler.CompileDX(_info);
	}

//}

	const DX12::Factory& D12RenderInterface::API_DirectX12() const
	{
		return mFactory;
	}
}

#endif // SA_RENDER_LOWLEVEL_DX12_IMPL

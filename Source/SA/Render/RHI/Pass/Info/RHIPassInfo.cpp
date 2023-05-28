// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/Info/RHIPassInfo.hpp>

namespace SA::RND::RHI
{
	void PassInfo::SetAllSubpassesSampling(Sampling _sampling)
	{
		for(auto& subpass : subpasses)
			subpass.sampling = _sampling;
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VK::PassInfo PassInfo::API_Vulkan() const
	{
		VK::PassInfo vkInfo;

		vkInfo.name = name;


		vkInfo.subpasses.reserve(subpasses.size());

		for(auto& subpass : subpasses)
			vkInfo.subpasses.emplace_back(subpass.API_Vulkan());


		return vkInfo;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	DX12::PassInfo PassInfo::API_DirectX12() const
	{
		DX12::PassInfo d12Info;

		d12Info.name = name;


		d12Info.subpasses.reserve(subpasses.size());

		for(auto& subpass : subpasses)
			d12Info.subpasses.emplace_back(subpass.API_DirectX12());


		return d12Info;
	}

#endif
}
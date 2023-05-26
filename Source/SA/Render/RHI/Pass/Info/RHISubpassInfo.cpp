// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/Info/RHISubpassInfo.hpp>

namespace SA::RND::RHI
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VK::SubpassInfo SubpassInfo::API_Vulkan() const
	{
		VK::SubpassInfo vkInfo;

		static_cast<SubpassInfoBase&>(vkInfo) = *this;

		vkInfo.sampling = VK::API_GetSampleCount(sampling);


		vkInfo.attachments.reserve(attachments.size());

		for(auto& attach : attachments)
			vkInfo.attachments.emplace_back(attach.API_Vulkan());


		return vkInfo;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	DX12::SubpassInfo SubpassInfo::API_DirectX12() const
	{
		DX12::SubpassInfo d12Info;

		static_cast<SubpassInfoBase&>(d12Info) = *this;

		d12Info.sampling = DX12::API_GetSampleCount(sampling);


		d12Info.attachments.reserve(attachments.size());

		for(auto& attach : attachments)
			d12Info.attachments.emplace_back(attach.API_DirectX12());


		return d12Info;
	}

#endif
}

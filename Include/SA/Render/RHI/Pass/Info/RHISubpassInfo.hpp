// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_SUBPASS_INFO_GUARD
#define SAPPHIRE_RENDER_RHI_SUBPASS_INFO_GUARD

#include <SA/Render/LowLevel/Common/Pass/Info/SubpassInfoBase.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/Pass/Info/VkSubpassInfo.hpp>

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	#include <SA/Render/LowLevel/DX12/Pass/Info/D12SubpassInfo.hpp>

#endif

#include "RHISampling.hpp"
#include "RHIAttachmentInfo.hpp"

namespace SA::RND::RHI
{
	struct SubpassInfo : public SubpassInfoBase<AttachmentInfo>
	{
		// All color attachments must have the same sample count.
		Sampling sampling = Sampling::Sample1Bit;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

		VK::SubpassInfo API_Vulkan() const;

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

		DX12::SubpassInfo API_DirectX12() const;

#endif
	};
}

#endif // SAPPHIRE_RENDER_VK_SUBPASS_INFO_GUARD

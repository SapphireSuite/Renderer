// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_RENDER_PASS_INFO_GUARD
#define SAPPHIRE_RENDER_RHI_RENDER_PASS_INFO_GUARD

#include <SA/Render/LowLevel/Common/Pass/Info/RenderPassInfo.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/Pass/Info/VkRenderPassInfo.hpp>

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <SA/Render/LowLevel/DX12/Pass/Info/D12RenderPassInfo.hpp>

#endif

#include "RHIAttachmentLoadMode.hpp"
#include "RHIAttachmentAccessMode.hpp"

#include <SA/Render/RHI/Common/Texture/RHITexture.hpp>

namespace SA::RND
{
	namespace RHI
	{
		struct AttachmentInfo : public AttachmentInfoBase<Texture>
		{
			AttachmentLoadMode loadMode = AttachmentLoadMode::Clear;
		};

		using SubpassInfo = SA::RND::SubpassInfo<AttachmentInfo>;
		using RenderPassInfo = SA::RND::RenderPassInfo<SubpassInfo>;
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		RenderPassInfo API_GetRenderPassInfo(const RHI::RenderPassInfo& _passInfo);
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		RenderPassInfo API_GetRenderPassInfo(const RHI::RenderPassInfo& _passInfo);
	}

#endif
}

#endif // SAPPHIRE_RENDER_RHI_RENDER_PASS_INFO_GUARD

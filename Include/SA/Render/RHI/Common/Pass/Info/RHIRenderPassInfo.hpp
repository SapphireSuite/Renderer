// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_RENDER_PASS_INFO_GUARD
#define SAPPHIRE_RENDER_RHI_RENDER_PASS_INFO_GUARD

#include <SA/Render/LowLevel/Common/Pass/Info/RenderPassInfo.hpp>

#include <SA/Render/RHI/Common/Texture/RHITexture.hpp>
#include <SA/Render/RHI/Common/Texture/RHITextureDescriptor.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/Pass/Info/VkRenderPassInfo.hpp>

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <SA/Render/LowLevel/DX12/Pass/Info/D12RenderPassInfo.hpp>

#endif

namespace SA::RND
{
	namespace RHI
	{
		using AttachmentInfo = SA::RND::AttachmentInfo<Texture>;
		using SubpassInfo = SA::RND::SubpassInfo<Texture>;
		using RenderPassInfo = SA::RND::RenderPassInfo<Texture, TextureDescriptor>;
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

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_CULLING_MODE_GUARD
#define SAPPHIRE_RENDER_RHI_CULLING_MODE_GUARD

#include <cstdint>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	#include <SA/Render/LowLevel/DX12/DX12API.hpp>

#endif

namespace SA::RND
{
	namespace RHI
	{
		enum class CullingMode : uint8_t
		{
			// No culling.
			None,

			// Front-face culling.
			Front,

			// Back-face culling.
			Back,
		};
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkCullModeFlags API_GetCullingMode(RHI::CullingMode _mode);
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		D3D12_CULL_MODE API_GetCullingMode(RHI::CullingMode _mode);
	}

#endif
}

#endif // SAPPHIRE_RENDER_RHI_CULLING_MODE_GUARD

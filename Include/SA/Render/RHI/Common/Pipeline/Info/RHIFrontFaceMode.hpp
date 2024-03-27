// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_FRONT_FACE_MODE_GUARD
#define SAPPHIRE_RENDER_RHI_FRONT_FACE_MODE_GUARD

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
		enum class FrontFaceMode : uint8_t
		{
			// Clockwise polygon are front-face.
			Clockwise,

			// Counter clockwise polygon are front-face.
			CounterClockwise,
		};	
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkFrontFace API_GetFrontFaceMode(RHI::FrontFaceMode _mode);
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		bool API_GetFrontFaceMode(RHI::FrontFaceMode _mode);
	}

#endif
}

#endif // SAPPHIRE_RENDER_RHI_FRONT_FACE_MODE_GUARD

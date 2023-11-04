// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_RESOURCE_INITIALIZER_GUARD
#define SAPPHIRE_RENDER_RHI_VK_RESOURCE_INITIALIZER_GUARD

#include "RHIResourceInitializer.hpp"

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/VkResourceInitializer.hpp>

namespace SA::RND::RHI
{
	class VkResourceInitializer : public ResourceInitializer
	{
		VK::ResourceInitializer mHandle;

	public:
		void Create(const Device* _device) override final;
		void Destroy(const Device* _device) override final;

		VK::ResourceInitializer& API_Vulkan() override final;
	};
}

#endif

#endif // SAPPHIRE_RENDER_RHI_VK_RESOURCE_INITIALIZER_GUARD

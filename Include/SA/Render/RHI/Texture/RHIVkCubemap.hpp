// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_CUBEMAP_GUARD
#define SAPPHIRE_RENDER_RHI_VK_CUBEMAP_GUARD

#include <SA/Render/RHI/Texture/RHICubemap.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/Texture/VkCubemap.hpp>

namespace SA::RND::RHI
{
	class VkCubemap : public Cubemap
	{
		VK::Cubemap mHandle;

	public:
		void Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawCubemap& _raw) override final;
		void Destroy(const Device* _device) override final;

		const VK::Cubemap& API_Vulkan() const override final;
	};
}

#endif

#endif // SAPPHIRE_RENDER_RHI_VK_CUBEMAP_GUARD

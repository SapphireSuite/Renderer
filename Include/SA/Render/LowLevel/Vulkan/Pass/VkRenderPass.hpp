// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_RENDER_PASS_GUARD
#define SAPPHIRE_RENDER_VK_RENDER_PASS_GUARD

#include "Info/VkPassInfo.hpp"

namespace SA::RND::VK
{
	class Device;

	class RenderPass
	{
		VkRenderPass mHandle = VK_NULL_HANDLE;

	public:
		void Create(const Device& _device, const PassInfo& _info);
		void Create(const Device& _device, const VkRenderPassCreateInfo& _vkInfo);
		void Destroy(const Device& _device);

		operator VkRenderPass() const noexcept;
	};
}

#endif // SAPPHIRE_RENDER_VK_RENDER_PASS_GUARD

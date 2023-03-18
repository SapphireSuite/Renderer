// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_SHADER_GUARD
#define SAPPHIRE_RENDER_VK_SHADER_GUARD

#include "VulkanAPI.hpp"

#include <SA/Render/Wrappers/Base/RawShader.hpp>

namespace SA::VK
{
	class Device;

	class Shader
	{
		VkShaderModule mHandle = VK_NULL_HANDLE;

	public:
		void Create(const Device& _device, const RawShader& _raw);
		void Destroy(const Device& _device);
	};
}

#endif // SAPPHIRE_RENDER_VK_SHADER_GUARD

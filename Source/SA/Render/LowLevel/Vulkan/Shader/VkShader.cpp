// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Shader/VkShader.hpp>

#include <Device/VkDevice.hpp>

namespace SA::RND::VK
{
	void Shader::Create(const Device& _device, const RawShader& _raw)
	{
		VkShaderModuleCreateInfo shaderModuleCreateInfo{};
		shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		shaderModuleCreateInfo.pNext = nullptr;
		shaderModuleCreateInfo.flags = 0u;
		shaderModuleCreateInfo.codeSize = _raw.data.size() * sizeof(decltype(_raw.data)::value_type);
		shaderModuleCreateInfo.pCode = _raw.data.data();

		SA_VK_API(vkCreateShaderModule(_device, &shaderModuleCreateInfo, nullptr, &mHandle));
		
		SA_LOG(L"Shader created", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));
	}

	void Shader::Destroy(const Device& _device)
	{
		SA_LOG_RAII(L"Shader destroyed", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));

		SA_VK_API(vkDestroyShaderModule(_device, mHandle, nullptr));
		mHandle = VK_NULL_HANDLE;
	}
}

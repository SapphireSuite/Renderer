// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/Descriptor/PipelineBindingSetDescriptor.hpp>

namespace SA::RND::RHI
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	std::vector<VkDescriptorSetLayoutBinding> PipelineBindingSetDescriptor::API_Vulkan() const
	{
		std::vector<VkDescriptorSetLayoutBinding> result;

		result.reserve(bindings.size());

		for (auto& binding : bindings)
		{
			auto& outBinding = result.emplace_back();

			outBinding.binding = binding.binding;
			outBinding.descriptorCount = binding.num;
			outBinding.descriptorType = VK::API_GetDescriptorType(binding.type);
			outBinding.stageFlags = VK::API_GetShaderStageFlags((ShaderStage)binding.stageFlags);
		}

		return result;
	}

#endif
}

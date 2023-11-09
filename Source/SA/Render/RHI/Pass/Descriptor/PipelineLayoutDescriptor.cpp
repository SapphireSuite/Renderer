// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/Descriptor/PipelineLayoutDescriptor.hpp>

#include <Shader/Descriptor/ShaderDescriptor.hpp>

namespace SA::RND::RHI
{
	void PipelineLayoutDescriptor::AddShader(const ShaderDescriptor& _desc)
	{
		if (sets.size() < _desc.sets.size())
			sets.resize(_desc.sets.size());

		for (uint32_t i = 0u; i < _desc.sets.size(); ++i)
		{
			for (auto& shBind : _desc.sets[i].bindings)
			{
				PipelineBindingDescriptor* pipBindDesc = nullptr;

				// Search existing binding.
				for (auto& pipBindDescIt : sets[i].bindings)
				{
					if (pipBindDescIt.binding == shBind.binding)
					{
						pipBindDesc = &pipBindDescIt;
						break;
					}
				}

				// Not found: emplace new binding.
				if (!pipBindDesc)
					pipBindDesc = &sets[i].bindings.emplace_back(shBind);

				pipBindDesc->stageFlags |= _desc.stage;
			}
		}
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	std::vector<std::vector<VkDescriptorSetLayoutBinding>> PipelineLayoutDescriptor::API_Vulkan() const
	{
		std::vector<std::vector<VkDescriptorSetLayoutBinding>> result;

		result.reserve(sets.size());

		for (auto& set : sets)
		{
			auto& outSet = result.emplace_back();

			outSet.reserve(set.bindings.size());

			for (auto& binding : set.bindings)
			{
				auto& outBinding = outSet.emplace_back();

				outBinding.binding = binding.binding;
				outBinding.descriptorCount = binding.num;
				outBinding.descriptorType = VK::API_GetDescriptorType(binding.type);
				outBinding.stageFlags = VK::API_GetShaderStageFlags((ShaderStage)binding.stageFlags);
			}
		}

		return result;
	}

#endif
}

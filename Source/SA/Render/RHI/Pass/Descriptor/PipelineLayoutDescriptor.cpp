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
}

// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/RHI/Common/Pass/Info/RHIRenderPassInfo.hpp>

namespace SA::RND::VK
{
	RenderPassInfo API_GetRenderPassInfo(const RHI::RenderPassInfo& _inPassInfo)
	{
		RenderPassInfo vkPassInfo;

		vkPassInfo.name = _inPassInfo.name;

		// Texture to Desc map
		{
			vkPassInfo.textureToDescriptorMap.reserve(_inPassInfo.textureToDescriptorMap.size());

			for (auto it = _inPassInfo.textureToDescriptorMap.begin(); it != _inPassInfo.textureToDescriptorMap.end(); ++it)
				vkPassInfo.textureToDescriptorMap[&it->first->API_Vulkan()] = it->second.API_Vulkan();
		}

		// Subpasses
		{
			vkPassInfo.subpasses.reserve(_inPassInfo.subpasses.size());

			for (auto& inSubpass : _inPassInfo.subpasses)
			{
				auto& vkSubpass = vkPassInfo.subpasses.emplace_back();
				vkSubpass.name = inSubpass.name;

				// Attachments
				{
					vkSubpass.attachments.reserve(inSubpass.attachments.size());

					for (auto& inAttach : inSubpass.attachments)
					{
						auto& vkAttach = vkSubpass.attachments.emplace_back();
						vkAttach.texture = &inAttach.texture->API_Vulkan();
						vkAttach.resolved = inAttach.resolved ? &inAttach.resolved->API_Vulkan() : nullptr;
						vkAttach.loadMode = inAttach.loadMode;
					}
				}

				// Inputs
				{
					vkSubpass.inputs.reserve(inSubpass.inputs.size());

					for (auto& inInput : inSubpass.inputs)
					{
						auto& vkInput = vkSubpass.inputs.emplace_back();
						vkInput = &inInput->API_Vulkan();
					}
				}
			}
		}

		return vkPassInfo;
	}
}

// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/RHI/Common/Pass/Info/RHIRenderPassInfo.hpp>

namespace SA::RND::DX12
{
	RenderPassInfo API_GetRenderPassInfo(const RHI::RenderPassInfo& _inPassInfo)
	{
		RenderPassInfo d12PassInfo;

		d12PassInfo.name = _inPassInfo.name;

		// Texture to Desc map
		{
			d12PassInfo.mTextureToDescriptorMap.reserve(_inPassInfo.mTextureToDescriptorMap.size());

			for (auto it = _inPassInfo.mTextureToDescriptorMap.begin(); it != _inPassInfo.mTextureToDescriptorMap.end(); ++it)
				d12PassInfo.mTextureToDescriptorMap[&it->first->API_DirectX12()] = it->second.API_DirectX12();
		}

		// Subpasses
		{
			d12PassInfo.subpasses.reserve(_inPassInfo.subpasses.size());

			for (auto& inSubpass : _inPassInfo.subpasses)
			{
				auto& d12Subpass = d12PassInfo.subpasses.emplace_back();
				d12Subpass.name = inSubpass.name;

				// Attachments
				{
					d12Subpass.attachments.reserve(inSubpass.attachments.size());

					for (auto& inAttach : inSubpass.attachments)
					{
						auto& d12Attach = d12Subpass.attachments.emplace_back();
						d12Attach.texture = &inAttach.texture->API_DirectX12();
						d12Attach.resolved = inAttach.resolved ? &inAttach.resolved->API_DirectX12() : nullptr;
						d12Attach.loadMode = inAttach.loadMode;
					}
				}

				// Inputs
				{
					d12Subpass.inputs.reserve(inSubpass.inputs.size());

					for (auto& inInput : inSubpass.inputs)
					{
						auto& d12Input = d12Subpass.inputs.emplace_back();
						d12Input = &inInput->API_DirectX12();
					}
				}
			}
		}

		return d12PassInfo;
	}
}

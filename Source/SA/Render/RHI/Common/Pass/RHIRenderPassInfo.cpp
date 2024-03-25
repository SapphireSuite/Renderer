// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <Pass/Info/RHIRenderPassInfo.hpp>

#include <SA/Collections/Debug>

namespace SA::RND::RHI
{
	SubpassInfo& RenderPassInfo::AddSubpass(std::string _name)
	{
		SubpassInfo& subpass = subpasses.emplace_back();

		subpass.name = std::move(_name);

		return subpass;
	}

	bool RenderPassInfo::RemoveSubpass(std::string_view _name)
	{
		for (auto it = subpasses.begin(); it != subpasses.end(); ++it)
		{
			if (it->name == _name)
			{
				subpasses.erase(it);
				return true;
			}
		}

		SA_LOG((L"Subpass with name [%1] not found", _name), Error, SA.Render.RHI);
		return false;
	}


	bool RenderPassInfo::RegisterRenderTarget(Texture* _texture, const TextureDescriptor& _desc)
	{
		auto it = mTextureToDescriptorMap.find(_texture);

		if (it != mTextureToDescriptorMap.end())
		{
			SA_LOG((L"Texture [%1] already registered.", _texture), Error, SA.Render.RHI);
			return false;
		}

		mTextureToDescriptorMap[_texture] = _desc;

		return true;
	}
}

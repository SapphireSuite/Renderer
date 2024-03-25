// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_RENDER_PASS_INFO_GUARD
#define SAPPHIRE_RENDER_COMMON_RENDER_PASS_INFO_GUARD

#include "SubpassInfo.hpp"

namespace SA::RND
{
	template <typename TextureT, typename TextureDescT>
	struct RenderPassInfo
	{
		/// Internal use only: required public for API copy.
		std::unordered_map<const TextureT*, TextureDescT> mTextureToDescriptorMap;

		std::string name;

		std::vector<SubpassInfo<TextureT>> subpasses;

		SubpassInfo<TextureT>& AddSubpass(std::string _name)
		{
			SubpassInfo& subpass = subpasses.emplace_back();

			subpass.name = std::move(_name);

			return subpass;
		}

		bool RemoveSubpass(std::string_view _name)
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


		bool RegisterRenderTarget(const TextureT* _texture, const TextureDescT& _desc)
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
	};
}

#endif // SAPPHIRE_RENDER_COMMON_RENDER_PASS_INFO_GUARD

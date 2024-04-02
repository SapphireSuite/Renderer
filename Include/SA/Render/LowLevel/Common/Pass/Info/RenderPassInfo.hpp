// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_RENDER_PASS_INFO_GUARD
#define SAPPHIRE_RENDER_COMMON_RENDER_PASS_INFO_GUARD

#include "SubpassInfo.hpp"

namespace SA::RND
{
	template <typename SubpassT>
	struct RenderPassInfo
	{
		using TextureT = typename SubpassT::TextureT;
		using TextureDescT = typename SubpassT::TextureT::TextureDescT;

		/**
		* WARN: Internal use only.
		* Use RegisterRenderTarget instead.
		*/
		std::unordered_map<const TextureT*, TextureDescT> textureToDescriptorMap;

		std::string name;

		std::vector<SubpassT> subpasses;

		SubpassT& AddSubpass(std::string _name)
		{
			SubpassT& subpass = subpasses.emplace_back();

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
			auto it = textureToDescriptorMap.find(_texture);

			if (it != textureToDescriptorMap.end())
			{
				SA_LOG((L"Texture [%1] already registered.", _texture), Error, SA.Render.RHI);
				return false;
			}

			textureToDescriptorMap[_texture] = _desc;

			return true;
		}
	};
}

#endif // SAPPHIRE_RENDER_COMMON_RENDER_PASS_INFO_GUARD

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_RENDER_PASS_INFO_GUARD
#define SAPPHIRE_RENDER_COMMON_RENDER_PASS_INFO_GUARD

#include "SubpassInfo.hpp"

namespace SA::RND
{
	template <typename TextureT>
	struct RenderPassInfo
	{
		std::string name;

		std::vector<SubpassInfo<TextureT>> subpasses;


		SubpassInfo<TextureT>& AddSubpass(std::string _name)
		{
			SubpassInfo<TextureT>& subpass = subpasses.emplace_back();

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

			return false;
		}
	};
}

#endif // SAPPHIRE_RENDER_COMMON_RENDER_PASS_INFO_GUARD

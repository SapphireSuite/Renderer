// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_PASS_INFO_BASE_GUARD
#define SAPPHIRE_RENDER_PASS_INFO_BASE_GUARD

#include <string>
#include <vector>

namespace SA::RND
{
	template <typename SubpassT>
	struct PassInfoBase
	{
		std::string name;

		std::vector<SubpassT> subpasses;

		SubpassT& AddSubpass(std::string _name)
		{
			SubpassT& subpass = subpasses.emplace_back();

			subpass.name = std::move(_name);

			return subpass;
		}

		bool RemoveSubpass(std::string _name)
		{
			for(auto it = subpasses.begin(); it != subpasses.end(); ++it)
			{
				if(it->name == _name)
				{
					subpasses.erase(it);
					return true;
				}
			}

			return false;
		}
	};
}

#endif // SAPPHIRE_RENDER_PASS_INFO_BASE_GUARD

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_PASS_INFO_BASE_GUARD
#define SAPPHIRE_RENDER_PASS_INFO_BASE_GUARD

#include <string>
#include <vector>

#include <SA/Collections/Debug>

#include "AttachmentUsage.hpp"

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

		bool RemoveSubpass(std::string_view _name)
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
	
		auto& FindAttachment(std::string_view _attachName, std::string_view _subpassName = "")
		{
			for(auto& subpass : subpasses)
			{
				if(_subpassName.empty() || subpass.name == _subpassName)
				{
					for(auto& attach : subpass.attachments)
					{
						if(attach.name == _attachName)
							return attach;
					}
				}
			}

			SA_LOG((L"No attachment named [%1::%2] found!", _subpassName.data(), _attachName.data()), Error, SA.Render.Common);
		}

		auto& FindPresentAttachment()
		{
			for(auto& attach : subpasses.back().attachments)
			{
				if(attach.usage == AttachmentUsage::Present)
					return attach;
			}

			SA_LOG(L"No present attachment found!", Error, SA.Render.Common);

			return subpasses.back().attachments.back();
		}
	};
}

#endif // SAPPHIRE_RENDER_PASS_INFO_BASE_GUARD

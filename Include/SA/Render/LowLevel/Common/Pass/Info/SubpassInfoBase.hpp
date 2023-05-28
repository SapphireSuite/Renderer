// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SUBPASS_INFO_BASE_GUARD
#define SAPPHIRE_RENDER_SUBPASS_INFO_BASE_GUARD

#include <string>
#include <vector>

#include <SA/Maths/Space/Vector2.hpp>

namespace SA::RND
{
	template <typename AttachT>
	struct SubpassInfoBase
	{
		std::string name;

		std::vector<AttachT> attachments;

		AttachT& AddAttachment(std::string _name)
		{
			AttachT& attach = attachments.emplace_back();

			attach.name = std::move(_name);

			return attach;
		}

		bool RemoveAttachment(std::string_view _name)
		{
			for(auto it = attachments.begin(); it != attachments.end(); ++it)
			{
				if(it->name == _name)
				{
					attachments.erase(it);
					return true;
				}
			}

			return false;
		}

		AttachT& FindAttachment(std::string_view _name)
		{
			for(auto it = attachments.begin(); it != attachments.end(); ++it)
			{
				if(it->name == _name)
					return *it;
			}

			SA_LOG((L"No attachment named [%1] found!", _name.data()), Error, SA.Render.Common);

			return attachments[0];
		}

		void SetAllAttachmentExtents(const Vec2ui& _extents)
		{
			for(auto& attach : attachments)
				attach.extents = _extents;
		}
	};
}

#endif // SAPPHIRE_RENDER_SUBPASS_INFO_BASE_GUARD
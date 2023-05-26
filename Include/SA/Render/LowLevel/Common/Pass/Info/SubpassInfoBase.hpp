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

		void SetAllAttachmentExtents(const Vec2ui& _extents)
		{
			for(auto& attach : attachments)
				attach.extents = _extents;
		}
	};
}

#endif // SAPPHIRE_RENDER_SUBPASS_INFO_BASE_GUARD

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/VkFrameBufferInfo.hpp>

namespace SA::RND::VK
{
	void FrameBufferInfo::SetAllAttachmentsExtents(const Vec2ui& _extents)
	{
		for(auto& image : imageInfos)
			image.extents = _extents;
	}
}

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_FRAME_BUFFER_INFO_GUARD
#define SAPPHIRE_RENDER_RHI_FRAME_BUFFER_INFO_GUARD

#include <vector>

#include "RHIFrameBufferAttachmentInfo.hpp"

namespace SA::RND::RHI
{
	class Pass;
	struct PassInfo;

	struct FrameBufferInfo
	{
		const Pass* pass = nullptr;

		std::vector<FrameBufferAttachmentInfo> attachments;

		void InitFromPass(const Pass* _pass, const PassInfo& _info);

		void SetAllAttachmentsExtents(const Vec2ui& _extents);

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

		VK::FrameBufferInfo API_Vulkan() const;

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL
	};
}

#endif // SAPPHIRE_RENDER_RHI_FRAME_BUFFER_INFO_GUARD

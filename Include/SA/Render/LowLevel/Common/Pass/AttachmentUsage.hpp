// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ATTACHMENT_USAGE_GUARD
#define SAPPHIRE_RENDER_ATTACHMENT_USAGE_GUARD

namespace SA::RND
{
	enum class AttachmentUsage
	{
		None,

		// Will be used as input attachment in next subpass.
		InputNext,

		// Will be used as output (swapchain) image to present.
		Present
	};
}

#endif // SAPPHIRE_RENDER_ATTACHMENT_USAGE_GUARD

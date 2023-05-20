// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_ATTACHMENT_TYPE_GUARD
#define SAPPHIRE_RENDER_RHI_ATTACHMENT_TYPE_GUARD

namespace SA::RND::RHI
{
	enum class AttachmentType
	{
		Unknown = 0,

		Color,

		Depth,
	};
}

#endif // SAPPHIRE_RENDER_RHI_ATTACHMENT_TYPE_GUARD

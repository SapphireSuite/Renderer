// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ATTACHMENT_TYPE_GUARD
#define SAPPHIRE_RENDER_ATTACHMENT_TYPE_GUARD

namespace SA::RND
{
	enum class AttachmentType
	{
		Unknown = 0,

		Color,

		Depth,
	};
}

#endif // SAPPHIRE_RENDER_ATTACHMENT_TYPE_GUARD
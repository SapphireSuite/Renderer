// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_ATTACHMENT_ACCESS_MODE_GUARD
#define SAPPHIRE_RENDER_COMMON_ATTACHMENT_ACCESS_MODE_GUARD

#include <cstdint>

namespace SA::RND
{
	enum class AttachmentAccessMode : uint8_t
	{
		None = 0,

		ReadOnly = 1,

		ReadWrite = 2,
	};
}

#endif // SAPPHIRE_RENDER_COMMON_ATTACHMENT_ACCESS_MODE_GUARD
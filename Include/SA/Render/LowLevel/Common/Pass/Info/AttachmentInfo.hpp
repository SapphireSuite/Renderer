// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_ATTACHMENT_PASS_INFO_GUARD
#define SAPPHIRE_RENDER_COMMON_ATTACHMENT_PASS_INFO_GUARD

#include "AttachmentLoadMode.hpp"

namespace SA::RND
{
	template <typename TextureT>
	struct AttachmentInfo
	{
		const TextureT* texture = nullptr;
		const TextureT* resolved = nullptr;

		AttachmentLoadMode loadMode = AttachmentLoadMode::Clear;
	};
}

#endif // SAPPHIRE_RENDER_COMMON_ATTACHMENT_PASS_INFO_GUARD

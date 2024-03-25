// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_ATTACHMENT_PASS_INFO_BASE_GUARD
#define SAPPHIRE_RENDER_COMMON_ATTACHMENT_PASS_INFO_BASE_GUARD

namespace SA::RND
{
	template <typename TextureT>
	struct AttachmentInfoBase
	{
		using TextureT = TextureT;

		const TextureT* texture = nullptr;
		const TextureT* resolved = nullptr;
	};
}

#endif // SAPPHIRE_RENDER_COMMON_ATTACHMENT_PASS_INFO_BASE_GUARD

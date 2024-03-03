// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_ATTACHMENT_INFO_GUARD
#define SAPPHIRE_RENDER_COMMON_ATTACHMENT_INFO_GUARD

#include <string>

#include <SA/Render/LowLevel/Common/Misc/Color.hpp>

namespace SA::RND
{
	template <typename TextureT>
	struct AttachmentInfo
	{
		std::string name;

		Color clearColor = Color{ 0.0f, 0.0f, 0.015f, 0.0f };

		TextureT* texture = nullptr;
	};
}

#endif // SAPPHIRE_RENDER_COMMON_ATTACHMENT_INFO_GUARD

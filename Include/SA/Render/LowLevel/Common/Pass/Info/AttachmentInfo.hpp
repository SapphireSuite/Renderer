// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_ATTACHMENT_INFO_GUARD
#define SAPPHIRE_RENDER_COMMON_ATTACHMENT_INFO_GUARD

#include <string>

#include "AttachmentLoadMode.hpp"

#include <SA/Render/LowLevel/Common/Misc/Color.hpp>

namespace SA::RND
{
	template <typename TextureT>
	struct AttachmentInfo
	{
		std::string name;

		TextureT* texture = nullptr;
		TextureT* resolved = nullptr;

		Color clearColor = Color{ 0.0f, 0.0f, 0.015f, 0.0f };

		AttachmentLoadMode loadMode = AttachmentLoadMode::Clear;
	};
}

#endif // SAPPHIRE_RENDER_COMMON_ATTACHMENT_INFO_GUARD

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ATTACHMENT_INFO_BASE_GUARD
#define SAPPHIRE_RENDER_ATTACHMENT_INFO_BASE_GUARD

#include <string>

#include <SA/Render/LowLevel/Common/Misc/Color.hpp>

#include <SA/Maths/Space/Vector2.hpp>

#include "AttachmentType.hpp"
#include "AttachmentUsage.hpp"

namespace SA::RND
{
	struct AttachmentInfoBase
	{
		std::string name;

		Color clearColor = Color{ 0.0f, 0.0f, 0.015f, 0.0f };

		AttachmentType type = AttachmentType::Color;

		AttachmentUsage usage = AttachmentUsage::InputNext;

		/**
		 * @brief Extents used for framebuffer creation only.
		 * API RenderPass implementation does not need this value.
		 */
		Vec2ui extents;
	};
}

#endif // SAPPHIRE_RENDER_ATTACHMENT_INFO_BASE_GUARD

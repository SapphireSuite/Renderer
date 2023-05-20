// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_ATTACHMENT_INFO_GUARD
#define SAPPHIRE_RENDER_RHI_ATTACHMENT_INFO_GUARD

#include <SA/Render/LowLevel/Common/Misc/Color.hpp>

#include <SA/Render/RHI/Misc/Format.hpp>

#include "AttachmentType.hpp"
#include "AttachmentUsage.hpp"
#include "AttachmentLoadMode.hpp"

namespace SA::RND::RHI
{
	struct AttachmentInfo
	{
		Format format = Format::R8G8B8A8_UNORM;

		Color clearColor = Color{ 0.0f, 0.0f, 0.05f, 0.0f };

		AttachmentType type = AttachmentType::Color;

		AttachmentUsage usage = AttachmentUsage::InputNext;

		AttachmentLoadMode loadMode = AttachmentLoadMode::Clear;
	};
}

#endif // SAPPHIRE_RENDER_RHI_ATTACHMENT_INFO_GUARD

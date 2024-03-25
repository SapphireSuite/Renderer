// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RHI_ATTACHMENT_PASS_INFO_GUARD
#define SAPPHIRE_RHI_ATTACHMENT_PASS_INFO_GUARD

#include "RHIAttachmentLoadMode.hpp"

#include <SA/Render/RHI/Common/Texture/RHITexture.hpp>

namespace SA::RND::RHI
{
	struct AttachmentInfo
	{
		Texture* texture = nullptr;
		Texture* resolved = nullptr;

		AttachmentLoadMode loadMode = AttachmentLoadMode::Clear;
	};
}

#endif // SAPPHIRE_RHI_ATTACHMENT_PASS_INFO_GUARD

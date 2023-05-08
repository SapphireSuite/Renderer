// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_SUB_PASS_ATTACHMENT_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_RHI_SUB_PASS_ATTACHMENT_DESCRIPTOR_GUARD

#include <SA/Render/LowLevel/Common/Misc/Color.hpp>

#include <SA/Render/RHI/Misc/Format.hpp>

#include "SubPassAttachmentLoadMode.hpp"

namespace SA::RND
{
	namespace RHI
	{
		struct SubPassAttachmentDescriptor
		{
			Format format;

			// Used as input attachment in next subpass.
			bool bInputNext = false;

			SubPassAttachmentLoadMode loadMode = SubPassAttachmentLoadMode::Clear;
			
			Color clearColor = Color{ 0.0f, 0.0f, 0.05f, 0.0f };
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_SUB_PASS_ATTACHMENT_DESCRIPTOR_GUARD

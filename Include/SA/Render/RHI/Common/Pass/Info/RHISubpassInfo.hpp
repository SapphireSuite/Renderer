// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RHI_SUBPASS_PASS_INFO_GUARD
#define SAPPHIRE_RHI_SUBPASS_PASS_INFO_GUARD

#include <vector>

#include "RHIAttachmentInfo.hpp"

namespace SA::RND::RHI
{
	struct SubpassInfo
	{
		std::string name;

	//{ Attachments
	
		std::vector<AttachmentInfo> attachments;

		AttachmentInfo& AddAttachment(RenderTarget* _texture, RenderTarget* _resolvedTexture = nullptr);

	//}


	//{ Input Attachments

		/// Render target from previous subpasses to use as input.
		std::vector<RenderTarget*> inputs;

		void AddInputAttachments(const std::vector<RenderTarget*>& _inputs);
		bool RemoveInputAttachment(RenderTarget* _input);

	//}
	};
}

#endif // SAPPHIRE_RHI_SUBPASS_PASS_INFO_GUARD

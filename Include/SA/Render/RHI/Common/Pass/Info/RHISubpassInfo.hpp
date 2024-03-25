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

		AttachmentInfo& AddAttachment(Texture* _texture, Texture* _resolvedTexture = nullptr);

	//}


	//{ Input Attachments

		/// Render target from previous subpasses to use as input.
		std::vector<Texture*> inputs;

		void AddInputAttachments(const std::vector<Texture*>& _inputs);
		bool RemoveInputAttachment(Texture* _input);

	//}
	};
}

#endif // SAPPHIRE_RHI_SUBPASS_PASS_INFO_GUARD

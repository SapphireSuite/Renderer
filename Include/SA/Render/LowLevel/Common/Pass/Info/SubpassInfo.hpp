// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_SUBPASS_PASS_INFO_GUARD
#define SAPPHIRE_RENDER_COMMON_SUBPASS_PASS_INFO_GUARD

#include <vector>

#include <SA/Collections/Debug>

#include "AttachmentInfoBase.hpp"

namespace SA::RND
{
	template <typename AttachT>
	struct SubpassInfo
	{
		using TextureT = AttachT::TextureT;

		std::string name;

	//{ Attachments
	
		std::vector<AttachT> attachments;

		AttachT& AddAttachment(const TextureT* _texture, const TextureT* _resolvedTexture = nullptr)
		{
			SA_ASSERT((Nullptr, _texture), SA.Render.RHI, L"Valid RenderTarget must be bound as subpass attachment");

			AttachT& attach = attachments.emplace_back();

			attach.texture = _texture;
			attach.resolved = _resolvedTexture;

			return attach;
		}

	//}


	//{ Input Attachments

		/// Render target from previous subpasses to use as input.
		std::vector<const TextureT*> inputs;

		void AddInputAttachments(const std::vector<const TextureT*>& _inputs)
		{
			inputs.insert(inputs.end(), _inputs.begin(), _inputs.end());
		}

		bool RemoveInputAttachment(const TextureT* _input)
		{
			for (auto inputIt = inputs.begin(); inputIt != inputs.end(); ++inputIt)
			{
				if (*inputIt == _input)
				{
					inputs.erase(inputIt);
					return true;
				}
			}

			SA_LOG((L"Input Attachment [%1] not found", _input), Error, SA.Render.RHI);
			return false;
		}

	//}
	};
}

#endif // SAPPHIRE_RENDER_COMMON_SUBPASS_PASS_INFO_GUARD

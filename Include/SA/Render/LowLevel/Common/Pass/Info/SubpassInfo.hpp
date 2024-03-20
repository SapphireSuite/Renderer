// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_SUBPASS_INFO_GUARD
#define SAPPHIRE_RENDER_COMMON_SUBPASS_INFO_GUARD

#include <vector>

#include <SA/Collections/Debug>

#include "AttachmentInfo.hpp"

namespace SA::RND
{
	template <typename TextureT>
	struct SubpassInfo
	{
		std::string name;

	//{ Attachments

		std::vector<AttachmentInfo<TextureT>> attachments;


		AttachmentInfo<TextureT>& AddAttachment(std::string _name, TextureT* _texture, TextureT* _resolvedTexture = nullptr)
		{
			AttachmentInfo<TextureT>& attach = attachments.emplace_back();

			attach.name = std::move(_name);
			attach.texture = _texture;
			attach.resolved = _resolvedTexture;

			return attach;
		}

		bool RemoveAttachment(std::string_view _name)
		{
			for (auto it = attachments.begin(); it != attachments.end(); ++it)
			{
				if (it->name == _name)
				{
					attachments.erase(it);
					return true;
				}
			}

			return false;
		}

		AttachmentInfo<TextureT>& FindAttachment(std::string_view _name)
		{
			for (auto it = attachments.begin(); it != attachments.end(); ++it)
			{
				if (it->name == _name)
					return *it;
			}

			SA_LOG((L"No attachment named [%1] found!", _name.data()), Error, SA.Render.Common);

			return attachments[0];
		}

	//}


	//{ Input Attachments

		/// Textures to use as input attachments.
		std::vector<TextureT*> inputs;

		void AddInputAttachments(const std::vector<TextureT*>& _inputs)
		{
			inputs.insert(inputs.end(), _inputs.begin(), _inputs.end());
		}

		void RemoveInputAttachment(TextureT* _input)
		{
			for (auto inputIt = inputs.begin(); inputIt != inputs.end(); ++inputIt)
			{
				if (*inputIt == _input)
				{
					inputs.erase(inputIt);
					return;
				}
			}

			SA_LOG((L"Input Attachment [%1] not found", _input), Error, SA.Render.Common);
		}
	//}
	};
}

#endif // SAPPHIRE_RENDER_COMMON_SUBPASS_INFO_GUARD

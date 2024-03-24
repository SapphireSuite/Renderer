// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <Pass/Info/RHISubpassInfo.hpp>

#include <SA/Collections/Debug>

namespace SA::RND::RHI
{
	AttachmentInfo& SubpassInfo::AddAttachment(RenderTarget* _texture, RenderTarget* _resolvedTexture)
	{
		SA_ASSERT((Nullptr, _texture), SA.Render.RHI, L"Valid RenderTarget must be bound as subpass attachment");

		AttachmentInfo& attach = attachments.emplace_back();

		attach.texture = _texture;
		attach.resolved = _resolvedTexture;

		return attach;
	}


//{ Input Attachments

	void SubpassInfo::AddInputAttachments(const std::vector<RenderTarget*>& _inputs)
	{
		inputs.insert(inputs.end(), _inputs.begin(), _inputs.end());
	}
	
	bool SubpassInfo::RemoveInputAttachment(RenderTarget* _input)
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
}

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_ATTACHMENT_INFO_GUARD
#define SAPPHIRE_RENDER_DX12_ATTACHMENT_INFO_GUARD

#include <SA/Render/LowLevel/Common/Pass/Info/AttachmentInfoBase.hpp>

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

namespace SA::RND::DX12
{
	struct AttachmentInfo : public AttachmentInfoBase
	{
		DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

		/// Whether to clear on attachment loading.
		bool bClearOnLoad = true;
	};
}

#endif // SAPPHIRE_RENDER_DX12_ATTACHMENT_INFO_GUARD

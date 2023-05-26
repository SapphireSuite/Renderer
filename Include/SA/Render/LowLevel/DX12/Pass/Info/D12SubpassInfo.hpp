// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_SUBPASS_INFO_GUARD
#define SAPPHIRE_RENDER_DX12_SUBPASS_INFO_GUARD

#include <SA/Render/LowLevel/Common/Pass/Info/SubpassInfoBase.hpp>

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

#include "D12AttachmentInfo.hpp"

namespace SA::RND::DX12
{
	struct SubpassInfo : public SubpassInfoBase
	{
		// All color attachments must have the same sample count.
		uint32_t sampling = 1;

		std::vector<AttachmentInfo> attachments;
	};
}

#endif // SAPPHIRE_RENDER_DX12_SUBPASS_INFO_GUARD

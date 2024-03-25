// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_D12_RENDER_PASS_INFO_GUARD
#define SAPPHIRE_RENDER_D12_RENDER_PASS_INFO_GUARD

#include <SA/Render/LowLevel/Common/Pass/Info/RenderPassInfo.hpp>

#include <SA/Render/LowLevel/DX12/Texture/D12Texture.hpp>

namespace SA::RND::DX12
{
	struct AttachmentInfo : public AttachmentInfoBase<Texture>
	{
		bool bClear = true;
	};

	using SubpassInfo = SA::RND::SubpassInfo<AttachmentInfo>;
	using RenderPassInfo = SA::RND::RenderPassInfo<SubpassInfo>;
}

#endif // SAPPHIRE_RENDER_D12_RENDER_PASS_INFO_GUARD

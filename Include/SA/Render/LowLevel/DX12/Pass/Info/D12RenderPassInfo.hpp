// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_D12_RENDER_PASS_INFO_GUARD
#define SAPPHIRE_RENDER_D12_RENDER_PASS_INFO_GUARD

#include <SA/Render/LowLevel/Common/Pass/Info/RenderPassInfo.hpp>

#include <SA/Render/LowLevel/DX12/Texture/D12Texture.hpp>
#include <SA/Render/LowLevel/DX12/Texture/D12TextureDescriptor.hpp>

namespace SA::RND::DX12
{
	using AttachmentInfo = SA::RND::AttachmentInfo<Texture>;
	using SubpassInfo = SA::RND::SubpassInfo<Texture>;
	using RenderPassInfo = SA::RND::RenderPassInfo<Texture, TextureDescriptor>;
}

#endif // SAPPHIRE_RENDER_D12_RENDER_PASS_INFO_GUARD

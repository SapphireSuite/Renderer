// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_RENDER_PASS_INFO_GUARD
#define SAPPHIRE_RENDER_DX12_RENDER_PASS_INFO_GUARD

#include <SA/Render/LowLevel/Common/Pass/Info/RenderPassInfo.hpp>

#include <SA/Render/LowLevel/DX12/Texture/D12Texture.hpp>

namespace SA::RND::DX12
{
	using RenderPassInfo = SA::RND::RenderPassInfo<Texture>;
}

#endif // SAPPHIRE_RENDER_D12_RENDER_PASS_INFO_GUARD

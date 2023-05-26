// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_PASS_INFO_GUARD
#define SAPPHIRE_RENDER_DX12_PASS_INFO_GUARD

#include <SA/Render/LowLevel/Common/Pass/Info/PassInfoBase.hpp>

#include "D12SubpassInfo.hpp"

namespace SA::RND::DX12
{
	struct PassInfo : public PassInfoBase<SubpassInfo>
	{
	};
}

#endif // SAPPHIRE_RENDER_DX12_PASS_INFO_GUARD

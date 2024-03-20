// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/RHI/Misc/RHISampling.hpp>

namespace SA::RND::DX12
{
	uint32_t API_GetSampling(RHI::Sampling _sampling)
	{
		return static_cast<uint32_t>(_sampling);
	}
}

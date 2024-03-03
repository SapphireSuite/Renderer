// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/LowLevel/Common/Misc/Sampling.hpp>

namespace SA::RND::DX12
{
	uint32_t API_GetSampling(Sampling _sampling)
	{
		return static_cast<uint32_t>(_sampling);
	}
}

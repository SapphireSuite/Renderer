// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/LowLevel/Common/Misc/Sampling.hpp>

namespace SA::RND::VK
{
	VkSampleCountFlagBits API_GetSampling(Sampling _sampling)
	{
		return static_cast<VkSampleCountFlagBits>(_sampling);
	}
}

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/RHI/Common/Misc/RHISampling.hpp>

namespace SA::RND::VK
{
	VkSampleCountFlagBits API_GetSampling(RHI::Sampling _sampling)
	{
		return static_cast<VkSampleCountFlagBits>(_sampling);
	}
}

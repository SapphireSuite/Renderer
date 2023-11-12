// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <DescriptorSet/VkDescriptorSet.hpp>

namespace SA::RND::VK
{
	DescriptorSet::operator VkDescriptorSet() const noexcept
	{
		return mHandle;
	}
}

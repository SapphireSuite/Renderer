// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Context/RHIVkContext.hpp>

#include <Pass/RHIVkPass.hpp>

namespace SA::RND::RHI
{
	Pass* VkContext::InstantiatePassClass()
	{
		return new VkPass();
	}
}

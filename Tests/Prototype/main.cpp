// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/LowLevel/Vulkan/VkInstance.hpp>

int main()
{
	SA::Debug::InitDefaultLogger();

	SA::VK::Instance instance;

	instance.Create();

	instance.Destroy();

	return 0;
}

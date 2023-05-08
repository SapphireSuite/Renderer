// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Queue/VkQueueRequirements.hpp>

namespace SA::RND::VK
{
	QueueRequirements QueueRequirements::GraphicsOnly{ 1, 0, 0, 0 };
	QueueRequirements QueueRequirements::GraphicsCompute{ 1 , 1, 0, 0 };
	QueueRequirements QueueRequirements::GraphicsPresent{ 1, 0, 0, 1 };
	QueueRequirements QueueRequirements::GraphicsComputePresent{ 1, 1, 0, 1 };
	QueueRequirements QueueRequirements::GraphicsComputePresentTransfer{ 1, 1, 1, 1 };

	bool QueueRequirements::IsEmpty() const noexcept
	{
		return graphicsNum == 0 &&
			computeNum == 0 &&
			transferNum == 0 &&
			presentNum == 0;
	}

	int QueueRequirements::GetCompletedCode() const noexcept
	{
		return IsEmpty() ? 1 : (bStrictRequirement ? -1 : 0);
	}
}

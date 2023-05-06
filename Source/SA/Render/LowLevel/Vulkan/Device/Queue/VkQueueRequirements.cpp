// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/Queue/VkQueueRequirements.hpp>

namespace SA::VK
{
	QueueRequirements QueueRequirements::GraphicOnly{ 1, 0, 0, 0 };
	QueueRequirements QueueRequirements::GraphicCompute{ 1 , 1, 0, 0 };
	QueueRequirements QueueRequirements::GraphicPresent{ 1, 0, 0, 1 };
	QueueRequirements QueueRequirements::GraphicComputePresent{ 1, 1, 0, 1 };
	QueueRequirements QueueRequirements::GraphicComputePresentTransfer{ 1, 1, 1, 1 };

	bool QueueRequirements::IsEmpty() const noexcept
	{
		return graphicNum == 0 &&
			computeNum == 0 &&
			transferNum == 0 &&
			presentNum == 0;
	}

	int QueueRequirements::GetCompletedCode() const noexcept
	{
		return IsEmpty() ? 1 : (bStrictRequirement ? -1 : 0);
	}
}

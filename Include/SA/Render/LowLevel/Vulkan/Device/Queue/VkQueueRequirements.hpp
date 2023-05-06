// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_QUEUE_REQUIREMENTS_GUARD
#define SAPPHIRE_RENDER_VK_QUEUE_REQUIREMENTS_GUARD

#include <cstdint>

namespace SA::VK
{
	struct QueueRequirements
	{
		/// Number of graphics queues required.
		uint32_t graphicsNum = 1;
		
		/// Number of compute queues required.
		uint32_t computeNum = 1;
		
		/// Number of transfer queues required.
		uint32_t transferNum = 1;
		
		/// Number of present queues required.
		uint32_t presentNum = 0;

		/**
		 * Device must provide exact number of requested queues.
		 * Device will be considerated not suitable otherwise.
		*/
		bool bStrictRequirement = false;

		static QueueRequirements GraphicsOnly;
		static QueueRequirements GraphicsCompute;
		static QueueRequirements GraphicsPresent;
		static QueueRequirements GraphicsComputePresent;
		static QueueRequirements GraphicsComputePresentTransfer;

		bool IsEmpty() const noexcept;
		int GetCompletedCode() const noexcept;
	};
}

#endif // SAPPHIRE_RENDER_VK_QUEUE_REQUIREMENTS_GUARD

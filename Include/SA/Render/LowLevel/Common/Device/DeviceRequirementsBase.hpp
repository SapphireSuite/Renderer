// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DEVICE_REQUIREMENTS_BASE_GUARD
#define SAPPHIRE_RENDER_DEVICE_REQUIREMENTS_BASE_GUARD

#include "QueueRequirements.hpp"

namespace SA::RND
{
	struct DeviceRequirementsBase
	{
		QueueRequirements queue;
	};
}

#endif // SAPPHIRE_RENDER_DEVICE_REQUIREMENTS_BASE_GUARD

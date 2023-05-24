// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DEVICE_REQUIREMENTS_GUARD
#define SAPPHIRE_RENDER_DEVICE_REQUIREMENTS_GUARD

#include "QueueRequirements.hpp"

namespace SA::RND
{
	struct DeviceRequirements
	{
		QueueRequirements queue;
	};
}

#endif // SAPPHIRE_RENDER_DEVICE_REQUIREMENTS_GUARD

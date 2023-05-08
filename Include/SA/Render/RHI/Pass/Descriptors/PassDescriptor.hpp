// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_PASS_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_RHI_PASS_DESCRIPTOR_GUARD

#include "SubPassDescriptor.hpp"

namespace SA::RND
{
	namespace RHI
	{
		struct PassDescriptor
		{
			std::vector<SubPassDescriptor> subPassDescs;
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_PASS_DESCRIPTOR_GUARD

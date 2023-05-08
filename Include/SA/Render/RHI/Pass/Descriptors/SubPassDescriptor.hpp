// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_SUB_PASS_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_RHI_SUB_PASS_DESCRIPTOR_GUARD

#include "SampleBits.hpp"
#include "SubPassAttachmentDescriptor.hpp"

namespace SA::RND
{
	namespace RHI
	{
		struct SubPassDescriptor
		{
			// All color attachment must have the same sample count.
			SampleBits sampling = SampleBits::Sample1Bit;

			std::vector<SubPassAttachmentDescriptor> attachmentDescs;
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_SUB_PASS_DESCRIPTOR_GUARD

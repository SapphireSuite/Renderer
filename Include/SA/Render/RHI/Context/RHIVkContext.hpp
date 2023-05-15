// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_CONTEXT_GUARD
#define SAPPHIRE_RENDER_RHI_VK_CONTEXT_GUARD

#include "RHIContext.hpp"

namespace SA::RND::RHI
{
	class VkContext : public Context
	{
	protected:
		Pass* InstantiatePassClass() override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_VK_CONTEXT_GUARD

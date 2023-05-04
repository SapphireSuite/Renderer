// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VULKAN_DEBUG_GUARD
#define SAPPHIRE_RENDER_VULKAN_DEBUG_GUARD

#include <SA/Collections/Debug>

#include "Exception_Vulkan.hpp"

#define SA_VK_VALIDATION_LAYERS (SA_DEBUG || SA_RENDER_VALIDATION_LAYER_RELEASE)

#endif // SAPPHIRE_RENDER_VULKAN_DEBUG_GUARD

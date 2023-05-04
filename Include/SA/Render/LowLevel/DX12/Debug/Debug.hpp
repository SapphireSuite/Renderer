// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_DEBUG_GUARD
#define SAPPHIRE_RENDER_DX12_DEBUG_GUARD

#include <SA/Collections/Debug>

#include "Exception_DX12.hpp"
#include "SetDebugName.hpp"

#define SA_DX12_VALIDATION_LAYERS (SA_DEBUG || SA_RENDER_VALIDATION_LAYER_RELEASE)

#endif // SAPPHIRE_RENDER_DX12_DEBUG_GUARD

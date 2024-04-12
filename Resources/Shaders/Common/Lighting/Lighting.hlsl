// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_LIGHTING_GUARD
#define SAPPHIRE_RENDER_SHADER_LIGHTING_GUARD

#include "DirectionalLight.hlsl"
#include "PointLight.hlsl"
#include "SpotLight.hlsl"

#define SA_LIT_IMPLEMENTATION (SA_DIRECTIONAL_LIGHTS || SA_POINT_LIGHTS || SA_SPOT_LIGHTS)

#endif // SAPPHIRE_RENDER_SHADER_LIGHTING_GUARD

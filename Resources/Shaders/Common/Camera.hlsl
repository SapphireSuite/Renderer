// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_CAMERA_GUARD
#define SAPPHIRE_RENDER_SHADER_CAMERA_GUARD

#include "Preprocessors.hlsl"

cbuffer Camera : SA_REG(b, SA_CAMERA_BUFFER_ID)
{
	/// Camera inverse transformation matrix.
	float4x4 inverseView;

	/// Camera projection matrix.
	float4x4 projection;

    /// Camera raw position.
	float3 position;
};

float4x4 ComputeInvViewProj()
{
	return mul(Camera.projection, Camera.inverseView);
}

float4 ComputeViewPosition(float3 _modelPosition)
{
	return mul(ComputeInvViewProj(), float4(_modelPosition, 1.0));
}

#endif // SAPPHIRE_RENDER_SHADER_CAMERA_GUARD

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_CAMERA_GUARD
#define SAPPHIRE_RENDER_SHADER_CAMERA_GUARD

#include "Frame.hlsl"

namespace SA
{
	struct Camera
	{
		// proj * inverseView matrix.
		float4x4 invViewProj;

		// Camera raw position.
		float3 position;
	};

	ConstantBuffer<Camera> cameras : SA_REG(b, SA_CAMERA_ID);

	Camera GetCamera()
	{
		return cameras[frame.cameraIndex];
	}

	float4 ComputeObjectViewPosition(float4 _objPosition)
	{
		return GetCamera().invViewProj * _objPosition;
	}

	float3 GetCameraViewPosition()
	{
		return GetCamera().position;
	}
}

#endif // SAPPHIRE_RENDER_SHADER_CAMERA_GUARD

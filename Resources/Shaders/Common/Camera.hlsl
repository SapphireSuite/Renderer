// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_CAMERA_GUARD
#define SAPPHIRE_RENDER_SHADER_CAMERA_GUARD

#include "Preprocessors.hlsl"

#ifdef SA_CAMERA_BUFFER_ID

#define SA_CAMERA_BUFFER 1

namespace SA
{
	/**
	*	Must match `CameraUBO` struct in `CameraUBO.hpp`
	*/
	struct Camera
	{
		/// Camera inverse transformation matrix.
		//float4x4 inverseView;

		/// Camera projection matrix.
		//float4x4 projection;

		/**
		*	Camera inverse view projection matrix.
		*	projection * inverseView.
		*/
		float4x4 invViewProj;

		/// Camera raw position.
		float3 position;

		float padding;
	};

	cbuffer CameraBuffer : SA_REG_SPACE(b, SA_CAMERA_BUFFER_ID, 0)
	{
		Camera camera;
	};


	//---------- Helper Functions ----------

	float3 GetCameraViewPosition()
	{
		return camera.position;
	}

	float4 ComputeObjectViewPosition(float3 _worldPosition)
	{
		return mul(camera.invViewProj, float4(_worldPosition, 1.0));
	}
}

#else // SA_CAMERA_BUFFER_ID

#define SA_CAMERA_BUFFER 0

#endif // SA_CAMERA_BUFFER_ID

#endif // SAPPHIRE_RENDER_SHADER_CAMERA_GUARD

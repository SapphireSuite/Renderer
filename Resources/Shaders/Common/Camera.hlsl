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
	//{ View

		/// Camera transformation matrix.
		float4x4 view;

		/// Camera inverse transformation matrix.
		float4x4 inverseView;

	//}

	
	//{ Projection
	
		/// Camera projection matrix.
		float4x4 projection;

		/// Camera inverse projection matrix.
		float4x4 inverseProjection;

		/**
		*	Camera inverse view projection matrix.
		*	projection * inverseView.
		*/
		float4x4 invViewProj;


		/// Z-Near plane.
		float zNear;

		/// Z-Far plane.
		float zFar;
		
		/// Screen dimensions.
		uint2 screen;

	//}
	};

	cbuffer CameraBuffer : SA_REG_SPACE(b, SA_CAMERA_BUFFER_ID, 0)
	{
		Camera camera;
	};


	//---------- Helper Functions ----------

	float3 GetCameraViewPosition()
	{
		return float3(camera.view._14, camera.view._24, camera.view._34);
	}

	float3 ComputeObjectViewPosition(float3 _worldPosition)
	{
		return mul(camera.inverseView, float4(_worldPosition, 1.0)).xyz;
	}

	float4 ComputeObjectViewProjPosition(float3 _worldPosition)
	{
		return mul(camera.invViewProj, float4(_worldPosition, 1.0));
	}


	/**
	*	\brief Compute screen-space to view-space position.
	*
	*	\param[in] _ssPosition Screen-space position: (x, y) = [0, screen], z = [0, 1].
	*
	*	\return View-space position.
	*/
	float3 ComputeScreenSpaceToViewSpace(float3 _ssPosition)
	{
		// Convert to NDC
		const float2 texCoord = _ssPosition.xy / float2(camera.screen);
	
		// Convert to clip space
		float4 clipPos = float4(texCoord * 2.0 - 1.0, _ssPosition.z, 1.0);
	
		// Viewport is flipped so Y-axis needs to be reversed.
		clipPos.y = -clipPos.y;
	
		// Convert to view-space
		const float4 viewPosition4 = mul(camera.inverseProjection, clipPos);
	
		// Fix perspective
		return viewPosition4.xyz / viewPosition4.w;
	}

	float2 ComputeScreenSpaceToViewSpace2D(float2 _ssPosition)
	{
		// Convert to NDC
		const float2 texCoord = _ssPosition / float2(camera.screen);
	
		// Convert to clip space
		float4 clipPos = float4(texCoord * 2.0 - 1.0, 0.0, 1.0);
	
		// Viewport is flipped so Y-axis needs to be reversed.
		clipPos.y = -clipPos.y;
	
		// Convert to view-space
		const float4 viewPosition4 = mul(camera.inverseProjection, clipPos);
	
		// Fix perspective
		return viewPosition4.xy / viewPosition4.w;
	}
}

#else // SA_CAMERA_BUFFER_ID

#define SA_CAMERA_BUFFER 0

#endif // SA_CAMERA_BUFFER_ID

#endif // SAPPHIRE_RENDER_SHADER_CAMERA_GUARD

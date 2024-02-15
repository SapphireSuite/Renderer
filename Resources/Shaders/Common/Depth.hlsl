// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_DEPTH_GUARD
#define SAPPHIRE_RENDER_SHADER_DEPTH_GUARD

#ifdef SA_DEPTH_BUFFER_ID

#define SA_DEPTH_ONLY_PREPASS 1

namespace SA
{
#if SA_VULKAN_API
#if SA_MULTISAMPLED_DEPTH_BUFFER

	[[vk::input_attachment_index(SA_DEPTH_INPUT_ATTACH_ID)]]
	SubpassInputMS<float> depthTexture : SA_REG_SPACE(t, SA_DEPTH_BUFFER_ID, 2);

#else // SA_MULTISAMPLED_DEPTH_BUFFER

	[[vk::input_attachment_index(SA_DEPTH_INPUT_ATTACH_ID)]]
	SubpassInput<float> depthTexture : SA_REG_SPACE(t, SA_DEPTH_BUFFER_ID, 2);

#endif // SA_MULTISAMPLED_DEPTH_BUFFER
#endif // SA_VULKAN_API

#if SA_DX12_API
#if SA_MULTISAMPLED_DEPTH_BUFFER

	Texture2DMS<float> depthTexture : SA_REG_SPACE(t, SA_DEPTH_BUFFER_ID, 2);

#else // SA_MULTISAMPLED_DEPTH_BUFFER

	Texture2D<float> depthTexture : SA_REG_SPACE(t, SA_DEPTH_BUFFER_ID, 2);

#endif // SA_MULTISAMPLED_DEPTH_BUFFER
#endif // SA_DX12_API

	/**
	*	Apply depth testing from Depth-Only prepass.
	*/
	void ApplyDepthTesting(float4 _svPosition, int _sampleIndex = 0)
	{
#if SA_VULKAN_API
#if SA_MULTISAMPLED_DEPTH_BUFFER

		const float sampledDepth = depthTexture.SubpassLoad(_sampleIndex);

#else // SA_MULTISAMPLED_DEPTH_BUFFER

		const float sampledDepth = depthTexture.SubpassLoad();

#endif // SA_MULTISAMPLED_DEPTH_BUFFER
#endif // SA_VULKAN_API

#if SA_DX12_API

		uint depthWidth = 0.0f;
		uint depthHeight = 0.0f;

#if SA_MULTISAMPLED_DEPTH_BUFFER

		uint depthSampleLevel;
		depthTexture.GetDimensions(depthWidth, depthHeight, depthSampleLevel);

		const float sampledDepth = depthTexture.Load(uint2(_svPosition.x * depthWidth, _svPosition.y * depthHeight), _sampleIndex);

#else // SA_MULTISAMPLED_DEPTH_BUFFER

		depthTexture.GetDimensions(depthWidth, depthHeight);

		const float sampledDepth = depthTexture.Load(uint3(_svPosition.x * depthWidth, _svPosition.y * depthHeight, 0));

#endif // SA_MULTISAMPLED_DEPTH_BUFFER
#endif // SA_DX12_API


	#if SA_DEPTH_INVERTED
		if(_svPosition.z < sampledDepth)
	#else
		if(_svPosition.z > sampledDepth)
	#endif
		{
			// Occluded by a closer object.
			discard;
		}
	}
}

#else // SA_DEPTH_INPUT_ATTACH_ID

#define SA_DEPTH_ONLY_PREPASS 0

#endif // SA_DEPTH_INPUT_ATTACH_ID

#endif // SAPPHIRE_RENDER_SHADER_DEPTH_GUARD

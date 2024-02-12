// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_DEPTH_GUARD
#define SAPPHIRE_RENDER_SHADER_DEPTH_GUARD

#if defined(SA_DEPTH_INPUT_ATTACH_ID) && defined(SA_DEPTH_BUFFER_ID)

#define SA_DEPTH_ONLY_PREPASS 1

namespace SA
{
#if SA_MULTISAMPLED_DEPTH_BUFFER

	[[vk::input_attachment_index(SA_DEPTH_INPUT_ATTACH_ID)]]
	SubpassInputMS<float> depthTexture : SA_REG_SPACE(t, SA_DEPTH_BUFFER_ID, 2);

#else

	[[vk::input_attachment_index(SA_DEPTH_INPUT_ATTACH_ID)]]
	SubpassInput<float> depthTexture : SA_REG_SPACE(t, SA_DEPTH_BUFFER_ID, 2);

#endif

#if SA_DEPTH_INVERTED
	static const float depthBias = -0.001f;
#else
	static const float depthBias = 0.001f;
#endif

	/**
	*	Apply depth testing from Depth-Only prepass.
	*/
	void ApplyDepthTesting(float4 _svPosition, int _sampleIndex = 0)
	{
#if SA_MULTISAMPLED_DEPTH_BUFFER

		float sampledDepth = depthTexture.SubpassLoad(_sampleIndex);

#else

		float sampledDepth = depthTexture.SubpassLoad();

#endif

		// Add depth bias to avoid Z-fighting.
		sampledDepth += depthBias;

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

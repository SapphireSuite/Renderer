// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_DEPTH_GUARD
#define SAPPHIRE_RENDER_SHADER_DEPTH_GUARD

#ifdef SA_DEPTH_INPUT_ATTACH_ID

#define SA_DEPTH_ONLY_PREPASS 1

namespace SA
{
	[[vk::input_attachment_index(0)]]
	SubpassInput<float> depthTexture : SA_REG_SPACE(t, SA_DEPTH_INPUT_ATTACH_ID, 2);

#if SA_DEPTH_INVERTED
	static const float depthBias = -0.0001f;
#else
	static const float depthBias = 0.0001f;
#endif

	/**
	*	Apply depth testing from Depth-Only prepass.
	*/
	void ApplyDepthTesting(float4 _svPosition)
	{
		const float sampledDepth = depthTexture.SubpassLoad() + depthBias; // Add depth bias to avoid Z-fighting.

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

#else

#define SA_DEPTH_ONLY_PREPASS 0

#endif

#endif // SAPPHIRE_RENDER_SHADER_DEPTH_GUARD

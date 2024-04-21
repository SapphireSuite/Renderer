// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_COMPUTE_ACTIVE_LIGHT_CLUSTERS_GUARD
#define SAPPHIRE_RENDER_SHADER_COMPUTE_ACTIVE_LIGHT_CLUSTERS_GUARD

#include <Passes/LightCulling/LightClusterCommon.hlsl>

//---------- Inputs ----------

#define NUM_THREAD_X 32
#define NUM_THREAD_Y 32

Texture2D<float> depthTexture : register(t2);


//---------- Outputs ----------

RWStructuredBuffer<uint> activeClusterStates : register(u3);


//-------------------- Compute Shader --------------------

[numthreads(NUM_THREAD_X, NUM_THREAD_Y, 1)]
void main(uint3 _dispatchThreadID : SV_DispatchThreadID)
{
	uint2 depthTextureSize;
	depthTexture.GetDimensions(depthTextureSize.x, depthTextureSize.y);
	
	if (_dispatchThreadID.x >= depthTextureSize.x ||
		_dispatchThreadID.y >= depthTextureSize.y)
		return;
	
	const float depthValue = depthTexture[_dispatchThreadID.xy];
	
	// Discard empty depth.
#if SA_DEPTH_INVERTED

	if(depthValue == 0.0f)
		return;

#else
	
	if (depthValue == 1.0f)
		return;
	
#endif

	const uint clusterIndex = SA::GetClusterIndex(_dispatchThreadID.xy, depthValue);
	
	activeClusterStates[clusterIndex] = true;
}

#endif // SAPPHIRE_RENDER_SHADER_COMPUTE_ACTIVE_LIGHT_CLUSTERS_GUARD

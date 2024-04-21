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
	
	float sampledDepth = depthTexture[_dispatchThreadID.xy];
	
	// Discard empty depth.
#if SA_DEPTH_INVERTED

	if(sampledDepth == 0.0f)
		return;

	sampledDepth = 1.0f - sampledDepth;

#else
	
	if (sampledDepth == 1.0f)
		return;
	
#endif

	// Convert to view-space depth position.
	const float4 viewDepthPosition = mul(camera.inverseProjection, float4(0.0f, 0.0f, sampledDepth, 1.0f));
	
	// Fix perspective.
	const float vsDepth = viewDepthPosition.z / viewDepthPosition.w;

	const uint clusterIndex = SA::GetClusterIndex(_dispatchThreadID.xy, vsDepth);
	
	activeClusterStates[clusterIndex] = true;
}

#endif // SAPPHIRE_RENDER_SHADER_COMPUTE_ACTIVE_LIGHT_CLUSTERS_GUARD

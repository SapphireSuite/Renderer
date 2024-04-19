// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_CLEAR_CULLED_LIGHT_GRID_GUARD
#define SAPPHIRE_RENDER_SHADER_CLEAR_CULLED_LIGHT_GRID_GUARD

#include <Passes/LightCulling/LightClusterCommon.hlsl>

//---------- Inputs ----------

#define NUM_THREAD_X 1024

RWStructuredBuffer<SA::ClusterLightList> culledLightGrid : register(u0);


//-------------------- Compute Shader --------------------

[numthreads(NUM_THREAD_X, 1, 1)]
void main(uint _dispatchThreadID : SV_DispatchThreadID)
{
	uint size;
	uint stride;
	culledLightGrid.GetDimensions(size, stride);
	
	if (_dispatchThreadID >= size)
		return;
	
	culledLightGrid[_dispatchThreadID].num = 0;
}

#endif // SAPPHIRE_RENDER_SHADER_CLEAR_CULLED_LIGHT_GRID_GUARD

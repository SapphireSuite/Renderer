// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_NORMAL_MAP_GUARD
#define SAPPHIRE_RENDER_SHADER_NORMAL_MAP_GUARD

#include "../Preprocessors.hlsl"
#include "../VertexFactory.hlsl"

namespace SA
{
#if SA_MATERIAL_NORMAL_MAP_ID
	
	#define SA_MATERIAL_NORMAL_MAP 1
	
	Texture2D<float3> normalMap : SA_REG_SPACE(t, SA_MATERIAL_NORMAL_MAP_ID, 3);
	SamplerState normalMapSampler : SA_REG_SPACE(s, SA_MATERIAL_NORMAL_MAP_ID, 3);

#else // SA_MATERIAL_NORMAL_MAP_ID
	
	#define SA_MATERIAL_NORMAL_MAP 0
	
#endif  // SA_MATERIAL_NORMAL_MAP_ID
	
	
	//---------- Helper Functions ----------
	
	float3 SampleNormalMap(float2 uv)
	{
	#if SA_MATERIAL_NORMAL_MAP
	
		return normalMap.Sample(normalMapSampler, uv).xyz * 2.0f - 1.0f;

	#else
		
		return float3(0.0f, 0.0f, 1.0f);
		
	#endif
	}
}

#endif // SAPPHIRE_RENDER_SHADER_NORMAL_MAP_GUARD

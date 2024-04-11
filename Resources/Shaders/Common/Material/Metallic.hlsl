// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_METALLIC_GUARD
#define SAPPHIRE_RENDER_SHADER_METALLIC_GUARD

#include "../Preprocessors.hlsl"

namespace SA
{
#ifdef SA_MATERIAL_METALLIC_ID
	
	#define SA_MATERIAL_METALLIC 1
	
	Texture2D<float> metallic : SA_REG_SPACE(t, SA_MATERIAL_METALLIC_ID, 3);
	SamplerState metallicSampler : SA_REG_SPACE(s, SA_MATERIAL_METALLIC_ID, 3);

#else // SA_MATERIAL_METALLIC_ID
	
	#define SA_MATERIAL_METALLIC 0
	
#endif  // SA_MATERIAL_METALLIC_ID
	
	
	//---------- Helper Functions ----------

	float SampleMetallic(float2 _uv)
	{
#if SA_MATERIAL_METALLIC
			
		return metallic.Sample(metallicSampler, _uv);
			
#else
		// Default metallic value.
		return 0.5f;

#endif
	}
}

#endif // SAPPHIRE_RENDER_SHADER_METALLIC_GUARD

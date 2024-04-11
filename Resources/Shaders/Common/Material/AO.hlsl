// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_AO_GUARD
#define SAPPHIRE_RENDER_SHADER_AO_GUARD

#include "../Preprocessors.hlsl"

namespace SA
{
#ifdef SA_MATERIAL_AO_ID
	
	#define SA_MATERIAL_AO 1
	
	Texture2D<float> ao : SA_REG_SPACE(t, SA_MATERIAL_AO_ID, 3);
	SamplerState aoSampler : SA_REG_SPACE(s, SA_MATERIAL_AO_ID, 3);

#else // SA_MATERIAL_AO_ID
	
	#define SA_MATERIAL_AO 0
	
#endif  // SA_MATERIAL_AO_ID
	
	
	//---------- Helper Functions ----------

	float SampleAO(float2 _uv)
	{
#if SA_MATERIAL_AO
			
		return ao.Sample(aoSampler, _uv);
			
#else
		// Default ao value.
		return 1.0f;

#endif
	}
}

#endif // SAPPHIRE_RENDER_SHADER_AO_GUARD

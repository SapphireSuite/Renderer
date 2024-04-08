// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_ROUGHNESS_GUARD
#define SAPPHIRE_RENDER_SHADER_ROUGHNESS_GUARD

namespace SA
{
#if SA_MATERIAL_ROUGHNESS_ID
	
	#define SA_MATERIAL_ROUGHNESS 1
	
	Texture2D<float> roughness : SA_REG_SPACE(t, SA_MATERIAL_ROUGHNESS_ID, 3);
	SamplerState roughnessSampler : SA_REG_SPACE(s, SA_MATERIAL_ROUGHNESS_ID, 3);

#else // SA_MATERIAL_ROUGHNESS_ID
	
	#define SA_MATERIAL_ROUGHNESS 0
	
#endif  // SA_MATERIAL_ROUGHNESS_ID
	
	
	//---------- Helper Functions ----------

	float SampleRoughness(float2 _uv)
	{
#if SA_MATERIAL_ROUGHNESS
			
		return roughness.Sample(roughnessSampler, _uv);
			
#else
		// Default roughness value.
		return 0.0f;

#endif
	}
}

#endif // SAPPHIRE_RENDER_SHADER_ROUGHNESS_GUARD

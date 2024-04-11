// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_ALBEDO_GUARD
#define SAPPHIRE_RENDER_SHADER_ALBEDO_GUARD

#include "../Preprocessors.hlsl"

namespace SA
{
#ifdef SA_MATERIAL_ALBEDO_ID
	
	#define SA_MATERIAL_ALBEDO 1
	
	Texture2D<float4> albedo : SA_REG_SPACE(t, SA_MATERIAL_ALBEDO_ID, 3);
	SamplerState albedoSampler : SA_REG_SPACE(s, SA_MATERIAL_ALBEDO_ID, 3);
	
#else // SA_MATERIAL_ALBEDO_ID
	
	#define SA_MATERIAL_ALBEDO 0
	
#endif  // SA_MATERIAL_ALBEDO_ID
	
	
	//---------- Helper Functions ----------

	float4 SampleAlbedo(float2 _uv)
	{
	#if SA_MATERIAL_ALBEDO
			
		return albedo.Sample(albedoSampler, _uv);
			
	#else
			
		// Missing albedo texture implementation.
		const float4 cyan = float4(0.0f, 1.0f, 1.0f, 1.0f);
		const float4 magenta = float4(1.0f, 0.0f, 1.0f, 1.0f);
			
		if(_uv.x < 0.5)
		{
			if (_uv.y < 0.5)
				return cyan;
			else
				return magenta;
		}
		else
		{
			if (_uv.y < 0.5)
				return magenta;
			else
				return cyan;
		}
			
	#endif
	}
}

#endif // SAPPHIRE_RENDER_SHADER_ALBEDO_GUARD

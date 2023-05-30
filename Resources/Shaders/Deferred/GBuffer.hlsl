// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

//-------------------- Vertex Shader --------------------

#include <Forward/Lit.hlsl>

// Use Forward-Lit vertex shader implementation.

//-------------------- Pixel Shader --------------------

#include <Common/NormalMapping.hlsl>

#if SA_HAS_UV

	#if SA_HAS_ALBEDO

		Texture2D albedo : register(t0);
		SamplerState albedoSampler : register(s0);

	#endif // SA_HAS_ALBEDO

	#if SA_HAS_HEIGHT_MAP

		Texture2D heightMap : register(t2);
		SamplerState heightMapSampler : register(s2);

	#endif // SA_HAS_HEIGHT_MAP

	#if SA_HAS_METALLIC_MAP

		Texture2D metallicMap : register(t3);
		SamplerState metallicMapSampler : register(s3);

	#endif // SA_HAS_METALLIC_MAP

	#if SA_HAS_ROUGH_MAP

		Texture2D roughMap : register(t4);
		SamplerState roughMapSampler : register(s4);

	#endif // SA_HAS_ROUGH_MAP

	#if SA_HAS_AO_MAP

		Texture2D aoMap : register(t5);
		SamplerState aoMapSampler : register(s5);

	#endif // SA_HAS_AO_MAP

#endif // SA_HAS_UV

struct PixelOut
{
	float4 position : POSITION;

#if SA_HAS_NORMAL

	float4 normal : NORMAL;

#endif // SA_HAS_NORMAL

#if SA_HAS_UV

	#if SA_HAS_ALBEDO

		float4 color;

	#endif // SA_HAS_ALBEDO

	#if SA_HAS_METALLIC_MAP || SA_HAS_ROUGH_MAP || SA_HAS_AO_MAP
		
		float4 pbr;
	
	#endif

#endif // SA_HAS_UV
};

PixelOut mainPS(V2P _input)
{
	PixelOut pixel;

	pixel.position = float4(_input.position, 1.0);

#if SA_HAS_UV

	#if SA_HAS_NORMAL

		pixel.normal = float4(SA::ComputePixelNormal(_input), 1.0);

	#else
	
		pixel.normal = float4(0.0, 0.0, 0.0, 1.0);

	#endif // SA_HAS_NORMAL

#endif // SA_HAS_UV

	return pixel
}
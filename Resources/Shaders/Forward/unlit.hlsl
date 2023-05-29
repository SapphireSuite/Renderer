// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

//-------------------- Vertex Shader --------------------

/// Vertex Input Assembly.
struct VertexInput
{
	float3 position : POSITION;

#if SA_HAS_UV

	float2 uv : TEXCOORD;

#elif SA_HAS_COLOR

	float4 color : COLOR;

#endif
};

/// Vertex to Pixel data
struct V2P
{
	float4 position : SV_POSITION;

#if SA_HAS_UV

	float2 uv : TEXCOORD;

#elif SA_HAS_COLOR

	float4 color : COLOR;

#endif
};

V2P mainVS(VertexInput _input)
{
	V2P output;

	// TODO: apply model and camera transformation.
	output.position = float4(_input.position, 1.0);

#if SA_HAS_UV

	output.uv = _input.uv;

#elif SA_HAS_COLOR

	output.color = _input.color;

#endif

	return output;
}

//-------------------- Pixel Shader --------------------

#if SA_HAS_UV

Texture2D albedo : register(t0);
SamplerState albedoSampler : register(s0);

#endif

float4 mainPS(V2P _input) : SV_TARGET
{
#if SA_HAS_UV

	const float4 color = albedo.Sample(albedoSampler, _input.uv);

#elif SA_HAS_COLOR

	const float4 color = _input.color;

#else

	const float4 color = float4(1, 1, 1, 1);

#endif

	if(color.a < 0.001)
		discard;

	return color;
}

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

//-------------------- Vertex Shader --------------------

/// Vertex Input Assembly.
struct VertexInput
{
	float3 position : POSITION;
	float2 uv : TEXCOORD;
};

/// Vertex to Pixel data
struct V2P
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

V2P mainVS(VertexInput _input)
{
	V2P output;

	// TODO: apply model and camera transformation.
	output.position = float4(_input.position, 1.0);

	output.uv = _input.uv;

	return output;
}

//-------------------- Pixel Shader --------------------

Texture2D albedo : register(t0);
SamplerState albedoSampler : register(s0);

float4 mainPS(V2P _input) : SV_TARGET
{
	float4 color = albedo.Sample(albedoSampler, _input.uv);

	if(color.a < 0.001)
		discard;

	return color;
}

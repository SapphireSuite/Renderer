// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SA_RENDER_SHADER_UNLIT_GUARD
#define SA_RENDER_SHADER_UNLIT_GUARD

//-------------------- Vertex Shader --------------------

#include <Common/Object.hlsl>
#include <Common/Camera.hlsl>

struct VertexInputAssembly
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
	float4 svPosition : SV_POSITION;

#if SA_HAS_UV

	float2 uv : TEXCOORD;

#elif SA_HAS_COLOR

	float4 color : COLOR;

#endif
};

V2P mainVS(VertexInputAssembly _input,
	uint _instanceID : SV_InstanceID)
{
	V2P output;

	const float4 objPosition = ComputeObjectPosition(float4(_input.position, 1.0), _instanceID);
	output.svPosition = ComputeObjectViewPosition(objPosition);

#if SA_HAS_UV

	// TODO: Apply material tilling.
	output.uv = _input.uv;

#elif SA_HAS_COLOR

	output.color = _input.color;

#endif

	return output;
}

//-------------------- Pixel Shader --------------------

#if SA_HAS_UV && SA_HAS_ALBEDO

	Texture2D albedo : register(t0);
	SamplerState albedoSampler : register(s0);

#endif

float4 mainPS(V2P _input) : SV_TARGET
{
#if SA_HAS_UV && SA_HAS_ALBEDO

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

#endif // SA_RENDER_SHADER_UNLIT_GUARD

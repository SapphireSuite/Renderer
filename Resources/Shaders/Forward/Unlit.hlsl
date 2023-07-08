// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Common/VertexFactory.hlsl>
#include <Common/Preprocessors.hlsl>

//-------------------- Vertex Shader --------------------

SA::V2P mainVS(SA::VertexInputAssembly _input)
{
	SA::V2P output;

	// TODO: apply model and camera transformation.
	output.svPosition = float4(_input.position, 1.0);

#if SA_HAS_UV

	output.uv = _input.uv;

#elif SA_HAS_COLOR

	output.color = _input.color;

#endif

	return output;
}

//-------------------- Pixel Shader --------------------

#if SA_HAS_UV

Texture2D albedo : SA_REG(t, SA_ALBEDO_ID);
SamplerState albedoSampler : SA_REG(s, SA_ALBEDO_ID);

#endif

float4 mainPS(SA::V2P _input) : SV_TARGET
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

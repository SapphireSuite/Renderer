// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Common/VertexFactory.hlsl>
#include <Common/Preprocessors.hlsl>

//-------------------- Vertex Shader --------------------

struct VertexOutput : SA::VertexOutputBase
{
};

VertexOutput mainVS(SA::VertexInputAssembly _input)
{
	VertexOutput output;

	// TODO: apply model and camera transformation.
	output.svPosition = float4(_input.position, 1.0);

#if SA_HAS_COLOR

	output.color = _input.color;

#endif

	return output;
}


//-------------------- Pixel Shader ---------------------

struct PixelInput : VertexOutput
{
};

float4 mainPS(PixelInput _input) : SV_TARGET
{
#if SA_HAS_COLOR

	const float4 color = _input.color;

#else

	const float4 color = float4(1, 1, 1, 1);

#endif

	if (color.a < 0.001)
		discard;

	return color;
}
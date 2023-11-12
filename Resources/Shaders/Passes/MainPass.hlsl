// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Common/VertexFactory.hlsl>
#include <Common/Preprocessors.hlsl>
#include <Common/Camera.hlsl>

//-------------------- Vertex Shader --------------------

struct VertexOutput
{
	/// Vertex world position
	float3 worldPosition : POSITION;
	
	/// Shader view position
	float4 svPosition : SV_POSITION;
	
#if SA_VERTEX_HAS_COLOR
	
	/// Vertex color
	float4 color : COLOR;
	
#endif

#ifdef SA_CAMERA_BUFFER_ID

	/// Camera view position.
	float3 viewPosition : VIEW_POSITION;

#endif

};

VertexOutput mainVS(SA::VertexInputAssembly _input)
{
	VertexOutput output;

	output.worldPosition = _input.position;

#ifdef SA_CAMERA_BUFFER_ID

	output.svPosition = SA::ComputeObjectViewPosition(output.worldPosition);

	output.viewPosition = SA::GetCameraViewPosition();

#else

	output.svPosition = float4(output.worldPosition, 1.0);

#endif

#if SA_VERTEX_HAS_COLOR

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
#if SA_VERTEX_HAS_COLOR

	const float4 color = _input.color;

#else

	const float4 color = float4(1, 1, 1, 1);

#endif

	if (color.a < 0.001)
		discard;

	return color;
}
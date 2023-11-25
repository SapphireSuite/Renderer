// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Common/VertexFactory.hlsl>
#include <Common/Preprocessors.hlsl>
#include <Common/Object.hlsl>
#include <Common/Camera.hlsl>

//-------------------- Vertex Shader --------------------

struct VertexOutput
{
	/// Vertex world position
	float3 worldPosition : POSITION;
	
	/// Shader view position
	float4 svPosition : SV_POSITION;
	
#if SA_VERTEX_NORMAL

	/// Vertex world normal
	float3 normal : NORMAL;

#endif

#if SA_VERTEX_COLOR
	
	/// Vertex color
	float4 color : COLOR;
	
#endif

#ifdef SA_CAMERA_BUFFER_ID

	/// Camera view position.
	float3 viewPosition : VIEW_POSITION;

#endif

};

VertexOutput mainVS(SA::VertexInputAssembly _input,
	uint _instanceId : SV_InstanceID)
{
	VertexOutput output;


	//---------- Position ----------

#ifdef SA_OBJECT_BUFFER_ID

	output.worldPosition = SA::ComputeObjectWorldPosition(_input.position, _instanceId);

#else

	output.worldPosition = _input.position;

#endif

#ifdef SA_CAMERA_BUFFER_ID

	output.svPosition = SA::ComputeObjectViewPosition(output.worldPosition);

	output.viewPosition = SA::GetCameraViewPosition();

#else

	output.svPosition = float4(output.worldPosition, 1.0);

#endif


	//---------- Normal ----------

#if SA_VERTEX_NORMAL

	#ifdef SA_OBJECT_BUFFER_ID

		output.normal = SA::ComputeObjectWorldNormal(_input.normal, _instanceId);

	#else

		output.normal = _input.normal;

	#endif

#endif


	//---------- Color ----------

#if SA_VERTEX_COLOR

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
#if SA_VERTEX_COLOR

	const float4 color = _input.color;

#else

	const float4 color = float4(1, 1, 1, 1);

#endif

	if (color.a < 0.001)
		discard;

	return color;
}
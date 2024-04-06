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
	precise float4 svPosition : SV_POSITION;
	
#if SA_VERTEX_NORMAL

	/// Vertex world normal
	float3 normal : NORMAL;

#endif

#if SA_VERTEX_COLOR
	
	/// Vertex color
	float4 color : COLOR;
	
#endif

#if SA_CAMERA_BUFFER

	/// Camera view position.
	float3 viewPosition : VIEW_POSITION;

#endif

};

VertexOutput mainVS(SA::VertexInputAssembly _input,
	uint _instanceId : SV_InstanceID)
{
	VertexOutput output;


	//---------- Position ----------

#if SA_OBJECT_BUFFER

	output.worldPosition = SA::ComputeObjectWorldPosition(_input.position, _instanceId);

#else

	output.worldPosition = _input.position;

#endif

#if SA_CAMERA_BUFFER

	output.svPosition = SA::ComputeObjectViewPosition(output.worldPosition);

	output.viewPosition = SA::GetCameraViewPosition();

#else

	output.svPosition = float4(output.worldPosition, 1.0);

#endif

#if SA_DEPTH_INVERTED

	/**
	*	z = w - z
	*	Shader normalization: divide each component by w
	*	z/w = (w - z)/w
	*	z/w = 1 - z/w.
	*/
	output.svPosition.z = output.svPosition.w - output.svPosition.z;

#endif // SA_DEPTH_INVERTED

	//---------- Normal ----------

#if SA_VERTEX_NORMAL

	#if SA_OBJECT_BUFFER

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

struct PixelOutput
{
	float4 color  : SV_TARGET;
};

PixelOutput mainPS(
	PixelInput _input)
{
	PixelOutput output;

#if SA_VERTEX_COLOR

	output.color = _input.color;

#else

	output.color = float4(1, 1, 1, 1);

#endif

	if (output.color.a < 0.001)
		discard;

	return output;
}
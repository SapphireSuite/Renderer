// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <Common/VertexFactory.hlsl>
#include <Common/Object.hlsl>
#include <Common/Camera.hlsl>


//-------------------- Vertex Shader --------------------

struct VertexOutput
{
	/// Shader view position
	float4 svPosition : SV_POSITION;
};


VertexOutput mainVS(SA::VertexInputAssembly _input,
	uint _instanceId : SV_InstanceID)
{
	VertexOutput output;

	
	//---------- World Position ----------
	
#if SA_OBJECT_BUFFER

	const float3 worldPosition = SA::ComputeObjectWorldPosition(_input.position, _instanceId);
	
#else
	
	const float3 worldPosition = _input.position;
	
#endif // SA_OBJECT_BUFFER
	
	
	//---------- SV Position ----------
	
#if SA_CAMERA_BUFFER

	output.svPosition = SA::ComputeObjectViewProjPosition(worldPosition);
	
#else
	
	output.svPosition = float4(worldPosition, 1.0);
	
#endif // SA_CAMERA_BUFFER
	
#if SA_DEPTH_INVERTED

	/**
	*	z = w - z
	*	Shader normalization: divide each component by w
	*	z/w = (w - z)/w
	*	z/w = 1 - z/w.
	*/
	output.svPosition.z = output.svPosition.w - output.svPosition.z;

#endif // SA_DEPTH_INVERTED
	
	return output;
}

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Common/VertexFactory.hlsl>
#include <Common/Preprocessors.hlsl>
#include <Common/Object.hlsl>
#include <Common/Camera.hlsl>

//-------------------- Vertex Shader --------------------

struct VertexOutput
{
//{ Position

	/// Vertex world position
	float3 worldPosition : POSITION;
	
	/// Shader view position
	precise float4 svPosition : SV_POSITION;
	
#if SA_CAMERA_BUFFER

	/// Camera view position.
	float3 viewPosition : VIEW_POSITION;

#endif
	
//}


#if SA_VERTEX_NORMAL

	/// Vertex world normal
	float3 normal : NORMAL;

#endif

	
#if SA_VERTEX_TANGENT

	/// Vertex world tangent
	float3 tangent : TANGENT;

#endif
	
	
#if SA_VERTEX_BITANGENT

	/// Vertex world bitangent
	float3 bitangent : BITANGENT;

#endif
	

#if SA_VERTEX_UV

	/// Vertex UV
	float2 uv : TEXCOORD;

#endif
	
	
#if SA_VERTEX_COLOR
	
	/// Vertex color
	float4 color : COLOR;
	
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

	
	//---------- Tangent ----------

#if SA_VERTEX_TANGENT

	#if SA_OBJECT_BUFFER

		output.tangent = SA::ComputeObjectWorldNormal(_input.tangent, _instanceId);

	#else

		output.tangent = _input.tangent;

	#endif

#endif
	
	
	//---------- Bitangent ----------

#if SA_VERTEX_BITANGENT

	#if SA_OBJECT_BUFFER

		output.bitangent = SA::ComputeObjectWorldNormal(_input.bitangent, _instanceId);

	#else

		output.bitangent = _input.bitangent;

	#endif

#endif
	

	//---------- UV ----------

#if SA_VERTEX_UV

	output.uv = _input.uv;

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
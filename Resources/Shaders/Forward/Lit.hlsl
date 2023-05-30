// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_LIT_GUARD
#define SAPPHIRE_RENDER_SHADER_LIT_GUARD

//-------------------- Vertex Shader --------------------

#include <Common/Object.hlsl>
#include <Common/Camera.hlsl>
#include <Common/VertexAssembly.hlsl>

struct V2P : SA::VertexAssembly
{
	float4 svPosition : SV_POSITION;

	float3 cameraPosition : CAMERA_POSITION;
};

V2P mainVS(SA::VertexAssembly _input,
	uint _instanceID : SV_InstanceID)
{
	V2P output;

	const float4 objPosition = ComputeObjectPosition(float4(_input.position, 1.0), _instanceID);
	output.position = objPosition.xyz / objPosition.w;
	output.svPosition = ComputeObjectViewPosition(objPosition);

	output.viewPosition = GetCameraViewPosition();

#if SA_HAS_NORMAL

	const float3x3 normalMat = GetObjectNormalMatrix(_instanceID);

	output.normal = normalMat * _input.normal;

	#if SA_HAS_TANGENT

		output.tangent = normalMat * _input.tangent;

	#endif // SA_HAS_TANGENT

	#if SA_HAS_BITANGENT

		output.bitangent = normalMat * _input.bitangent;

	#endif // SA_HAS_BITANGENT

#endif

#if SA_HAS_UV

	// TODO: Apply material tilling.
	output.uv = _input.uv;

#elif SA_HAS_COLOR

	output.color = _input.color;

#endif

	return output;
}

#endif // SAPPHIRE_RENDER_SHADER_LIT_GUARD

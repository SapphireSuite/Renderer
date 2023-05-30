// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_OBJECT_GUARD
#define SAPPHIRE_RENDER_SHADER_OBJECT_GUARD

#include "Frame.hlsl"

namespace SA
{
	/// Object transformation matrices.
	ConstantBuffer<float4x4> objectTransformMats : SA_REG(b, SA_OBJECT_TRANSFORM_MATS_ID);

#if SA_HAS_NORMAL_MATRIX

	/// Normal matrices used with non-uniform scale.
	ConstantBuffer<float3x3> objectNormalMats : SA_REG(b, SA_OBJECT_NORMAL_MATS_ID);

#endif

	float4 ComputeObjectPosition(float4 _position, uint _instanceID)
	{
		return objectTransformMats[_instanceID] * _position;
	}

	float3x3 GetObjectNormalMatrix(_instanceID)
	{
#if SA_HAS_NORMAL_MATRIX

		return objectNormalMats[_instanceID];

#else

		return float3x3(objectTransformMats[_instanceID]);

#endif
	}
}

#endif // SAPPHIRE_RENDER_SHADER_OBJECT_GUARD

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADE_OBJECT_GUARD
#define SAPPHIRE_RENDER_SHADE_OBJECT_GUARD

#include "Preprocessors.hlsl"

#ifdef SA_OBJECT_BUFFER_ID

namespace SA
{
	/**
	*	Must match `ObjectUBO` struct in `ObjectUBO.hpp`
	*/
	struct Object
	{
		/// Object transformation matrix.
		float4x4 transform;
	};

	cbuffer ObjectBuffer : SA_REG_SPACE(b, SA_OBJECT_BUFFER_ID, 1)
	{
		Object object[100];
	};


	//---------- Helper Functions ----------

	float3 ComputeObjectWorldPosition(float3 _vertexPosition, uint _instanceId = 0)
	{
		float4 outPosition = mul(object[_instanceId].transform, float4(_vertexPosition, 1.0));

		return outPosition.xyz / outPosition.w;
	}
}

#endif // SA_OBJECT_BUFFER_ID

#endif // SAPPHIRE_RENDER_SHADE_OBJECT_GUARD

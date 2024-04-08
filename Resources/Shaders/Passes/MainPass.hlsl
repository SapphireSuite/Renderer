// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Common/Config.hlsl>
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


//{ Normal

#if SA_VERTEX_NORMAL

	#if SA_VERTEX_TANGENT && SA_MATERIAL_NORMAL_MAP

		#if !SA_COMPUTE_LIGHTING_TANGENT_SPACE

			/// TBN (tangent, bitangent, normal) transformation matrix.
			float3x3 TBN : TBN;

		#endif // !SA_COMPUTE_LIGHTING_TANGENT_SPACE

	#else
	
		/// Vertex world normal
		float3 normal : NORMAL;

	#endif

#endif
	
//}
	

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


//{ Positions

	//---------- World Position ----------

#if SA_OBJECT_BUFFER

	output.worldPosition = SA::ComputeObjectWorldPosition(_input.position, _instanceId);

#else

	output.worldPosition = _input.position;

#endif

	
	//---------- SV Position ----------
	
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

//}
	
	
//{ Normal Mapping

#if SA_VERTEX_NORMAL

	#if SA_VERTEX_TANGENT && SA_MATERIAL_NORMAL_MAP
	
		//---------- TBN ----------
	
		#if SA_OBJECT_BUFFER
	
			const float3 normal = SA::ComputeObjectWorldNormal(_input.normal, _instanceId);
			const float3 tangent = SA::ComputeObjectWorldNormal(_input.tangent, _instanceId);
	
			#if SA_VERTEX_BITANGENT
	
				const float3 bitangent = SA::ComputeObjectWorldNormal(_input.bitangent, _instanceId);
	
			#else // SA_VERTEX_BITANGENT
	
				const float3 bitangent = cross(normal, tangent);
	
			#endif // SA_VERTEX_BITANGENT
	
		#else // SA_OBJECT_BUFFER
	
			const float3 normal = normalize(_input.normal);
			const float3 tangent = normalize(_input.tangent);
	
			#if SA_VERTEX_BITANGENT
	
				const float3 bitangent = normalize(_input.bitangent);
	
			#else // SA_VERTEX_BITANGENT
	
				const float3 bitangent = cross(normal, tangent);
	
			#endif // SA_VERTEX_BITANGENT
	
		#endif // SA_OBJECT_BUFFER
	
	
		#if SA_COMPUTE_LIGHTING_TANGENT_SPACE

			const float3x3 invTBN = transpose(float3x3(tangent, bitangent, normal));
	
		#else // SA_COMPUTE_LIGHTING_TANGENT_SPACE

			output.TBN = float3x3(tangent, bitangent, normal);
	
		#endif // SA_COMPUTE_LIGHTING_TANGENT_SPACE
	
	#else // SA_VERTEX_TANGENT && SA_MATERIAL_NORMAL_MAP
	
		//---------- Normal ----------
	
		#if SA_OBJECT_BUFFER

			output.normal = SA::ComputeObjectWorldNormal(_input.normal, _instanceId);

		#else // SA_OBJECT_BUFFER

			output.normal = normalize(_input.normal);

		#endif // SA_OBJECT_BUFFER
	
	#endif // SA_VERTEX_TANGENT && SA_MATERIAL_NORMAL_MAP
	
#endif // SA_VERTEX_NORMAL
	
//}

	
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
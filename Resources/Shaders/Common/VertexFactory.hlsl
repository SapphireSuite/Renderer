// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_VERTEX_FACTORY_GUARD
#define SAPPHIRE_RENDER_SHADER_VERTEX_FACTORY_GUARD

namespace SA
{
	/// Vertex Input Assembly data for vertex shader.
	struct VertexInputAssembly
	{
		float3 position : POSITION;

	#if SA_VERTEX_HAS_NORMAL

		float3 normal : NORMAL;

	#endif

	#if SA_VERTEX_HAS_TANGENT

		float3 tangent : TANGENT;

	#endif

	#if SA_VERTEX_HAS_BITANGENT

		float3 bitangent : BITANGENT;

	#endif

	#if SA_VERTEX_HAS_UV

		float2 uv : TEXCOORD;

	#endif

	#if SA_VERTEX_HAS_COLOR

		float4 color : COLOR;

	#endif
	};
}

#endif // SAPPHIRE_RENDER_SHADER_VERTEX_FACTORY_GUARD

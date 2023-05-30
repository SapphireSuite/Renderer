// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_NORMAL_MAPPING_GUARD
#define SAPPHIRE_RENDER_SHADER_NORMAL_MAPPING_GUARD

#include <Common/Preprocessors.hlsl>
#include <Common/VertexAssembly.hlsl>

namespace SA
{
#if SA_HAS_UV && SA_HAS_NORMAL

	#if SA_HAS_TANGENT && SA_HAS_NORMAL_MAP

		Texture2D normalMap : SA_REG(t, SA_NORMAL_MAP_ID);
		SamplerState normalMapSampler : SA_REG(s, SA_NORMAL_MAP_ID);

		float3 ApplyNormalMapping(in V2P _vertex)
		{
			const float3 N = normalize(_vertex.normal);

			const float3 T = normalize(_vertex.tangent);

		#if SA_HAS_BITANGENT

			const float3 B = normalize(_vertex.bitangent);

		#else

			const float3 B = cross (N, T);

		#endif // SA_HAS_BITANGENT

			const float3x3 TBN = float3x3(T, B, N);

			return normalize(TBN * (normalMap.Sample(normalMapSampler, _vertex.uv).rgb * 2.0 - 1.0));
		}

	#endif // SA_HAS_TANGENT && SA_HAS_NORMAL_MAP

	float3 ComputePixelNormal(in V2P _vertex)
	{
		#if SA_HAS_TANGENT && SA_HAS_NORMAL_MAP

			return ApplyNormalMapping(_vertex);

		#else

			return normalize(_vertex.normal);

		#endif
	}

#endif // SA_HAS_UV && SA_HAS_NORMAL
}

#endif // SAPPHIRE_RENDER_SHADER_NORMAL_MAPPING_GUARD
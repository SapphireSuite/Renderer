// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_MATERIAL_BASE_GUARD
#define SAPPHIRE_RENDER_SHADER_MATERIAL_BASE_GUARD

namespace SA
{
	struct MaterialBase
	{
	#if SA_HAS_MAT_UV_TILLING

		/// Material UV tilling.
		float2 uvTiling;

	#endif // SA_HAS_MAT_UV_TILLING

	#if SA_HAS_MAT_UV_OFFSET

		/// Material UV offset.
		float2 uvOffset;

	#endif // SA_HAS_MAT_UV_OFFSET
	};

	float2 ApplyMaterialTilling(in MaterialBase _mat, in _uv)
	{
		float2 result = _uv;

	#if SA_HAS_MAT_UV_TILLING

		result = _uv * _mat.uvTiling;

	#endif // SA_HAS_UV_TILLING

	#if SA_HAS_MAT_UV_OFFSET

		result += _mat.uvOffset;

	#endif // SA_HAS_MAT_UV_OFFSET

		return result;
	}
}

#endif // SAPPHIRE_RENDER_SHADER_MATERIAL_BASE_GUARD

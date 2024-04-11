// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_ILLUMINATION_GUARD
#define SAPPHIRE_RENDER_SHADER_ILLUMINATION_GUARD

namespace SA
{
	// Constants.
	static const float PI = 3.14159265359;

	struct IlluminationData
	{
		/// Albedo from texture.
		float3 albedo;

		/// Metallic from texture.
		float metallic;

		/// Roughness from texture.
		float roughness;

		/// World position
		float3 vPosition;

		/// Normal vector (normalized).
		float3 vnNormal;

		/// Object to camera direction (normalized).
		float3 vnCamera;
	
		/// Object to light vector.
		float3 vLight;

		/// Object to light direction (normalized).
		float3 vnLight;

		/// Fresnel reflectance.
		float3 f0;
	};


	struct LightData
	{
		float3 color;

		float intensity;

	//{ Attenuation

		float range;
	
		/// Should apply attenuation.
		bool bAttenuation;

	//}
	};


	float ComputeAttenuation(float3 _vLight, float _lightRange)
	{
		const float distance = length(_vLight);

		return max(1 - (distance / _lightRange), 0.0);
	}

	float3 FresnelSchlick(float3 _f0, float _cosTheta)
	{
		return _f0 + (1.0 - _f0) * pow(1.0 - _cosTheta, 5.0);
	}

	float DistributionGGX(float _cosAlpha, float _roughness)
	{
		// Normal distribution function: GGX model.
		const float roughSqr = _roughness * _roughness;

		const float denom = _cosAlpha * _cosAlpha * (roughSqr - 1.0) + 1.0;

		return roughSqr / (PI * denom * denom);
	}

	float GeometrySchlickGGX(float _cosRho, float _roughness)
	{
		// Geometry distribution function: GGX model.

		const float r = _roughness + 1.0;

		const float k = (r * r) / 8.0;

		return _cosRho / (_cosRho * (1.0 - k) + k);
	}
  
	float GeometrySmith(float _cosTheta, float _cosRho, float _roughness)
	{
		float ggx1 = GeometrySchlickGGX(_cosRho, _roughness);
		float ggx2 = GeometrySchlickGGX(_cosTheta, _roughness);
	
		return ggx1 * ggx2;
	}

	float3 ComputeBRDF(IlluminationData _data, LightData _lData)
	{
		const float cosTheta = dot(_data.vnNormal, _data.vnLight);

		const float attenuation = _lData.bAttenuation ? ComputeAttenuation(_data.vLight, _lData.range) : 1.0f;

		if (cosTheta > 0.0 && attenuation > 0.0)
		{
		//{ Specular Component

			// Halfway vector.
			const float3 vnHalf = normalize(_data.vnLight + _data.vnCamera);

			// Blinn-Phong variant. Phong formula is: dot(vnNormal, vnCamera)
			const float cosAlpha = dot(_data.vnNormal, vnHalf);
			const float cosRho = dot(_data.vnNormal, _data.vnCamera);

			const float3 F = FresnelSchlick(_data.f0, cosTheta);

			float3 specularBRDF = float3(0.0f, 0.0f, 0.0f);

			if(cosAlpha > 0.0 && cosRho > 0.0)
			{
				const float NDF = DistributionGGX(cosAlpha, _data.roughness);
				const float G = GeometrySmith(cosTheta, cosRho, _data.roughness);

				// Cook-Torrance specular BRDF.
				specularBRDF = (NDF * G * F) / (4.0 * cosTheta * cosRho);
			}

		//}


		//{ Diffuse Component

			const float3 kD = (float3(1.0f, 1.0f, 1.0f) - F) * (1.0 - _data.metallic);

			// Lambert Diffuse.
			const float3 diffuseBRDF = kD * _data.albedo / PI;

		//}

			return (diffuseBRDF + specularBRDF) * cosTheta * attenuation * _lData.color * _lData.intensity;
		}

		return float3(0.0f, 0.0f, 0.0f);
	}
}

#endif // SAPPHIRE_RENDER_SHADER_ILLUMINATION_GUARD

// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_SAMPLED_TEXTURE_GUARD
#define SAPPHIRE_RENDER_RHI_SAMPLED_TEXTURE_GUARD

#include "RHIITexture.hpp"

#include <SA/Render/LowLevel/Common/Texture/RawTexture.hpp>

namespace SA::RND::RHI
{
	class Device;
	class ResourceInitializer;

	/**
	* \brief Texture used as input for sampling.
	*/
	class SampledTexture : public ITexture
	{
	public:
		virtual ~SampledTexture() = default;

		virtual void Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawTexture& _raw) = 0;
		virtual void Destroy(const Device* _device) = 0;
	};
}

#endif // SAPPHIRE_RENDER_RHI_SAMPLED_TEXTURE_GUARD

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_STATIC_MESH_GUARD
#define SAPPHIRE_RENDER_RHI_VK_STATIC_MESH_GUARD

#include <SA/Render/RHI/Mesh/RHIStaticMesh.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

#include <SA/Render/LowLevel/Vulkan/Mesh/VkStaticMesh.hpp>

namespace SA::RND::RHI
{
	class VkStaticMesh : public StaticMesh
	{
		VK::StaticMesh mHandle;

	public:
		void Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawMesh& _raw) override final;
		void Destroy(const Device* _device) override final;

		const VK::StaticMesh& API_Vulkan() const override final;
	};
}

#endif

#endif // SAPPHIRE_RENDER_RHI_VK_STATIC_MESH_GUARD

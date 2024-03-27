// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_STATIC_MESH_GUARD
#define SAPPHIRE_RENDER_RHI_VK_STATIC_MESH_GUARD

#include <SA/Render/RHI/Common/Mesh/RHIStaticMesh.hpp>

#include <SA/Render/LowLevel/Vulkan/Mesh/VkStaticMesh.hpp>

namespace SA::RND::RHI
{
	class VkStaticMesh : public StaticMesh
	{
		VK::StaticMesh mHandle;

	public:
		void Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawStaticMesh& _raw) override final;
		void Destroy(const Device* _device) override final;

		void Draw(const CommandBuffer* _cmd, uint32_t _instanceNum = 1) override final;

		const VK::StaticMesh& API_Vulkan() const override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_VK_STATIC_MESH_GUARD

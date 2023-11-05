// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_STATIC_MESH_GUARD
#define SAPPHIRE_RENDER_RHI_STATIC_MESH_GUARD

#include <SA/Render/LowLevel/Common/Mesh/RawMesh.hpp>

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
	namespace VK
	{
		class StaticMesh;
	}
#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL
	namespace DX12
	{
		class StaticMesh;
	}
#endif

	namespace RHI
	{
		class Device;
		class ResourceInitializer;
		class CommandBuffer;

		class StaticMesh
		{
		public:
			virtual ~StaticMesh() = default;

			virtual void Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawMesh& _raw) = 0;
			virtual void Destroy(const Device* _device) = 0;

			virtual void Draw(const CommandBuffer* _cmd, uint32_t _instanceNum = 1) = 0;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

			virtual const VK::StaticMesh& API_Vulkan() const;

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

			virtual const DX12::StaticMesh& API_DirectX12() const;

#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_STATIC_MESH_GUARD

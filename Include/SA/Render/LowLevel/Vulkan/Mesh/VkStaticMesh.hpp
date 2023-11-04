// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_STATIC_MESH_GUARD
#define SAPPHIRE_RENDER_VK_STATIC_MESH_GUARD

#include <SA/Render/LowLevel/Common/Mesh/RawMesh.hpp>

#include <SA/Render/LowLevel/Vulkan/Buffers/VkBuffer.hpp>

namespace SA::RND::VK
{
	class Device;
	class ResourceInitializer;

	class StaticMesh
	{
		Buffer mVertexBuffer;
		Buffer mIndexBuffer;

		uint32_t mIndexCount = 0;
		SA::RND::IndexBufferType mIndexBufferType;

	public:
		void Create(const Device& _device, ResourceInitializer& _init, const RawMesh& _raw);
		void Destroy(const Device& _device);
	};
}

#endif // SAPPHIRE_RENDER_VK_STATIC_MESH_GUARD

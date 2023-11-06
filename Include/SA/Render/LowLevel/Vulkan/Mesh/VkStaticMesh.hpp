// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_STATIC_MESH_GUARD
#define SAPPHIRE_RENDER_VK_STATIC_MESH_GUARD

#include <SA/Render/LowLevel/Common/Mesh/RawStaticMesh.hpp>

#include <SA/Render/LowLevel/Vulkan/Buffers/VkBuffer.hpp>

namespace SA::RND::VK
{
	class Device;
	class ResourceInitializer;
	class CommandBuffer;

	class StaticMesh
	{
		Buffer mVertexBuffer;
		Buffer mIndexBuffer;

		uint32_t mIndicesCount = 0;
		SA::RND::IndexBufferType mIndexBufferType;

	public:
		void Create(const Device& _device, ResourceInitializer& _init, const RawStaticMesh& _raw);
		void Destroy(const Device& _device);

		void Draw(const CommandBuffer& _cmd, uint32_t _instanceNum = 1u);
	};
}

#endif // SAPPHIRE_RENDER_VK_STATIC_MESH_GUARD

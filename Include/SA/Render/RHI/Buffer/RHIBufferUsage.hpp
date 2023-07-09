// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_BUFFER_USAGE_GUARD
#define SAPPHIRE_RENDER_RHI_BUFFER_USAGE_GUARD

#include <cstdint>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>
#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL
#include <SA/Render/LowLevel/DX12/DX12API.hpp>
#endif

namespace SA::RND
{
	namespace RHI
	{
		enum BufferUsage : uint32_t
		{
			None = 0,

			/// Uniform buffer object.
			UniformBuffer = 1 << 0,

			/// Storage buffer object.
			StorageBuffer = 1 << 1,

			VertexBuffer = 1 << 2,

			IndexBuffer = 1 << 3,

			/// CPU accessible for upload.
			CPUUpload = 1 << 4,

			/// CPU accessible for readback.
			CPUReadBack = 1 << 5,
		};
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkBufferUsageFlags API_GetBufferUsage(RHI::BufferUsage _usage);

		VkMemoryPropertyFlags API_GetBufferMemoryProperties(RHI::BufferUsage _usage);
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		D3D12_RESOURCE_STATES API_GetBufferUsage(RHI::BufferUsage _usage);
		
		D3D12_HEAP_TYPE API_GetBufferMemoryHeapType(RHI::BufferUsage _usage);
	}

#endif
}

#endif // SAPPHIRE_RENDER_RHI_BUFFER_USAGE_GUARD

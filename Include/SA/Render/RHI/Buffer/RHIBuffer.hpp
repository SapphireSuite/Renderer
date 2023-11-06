// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_BUFFER_GUARD
#define SAPPHIRE_RENDER_RHI_BUFFER_GUARD

#include "RHIBufferUsage.hpp"

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
	namespace VK
	{
		class Buffer;
	}
#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL
	namespace DX12
	{
		class Buffer;
	}
#endif

	namespace RHI
	{
		class Device;

		class Buffer
		{
		public:
			virtual ~Buffer() = default;

			virtual void Create(const Device* _device, uint64_t _size, BufferUsage _usage, const void* _src = nullptr) = 0;
			virtual void Destroy(const Device* _device) = 0;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

			virtual const VK::Buffer& API_Vulkan() const;

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

			virtual const DX12::Buffer& API_DirectX12() const;

#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_BUFFER_GUARD

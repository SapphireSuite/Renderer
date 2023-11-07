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


			virtual void UploadData(const void* _src, uint64_t _size, uint64_t _offset = 0u) = 0;

			template <typename T>
			void UploadData(const T& _src)
			{
				UploadData(&_src, sizeof(T));
			}


			virtual void ReadbackData(void* _dst, uint64_t _size, uint64_t _offset = 0u) = 0;

			template <typename T>
			void ReadbackData(T& _src)
			{
				ReadbackData(&_src, sizeof(T));
			}

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

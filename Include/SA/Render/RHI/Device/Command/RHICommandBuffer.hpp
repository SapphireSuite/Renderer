// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_COMMAND_BUFFER_GUARD
#define SAPPHIRE_RENDER_RHI_COMMAND_BUFFER_GUARD

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		class CommandBuffer;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		class CommandList;
	}

#endif

	namespace RHI
	{
		class CommandBuffer
		{
		public:
			virtual ~CommandBuffer() = default;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

			virtual VK::CommandBuffer& API_Vulkan();
			virtual const VK::CommandBuffer& API_Vulkan() const;

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

			virtual DX12::CommandList& API_DirectX12();
			virtual const DX12::CommandList& API_DirectX12() const;

#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_COMMAND_BUFFER_GUARD

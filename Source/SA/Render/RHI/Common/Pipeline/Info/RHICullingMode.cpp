// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/Info/RHICullingMode.hpp>

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkCullModeFlags API_GetCullingMode(RHI::CullingMode _mode)
		{
			static constexpr VkCullModeFlags vkCullModeIndexMap[] = {
				VK_CULL_MODE_NONE,
				VK_CULL_MODE_FRONT_BIT,
				VK_CULL_MODE_BACK_BIT
			};

			const uint8_t index = static_cast<uint8_t>(_mode);

			SA_ASSERT((OutOfRange, index, 0u, sizeof(vkCullModeIndexMap)), SA.Render.RHI.Vulkan,
				(L"CullingMode value [%1] invalid", index));

			return vkCullModeIndexMap[index];
		}
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		D3D12_CULL_MODE API_GetCullingMode(RHI::CullingMode _mode)
		{
			static constexpr D3D12_CULL_MODE d12CullModeIndexMap[] = {
				D3D12_CULL_MODE_NONE,
				D3D12_CULL_MODE_FRONT,
				D3D12_CULL_MODE_BACK
			};

			const uint8_t index = static_cast<uint8_t>(_mode);

			SA_ASSERT((OutOfRange, index, 0u, sizeof(d12CullModeIndexMap)), SA.Render.RHI.DX12,
				(L"CullingMode value [%1] invalid", index));

			return d12CullModeIndexMap[index];
		}
	}

#endif
}

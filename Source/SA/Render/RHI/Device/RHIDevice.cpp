// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/RHIDevice.hpp>

#include <SA/Collections/Debug>

namespace SA::RND::RHI
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	const VK::Device* Device::API_Vulkan() const
	{
		SA_ASSERT((Default, false), SA.Render.RHI.Vulkan, L"Query Vulkan API handle from non-vulkan object!");

		return nullptr;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	const DX12::Device* Device::API_DirectX12() const
	{
		SA_ASSERT((Default, false), SA.Render.RHI.DX12, L"Query DirectX12 API handle from non-dx12 object!");

		return nullptr;
	}

#endif
}

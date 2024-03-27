// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_DEVICE_REQUIREMENTS_GUARD
#define SAPPHIRE_RENDER_RHI_DEVICE_REQUIREMENTS_GUARD

#include <SA/Render/LowLevel/Common/Device/DeviceRequirementsBase.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
	#include <SA/Render/LowLevel/Vulkan/Device/VkDeviceRequirements.hpp>
#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL
	#include <SA/Render/LowLevel/DX12/Device/D12DeviceRequirements.hpp>
#endif

namespace SA::RND::RHI
{
	class WindowSurface;

	struct DeviceRequirements : public DeviceRequirementsBase
	{
		const WindowSurface* winSurface = nullptr;

		void SetWindowSurface(const WindowSurface* _winSurface = nullptr, bool bSetPresentQueue = true);


#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

		VK::DeviceRequirements API_Vulkan() const;

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

		DX12::DeviceRequirements API_DirectX12() const;

#endif
	};
}

#endif // SAPPHIRE_RENDER_RHI_DEVICE_REQUIREMENTS_GUARD

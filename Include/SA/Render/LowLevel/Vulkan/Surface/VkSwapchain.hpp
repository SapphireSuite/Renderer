// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_SWAPCHAIN_GUARD
#define SAPPHIRE_RENDER_VK_SWAPCHAIN_GUARD

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

namespace SA::VK
{
	class Device;
	class Surface;

	class Swapchain
	{
//{ Swapchain KHR

		VkSwapchainKHR mHandle = VK_NULL_HANDLE;

		void CreateSwapChainKHR(const Device& _device, const Surface& _surface);
		void DestroySwapChainKHR(const Device& _device);

//}


//{ Sync

		struct Synchronisation
		{
			VkSemaphore acquireSemaphore = VK_NULL_HANDLE;
			VkSemaphore presentSemaphore = VK_NULL_HANDLE;
			VkFence		fence = VK_NULL_HANDLE;
		};

		void CreateSynchronisation(const Device& _device);
		void DestroySynchronisation(const Device& _device);

//}

//{ Frame

		uint32_t mFrameIndex = 0u;
		uint32_t mImageIndex = 0u;

		struct Frame
		{
			Synchronisation sync;
		};

		std::vector<Frame> mFrames;
//}

		Vec2ui mExtent;

	public:
		void Create(const Device& _device, const Surface& _surface);
		void Destroy(const Device& _device);

//{ Render

		void Begin(const Device& _device);
		void End(const Device& _device);

//}
	};
}

#endif // SAPPHIRE_RENDER_VK_SWAPCHAIN_GUARD

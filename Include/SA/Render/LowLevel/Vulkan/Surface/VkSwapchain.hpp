// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_SWAPCHAIN_GUARD
#define SAPPHIRE_RENDER_VK_SWAPCHAIN_GUARD

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

namespace SA::RND::VK
{
	class Device;
	class Queue;
	class WindowSurface;
	class CommandBuffer;
	struct SurfaceSupportDetails;

	class Swapchain
	{
//{ Swapchain KHR

		VkSwapchainKHR mHandle = VK_NULL_HANDLE;

		void CreateSwapChainKHR(const Device& _device,
			const WindowSurface& _surface,
			const SurfaceSupportDetails& _details,
			const VkSurfaceFormatKHR& _surfaceFormat);
		void DestroySwapChainKHR(const Device& _device);


//}


//{ Image View

		// void CreateImageView(const Device& _device, VkFormat _format);
		// void DestroyImageView(const Device& _device);

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
			// VkImageView imageView;
			Synchronisation sync;
		};

		std::vector<Frame> mFrames;
//}

		VkFormat mFormat;
		Vec2ui mExtent;

	public:
		void Create(const Device& _device, const WindowSurface& _surface);
		void Destroy(const Device& _device);

		/// Get number of image (frame-buffering num).
		uint32_t GetImageNum() const noexcept;

		VkFormat GetFormat() const noexcept;

//{ Render

		uint32_t Begin(const Device& _device);
		void End(const Device& _device, const std::vector<CommandBuffer>& _cmdBuffers);
		void End(const Queue& _graphicsQueue, const Queue& _presentQueue, const std::vector<CommandBuffer>& _cmdBuffers);

//}
	};
}

#endif // SAPPHIRE_RENDER_VK_SWAPCHAIN_GUARD

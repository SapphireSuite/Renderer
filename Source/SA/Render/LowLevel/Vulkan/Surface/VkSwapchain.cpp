// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Surface/VkSwapchain.hpp>

#include <Device/VkDevice.hpp>
#include <Device/Command/VkCommandBuffer.hpp>

#include <Surface/VkWindowSurface.hpp>

namespace SA::RND::VK
{
//{ Swapchain KHR

	void Swapchain::CreateSwapChainKHR(const Device& _device,
		const WindowSurface& _surface,
		const SurfaceSupportDetails& _details,
		const VkSurfaceFormatKHR& _surfaceFormat)
	{
		const VkPresentModeKHR presentMode = _details.ChooseSwapPresentMode();
		mExtents = _details.ChooseSwapExtent();
		mFormat = _surfaceFormat.format;

	//{ Image num

		// Min image count to avoid driver blocking.
		uint32_t imageNum = _details.capabilities.minImageCount + 1;

		if(_details.capabilities.maxImageCount > 0 && imageNum > _details.capabilities.maxImageCount)
			imageNum = _details.capabilities.maxImageCount;

		mFrames.resize(imageNum);

	//}

		// Create Swapchain.
		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.pNext = nullptr;
		createInfo.flags = 0u;
		createInfo.surface = _surface;
		createInfo.minImageCount = imageNum;
		createInfo.imageFormat = _surfaceFormat.format;
		createInfo.imageColorSpace = _surfaceFormat.colorSpace;
		createInfo.imageExtent = VkExtent2D{ mExtents.x, mExtents.y };
		createInfo.imageArrayLayers = 1u;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0u;
		createInfo.pQueueFamilyIndices = nullptr;
		createInfo.preTransform = _details.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;


		// TODO: Implement if no present queue.
		uint32_t familyIndices[]
		{
			_device.queueMgr.graphics[0].GetFamilyIndex(),
			_device.queueMgr.present[0].GetFamilyIndex(),
		};

		// Graphic and present familiy are different.
		if(familyIndices[0] != familyIndices[1])
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = sizeof(familyIndices) / sizeof(uint32_t);
			createInfo.pQueueFamilyIndices = familyIndices;
		}

		SA_VK_API(vkCreateSwapchainKHR(_device, &createInfo, nullptr, &mHandle), L"Failed to create swapchain!");

		SA_LOG(L"Swapchain created!", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));
	}
	
	void Swapchain::DestroySwapChainKHR(const Device& _device)
	{
		SA_LOG_RAII(L"Swapchain KHR destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));

		SA_VK_API(vkDestroySwapchainKHR(_device, mHandle, nullptr));
		mHandle = VK_NULL_HANDLE;
		mFrames.clear();
	}

//}


//{ Image View

/*
	void Swapchain::CreateImageView(const Device& _device, VkFormat _format)
	{
		uint32_t imageNum = GetImageNum();
		
		std::vector<VkImage> images;
		images.resize(imageNum);
		
		SA_VK_API(vkGetSwapchainImagesKHR(_device, mHandle, &imageNum, images.data()));

		VkImageViewCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.pNext = nullptr;
		createInfo.flags = 0;
		// createInfo.image; // Set in loop.
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = _format;
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		for(uint32_t i = 0; i < imageNum; ++i)
		{
			createInfo.image = images[i];

			SA_VK_API(vkCreateImageView(_device, &createInfo, nullptr, &mFrames[i].imageView),
				L"Failed to create Swapchain image view");

			SA_LOG(L"Swapchain ImageView created.", Info, SA.Render.Vulkan, ("Handle [%1]", mFrames[i].imageView));
		}
	}
	
	void Swapchain::DestroyImageView(const Device& _device)
	{
		for(auto& frame : mFrames)
		{
			SA_VK_API(vkDestroyImageView(_device, frame.imageView, nullptr));
		}
	}

*/
//}


//{ Sync

	void Swapchain::CreateSynchronisation(const Device& _device)
	{
		VkSemaphoreCreateInfo semaphoreCreateInfo{};
		semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		semaphoreCreateInfo.pNext = nullptr;
		semaphoreCreateInfo.flags = 0u;

		VkFenceCreateInfo fenceCreateInfo{};
		fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceCreateInfo.pNext = nullptr;
		fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for(auto& frame : mFrames)
		{
			SA_VK_API(vkCreateSemaphore(_device, &semaphoreCreateInfo, nullptr, &frame.sync.acquireSemaphore),
				L"Failed to create acquire semaphore!");
			
			SA_VK_API(vkCreateSemaphore(_device, &semaphoreCreateInfo, nullptr, &frame.sync.presentSemaphore),
				L"Failed to create present semaphore!");
			
			SA_VK_API(vkCreateFence(_device, &fenceCreateInfo, nullptr, &frame.sync.fence),
				L"Failed to create fence!");
		}

		SA_LOG(L"Swapchain synchronisation created.", Info, SA.Render.Vulkan);
	}
	
	void Swapchain::DestroySynchronisation(const Device& _device)
	{
		for(auto& frame : mFrames)
		{
			SA_VK_API(vkDestroySemaphore(_device, frame.sync.acquireSemaphore, nullptr));
			SA_VK_API(vkDestroySemaphore(_device, frame.sync.presentSemaphore, nullptr));
			SA_VK_API(vkDestroyFence(_device, frame.sync.fence, nullptr));
		}

		SA_LOG(L"Swapchain synchronisation destroyed.", Info, SA.Render.Vulkan);
	}

//}


	void Swapchain::Create(const Device& _device, const WindowSurface& _surface)
	{
		const SurfaceSupportDetails details = _surface.QuerySupportDetails(_device);
		const VkSurfaceFormatKHR surfaceFormat = details.ChooseSwapSurfaceFormat();

		CreateSwapChainKHR(_device, _surface, details, surfaceFormat);
		//CreateImageView(_device, surfaceFormat.format);
		CreateSynchronisation(_device);
	}
	
	void Swapchain::Destroy(const Device& _device)
	{
		DestroySynchronisation(_device);
		//DestroyImageView(_device);
		DestroySwapChainKHR(_device);
	}

	uint32_t Swapchain::GetImageNum() const noexcept
	{
		return static_cast<uint32_t>(mFrames.size());
	}

	VkFormat Swapchain::GetFormat() const noexcept
	{
		return mFormat;
	}

	Vec2ui Swapchain::GetExtents() const noexcept
	{
		return mExtents;
	}

//{ Render

	uint32_t Swapchain::Begin(const Device& _device)
	{
		Frame& frame = mFrames[mFrameIndex];

		// Wait current Fence.
		vkWaitForFences(_device, 1, &frame.sync.fence, true, UINT64_MAX);

		// Reset current Fence.
		vkResetFences(_device, 1, &frame.sync.fence);

		SA_VK_API(vkAcquireNextImageKHR(_device, mHandle, UINT64_MAX, frame.sync.acquireSemaphore, VK_NULL_HANDLE, &mImageIndex),
			L"Failed to aquire next image!");

		return mFrameIndex;
	}

	void Swapchain::End(const Device& _device, const std::vector<CommandBuffer>& _cmdBuffers)
	{
		const Queue& graphics = _device.queueMgr.graphics[0];
		const Queue& present =_device.queueMgr.present.GetQueueNum() > 0 ? _device.queueMgr.present[0] : graphics;

		End(graphics, present, _cmdBuffers);
	}

	void Swapchain::End(const Queue& _graphicsQueue, const Queue& _presentQueue, const std::vector<CommandBuffer>& _cmdBuffers)
	{
		Frame& frame = mFrames[mFrameIndex];

		// Submit graphics.
		{
			const VkPipelineStageFlags waitStages = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

			VkSubmitInfo submitInfo{};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.pNext = nullptr;
			submitInfo.waitSemaphoreCount = 1u;
			submitInfo.pWaitSemaphores = &frame.sync.acquireSemaphore;
			submitInfo.pWaitDstStageMask = &waitStages;
			submitInfo.commandBufferCount = static_cast<uint32_t>(_cmdBuffers.size());
			submitInfo.pCommandBuffers = reinterpret_cast<const VkCommandBuffer*>(_cmdBuffers.data()); // Warning: Unsafe.
			submitInfo.signalSemaphoreCount = 1u;
			submitInfo.pSignalSemaphores = &frame.sync.presentSemaphore;

			SA_VK_API(vkQueueSubmit(_graphicsQueue, 1, &submitInfo, frame.sync.fence),
				L"Failed to submit to graphics queue!");
		}

		// Submit present.
		{
			VkPresentInfoKHR presentInfo{};
			presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			presentInfo.pNext = nullptr;
			presentInfo.waitSemaphoreCount = 1u;
			presentInfo.pWaitSemaphores = &frame.sync.presentSemaphore;
			presentInfo.swapchainCount = 1u;
			presentInfo.pSwapchains = &mHandle;
			presentInfo.pImageIndices = &mImageIndex;
			presentInfo.pResults = nullptr;

			SA_VK_API(vkQueuePresentKHR(_presentQueue, &presentInfo),
				L"Failed to submit present queue!")
		}

		// Increment next frame.
		mFrameIndex = (mFrameIndex + 1) % mFrames.size();
	}

//}
}

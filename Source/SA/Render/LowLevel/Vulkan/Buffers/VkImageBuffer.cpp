// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Buffers/VkImageBuffer.hpp>

#include <Device/VkDevice.hpp>

namespace SA::RND::VK
{
	void ImageBuffer::Create(const Device& _device, const ImageBufferInfo& _info)
	{
		CreateVkImage(_device, _info.VkImageInfo());
		CreateVkImageView(_device, _info.VkImageViewInfo(mImage));
	}
	
	void ImageBuffer::CreateFromImage(const Device& _device, VkImage _image, const ImageBufferInfo& _info)
	{
		// Not owner (aka not responsible for allocation): mImageMemory nullptr.
		mImage = _image;

		CreateVkImageView(_device, _info.VkImageViewInfo(mImage));
	}

	void ImageBuffer::Destroy(const Device& _device)
	{
		DestroyVkImageView(_device);
		DestroyVkImage(_device);
	}

//{ Image

	void ImageBuffer::CreateVkImage(const Device& _device, const VkImageCreateInfo& _vkInfos)
	{
		SA_VK_API(vkCreateImage(_device, &_vkInfos, nullptr, &mImage), L"Failed to create image!");
		SA_LOG(L"Image created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mImage));

		// Create Image memory.
		VkMemoryRequirements memRequirements;
		vkGetImageMemoryRequirements(_device, mImage, &memRequirements);

		const uint32_t memoryTypeIndex = BufferBase::FindMemoryType(_device, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		VkMemoryAllocateInfo memoryAllocInfo{};
		memoryAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		memoryAllocInfo.pNext = nullptr;
		memoryAllocInfo.allocationSize = memRequirements.size;
		memoryAllocInfo.memoryTypeIndex = memoryTypeIndex;

		SA_VK_API(vkAllocateMemory(_device, &memoryAllocInfo, nullptr, &mImageMemory), L"Failed to allocate image memory!");
		SA_LOG(L"Image memory created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mImageMemory));

		SA_VK_API(vkBindImageMemory(_device, mImage, mImageMemory, 0));
	}
	
	void ImageBuffer::DestroyVkImage(const Device& _device)
	{
		// In case the image was given to the buffer (using CreateFromImage).
		if(mImageMemory != VK_NULL_HANDLE)
		{
			SA_VK_API(vkDestroyImage(_device, mImage, nullptr));

			SA_LOG(L"Image destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mImage));

			mImage = VK_NULL_HANDLE;


			// Free memory after destroying image: memory no more used.
			SA_VK_API(vkFreeMemory(_device, mImageMemory, nullptr));

			SA_LOG(L"Image memory destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mImageMemory));

			mImageMemory = VK_NULL_HANDLE;
		}
		else
		{
			// Image owned by Swapchain.
			mImage = VK_NULL_HANDLE;
		}
	}

//}

//{ Image View
	
	void ImageBuffer::CreateVkImageView(const Device& _device, const VkImageViewCreateInfo& _vkInfos)
	{
		SA_VK_API(vkCreateImageView(_device, &_vkInfos, nullptr, &mImageView), L"Failed to create image view!");
		SA_LOG(L"Image View created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mImageView));
	}
	
	void ImageBuffer::DestroyVkImageView(const Device& _device)
	{
		SA_VK_API(vkDestroyImageView(_device, mImageView, nullptr));
		
		SA_LOG(L"Image View destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mImageView));
		
		mImageView = VK_NULL_HANDLE;
	}

//}		


	ImageBuffer::operator VkImage() const noexcept
	{
		return mImage;
	}
	
	ImageBuffer::operator VkImageView() const noexcept
	{
		return mImageView;
	}
	
	ImageBuffer::operator VkDeviceMemory() const noexcept
	{
		return mImageMemory;
	}
}

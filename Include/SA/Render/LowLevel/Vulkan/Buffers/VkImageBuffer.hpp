// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_IMAGE_BUFFER_GUARD
#define SAPPHIRE_RENDER_VK_IMAGE_BUFFER_GUARD

#include "VkBufferBase.hpp"
#include "VkImageBufferInfo.hpp"

namespace SA::RND::VK
{
	class Device;

	class ImageBuffer : public BufferBase
	{
		VkImage mImage = VK_NULL_HANDLE;
		VkDeviceMemory mImageMemory = VK_NULL_HANDLE;
	
		VkImageView mImageView = VK_NULL_HANDLE;


	public:
		void Create(const Device& _device, const ImageBufferInfo& _info);
		void CreateFromImage(const Device& _device, VkImage _image, const ImageBufferInfo& _info);
		void Destroy(const Device& _device);

//{ Image

		void CreateVkImage(const Device& _device, const VkImageCreateInfo& _vkInfos);
		void DestroyVkImage(const Device& _device);

//}

//{ ImageView

		void CreateVkImageView(const Device& _device, const VkImageViewCreateInfo& _vkInfos);
		void DestroyVkImageView(const Device& _device);

//}

		operator VkImage() const noexcept;
		operator VkImageView() const noexcept;
		operator VkDeviceMemory() const noexcept;
	};
}

#endif // SAPPHIRE_RENDER_VK_IMAGE_BUFFER_GUARD

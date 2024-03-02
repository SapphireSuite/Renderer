// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Texture/VkCubemap.hpp>

#include <Device/VkDevice.hpp>
#include <VkResourceInitializer.hpp>

#include <Buffers/VkBuffer.hpp>

namespace SA::RND::VK
{
	void Cubemap::Create(const Device& _device, ResourceInitializer& _init, const RawCubemap& _raw)
	{
		// Create resources
		{
			// Texture
			{
				// Image
				{
					VkImageCreateInfo infos{
						.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
						.pNext = nullptr,
						.flags = 0u,
						.imageType = VK_IMAGE_TYPE_3D,
						.format = API_GetFormat(_raw.texture.format),
						.extent = VkExtent3D{ _raw.texture.extents.x, _raw.texture.extents.y, 1 },
						.mipLevels = _raw.texture.mipLevels,
						.arrayLayers = 6u,
						.samples = VK_SAMPLE_COUNT_1_BIT,
						.tiling = VK_IMAGE_TILING_OPTIMAL,
						.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
						.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
						.queueFamilyIndexCount = 0u,
						.pQueueFamilyIndices = nullptr,
						.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
					};

					SA_VK_API(vkCreateImage(_device, &infos, nullptr, &mTextureImage), L"Failed to create cubemap texture image!");
					SA_LOG(L"Cubemap texture image created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mTextureImage));
				}

				// Memory
				{
					VkMemoryRequirements memRequirements;
					vkGetImageMemoryRequirements(_device, mTextureImage, &memRequirements);

					const uint32_t memoryTypeIndex = BufferBase::FindMemoryType(_device, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

					VkMemoryAllocateInfo memoryAllocInfo{};
					memoryAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
					memoryAllocInfo.pNext = nullptr;
					memoryAllocInfo.allocationSize = memRequirements.size;
					memoryAllocInfo.memoryTypeIndex = memoryTypeIndex;

					SA_VK_API(vkAllocateMemory(_device, &memoryAllocInfo, nullptr, &mTextureMemory), L"Failed to allocate cubemap texture memory!");
					SA_LOG(L"Cubemap texture memory created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mTextureMemory));

					SA_VK_API(vkBindImageMemory(_device, mTextureImage, mTextureMemory, 0));
				}
			}

			// Irradiance
			{
				// Image
				{
					VkImageCreateInfo infos{
						.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
						.pNext = nullptr,
						.flags = 0u,
						.imageType = VK_IMAGE_TYPE_3D,
						.format = API_GetFormat(_raw.irradiance.format),
						.extent = VkExtent3D{ _raw.irradiance.extents.x, _raw.irradiance.extents.y, 1 },
						.mipLevels = _raw.irradiance.mipLevels,
						.arrayLayers = 6u,
						.samples = VK_SAMPLE_COUNT_1_BIT,
						.tiling = VK_IMAGE_TILING_OPTIMAL,
						.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
						.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
						.queueFamilyIndexCount = 0u,
						.pQueueFamilyIndices = nullptr,
						.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
					};

					SA_VK_API(vkCreateImage(_device, &infos, nullptr, &mIrradianceImage), L"Failed to create cubemap irradiance image!");
					SA_LOG(L"Cubemap irradiance image created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mIrradianceImage));
				}

				// Memory
				{
					VkMemoryRequirements memRequirements;
					vkGetImageMemoryRequirements(_device, mIrradianceImage, &memRequirements);

					const uint32_t memoryTypeIndex = BufferBase::FindMemoryType(_device, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

					VkMemoryAllocateInfo memoryAllocInfo{};
					memoryAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
					memoryAllocInfo.pNext = nullptr;
					memoryAllocInfo.allocationSize = memRequirements.size;
					memoryAllocInfo.memoryTypeIndex = memoryTypeIndex;

					SA_VK_API(vkAllocateMemory(_device, &memoryAllocInfo, nullptr, &mIrradianceMemory), L"Failed to allocate cubemap irradiance memory!");
					SA_LOG(L"Cubemap irradiance memory created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mIrradianceMemory));

					SA_VK_API(vkBindImageMemory(_device, mIrradianceImage, mIrradianceMemory, 0));
				}
			}
		}


		// Copy data to GPU
		{
			// Transitions Undef to Copy-Dst
			{
				VkImageMemoryBarrier undefToDstBarrier
				{
					.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
					.pNext = nullptr,
					.srcAccessMask = 0,
					.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT,
					.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
					.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
					.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.image = mTextureImage,
					.subresourceRange = VkImageSubresourceRange{
						.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
						.baseMipLevel = 0u,
						.levelCount = _raw.texture.mipLevels,
						.baseArrayLayer = 0u,
						.layerCount = 6u
					}
				};

				VkImageMemoryBarrier undefToDstBarriers[2]{ undefToDstBarrier, undefToDstBarrier };
				undefToDstBarriers[1].image = mIrradianceImage;
				undefToDstBarriers[1].subresourceRange.levelCount = _raw.irradiance.mipLevels;

				SA_VK_API(vkCmdPipelineBarrier(_init.cmd, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 2, undefToDstBarriers));
			}

			// Copy Data
			{
				// Texture
				{
					Buffer& staging = _init.CreateStagingBuffer(_device, _raw.texture.data.size(), _raw.texture.data.data());

					uint64_t offset = 0u;
					VkExtent3D vkExtents{ _raw.texture.extents.x, _raw.texture.extents.y, 1 };
					uint32_t channelNum = API_GetChannelNum(_raw.texture.format);

					std::vector<VkBufferImageCopy> bufferImageCopies;

					for (uint32_t currMipLevel = 0u; currMipLevel < _raw.texture.mipLevels; ++currMipLevel)
					{
						bufferImageCopies.emplace_back(
							VkBufferImageCopy
							{
								.bufferOffset = offset,
								.bufferRowLength = 0,
								.bufferImageHeight = 0,
								.imageSubresource = VkImageSubresourceLayers{
									.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
									.mipLevel = currMipLevel,
									.baseArrayLayer = 0,
									.layerCount = 1u,
								},
								.imageOffset = {0, 0, 0},
								.imageExtent = vkExtents
							}
						);


						offset += vkExtents.width * vkExtents.height * channelNum;

						if (vkExtents.width > 1)
							vkExtents.width >>= 1;

						if (vkExtents.height > 1)
							vkExtents.height >>= 1;
					}

					SA_VK_API(vkCmdCopyBufferToImage(_init.cmd, staging, mTextureImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, static_cast<uint32_t>(bufferImageCopies.size()), bufferImageCopies.data()));
				}

				// Irradiance
				{
					Buffer& staging = _init.CreateStagingBuffer(_device, _raw.irradiance.data.size(), _raw.irradiance.data.data());

					uint64_t offset = 0u;
					VkExtent3D vkExtents{ _raw.irradiance.extents.x, _raw.irradiance.extents.y, 1 };
					uint32_t channelNum = API_GetChannelNum(_raw.irradiance.format);

					std::vector<VkBufferImageCopy> bufferImageCopies;

					for (uint32_t currMipLevel = 0u; currMipLevel < _raw.irradiance.mipLevels; ++currMipLevel)
					{
						bufferImageCopies.emplace_back(
							VkBufferImageCopy
							{
								.bufferOffset = offset,
								.bufferRowLength = 0,
								.bufferImageHeight = 0,
								.imageSubresource = VkImageSubresourceLayers{
									.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
									.mipLevel = currMipLevel,
									.baseArrayLayer = 0,
									.layerCount = 1u,
								},
								.imageOffset = {0, 0, 0},
								.imageExtent = vkExtents
							}
						);


						offset += vkExtents.width * vkExtents.height * channelNum;

						if (vkExtents.width > 1)
							vkExtents.width >>= 1;

						if (vkExtents.height > 1)
							vkExtents.height >>= 1;
					}

					SA_VK_API(vkCmdCopyBufferToImage(_init.cmd, staging, mIrradianceImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, static_cast<uint32_t>(bufferImageCopies.size()), bufferImageCopies.data()));
				}
			}

			// Transitions Copy-Dst to Read-Only
			{
				VkImageMemoryBarrier dstToReadOnlyBarrier
				{
					.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
					.pNext = nullptr,
					.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT,
					.dstAccessMask = VK_ACCESS_SHADER_READ_BIT,
					.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
					.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
					.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.image = mTextureImage,
					.subresourceRange = VkImageSubresourceRange{
						.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
						.baseMipLevel = 0u,
						.levelCount = _raw.texture.mipLevels,
						.baseArrayLayer = 0u,
						.layerCount = 1u
					}
				};

				VkImageMemoryBarrier dstToReadOnlyBarriers[2]{ dstToReadOnlyBarrier, dstToReadOnlyBarrier };
				dstToReadOnlyBarriers[1].image = mIrradianceImage;
				dstToReadOnlyBarriers[1].subresourceRange.levelCount = _raw.irradiance.mipLevels;

				SA_VK_API(vkCmdPipelineBarrier(_init.cmd, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, nullptr, 0, nullptr, 2, dstToReadOnlyBarriers));
			}
		}
	}
	
	void Cubemap::Destroy(const Device& _device)
	{
		// Texture
		{
			SA_VK_API(vkDestroyImage(_device, mTextureImage, nullptr));

			SA_LOG(L"Cubemap texture image destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mTextureImage));

			mTextureImage = VK_NULL_HANDLE;


			// Free memory after destroying image: memory not used anymore.
			SA_VK_API(vkFreeMemory(_device, mTextureMemory, nullptr));

			SA_LOG(L"Cubemap texture memory destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mTextureMemory));

			mTextureMemory = VK_NULL_HANDLE;
		}


		// Irradiance
		{
			SA_VK_API(vkDestroyImage(_device, mIrradianceImage, nullptr));

			SA_LOG(L"Cubemap irradiance image destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mIrradianceImage));

			mIrradianceImage = VK_NULL_HANDLE;


			// Free memory after destroying image: memory not used anymore.
			SA_VK_API(vkFreeMemory(_device, mIrradianceMemory, nullptr));

			SA_LOG(L"Cubemap irradiance memory destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mIrradianceMemory));

			mIrradianceMemory = VK_NULL_HANDLE;
		}
	}
}

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Texture/VkTexture.hpp>

#include <Device/VkDevice.hpp>
#include <VkResourceInitializer.hpp>

#include <Buffers/VkBuffer.hpp>

namespace SA::RND::VK
{
	void Texture::Create(const Device& _device, ResourceInitializer& _init, const RawTexture& _raw)
	{
		// Image
		{
			const VkImageCreateInfo infos{
				.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0u,
				.imageType = VK_IMAGE_TYPE_2D,
				.format = API_GetFormat(_raw.format),
				.extent = VkExtent3D{ _raw.extents.x, _raw.extents.y, 1 },
				.mipLevels = _raw.mipLevels,
				.arrayLayers = 1u,
				.samples = VK_SAMPLE_COUNT_1_BIT,
				.tiling = VK_IMAGE_TILING_OPTIMAL,
				.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
				.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
				.queueFamilyIndexCount = 0u,
				.pQueueFamilyIndices = nullptr,
				.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
			};

			SA_VK_API(vkCreateImage(_device, &infos, nullptr, &mImage), L"Failed to create texture image!");
			SA_LOG(L"Texture image created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mImage));
		}

		// Memory
		{
			VkMemoryRequirements memRequirements;
			vkGetImageMemoryRequirements(_device, mImage, &memRequirements);

			const uint32_t memoryTypeIndex = BufferBase::FindMemoryType(_device, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

			const VkMemoryAllocateInfo memoryAllocInfo{
				.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
				.pNext = nullptr,
				.allocationSize = memRequirements.size,
				.memoryTypeIndex = memoryTypeIndex,
			};

			SA_VK_API(vkAllocateMemory(_device, &memoryAllocInfo, nullptr, &mMemory), L"Failed to allocate texture memory!");
			SA_LOG(L"Texture memory created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mMemory));

			SA_VK_API(vkBindImageMemory(_device, mImage, mMemory, 0));
		}


		// Copy data to GPU
		{
			// Transition Under to Dst
			{
				const VkImageMemoryBarrier undefToDstBarrier
				{
					.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
					.pNext = nullptr,
					.srcAccessMask = 0,
					.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT,
					.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
					.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
					.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.image = mImage,
					.subresourceRange = VkImageSubresourceRange{
						.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
						.baseMipLevel = 0u,
						.levelCount = _raw.mipLevels,
						.baseArrayLayer = 0u,
						.layerCount = 1u
					}
				};

				SA_VK_API(vkCmdPipelineBarrier(_init.cmd, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &undefToDstBarrier));
			}


			// Copy Data
			{
				Buffer& staging = _init.CreateStagingBuffer(_device, _raw.data.size(), _raw.data.data());

				uint64_t offset = 0u;
				VkExtent3D vkExtents{ _raw.extents.x, _raw.extents.y, 1 };
				const uint32_t channelNum = API_GetChannelNum(_raw.format);

				std::vector<VkBufferImageCopy> bufferImageCopies;

				for (uint32_t currMipLevel = 0u; currMipLevel < _raw.mipLevels; ++currMipLevel)
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

				SA_VK_API(vkCmdCopyBufferToImage(_init.cmd, staging, mImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, static_cast<uint32_t>(bufferImageCopies.size()), bufferImageCopies.data()));
			}


			// Transition Dst to Read-Only
			{
				const VkImageMemoryBarrier dstToReadOnlyBarrier
				{
					.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
					.pNext = nullptr,
					.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT,
					.dstAccessMask = VK_ACCESS_SHADER_READ_BIT,
					.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
					.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
					.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.image = mImage,
					.subresourceRange = VkImageSubresourceRange{
						.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
						.baseMipLevel = 0u,
						.levelCount = _raw.mipLevels,
						.baseArrayLayer = 0u,
						.layerCount = 1u
					}
				};

				SA_VK_API(vkCmdPipelineBarrier(_init.cmd, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, nullptr, 0, nullptr, 1, &dstToReadOnlyBarrier));
			}
		}
	}

	void Texture::Destroy(const Device& _device)
	{
		// In case the image was given to the texture (using CreateFromImage).
		if (mMemory != VK_NULL_HANDLE)
		{
			SA_VK_API(vkDestroyImage(_device, mImage, nullptr));

			SA_LOG(L"Texture image destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mImage));

			mImage = VK_NULL_HANDLE;


			// Free memory after destroying image: memory not used anymore.
			SA_VK_API(vkFreeMemory(_device, mMemory, nullptr));

			SA_LOG(L"Texture memory destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mMemory));

			mMemory = VK_NULL_HANDLE;
		}
		else
		{
			// Image owned by Swapchain.
			mImage = VK_NULL_HANDLE;
		}
	}
}

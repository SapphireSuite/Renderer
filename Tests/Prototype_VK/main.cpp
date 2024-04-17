// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Collections/Debug>

#include <SA/Maths/Transform/Transform.hpp>
#include <SA/Maths/Space/Vector4.hpp>

#include <SA/Render/LowLevel/Common/Camera/Camera_GPU.hpp>
#include <SA/Render/LowLevel/Common/Lighting/DirectionalLight_GPU.hpp>
#include <SA/Render/LowLevel/Common/Lighting/PointLight_GPU.hpp>
#include <SA/Render/LowLevel/Common/Mesh/RawStaticMesh.hpp>
#include <SA/Render/LowLevel/Vulkan/VkInstance.hpp>
#include <SA/Render/LowLevel/Vulkan/Device/VkDevice.hpp>
#include <SA/Render/LowLevel/Vulkan/Surface/VkWindowSurface.hpp>
#include <SA/Render/LowLevel/Vulkan/Surface/VkSwapchain.hpp>
#include <SA/Render/LowLevel/Vulkan/Device/Command/VkCommandPool.hpp>
#include <SA/Render/LowLevel/Vulkan/Pass/VkRenderPass.hpp>
#include <SA/Render/LowLevel/Vulkan/Pass/VkFrameBuffer.hpp>
#include <SA/Render/LowLevel/Vulkan/Pipeline/VkPipelineLayout.hpp>
#include <SA/Render/LowLevel/Vulkan/Pipeline/VkPipeline.hpp>
#include <SA/Render/LowLevel/Vulkan/Shader/VkShader.hpp>
#include <SA/Render/LowLevel/Vulkan/Mesh/VkStaticMesh.hpp>
#include <SA/Render/LowLevel/Vulkan/VkResourceInitializer.hpp>
#include <SA/Render/LowLevel/Vulkan/DescriptorSet/VkDescriptorPool.hpp>
#include <SA/Render/ShaderCompiler/ShaderCompiler.hpp>
using namespace SA::RND;

// Must be included after vulkan.
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize2.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

GLFWwindow* window = nullptr;

VK::Instance instance;
VK::WindowSurface winSurface;
VK::Device device;
VK::Swapchain swapchain;
VK::CommandPool cmdPool;
VK::RenderPass depthPrePass;
VK::RenderPass renderPass;
std::vector<VK::FrameBuffer> depthPrepassFrameBuffers;
std::vector<VK::FrameBuffer> frameBuffers;
std::vector<VK::CommandBuffer> cmdBuffers;
VK::Shader buildLightClusterGridShader;
VK::Shader computeActiveLightClustersShader;
VK::Shader buildActiveLightClusterListShader;
VK::Shader depthOnlyVertexShader;
VK::Shader vertexShader;
VK::Shader fragmentShader;
VK::PipelineLayout pipLayout;
VK::Pipeline depthPrepassPipeline;
VK::Pipeline pipeline;
RawStaticMesh sphereRaw;
VK::StaticMesh sphereMesh;
RHI::ShaderDescriptor csBuildLightClusterGridDesc;
RHI::ShaderDescriptor csComputeActiveLightClustersDesc;
RHI::ShaderDescriptor csBuildActiveLightClusterListDesc;
RHI::ShaderDescriptor depthOnlyVsDesc;
RHI::ShaderDescriptor vsDesc;
RHI::ShaderDescriptor fsDesc;
std::vector<VK::Buffer> cameraBuffers;
SA::TransformPRSf cameraTr;
VK::DescriptorPool cameraDescPool;
VK::DescriptorSetLayout cameraDescSetLayout;
std::vector<VK::DescriptorSet> cameraSets;
VK::Buffer objectBuffer;
VK::DescriptorPool objectDescPool;
VK::DescriptorSetLayout objectDescSetLayout;
VK::DescriptorSet objectSet;
VK::Buffer lightClusterInfoBuffer;
VK::Buffer lightClusterGridBuffer;
VK::Buffer activeLightClustersBuffer;
VK::Buffer activeLightClusterListBuffer;
VK::Buffer lightClusterIndirectArgsBuffer;
VK::DescriptorPool lightClusterGridDescPool;
VK::DescriptorSetLayout lightClusterGridDescSetLayout;
VK::DescriptorSet lightClusterGridSet;
VK::PipelineLayout lightClusterGridPipelineLayout;
VK::Pipeline lightClusterGridPipeline;
VK::DescriptorPool activeLightClustersDescPool;
VK::DescriptorSetLayout activeLightClustersDescSetLayout;
VK::DescriptorSet activeLightClustersSet;
VK::DescriptorPool activeLightClusterListDescPool;
VK::DescriptorSetLayout activeLightClusterListDescSetLayout;
VK::DescriptorSet activeLightClusterListSet;
VK::PipelineLayout activeLightClustersPipelineLayout;
VK::Pipeline activeLightClustersPipeline;
VkImageView depthUAV = VK_NULL_HANDLE;
VK::PipelineLayout activeLightClusterListPipelineLayout;
VK::Pipeline activeLightClusterListPipeline;
VK::Buffer pointLightBuffer;
VK::Buffer directionalLightBuffer;
VK::DescriptorPool lightDescPool;
VK::DescriptorSetLayout lightDescSetLayout;
VK::DescriptorSet lightSet;
VK::Texture albedo;
VkImageView albedoSRV = VK_NULL_HANDLE;
VK::Texture normalMap;
VkImageView normalMapSRV = VK_NULL_HANDLE;
VK::Texture metallic;
VkImageView metallicSRV = VK_NULL_HANDLE;
VK::Texture roughness;
VkImageView roughnessSRV = VK_NULL_HANDLE;
VK::DescriptorPool materialDescPool;
VK::DescriptorSetLayout materialDescSetLayout;
VK::DescriptorSet materialSet;
VkSampler sampler;

SA::Vec3ui lightClusterGridSize = { 32, 32, 32 };

struct SceneTexture
{
	VK::Texture color;
	VK::Texture resolvedColor;
	VK::Texture depth;
	VK::Texture resolvedDepth;
};
std::vector<SceneTexture> sceneTextures;

constexpr bool bDepth = true;
constexpr bool bDepthPrepass = true;
constexpr bool bDepthInverted = true;
constexpr bool bMSAA = true;

void GLFWErrorCallback(int32_t error, const char* description)
{
	SA_LOG((L"GLFW Error [%1]: %2", error, description), Error, SA.Render.Proto.GLFW.API);
}

float RandFloat(float min, float max)
{
	return min + static_cast <float> (rand()) / static_cast <float> (RAND_MAX / (max - min));
}

SA::Vec3f RandVec3Position()
{
	return SA::Vec3f(RandFloat(-10, 10), RandFloat(-10, 10), RandFloat(-10, 10));
}

SA::Quatf RandQuat()
{
	return SA::Quatf::FromEuler({ RandFloat(0, 360), RandFloat(0, 360), RandFloat(0, 360) });
}

SA::Vec3f RandVec3Scale()
{
	return SA::Vec3f(RandFloat(0.5, 2.5), RandFloat(0.5, 2.5), RandFloat(0.5, 2.5));
}

SA::Vec3f RandVec3UniScale()
{
	return SA::Vec3f(RandFloat(0.1, 1.5));
}


void Init()
{
	SA::Debug::InitDefaultLogger();

	srand(time(nullptr));

	// GLFW
	{
		glfwSetErrorCallback(GLFWErrorCallback);
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		window = glfwCreateWindow(1200, 900, "Vulkan Prototype", nullptr, nullptr);
		SA_ASSERT((Nullptr, window), SA.Render.Proto.GLFW, L"GLFW create window failed!");
		
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	// Render
	{
		// Instance
		{
			std::vector<const char*> vkExts;

			// Query GLFW extensions.
			{
				uint32_t glfwExtensionCount = 0;
				const char** glfwExtensions = nullptr;

				glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

				vkExts.reserve(glfwExtensionCount);
				vkExts.insert(vkExts.end(), glfwExtensions, glfwExtensions + glfwExtensionCount);
			}

			instance.Create(vkExts);
		}

		VK::DeviceRequirements deviceReqs;

		// Window Surface
		{
			VkSurfaceKHR glfwsurface;
			glfwCreateWindowSurface(instance, window, nullptr, &glfwsurface);
			
			winSurface.Create(std::move(glfwsurface));

			deviceReqs.SetWindowSurface(&winSurface);
		}

		// Device
		{
			std::vector<VK::DeviceInfo> deviceInfos = instance.QueryDeviceInfos(deviceReqs);
			device.Create(deviceInfos[0]);
		}

		// Swapchain
		{
			swapchain.Create(device, winSurface);
		}

		// Cmd Buffers
		{
			cmdPool.Create(device, device.queueMgr.graphics[0].GetFamilyIndex());

			cmdBuffers = cmdPool.AllocateMultiple(device, swapchain.GetImageNum());
		}

		// Window Dependent resources
		{
			uint32_t num = swapchain.GetImageNum();
			sceneTextures.resize(num);
			frameBuffers.resize(num);
			depthPrepassFrameBuffers.resize(num);

			for (uint32_t i = 0; i < num; ++i)
			{
				VK::RenderPassInfo depthOnlyPassInfo;
				VK::RenderPassInfo passInfo;

				// Scene Textures
				{
					auto& sceneTexture = sceneTextures[i];

					SA::RND::VK::TextureDescriptor desc
					{
						.extents = swapchain.GetExtents(),
						.format = swapchain.GetFormat(),
						.sampling = VK_SAMPLE_COUNT_1_BIT,
						.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
						.clearColor = Color{ 0.0f, 0.0f, 0.010f, 0.0f },
					};

					if (bMSAA)
					{
						sceneTexture.resolvedColor.CreateFromImage(swapchain, i);
						passInfo.RegisterRenderTarget(&sceneTexture.resolvedColor, desc);

						desc.sampling = VK_SAMPLE_COUNT_8_BIT;
						sceneTexture.color.Create(device, desc);
						passInfo.RegisterRenderTarget(&sceneTexture.color, desc);
						desc.sampling = VK_SAMPLE_COUNT_1_BIT;
					}
					else
					{
						sceneTexture.color.CreateFromImage(swapchain, i);
						passInfo.RegisterRenderTarget(&sceneTexture.color, desc);
					}

					if (bDepth)
					{
						desc.format = VK_FORMAT_D16_UNORM;
						desc.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
						desc.clearColor = bDepthInverted ? Color{ .r = 0.0f, .g = 0.0f } : Color{ .r = 1.0f, .g = 0.0f };

						if (bMSAA)
						{
							desc.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
							sceneTexture.resolvedDepth.Create(device, desc);
							depthOnlyPassInfo.RegisterRenderTarget(&sceneTexture.resolvedDepth, desc);

							desc.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
							desc.sampling = VK_SAMPLE_COUNT_8_BIT;
							sceneTexture.depth.Create(device, desc);
							passInfo.RegisterRenderTarget(&sceneTexture.depth, desc);
							depthOnlyPassInfo.RegisterRenderTarget(&sceneTexture.depth, desc);
						}
						else
						{
							sceneTexture.depth.Create(device, desc);
							passInfo.RegisterRenderTarget(&sceneTexture.depth, desc);
							depthOnlyPassInfo.RegisterRenderTarget(&sceneTexture.depth, desc);
						}
					}
				}

				// RenderPass
				{
					// Forward
					if (false)
					{
						if (bDepth && bDepthPrepass)
						{
							auto& depthPrepass = passInfo.AddSubpass("Depth-Only Prepass");
							auto& depthRT = depthPrepass.AddAttachment(&sceneTextures[i].depth);
						}

						auto& mainSubpass = passInfo.AddSubpass("Main");

						// Color and present attachment.
						auto& colorRT = mainSubpass.AddAttachment(&sceneTextures[i].color, bMSAA ? &sceneTextures[i].resolvedColor : nullptr);

						if (bDepth)
						{
							// Always add depth, even with depth prepass: set depth as read only.
							auto& depthRT = mainSubpass.AddAttachment(&sceneTextures[i].depth);

							if (bDepthPrepass)
							{
								depthRT.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
								depthRT.accessMode = AttachmentAccessMode::ReadOnly;
							}
						}
					}

					// Forward+
					if (true)
					{
						depthOnlyPassInfo.AddSubpass("Depth-Only Prepass").AddAttachment(&sceneTextures[i].depth, bMSAA ? &sceneTextures[i].resolvedDepth : nullptr);


						auto& mainSubpass = passInfo.AddSubpass("Main");

						auto& colorRT = mainSubpass.AddAttachment(&sceneTextures[i].color, bMSAA ? &sceneTextures[i].resolvedColor : nullptr);
						
						if (bDepth)
						{
							// Always add depth, even with depth prepass: set depth as read only.
							auto& depthRT = mainSubpass.AddAttachment(&sceneTextures[i].depth);

							if (bDepthPrepass)
							{
								depthRT.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
								depthRT.accessMode = AttachmentAccessMode::ReadOnly;
							}
						}
					}

					if (!depthPrePass)
					{
						VkAttachmentDescription2 depthAttachment{};
						depthAttachment.sType = VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2;
						depthAttachment.pNext = nullptr;
						depthAttachment.format = VK_FORMAT_D16_UNORM;
						depthAttachment.samples = VK_SAMPLE_COUNT_8_BIT;
						depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
						depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
						depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
						depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
						depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
						depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;

						// Create resolved depth attachment
						VkAttachmentDescription2 resolvedDepthAttachment{};
						resolvedDepthAttachment.sType = VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2;
						resolvedDepthAttachment.pNext = nullptr;
						resolvedDepthAttachment.format = VK_FORMAT_D16_UNORM;
						resolvedDepthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
						resolvedDepthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
						resolvedDepthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
						resolvedDepthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
						resolvedDepthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
						resolvedDepthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
						resolvedDepthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;

						VkAttachmentReference2 depthAttachmentRef{};
						depthAttachmentRef.sType = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2;
						depthAttachmentRef.pNext = nullptr;
						depthAttachmentRef.attachment = 0;
						depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

						VkAttachmentReference2 resolvedDepthAttachmentRef{};
						resolvedDepthAttachmentRef.sType = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2;
						resolvedDepthAttachmentRef.pNext = nullptr;
						resolvedDepthAttachmentRef.attachment = 1;
						resolvedDepthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

						VkSubpassDescriptionDepthStencilResolve depthResolveInfo{
							.sType = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_DEPTH_STENCIL_RESOLVE,
							.pNext = nullptr,
							.depthResolveMode = VK_RESOLVE_MODE_AVERAGE_BIT,
							.stencilResolveMode = VK_RESOLVE_MODE_AVERAGE_BIT,
							.pDepthStencilResolveAttachment = &resolvedDepthAttachmentRef
						};

						VkSubpassDescription2 subpass{};
						subpass.sType = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2;
						subpass.pNext = &depthResolveInfo;
						subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
						subpass.colorAttachmentCount = 0;
						subpass.pColorAttachments = nullptr;
						subpass.pDepthStencilAttachment = &depthAttachmentRef;
						subpass.pResolveAttachments = nullptr;

						std::vector<VkAttachmentDescription2> attachments = { depthAttachment, resolvedDepthAttachment };

						VkRenderPassCreateInfo2 renderPassInfo{};
						renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2;
						renderPassInfo.pNext = nullptr;
						renderPassInfo.flags = 0;
						renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
						renderPassInfo.pAttachments = attachments.data();
						renderPassInfo.subpassCount = 1;
						renderPassInfo.pSubpasses = &subpass;
						renderPassInfo.dependencyCount = 0;
						renderPassInfo.pDependencies = nullptr;

						depthPrePass.Create(device, renderPassInfo);
					}

					if (!renderPass)
						renderPass.Create(device, passInfo);

					// FrameBuffers
					{
						depthPrepassFrameBuffers[i].Create(device, depthPrePass, depthOnlyPassInfo);
						frameBuffers[i].Create(device, renderPass, passInfo);
					}
				}
			}
		}

		VK::ResourceInitializer init;
		init.Create(device);

		// Mesh
		{
			Assimp::Importer importer;
			
			const aiScene* scene = importer.ReadFile("Resources/Models/Shapes/sphere.obj", aiProcess_CalcTangentSpace);
			const aiMesh* inMesh = scene->mMeshes[0];

			std::vector<SA::Vec3f> vertices;
			vertices.resize(inMesh->mNumVertices);
			std::memcpy(vertices.data(), inMesh->mVertices, inMesh->mNumVertices * sizeof(SA::Vec3f));

			std::vector<SA::Vec3f> normals;
			normals.resize(inMesh->mNumVertices);
			std::memcpy(normals.data(), inMesh->mNormals, inMesh->mNumVertices * sizeof(SA::Vec3f));

			std::vector<SA::Vec3f> tangents;
			tangents.resize(inMesh->mNumVertices);
			std::memcpy(tangents.data(), inMesh->mTangents, inMesh->mNumVertices * sizeof(SA::Vec3f));

			std::vector<SA::Vec2f> uvs;
			uvs.resize(scene->mMeshes[0]->mNumVertices);

			for (auto i = 0; i < inMesh->mNumVertices; ++i)
				uvs[i] = SA::Vec2f(inMesh->mTextureCoords[0][i].x, inMesh->mTextureCoords[0][i].y);

			sphereRaw.vertices.BuildVertexBuffer(
				VertexComponent<SA::Vec3f>{
					"POSITION",
					std::move(vertices)
				},

				VertexComponent<SA::Vec3f>{
					"NORMAL",
					std::move(normals)
				},

				VertexComponent<SA::Vec3f>{
					"TANGENT",
					std::move(tangents)
				},

				VertexComponent<SA::Vec2f>{
					"UV",
					std::move(uvs)
				}
			);


			std::vector<uint16_t> indices;
			indices.resize(inMesh->mNumFaces * 3);

			for (int i = 0; i < inMesh->mNumFaces; ++i)
			{
				indices[i * 3] = inMesh->mFaces[i].mIndices[0];
				indices[i * 3 + 1] = inMesh->mFaces[i].mIndices[1];
				indices[i * 3 + 2] = inMesh->mFaces[i].mIndices[2];
			}

			sphereRaw.indices.U16(std::move(indices));

			sphereMesh.Create(device, init, sphereRaw);


			// Object
			{

				// Instanting
				std::vector<SA::Mat4f> objectsMats;
				objectsMats.resize(100);

				for (auto& mat : objectsMats)
					mat = SA::TransformPRSf(RandVec3Position(), RandQuat(), RandVec3UniScale()).Matrix();

				objectBuffer.Create(device, sizeof(SA::Mat4f) * 100, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
					VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, objectsMats.data());
				

				// DescPool.
				{
					VK::DescriptorPoolInfos info;
					info.poolSizes.emplace_back(VkDescriptorPoolSize{
						.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
						.descriptorCount = 1
						});
					info.setNum = 1;

					objectDescPool.Create(device, info);
				}

				// Layout
				{
					objectDescSetLayout.Create(device,
					{
						{
							.binding = 0,
							.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
							.descriptorCount = 1,
							.stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
							.pImmutableSamplers = nullptr
						}
					});
				}

				// Set
				{
					objectSet = objectDescPool.Allocate(device, objectDescSetLayout);


					VkDescriptorBufferInfo buffInfo;
					buffInfo.buffer = objectBuffer;
					buffInfo.offset = 0;
					buffInfo.range = VK_WHOLE_SIZE;

					VkWriteDescriptorSet write;
					write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
					write.pNext = nullptr;
					write.dstSet = objectSet;
					write.dstBinding = 0;
					write.dstArrayElement = 0;
					write.descriptorCount = 1;
					write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
					write.pBufferInfo = &buffInfo;

					vkUpdateDescriptorSets(device, 1, &write, 0, nullptr);
				}
			}
		}

		// Textures
		{
			stbi_set_flip_vertically_on_load(true);

			// Albedo
			{
				RawTexture raw;
				int32_t channelNum = 0;
				unsigned char* stbiData = stbi_load("Resources/Textures/RustedIron2/rustediron2_basecolor.png",
					reinterpret_cast<int32_t*>(&raw.extents.x),
					reinterpret_cast<int32_t*>(&raw.extents.y),
					&channelNum, 4);

				SA_ASSERT((Nullptr, stbiData), SA.Proto.VK, L"Failed to load 'RustedIron2/rustediron2_basecolor.png'");

				raw.format = Format::R8G8B8A8_SRGB;
				
				const uint32_t dataSize = raw.extents.x * raw.extents.y * 4;
				raw.data.resize(dataSize);
				std::memcpy(raw.data.data(), stbiData, dataSize);

				stbi_image_free(stbiData);

				albedo.Create(device, init, raw);


				// Image View
				{
					const VkImageViewCreateInfo createInfo
					{
						.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
						.pNext = nullptr,
						.flags = 0,
						.image = albedo,
						.viewType = VK_IMAGE_VIEW_TYPE_2D,
						.format = VK::API_GetFormat(raw.format),
						.components = VkComponentMapping{
							.r = VK_COMPONENT_SWIZZLE_IDENTITY,
							.g = VK_COMPONENT_SWIZZLE_IDENTITY,
							.b = VK_COMPONENT_SWIZZLE_IDENTITY,
							.a = VK_COMPONENT_SWIZZLE_IDENTITY,
						},
						.subresourceRange = VkImageSubresourceRange{
							.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
							.baseMipLevel = 0,
							.levelCount = 1,
							.baseArrayLayer = 0,
							.layerCount = 1,
						},
					};

					SA_VK_API(vkCreateImageView(device, &createInfo, nullptr, &albedoSRV));
				}
			}

			// Normal Map
			{
				RawTexture raw;
				int32_t channelNum = 0;
				unsigned char* stbiData = stbi_load("Resources/Textures/RustedIron2/rustediron2_normal.png",
					reinterpret_cast<int32_t*>(&raw.extents.x),
					reinterpret_cast<int32_t*>(&raw.extents.y),
					&channelNum, 4);

				SA_ASSERT((Nullptr, stbiData), SA.Proto.VK, L"Failed to load 'RustedIron2/rustediron2_normal.png'");

				raw.format = Format::R8G8B8A8_UNORM;

				const uint32_t dataSize = raw.extents.x * raw.extents.y * 4;
				raw.data.resize(dataSize);
				std::memcpy(raw.data.data(), stbiData, dataSize);

				stbi_image_free(stbiData);

				normalMap.Create(device, init, raw);


				// Image View
				{
					const VkImageViewCreateInfo createInfo
					{
						.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
						.pNext = nullptr,
						.flags = 0,
						.image = normalMap,
						.viewType = VK_IMAGE_VIEW_TYPE_2D,
						.format = VK::API_GetFormat(raw.format),
						.components = VkComponentMapping{
							.r = VK_COMPONENT_SWIZZLE_IDENTITY,
							.g = VK_COMPONENT_SWIZZLE_IDENTITY,
							.b = VK_COMPONENT_SWIZZLE_IDENTITY,
							.a = VK_COMPONENT_SWIZZLE_IDENTITY,
						},
						.subresourceRange = VkImageSubresourceRange{
							.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
							.baseMipLevel = 0,
							.levelCount = 1,
							.baseArrayLayer = 0,
							.layerCount = 1,
						},
					};

					SA_VK_API(vkCreateImageView(device, &createInfo, nullptr, &normalMapSRV));
				}
			}

			// Metallic
			{
				RawTexture raw;
				int32_t channelNum = 0;
				unsigned char* stbiData = stbi_load("Resources/Textures/RustedIron2/rustediron2_metallic.png",
					reinterpret_cast<int32_t*>(&raw.extents.x),
					reinterpret_cast<int32_t*>(&raw.extents.y),
					&channelNum, 1);

				SA_ASSERT((Nullptr, stbiData), SA.Proto.VK, L"Failed to load 'RustedIron2/rustediron2_metallic.png'");

				raw.format = Format::R8_UNORM;

				const uint32_t dataSize = raw.extents.x * raw.extents.y;
				raw.data.resize(dataSize);
				std::memcpy(raw.data.data(), stbiData, dataSize);

				stbi_image_free(stbiData);

				metallic.Create(device, init, raw);


				// Image View
				{
					const VkImageViewCreateInfo createInfo
					{
						.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
						.pNext = nullptr,
						.flags = 0,
						.image = metallic,
						.viewType = VK_IMAGE_VIEW_TYPE_2D,
						.format = VK::API_GetFormat(raw.format),
						.components = VkComponentMapping{
							.r = VK_COMPONENT_SWIZZLE_IDENTITY,
							.g = VK_COMPONENT_SWIZZLE_IDENTITY,
							.b = VK_COMPONENT_SWIZZLE_IDENTITY,
							.a = VK_COMPONENT_SWIZZLE_IDENTITY,
						},
						.subresourceRange = VkImageSubresourceRange{
							.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
							.baseMipLevel = 0,
							.levelCount = 1,
							.baseArrayLayer = 0,
							.layerCount = 1,
						},
					};

					SA_VK_API(vkCreateImageView(device, &createInfo, nullptr, &metallicSRV));
				}
			}

			// Roughness
			{
				RawTexture raw;
				int32_t channelNum = 0;
				unsigned char* stbiData = stbi_load("Resources/Textures/RustedIron2/rustediron2_roughness.png",
					reinterpret_cast<int32_t*>(&raw.extents.x),
					reinterpret_cast<int32_t*>(&raw.extents.y),
					&channelNum, 1);

				SA_ASSERT((Nullptr, stbiData), SA.Proto.VK, L"Failed to load 'RustedIron2/rustediron2_roughness.png'");

				raw.format = Format::R8_UNORM;

				const uint32_t dataSize = raw.extents.x * raw.extents.y;
				raw.data.resize(dataSize);
				std::memcpy(raw.data.data(), stbiData, dataSize);

				stbi_image_free(stbiData);

				roughness.Create(device, init, raw);


				// Image View
				{
					const VkImageViewCreateInfo createInfo
					{
						.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
						.pNext = nullptr,
						.flags = 0,
						.image = roughness,
						.viewType = VK_IMAGE_VIEW_TYPE_2D,
						.format = VK::API_GetFormat(raw.format),
						.components = VkComponentMapping{
							.r = VK_COMPONENT_SWIZZLE_IDENTITY,
							.g = VK_COMPONENT_SWIZZLE_IDENTITY,
							.b = VK_COMPONENT_SWIZZLE_IDENTITY,
							.a = VK_COMPONENT_SWIZZLE_IDENTITY,
						},
						.subresourceRange = VkImageSubresourceRange{
							.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
							.baseMipLevel = 0,
							.levelCount = 1,
							.baseArrayLayer = 0,
							.layerCount = 1,
						},
					};

					SA_VK_API(vkCreateImageView(device, &createInfo, nullptr, &roughnessSRV));
				}
			}

			// Sampler
			{
				const VkSamplerCreateInfo createInfo{
					.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
					.pNext = nullptr,
					.flags = 0,
					.magFilter = VK_FILTER_LINEAR,
					.minFilter = VK_FILTER_LINEAR,
					.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
					.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
					.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
					.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
					.mipLodBias = 0.0f,
					.anisotropyEnable = VK_TRUE,
					.maxAnisotropy = 16.0f,
					.compareEnable = VK_FALSE,
					.compareOp = VK_COMPARE_OP_ALWAYS,
					.minLod = 0.0f,
					.maxLod = 1.0f,
					.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
					.unnormalizedCoordinates = VK_FALSE,
				};

				SA_VK_API(vkCreateSampler(device, &createInfo, nullptr, &sampler));
			}

			// Descriptor Set
			{
				// Pool
				{
					VK::DescriptorPoolInfos info;
					info.poolSizes.emplace_back(VkDescriptorPoolSize{
						.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
						.descriptorCount = 4
					});
					info.setNum = 1;

					materialDescPool.Create(device, info);
				}

				// Layout
				{
					materialDescSetLayout.Create(device,{
						{
							.binding = 0,
							.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
							.descriptorCount = 1,
							.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
							.pImmutableSamplers = nullptr
						},
						{
							.binding = 1,
							.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
							.descriptorCount = 1,
							.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
							.pImmutableSamplers = nullptr
						},
						{
							.binding = 2,
							.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
							.descriptorCount = 1,
							.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
							.pImmutableSamplers = nullptr
						},
						{
							.binding = 3,
							.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
							.descriptorCount = 1,
							.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
							.pImmutableSamplers = nullptr
						}
					});
				}

				// Set
				{
					materialSet = materialDescPool.Allocate(device, materialDescSetLayout);

					std::vector<VkDescriptorImageInfo> imageInfos;
					imageInfos.reserve(4);

					std::vector<VkWriteDescriptorSet> writes;
					writes.reserve(4);

					// Albedo
					{
						VkDescriptorImageInfo& imageInfo = imageInfos.emplace_back();
						imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
						imageInfo.imageView = albedoSRV;
						imageInfo.sampler = sampler;

						VkWriteDescriptorSet& write = writes.emplace_back();
						write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
						write.pNext = nullptr;
						write.dstSet = materialSet;
						write.dstBinding = 0;
						write.dstArrayElement = 0;
						write.descriptorCount = 1;
						write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
						write.pImageInfo = &imageInfo;
					}


					// Normal Map
					{
						VkDescriptorImageInfo& imageInfo = imageInfos.emplace_back();
						imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
						imageInfo.imageView = normalMapSRV;
						imageInfo.sampler = sampler;

						VkWriteDescriptorSet& write = writes.emplace_back();
						write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
						write.pNext = nullptr;
						write.dstSet = materialSet;
						write.dstBinding = 1;
						write.dstArrayElement = 0;
						write.descriptorCount = 1;
						write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
						write.pImageInfo = &imageInfo;
					}

					// Metallic
					{
						VkDescriptorImageInfo& imageInfo = imageInfos.emplace_back();
						imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
						imageInfo.imageView = metallicSRV;
						imageInfo.sampler = sampler;

						VkWriteDescriptorSet& write = writes.emplace_back();
						write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
						write.pNext = nullptr;
						write.dstSet = materialSet;
						write.dstBinding = 2;
						write.dstArrayElement = 0;
						write.descriptorCount = 1;
						write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
						write.pImageInfo = &imageInfo;
					}

					// Roughness
					{
						VkDescriptorImageInfo& imageInfo = imageInfos.emplace_back();
						imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
						imageInfo.imageView = roughnessSRV;
						imageInfo.sampler = sampler;

						VkWriteDescriptorSet& write = writes.emplace_back();
						write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
						write.pNext = nullptr;
						write.dstSet = materialSet;
						write.dstBinding = 3;
						write.dstArrayElement = 0;
						write.descriptorCount = 1;
						write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
						write.pImageInfo = &imageInfo;
					}

					vkUpdateDescriptorSets(device, (uint32_t)writes.size(), writes.data(), 0, nullptr);
				}
			}
		}

		init.Submit(device);
		init.Destroy(device);

		// Shaders
		{
			ShaderCompiler compiler;

			compiler.Create();	

			// Compute
			{
				// BuildLightClusterGrid
				{
					ShaderCompileInfo csInfo
					{
						.path = L"Resources/Shaders/Passes/LightCulling/BuildLightClusterGrid.hlsl",
						.entrypoint = "main",
						.target = "cs_6_5",
					};

					csInfo.defines.push_back("SA_CAMERA_BUFFER_ID=1");

					ShaderCompileResult csShaderRes = compiler.CompileSPIRV(csInfo);
					csBuildLightClusterGridDesc = csShaderRes.desc;
					buildLightClusterGridShader.Create(device, csShaderRes.rawSPIRV);
				}

				// ComputeActiveLightClusters
				{
					ShaderCompileInfo csInfo
					{
						.path = L"Resources/Shaders/Passes/LightCulling/ComputeActiveLightClusters.hlsl",
						.entrypoint = "main",
						.target = "cs_6_5",
					};

					if (bDepthInverted)
						csInfo.defines.push_back("SA_DEPTH_INVERTED=1");

					csInfo.defines.push_back("SA_CAMERA_BUFFER_ID=1");

					ShaderCompileResult csShaderRes = compiler.CompileSPIRV(csInfo);
					csComputeActiveLightClustersDesc = csShaderRes.desc;
					computeActiveLightClustersShader.Create(device, csShaderRes.rawSPIRV);
				}

				// Build Active Light Cluster List
				{
					ShaderCompileInfo csInfo
					{
						.path = L"Resources/Shaders/Passes/LightCulling/BuildActiveLightClusterList.hlsl",
						.entrypoint = "main",
						.target = "cs_6_5",
					};

					ShaderCompileResult csShaderRes = compiler.CompileSPIRV(csInfo);
					csBuildActiveLightClusterListDesc = csShaderRes.desc;
					buildActiveLightClusterListShader.Create(device, csShaderRes.rawSPIRV);
				}
			}

			// DepthOnly
			{
				ShaderCompileInfo vsInfo
				{
					.path = L"Resources/Shaders/Passes/DepthOnly.hlsl",
					.entrypoint = "mainVS",
					.target = "vs_6_5",
				};

				if (bDepthInverted)
					vsInfo.defines.push_back("SA_DEPTH_INVERTED=1");

				vsInfo.defines.push_back("SA_CAMERA_BUFFER_ID=0");
				vsInfo.defines.push_back("SA_OBJECT_BUFFER_ID=0");

				sphereRaw.vertices.AppendDefines(vsInfo.defines);

				ShaderCompileResult vsShaderRes = compiler.CompileSPIRV(vsInfo);
				depthOnlyVsDesc = vsShaderRes.desc;

				depthOnlyVertexShader.Create(device, vsShaderRes.rawSPIRV);
			}

			// Vertex
			{
				ShaderCompileInfo vsInfo
				{
					.path = L"Resources/Shaders/Passes/MainPass.hlsl",
					.entrypoint = "mainVS",
					.target = "vs_6_5",
				};

				if(bDepthInverted)
					vsInfo.defines.push_back("SA_DEPTH_INVERTED=1");
				
				vsInfo.defines.push_back("SA_CAMERA_BUFFER_ID=0");
				vsInfo.defines.push_back("SA_OBJECT_BUFFER_ID=0");

				vsInfo.defines.push_back("SA_DIRECTIONAL_LIGHT_BUFFER_ID=0");
				vsInfo.defines.push_back("SA_POINT_LIGHT_BUFFER_ID=1");

				vsInfo.defines.push_back("SA_MATERIAL_ALBEDO_ID=0");
				vsInfo.defines.push_back("SA_MATERIAL_NORMAL_MAP_ID=1");
				vsInfo.defines.push_back("SA_MATERIAL_METALLIC_ID=2");
				vsInfo.defines.push_back("SA_MATERIAL_ROUGHNESS_ID=3");

				sphereRaw.vertices.AppendDefines(vsInfo.defines);

				ShaderCompileResult vsShaderRes = compiler.CompileSPIRV(vsInfo);
				vsDesc = vsShaderRes.desc;

				vertexShader.Create(device, vsShaderRes.rawSPIRV);
			}


			// Fragment
			{
				ShaderCompileInfo psInfo
				{
					.path = L"Resources/Shaders/Passes/MainPass.hlsl",
					.entrypoint = "mainPS",
					.target = "ps_6_5",
				};

				psInfo.defines.push_back("SA_CAMERA_BUFFER_ID=0");
				psInfo.defines.push_back("SA_OBJECT_BUFFER_ID=0");

				psInfo.defines.push_back("SA_DIRECTIONAL_LIGHT_BUFFER_ID=0");
				psInfo.defines.push_back("SA_POINT_LIGHT_BUFFER_ID=1");

				psInfo.defines.push_back("SA_MATERIAL_ALBEDO_ID=0");
				psInfo.defines.push_back("SA_MATERIAL_NORMAL_MAP_ID=1");
				psInfo.defines.push_back("SA_MATERIAL_METALLIC_ID=2");
				psInfo.defines.push_back("SA_MATERIAL_ROUGHNESS_ID=3");

				sphereRaw.vertices.AppendDefines(psInfo.defines);

				ShaderCompileResult psShaderRes = compiler.CompileSPIRV(psInfo);
				fsDesc = psShaderRes.desc;

				fragmentShader.Create(device, psShaderRes.rawSPIRV);
			}


			compiler.Destroy();	
		}

		// Camera
		{
			cameraBuffers.resize(swapchain.GetImageNum());

			for (auto& cameraBuffer : cameraBuffers)
			{
				cameraBuffer.Create(device, sizeof(Camera_GPU), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
			}

			// Pool.
			{
				VK::DescriptorPoolInfos info;
				info.poolSizes.emplace_back(VkDescriptorPoolSize{
					.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
					.descriptorCount = 1
					});
				info.setNum = swapchain.GetImageNum();

				cameraDescPool.Create(device, info);
			}

			// Layout
			{
				cameraDescSetLayout.Create(device,
					{
						{
							.binding = 0,
							.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
							.descriptorCount = 1,
							.stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
							.pImmutableSamplers = nullptr
						}
					});
			}


			// Set
			{
				cameraSets = cameraDescPool.Allocate(device,
					std::vector<VK::DescriptorSetLayout>(swapchain.GetImageNum(), cameraDescSetLayout));

				std::vector<VkDescriptorBufferInfo> bufferInfo;
				bufferInfo.reserve(swapchain.GetImageNum());

				std::vector<VkWriteDescriptorSet> writes;
				writes.reserve(swapchain.GetImageNum());

				for (uint32_t i = 0; i < cameraSets.size(); ++i)
				{
					VkDescriptorBufferInfo& buffInfo = bufferInfo.emplace_back();
					buffInfo.buffer = cameraBuffers[i];
					buffInfo.offset = 0;
					buffInfo.range = VK_WHOLE_SIZE;

					VkWriteDescriptorSet& descWrite = writes.emplace_back();
					descWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
					descWrite.pNext = nullptr;
					descWrite.dstSet = cameraSets[i];
					descWrite.dstBinding = 0;
					descWrite.dstArrayElement = 0;
					descWrite.descriptorCount = 1;
					descWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
					descWrite.pBufferInfo = &buffInfo;
				}

				vkUpdateDescriptorSets(device, (uint32_t)writes.size(), writes.data(), 0, nullptr);
			}
		}

		// Light
		{
			// Directional Light buffer
			{
				DirectionalLight_GPU light;
				light.direction = SA::Vec3f{ RandFloat(0.0f, 1.0f), RandFloat(0.0f, 1.0f), RandFloat(0.0f, 1.0f) };
				light.color = SA::Vec3f{ RandFloat(0.0f, 1.0f), RandFloat(0.0f, 1.0f), RandFloat(0.0f, 1.0f) };
				light.intensity = RandFloat(0.0f, 10.0f);

				directionalLightBuffer.Create(device, sizeof(DirectionalLight_GPU), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
										VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &light);
			}

			// Point lights Buffer
			{
				std::vector<PointLight_GPU> pointLights;
				pointLights.reserve(10);

				for (uint32_t i = 0; i < 10; ++i)
				{
					PointLight_GPU light;
					light.position = RandVec3Position();
					light.color = SA::Vec3f{ RandFloat(0.0f, 1.0f), RandFloat(0.0f, 1.0f), RandFloat(0.0f, 1.0f) };
					light.intensity = RandFloat(0.0f, 10.0f);
					light.radius = RandFloat(0.0f, 10.0f);

					pointLights.push_back(light);
				}

				pointLightBuffer.Create(device, sizeof(PointLight_GPU) * 10, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
										VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, pointLights.data());
			}


			// DescPool.
			{
				VK::DescriptorPoolInfos info;
				info.poolSizes.emplace_back(VkDescriptorPoolSize{
					.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
					.descriptorCount = 2
					});
				info.setNum = 1;

				lightDescPool.Create(device, info);
			}

			// Layout
			{
				lightDescSetLayout.Create(device,
				{
					{
						.binding = 0,
						.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
						.descriptorCount = 1,
						.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
						.pImmutableSamplers = nullptr
					},
					{
						.binding = 1,
						.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
						.descriptorCount = 1,
						.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
						.pImmutableSamplers = nullptr
					}
				});
			}

			// Set
			{
				lightSet = lightDescPool.Allocate(device, lightDescSetLayout);

				std::vector<VkDescriptorBufferInfo> bufferInfos;
				bufferInfos.reserve(2);

				std::vector<VkWriteDescriptorSet> writes;
				writes.reserve(2);

				// Directional Light
				{
					VkDescriptorBufferInfo& buffInfo = bufferInfos.emplace_back();
					buffInfo.buffer = directionalLightBuffer;
					buffInfo.offset = 0;
					buffInfo.range = VK_WHOLE_SIZE;

					VkWriteDescriptorSet& descWrite = writes.emplace_back();
					descWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
					descWrite.pNext = nullptr;
					descWrite.dstSet = lightSet;
					descWrite.dstBinding = 0;
					descWrite.dstArrayElement = 0;
					descWrite.descriptorCount = 1;
					descWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
					descWrite.pBufferInfo = &buffInfo;
				}

				// Point Lights
				{
					VkDescriptorBufferInfo& buffInfo = bufferInfos.emplace_back();
					buffInfo.buffer = pointLightBuffer;
					buffInfo.offset = 0;
					buffInfo.range = VK_WHOLE_SIZE;

					VkWriteDescriptorSet& descWrite = writes.emplace_back();
					descWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
					descWrite.pNext = nullptr;
					descWrite.dstSet = lightSet;
					descWrite.dstBinding = 1;
					descWrite.dstArrayElement = 0;
					descWrite.descriptorCount = 1;
					descWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
					descWrite.pBufferInfo = &buffInfo;
				}

				vkUpdateDescriptorSets(device, (uint32_t)writes.size(), writes.data(), 0, nullptr);
			}
		}

		// Pipeline layout
		{
			std::vector<VkDescriptorSetLayout> setLayouts{
				static_cast<VkDescriptorSetLayout>(cameraDescSetLayout),
				static_cast<VkDescriptorSetLayout>(objectDescSetLayout),
				static_cast<VkDescriptorSetLayout>(lightDescSetLayout),
				static_cast<VkDescriptorSetLayout>(materialDescSetLayout),
			};

			VkPipelineLayoutCreateInfo info{};
			info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			info.pNext = nullptr;
			info.flags = 0u;
			info.setLayoutCount = static_cast<uint32_t>(setLayouts.size());
			info.pSetLayouts = setLayouts.data();
			info.pushConstantRangeCount = 0;
			info.pPushConstantRanges = nullptr;

			pipLayout.Create(device, info);
		}

		// Pipeline
		{
			std::vector<VkPipelineShaderStageCreateInfo> shaderStages{
				{
					.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
					.pNext = nullptr,
					.flags = 0u,
					.stage = VK::API_GetShaderStage(vsDesc.stage),
					.module = vertexShader,
					.pName = vsDesc.entrypoint.c_str(),
					.pSpecializationInfo = nullptr
				},
				{
					.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
					.pNext = nullptr,
					.flags = 0u,
					.stage = VK::API_GetShaderStage(fsDesc.stage),
					.module = fragmentShader,
					.pName = fsDesc.entrypoint.c_str(),
					.pSpecializationInfo = nullptr
				}
			};

			auto vertInputState = vsDesc.MakeVkVertexInputStateInfoSingleVertexBuffer();
			VkPipelineVertexInputStateCreateInfo vkVertInputState = vertInputState.MakeVkInfo();

			VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo{
				.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0,
				.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
				.primitiveRestartEnable = VK_FALSE
			};

			VkViewport viewport{
				.x = 0.0f,
				.y = 900.0f,
				.width = 1200.0f,
				.height = -900.0f,
				.minDepth = 0.0f,
				.maxDepth = 1.0f,
			};

			VkRect2D scissor{
				.offset = VkOffset2D{ 0, 0 },
				.extent = VkExtent2D{ 1200, 900 },
			};

			VkPipelineViewportStateCreateInfo viewportStateInfo{
				.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0u,
				.viewportCount = 1u,
				.pViewports = &viewport,
				.scissorCount = 1u,
				.pScissors = &scissor,
			};

			VkPipelineRasterizationStateCreateInfo rasterizerInfo{
				.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0u,
				.depthClampEnable = VK_FALSE,
				.rasterizerDiscardEnable = VK_FALSE,
				.polygonMode = VK_POLYGON_MODE_FILL,
				.cullMode = VK_CULL_MODE_BACK_BIT,
				.frontFace = VK_FRONT_FACE_CLOCKWISE,
				.depthBiasEnable = VK_FALSE,
				.depthBiasConstantFactor = 0.0f,
				.depthBiasClamp = 0.0f,
				.depthBiasSlopeFactor = 0.0f,
				.lineWidth = 1.0f,
			};


			VkPipelineMultisampleStateCreateInfo multisamplingInfos{
				.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0u,
				.rasterizationSamples = bMSAA ? VK_SAMPLE_COUNT_8_BIT : VK_SAMPLE_COUNT_1_BIT,
				.sampleShadingEnable = bMSAA,
				.minSampleShading = 0.2f,
				.pSampleMask = nullptr,
				.alphaToCoverageEnable = VK_FALSE,
				.alphaToOneEnable = VK_FALSE,
			};

			VkPipelineDepthStencilStateCreateInfo depthStencilInfo{
				.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0u,
				.depthTestEnable = VK_TRUE,
				.depthWriteEnable = bDepthPrepass ? VK_FALSE : VK_TRUE,
				.depthCompareOp = bDepthInverted ? VK_COMPARE_OP_GREATER_OR_EQUAL : VK_COMPARE_OP_LESS_OR_EQUAL,
				.depthBoundsTestEnable = VK_FALSE,
				.stencilTestEnable = VK_FALSE,
				.front = {},
				.back = {},
				.minDepthBounds = 0.0f,
				.maxDepthBounds = 1.0f,
			};

			VkPipelineColorBlendAttachmentState colorBlendAttachment{
				.blendEnable = VK_TRUE,
				.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
				.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
				.colorBlendOp = VK_BLEND_OP_ADD,
				.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
				.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
				.alphaBlendOp = VK_BLEND_OP_ADD,
				.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
			};

			VkPipelineColorBlendStateCreateInfo colorBlendingInfo{
				.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0u,
				.logicOpEnable = VK_FALSE,
				.logicOp = VK_LOGIC_OP_COPY,
				.attachmentCount = 1,
				.pAttachments = &colorBlendAttachment,
				.blendConstants = {0, 0, 0, 0},
			};


			VkGraphicsPipelineCreateInfo pipelineCreateInfo{
				.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
				.pNext = nullptr,
				.flags = 0u,
				.stageCount = static_cast<uint32_t>(shaderStages.size()),
				.pStages = shaderStages.data(),
				.pVertexInputState = &vkVertInputState,
				.pInputAssemblyState = &inputAssemblyInfo,
				.pTessellationState = nullptr,
				.pViewportState = &viewportStateInfo,
				.pRasterizationState = &rasterizerInfo,
				.pMultisampleState = &multisamplingInfos,
				.pDepthStencilState = &depthStencilInfo,
				.pColorBlendState = &colorBlendingInfo,
				.pDynamicState = nullptr,
				.layout = pipLayout,
				.renderPass = renderPass,
				.subpass = /*bDepthPrepass ? 1 : */0,
				.basePipelineHandle = VK_NULL_HANDLE,
				.basePipelineIndex = -1,
			};

			pipeline.Create(device, pipelineCreateInfo);

			if (bDepthPrepass)
			{
				depthStencilInfo.depthWriteEnable = VK_TRUE;

				std::vector<VkPipelineShaderStageCreateInfo> depthOnlyShaderStages{
					{
						.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
						.pNext = nullptr,
						.flags = 0u,
						.stage = VK::API_GetShaderStage(depthOnlyVsDesc.stage),
						.module = depthOnlyVertexShader,
						.pName = depthOnlyVsDesc.entrypoint.c_str(),
						.pSpecializationInfo = nullptr
					}
				};

				VkGraphicsPipelineCreateInfo depthPrepassPipelineCreateInfo{
					.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
					.pNext = nullptr,
					.flags = 0u,
					.stageCount = 1, // only vertex shader.
					.pStages = depthOnlyShaderStages.data(),
					.pVertexInputState = &vkVertInputState,
					.pInputAssemblyState = &inputAssemblyInfo,
					.pTessellationState = nullptr,
					.pViewportState = &viewportStateInfo,
					.pRasterizationState = &rasterizerInfo,
					.pMultisampleState = &multisamplingInfos,
					.pDepthStencilState = &depthStencilInfo,
					.pColorBlendState = &colorBlendingInfo,
					.pDynamicState = nullptr,
					.layout = pipLayout,
					.renderPass = depthPrePass,
					.subpass = 0,
					.basePipelineHandle = VK_NULL_HANDLE,
					.basePipelineIndex = -1,
				};

				depthPrepassPipeline.Create(device, depthPrepassPipelineCreateInfo);
			}
		}

		// Light Culling
		{
			// LightClusterInfo
			{
				struct LightClusterInfo
				{
					SA::Vec3ui gridSize;

					float clusterSize;
					float clusterBias;
				};

				LightClusterInfo lightClusterInfo{
					.gridSize = lightClusterGridSize,
					.clusterSize = lightClusterGridSize.z / std::logf(1000.0f / 0.1f),
					.clusterBias = lightClusterGridSize.z * std::logf(0.1f) / std::logf(1000.0f/0.1f),
				};

				lightClusterInfoBuffer.Create(device, 2 * sizeof(float) + 3 * sizeof(uint32_t), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
										VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &lightClusterInfo);
			}

			// LightClusterGrid
			{
				lightClusterGridBuffer.Create(device, 2 * sizeof(SA::Vec4f) * lightClusterGridSize.x * lightClusterGridSize.y * lightClusterGridSize.z, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
					VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

				// DescPool.
				{
					VK::DescriptorPoolInfos info;
					info.poolSizes.emplace_back(VkDescriptorPoolSize{
						.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
						.descriptorCount = 2
						});
					info.poolSizes.emplace_back(VkDescriptorPoolSize{
						.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
						.descriptorCount = 1
						});
					info.setNum = 1;

					lightClusterGridDescPool.Create(device, info);
				}

				// Layout
				{
					lightClusterGridDescSetLayout.Create(device,
						{
							{
								.binding = 0,
								.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
								.descriptorCount = 1,
								.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT,
								.pImmutableSamplers = nullptr
							},
							{
								.binding = 1,
								.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
								.descriptorCount = 1,
								.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT,
								.pImmutableSamplers = nullptr
							},
							{
								.binding = 2,
								.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
								.descriptorCount = 1,
								.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT,
								.pImmutableSamplers = nullptr
							}
						});
				}

				// Set
				{
					lightClusterGridSet = lightClusterGridDescPool.Allocate(device, lightClusterGridDescSetLayout);

					std::vector<VkDescriptorBufferInfo> bufferInfos;
					bufferInfos.reserve(3);

					std::vector<VkWriteDescriptorSet> writes;
					writes.reserve(3);

					// LightCluserInfo
					{
						VkDescriptorBufferInfo& buffInfo = bufferInfos.emplace_back();
						buffInfo.buffer = lightClusterInfoBuffer;
						buffInfo.offset = 0;
						buffInfo.range = VK_WHOLE_SIZE;

						VkWriteDescriptorSet& descWrite = writes.emplace_back();
						descWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
						descWrite.pNext = nullptr;
						descWrite.dstSet = lightClusterGridSet;
						descWrite.dstBinding = 0;
						descWrite.dstArrayElement = 0;
						descWrite.descriptorCount = 1;
						descWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
						descWrite.pBufferInfo = &buffInfo;
					}

					// Camera buffer
					{
						VkDescriptorBufferInfo& buffInfo = bufferInfos.emplace_back();
						buffInfo.buffer = cameraBuffers[0];
						buffInfo.offset = 0;
						buffInfo.range = VK_WHOLE_SIZE;

						VkWriteDescriptorSet& descWrite = writes.emplace_back();
						descWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
						descWrite.pNext = nullptr;
						descWrite.dstSet = lightClusterGridSet;
						descWrite.dstBinding = 1;
						descWrite.dstArrayElement = 0;
						descWrite.descriptorCount = 1;
						descWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
						descWrite.pBufferInfo = &buffInfo;
					}

					// Output ClusterGrid
					{
						VkDescriptorBufferInfo& buffInfo = bufferInfos.emplace_back();
						buffInfo.buffer = lightClusterGridBuffer;
						buffInfo.offset = 0;
						buffInfo.range = VK_WHOLE_SIZE;

						VkWriteDescriptorSet& descWrite = writes.emplace_back();
						descWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
						descWrite.pNext = nullptr;
						descWrite.dstSet = lightClusterGridSet;
						descWrite.dstBinding = 2;
						descWrite.dstArrayElement = 0;
						descWrite.descriptorCount = 1;
						descWrite.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
						descWrite.pBufferInfo = &buffInfo;
					}

					vkUpdateDescriptorSets(device, (uint32_t)writes.size(), writes.data(), 0, nullptr);
				}

				// Pipeline Layout
				{
					std::vector<VkDescriptorSetLayout> setLayouts{
						static_cast<VkDescriptorSetLayout>(lightClusterGridDescSetLayout),
					};

					VkPipelineLayoutCreateInfo info{
						.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
						.pNext = nullptr,
						.flags = 0u,
						.setLayoutCount = static_cast<uint32_t>(setLayouts.size()),
						.pSetLayouts = setLayouts.data(),
						.pushConstantRangeCount = 0,
						.pPushConstantRanges = nullptr,
					};

					lightClusterGridPipelineLayout.Create(device, info);
				}

				// Pipeline
				{
					VkPipelineShaderStageCreateInfo shaderStage{
						.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
						.pNext = nullptr,
						.flags = 0u,
						.stage = VK_SHADER_STAGE_COMPUTE_BIT,
						.module = buildLightClusterGridShader,
						.pName = csBuildLightClusterGridDesc.entrypoint.c_str(),
						.pSpecializationInfo = nullptr
					};

					VkComputePipelineCreateInfo pipelineInfo{
						.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
						.pNext = nullptr,
						.flags = 0u,
						.stage = shaderStage,
						.layout = lightClusterGridPipelineLayout,
						.basePipelineHandle = VK_NULL_HANDLE,
						.basePipelineIndex = -1,
					};

					lightClusterGridPipeline.Create(device, pipelineInfo);
				}
			}

			// ActiveLightCluster
			{
				activeLightClustersBuffer.Create(device, lightClusterGridSize.x * lightClusterGridSize.y * lightClusterGridSize.z * sizeof(bool), VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
					VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

				// Depth texture ImageView
				{
					const VkImageViewCreateInfo createInfo
					{
						.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
						.pNext = nullptr,
						.flags = 0,
						.image = sceneTextures[0].resolvedDepth, // TODO: use triple buffering.
						.viewType = VK_IMAGE_VIEW_TYPE_2D,
						.format = VK_FORMAT_D16_UNORM,
						.components = VkComponentMapping{
							.r = VK_COMPONENT_SWIZZLE_IDENTITY,
							.g = VK_COMPONENT_SWIZZLE_IDENTITY,
							.b = VK_COMPONENT_SWIZZLE_IDENTITY,
							.a = VK_COMPONENT_SWIZZLE_IDENTITY,
						},
						.subresourceRange = VkImageSubresourceRange{
							.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT,
							.baseMipLevel = 0,
							.levelCount = 1,
							.baseArrayLayer = 0,
							.layerCount = 1,
						},
					};

					SA_VK_API(vkCreateImageView(device, &createInfo, nullptr, &depthUAV));
				}

				// DescPool.
				{
					VK::DescriptorPoolInfos info;
					info.poolSizes.emplace_back(VkDescriptorPoolSize{
						.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
						.descriptorCount = 2
						});
					info.poolSizes.emplace_back(VkDescriptorPoolSize{
						.type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
						.descriptorCount = 1
						});
					info.poolSizes.emplace_back(VkDescriptorPoolSize{
						.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
						.descriptorCount = 1
						});
					info.setNum = 1;

					activeLightClustersDescPool.Create(device, info);
				}

				// Layout
				{
					activeLightClustersDescSetLayout.Create(device,
						{
							{
								.binding = 0,
								.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
								.descriptorCount = 1,
								.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT,
								.pImmutableSamplers = nullptr
							},
							{
								.binding = 1,
								.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
								.descriptorCount = 1,
								.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT,
								.pImmutableSamplers = nullptr
							},
							{
								.binding = 2,
								.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
								.descriptorCount = 1,
								.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT,
								.pImmutableSamplers = nullptr
							},
							{
								.binding = 3,
								.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
								.descriptorCount = 1,
								.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT,
								.pImmutableSamplers = nullptr
							}
						});
				}

				// Set
				{
					activeLightClustersSet = activeLightClustersDescPool.Allocate(device, activeLightClustersDescSetLayout);

					std::vector<VkDescriptorImageInfo> imageInfos;
					imageInfos.reserve(1);

					std::vector<VkDescriptorBufferInfo> bufferInfos;
					bufferInfos.reserve(3);

					std::vector<VkWriteDescriptorSet> writes;
					writes.reserve(4);

					// LightCluserInfo
					{
						VkDescriptorBufferInfo& buffInfo = bufferInfos.emplace_back();
						buffInfo.buffer = lightClusterInfoBuffer;
						buffInfo.offset = 0;
						buffInfo.range = VK_WHOLE_SIZE;

						VkWriteDescriptorSet& descWrite = writes.emplace_back();
						descWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
						descWrite.pNext = nullptr;
						descWrite.dstSet = activeLightClustersSet;
						descWrite.dstBinding = 0;
						descWrite.dstArrayElement = 0;
						descWrite.descriptorCount = 1;
						descWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
						descWrite.pBufferInfo = &buffInfo;
					}

					// Camera buffer
					{
						VkDescriptorBufferInfo& buffInfo = bufferInfos.emplace_back();
						buffInfo.buffer = cameraBuffers[0];
						buffInfo.offset = 0;
						buffInfo.range = VK_WHOLE_SIZE;

						VkWriteDescriptorSet& descWrite = writes.emplace_back();
						descWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
						descWrite.pNext = nullptr;
						descWrite.dstSet = activeLightClustersSet;
						descWrite.dstBinding = 1;
						descWrite.dstArrayElement = 0;
						descWrite.descriptorCount = 1;
						descWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
						descWrite.pBufferInfo = &buffInfo;
					}

					// Depth texture
					{
						VkDescriptorImageInfo& imageInfo = imageInfos.emplace_back();
						imageInfo.imageLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
						imageInfo.imageView = depthUAV;

						VkWriteDescriptorSet& write = writes.emplace_back();
						write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
						write.pNext = nullptr;
						write.dstSet = activeLightClustersSet;
						write.dstBinding = 2;
						write.dstArrayElement = 0;
						write.descriptorCount = 1;
						write.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
						write.pImageInfo = &imageInfo;
					}

					// Output Active Clusters
					{
						VkDescriptorBufferInfo& buffInfo = bufferInfos.emplace_back();
						buffInfo.buffer = activeLightClustersBuffer;
						buffInfo.offset = 0;
						buffInfo.range = VK_WHOLE_SIZE;

						VkWriteDescriptorSet& descWrite = writes.emplace_back();
						descWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
						descWrite.pNext = nullptr;
						descWrite.dstSet = activeLightClustersSet;
						descWrite.dstBinding = 3;
						descWrite.dstArrayElement = 0;
						descWrite.descriptorCount = 1;
						descWrite.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
						descWrite.pBufferInfo = &buffInfo;
					}

					vkUpdateDescriptorSets(device, (uint32_t)writes.size(), writes.data(), 0, nullptr);
				}

				// PipelineLayout
				{
					std::vector<VkDescriptorSetLayout> setLayouts{
						static_cast<VkDescriptorSetLayout>(activeLightClustersDescSetLayout),
					};

					VkPipelineLayoutCreateInfo info{
						.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
						.pNext = nullptr,
						.flags = 0u,
						.setLayoutCount = static_cast<uint32_t>(setLayouts.size()),
						.pSetLayouts = setLayouts.data(),
						.pushConstantRangeCount = 0,
						.pPushConstantRanges = nullptr,
					};

					activeLightClustersPipelineLayout.Create(device, info);
				}

				// Pipeline
				{
					VkPipelineShaderStageCreateInfo shaderStage{
						.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
						.pNext = nullptr,
						.flags = 0u,
						.stage = VK_SHADER_STAGE_COMPUTE_BIT,
						.module = computeActiveLightClustersShader,
						.pName = csComputeActiveLightClustersDesc.entrypoint.c_str(),
						.pSpecializationInfo = nullptr
					};

					VkComputePipelineCreateInfo pipelineInfo{
						.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
						.pNext = nullptr,
						.flags = 0u,
						.stage = shaderStage,
						.layout = activeLightClustersPipelineLayout,
						.basePipelineHandle = VK_NULL_HANDLE,
						.basePipelineIndex = -1,
					};

					activeLightClustersPipeline.Create(device, pipelineInfo);
				}
			}
		}

		// Active Light Cluster List
		{
			activeLightClusterListBuffer.Create(device, lightClusterGridSize.x * lightClusterGridSize.y * lightClusterGridSize.z * sizeof(uint32_t), VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
											VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

			lightClusterIndirectArgsBuffer.Create(device, sizeof(uint32_t) * 3, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT,
				VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

			// DescPool.
			{
				VK::DescriptorPoolInfos info;
				info.poolSizes.emplace_back(VkDescriptorPoolSize{
					.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
					.descriptorCount = 3
					});
				info.poolSizes.emplace_back(VkDescriptorPoolSize{
					.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
					.descriptorCount = 1
					});
				info.setNum = 1;

				activeLightClusterListDescPool.Create(device, info);
			}

			// Layout
			{
				activeLightClusterListDescSetLayout.Create(device,
					{
						{
							.binding = 0,
							.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
							.descriptorCount = 1,
							.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT,
							.pImmutableSamplers = nullptr
						},
						{
							.binding = 1,
							.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
							.descriptorCount = 1,
							.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT,
							.pImmutableSamplers = nullptr
						},
						{
							.binding = 2,
							.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
							.descriptorCount = 1,
							.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT,
							.pImmutableSamplers = nullptr
						},
						{
							.binding = 3,
							.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
							.descriptorCount = 1,
							.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT,
							.pImmutableSamplers = nullptr
						}
					});
			}

			// Set
			{
				activeLightClusterListSet = activeLightClusterListDescPool.Allocate(device, activeLightClusterListDescSetLayout);

				std::vector<VkDescriptorBufferInfo> bufferInfos;
				bufferInfos.reserve(4);

				std::vector<VkWriteDescriptorSet> writes;
				writes.reserve(4);

				// Info Buffer
				{
					VkDescriptorBufferInfo& buffInfo = bufferInfos.emplace_back();
					buffInfo.buffer = lightClusterInfoBuffer;
					buffInfo.offset = 0;
					buffInfo.range = VK_WHOLE_SIZE;

					VkWriteDescriptorSet& descWrite = writes.emplace_back();
					descWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
					descWrite.pNext = nullptr;
					descWrite.dstSet = activeLightClusterListSet;
					descWrite.dstBinding = 0;
					descWrite.dstArrayElement = 0;
					descWrite.descriptorCount = 1;
					descWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
					descWrite.pBufferInfo = &buffInfo;
				}

				// Active Light Clusters
				{
					VkDescriptorBufferInfo& buffInfo = bufferInfos.emplace_back();
					buffInfo.buffer = activeLightClustersBuffer;
					buffInfo.offset = 0;
					buffInfo.range = VK_WHOLE_SIZE;

					VkWriteDescriptorSet& descWrite = writes.emplace_back();
					descWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
					descWrite.pNext = nullptr;
					descWrite.dstSet = activeLightClusterListSet;
					descWrite.dstBinding = 1;
					descWrite.dstArrayElement = 0;
					descWrite.descriptorCount = 1;
					descWrite.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
					descWrite.pBufferInfo = &buffInfo;
				}

				// Indirect Cmd buffer
				{
					VkDescriptorBufferInfo& buffInfo = bufferInfos.emplace_back();
					buffInfo.buffer = lightClusterIndirectArgsBuffer;
					buffInfo.offset = 0;
					buffInfo.range = VK_WHOLE_SIZE;

					VkWriteDescriptorSet& descWrite = writes.emplace_back();
					descWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
					descWrite.pNext = nullptr;
					descWrite.dstSet = activeLightClusterListSet;
					descWrite.dstBinding = 2;
					descWrite.dstArrayElement = 0;
					descWrite.descriptorCount = 1;
					descWrite.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
					descWrite.pBufferInfo = &buffInfo;
				}

				// Active List buffer
				{
					VkDescriptorBufferInfo& buffInfo = bufferInfos.emplace_back();
					buffInfo.buffer = activeLightClusterListBuffer;
					buffInfo.offset = 0;
					buffInfo.range = VK_WHOLE_SIZE;

					VkWriteDescriptorSet& descWrite = writes.emplace_back();
					descWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
					descWrite.pNext = nullptr;
					descWrite.dstSet = activeLightClusterListSet;
					descWrite.dstBinding = 3;
					descWrite.dstArrayElement = 0;
					descWrite.descriptorCount = 1;
					descWrite.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
					descWrite.pBufferInfo = &buffInfo;
				}

				vkUpdateDescriptorSets(device, (uint32_t)writes.size(), writes.data(), 0, nullptr);
			}

			// PipelineLayout
			{
				std::vector<VkDescriptorSetLayout> setLayouts{
					static_cast<VkDescriptorSetLayout>(activeLightClusterListDescSetLayout),
				};

				VkPipelineLayoutCreateInfo info{
					.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
					.pNext = nullptr,
					.flags = 0u,
					.setLayoutCount = static_cast<uint32_t>(setLayouts.size()),
					.pSetLayouts = setLayouts.data(),
					.pushConstantRangeCount = 0,
					.pPushConstantRanges = nullptr,
				};

				activeLightClusterListPipelineLayout.Create(device, info);
			}

			// Pipeline
			{
				VkPipelineShaderStageCreateInfo shaderStage{
					.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
					.pNext = nullptr,
					.flags = 0u,
					.stage = VK_SHADER_STAGE_COMPUTE_BIT,
					.module = buildActiveLightClusterListShader,
					.pName = csBuildActiveLightClusterListDesc.entrypoint.c_str(),
					.pSpecializationInfo = nullptr
				};

				VkComputePipelineCreateInfo pipelineInfo{
					.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
					.pNext = nullptr,
					.flags = 0u,
					.stage = shaderStage,
					.layout = activeLightClusterListPipelineLayout,
					.basePipelineHandle = VK_NULL_HANDLE,
					.basePipelineIndex = -1,
				};

				activeLightClusterListPipeline.Create(device, pipelineInfo);
			}
		}
	}
}

void Uninit()
{
	// Render
	{
		device.WaitIdle();

		pipeline.Destroy(device);
		depthPrepassPipeline.Destroy(device);
		pipLayout.Destroy(device);

		fragmentShader.Destroy(device);
		vertexShader.Destroy(device);
		depthOnlyVertexShader.Destroy(device);
		buildLightClusterGridShader.Destroy(device);
		computeActiveLightClustersShader.Destroy(device);
		buildActiveLightClusterListShader.Destroy(device);

		sphereMesh.Destroy(device);

		for (auto& cameraBuffer : cameraBuffers)
			cameraBuffer.Destroy(device);

		cameraDescSetLayout.Destroy(device);
		cameraDescPool.Destroy(device);

		objectBuffer.Destroy(device);
		objectDescSetLayout.Destroy(device);
		objectDescPool.Destroy(device);

		albedo.Destroy(device);
		vkDestroyImageView(device, albedoSRV, nullptr);
		normalMap.Destroy(device);
		vkDestroyImageView(device, normalMapSRV, nullptr);
		metallic.Destroy(device);
		vkDestroyImageView(device, metallicSRV, nullptr);
		roughness.Destroy(device);
		vkDestroyImageView(device, roughnessSRV, nullptr);
		vkDestroySampler(device, sampler, nullptr);
		materialDescSetLayout.Destroy(device);
		materialDescPool.Destroy(device);

		pointLightBuffer.Destroy(device);
		directionalLightBuffer.Destroy(device);
		lightDescSetLayout.Destroy(device);
		lightDescPool.Destroy(device);

		lightClusterInfoBuffer.Destroy(device);
		lightClusterGridBuffer.Destroy(device);
		lightClusterGridDescSetLayout.Destroy(device);
		lightClusterGridDescPool.Destroy(device);
		lightClusterGridPipelineLayout.Destroy(device);
		lightClusterGridPipeline.Destroy(device);

		activeLightClustersBuffer.Destroy(device);
		activeLightClustersDescSetLayout.Destroy(device);
		activeLightClustersDescPool.Destroy(device);
		activeLightClustersPipelineLayout.Destroy(device);
		activeLightClustersPipeline.Destroy(device);
		vkDestroyImageView(device, depthUAV, nullptr);

		activeLightClusterListBuffer.Destroy(device);
		lightClusterIndirectArgsBuffer.Destroy(device);
		activeLightClusterListDescSetLayout.Destroy(device);
		activeLightClusterListDescPool.Destroy(device);
		activeLightClusterListPipelineLayout.Destroy(device);
		activeLightClusterListPipeline.Destroy(device);

		for(auto& frameBuffer : frameBuffers)
			frameBuffer.Destroy(device);

		for (auto& frameBuffer : depthPrepassFrameBuffers)
			frameBuffer.Destroy(device);

		depthPrePass.Destroy(device);
		renderPass.Destroy(device);

		for (auto& sceneTexture : sceneTextures)
		{
			if (sceneTexture.depth)
				sceneTexture.depth.Destroy(device);

			if (sceneTexture.resolvedDepth)
				sceneTexture.resolvedDepth.Destroy(device);

			if (sceneTexture.color)
				sceneTexture.color.Destroy(device);

			if (sceneTexture.resolvedColor)
				sceneTexture.resolvedColor.Destroy(device);
		}

		cmdPool.Destroy(device);

		swapchain.Destroy(device);

		device.Destroy();

		winSurface.Destroy(instance);
		
		instance.Destroy();
	}

	// GLFW
	{
		glfwTerminate();
	}
}

void Loop()
{
	const uint32_t frameIndex = swapchain.Begin(device);

	// Update camera.
	{
		Camera_GPU cameraGPU;

		cameraGPU.UpdatePerspective(cameraTr.Matrix(), 90, 0.1f, 1000.0f, SA::Vec2ui(1200u, 900u));

		cameraBuffers[frameIndex].UploadData(device, &cameraGPU, sizeof(Camera_GPU));
	}

	VK::CommandBuffer& cmd = cmdBuffers[frameIndex];
	VK::FrameBuffer& fbuff = frameBuffers[frameIndex];
	VK::FrameBuffer& depthPrepassFbuff = depthPrepassFrameBuffers[frameIndex];

	cmd.Begin();

	depthPrePass.Begin(cmd, depthPrepassFbuff);
	//renderPass.Begin(cmd, fbuff);

	if (depthPrepassPipeline)
	{
		vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, depthPrepassPipeline);

		std::vector<VkDescriptorSet> boundSets{
			static_cast<VkDescriptorSet>(cameraSets[frameIndex]),
			static_cast<VkDescriptorSet>(objectSet)
		};

		vkCmdBindDescriptorSets(cmd,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			pipLayout,
			0, (uint32_t)boundSets.size(),
			boundSets.data(),
			0, nullptr
		);

		sphereMesh.Draw(cmd, 100u);

		//renderPass.NextSubpass(cmd);
	}

	depthPrePass.End(cmd);

	// Light Culling
	{
		// Build LightClusterGrid: TODO: Can be called only once at init (and refresh only when camera projection fields change).
		{
			vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_COMPUTE, lightClusterGridPipeline);

			std::vector<VkDescriptorSet> boundSets{
				static_cast<VkDescriptorSet>(lightClusterGridSet)
			};

			vkCmdBindDescriptorSets(cmd,
				VK_PIPELINE_BIND_POINT_COMPUTE,
				lightClusterGridPipelineLayout,
				0, (uint32_t)boundSets.size(),
				boundSets.data(),
				0, nullptr
			);

			vkCmdDispatch(cmd, (lightClusterGridSize.x / 32) + lightClusterGridSize.x % 32 == 0 ? 0 : 1, (lightClusterGridSize.y / 32) + lightClusterGridSize.y % 32 == 0 ? 0 : 1, 32);
		}

		// Compute ActiveLightClusters
		{
			vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_COMPUTE, activeLightClustersPipeline);

			std::vector<VkDescriptorSet> boundSets{
				static_cast<VkDescriptorSet>(activeLightClustersSet)
			};

			vkCmdBindDescriptorSets(cmd,
				VK_PIPELINE_BIND_POINT_COMPUTE,
				activeLightClustersPipelineLayout,
				0, (uint32_t)boundSets.size(),
				boundSets.data(),
				0, nullptr
			);

			vkCmdDispatch(cmd, (1200 / 32) + 1, (900 / 32) + 1, 1);
		}

		// Build Active Light Cluster List
		{
			vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_COMPUTE, activeLightClusterListPipeline);

			std::vector<VkDescriptorSet> boundSets{
				static_cast<VkDescriptorSet>(activeLightClusterListSet)
			};

			vkCmdBindDescriptorSets(cmd,
				VK_PIPELINE_BIND_POINT_COMPUTE,
				activeLightClusterListPipelineLayout,
				0, (uint32_t)boundSets.size(),
				boundSets.data(),
				0, nullptr
			);

			vkCmdDispatch(cmd, 1, 1, 1);
		}
	}

	renderPass.Begin(cmd, fbuff);

	vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

	std::vector<VkDescriptorSet> boundSets{
		static_cast<VkDescriptorSet>(cameraSets[frameIndex]),
		static_cast<VkDescriptorSet>(objectSet),
		static_cast<VkDescriptorSet>(lightSet),
		static_cast<VkDescriptorSet>(materialSet),
	};

	vkCmdBindDescriptorSets(cmd,
		VK_PIPELINE_BIND_POINT_GRAPHICS,
		pipLayout,
		0, (uint32_t)boundSets.size(),
		boundSets.data(),
		0, nullptr);

	sphereMesh.Draw(cmd, 100u);

	renderPass.End(cmd);

	cmd.End();

	swapchain.End(device, {cmd});
}

int main()
{
	Init();

	double oldMouseX = 0.0f;
	double oldMouseY = 0.0f;
	float dx = 0.0f;
	float dy = 0.0f;

	const float moveSpeed = 4.0f;
	const float rotSpeed = 16.0f;

	glfwGetCursorPos(window, &oldMouseX, &oldMouseY);

	const float fixedTime = 0.0025f;
	float accumulateTime = 0.0f;
	auto start = std::chrono::steady_clock::now();

	cameraTr.position.z = -2.0f;

	while(!glfwWindowShouldClose(window))
	{
		auto end = std::chrono::steady_clock::now();
		float deltaTime = std::chrono::duration_cast<std::chrono::duration<float, std::ratio<1, 1>>>(end - start).count();
		accumulateTime += deltaTime;
		start = end;

		// Fixed Update
		if (accumulateTime >= fixedTime)
		{
			accumulateTime -= fixedTime;

			glfwPollEvents();

			// Process input
			{
				if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
					glfwSetWindowShouldClose(window, true);
				if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
					cameraTr.position += fixedTime * moveSpeed * cameraTr.Right();
				if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
					cameraTr.position -= fixedTime * moveSpeed * cameraTr.Right();
				if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
					cameraTr.position -= fixedTime * moveSpeed * cameraTr.Up();
				if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
					cameraTr.position += fixedTime * moveSpeed * cameraTr.Up();
				if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
					cameraTr.position += fixedTime * moveSpeed * cameraTr.Forward();
				if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
					cameraTr.position -= fixedTime * moveSpeed * cameraTr.Forward();

				double mouseX = 0.0f;
				double mouseY = 0.0f;

				glfwGetCursorPos(window, &mouseX, &mouseY);

				if (mouseX != oldMouseX || mouseY != oldMouseY)
				{
					dx += static_cast<float>(mouseX - oldMouseX) * fixedTime * rotSpeed * SA::Maths::DegToRad<float>;
					dy += static_cast<float>(mouseY - oldMouseY) * fixedTime * rotSpeed * SA::Maths::DegToRad<float>;

					oldMouseX = mouseX;
					oldMouseY = mouseY;

					dx = dx > SA::Maths::Pi<float> ?
						dx - SA::Maths::Pi<float> :
						dx < -SA::Maths::Pi<float> ? dx + SA::Maths::Pi<float> : dx;
					dy = dy > SA::Maths::Pi<float> ?
						dy - SA::Maths::Pi<float> :
						dy < -SA::Maths::Pi<float> ? dy + SA::Maths::Pi<float> : dy;

					cameraTr.rotation = SA::Quatf(cos(dx), 0, sin(dx), 0) * SA::Quatf(cos(dy), sin(dy), 0, 0);
				}
			}
		}

		Loop();

		SA_LOG_END_OF_FRAME();
	}

	Uninit();

	return 0;
}

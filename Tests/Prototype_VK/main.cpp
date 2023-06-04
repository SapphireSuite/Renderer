// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Collections/Debug>

#include <SA/Render/LowLevel/Common/Mesh/RawMesh.hpp>
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
#include <SA/Render/ShaderCompiler/ShaderCompiler.hpp>
using namespace SA::RND;

// Must be included after vulkan.
#include <GLFW/glfw3.h>

GLFWwindow* window = nullptr;

VK::Instance instance;
VK::WindowSurface winSurface;
VK::Device device;
VK::Swapchain swapchain;
VK::CommandPool cmdPool;
VK::PassInfo passInfo;
VK::RenderPass renderPass;
std::vector<VK::FrameBuffer> frameBuffers;
std::vector<VK::CommandBuffer> cmdBuffers;
VK::Shader vertexShader;
VK::Shader fragmentShader;
VK::PipelineLayout pipLayout;
VK::Pipeline pipeline;
RawMesh triangle;
RHI::ShaderDescriptor vsDesc;
RHI::ShaderDescriptor fsDesc;

VkBuffer vertexPositionBuffer = VK_NULL_HANDLE;
VkDeviceMemory vertexPositionDeviceMemory = VK_NULL_HANDLE;
VkBuffer vertexColorBuffer = VK_NULL_HANDLE;
VkDeviceMemory vertexColorDeviceMemory = VK_NULL_HANDLE;

void GLFWErrorCallback(int32_t error, const char* description)
{
	SA_LOG((L"GLFW Error [%1]: %2", error, description), Error, SA.Render.Proto.GLFW.API);
}

void Init()
{
	SA::Debug::InitDefaultLogger();

	// GLFW
	{
		glfwSetErrorCallback(GLFWErrorCallback);
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		window = glfwCreateWindow(1200, 900, "Vulkan Prototype", nullptr, nullptr);
		SA_ASSERT((Nullptr, window), SA.Render.Proto.GLFW, L"GLFW create window failed!");
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

		// Render Pass
		{
			constexpr bool bDepth = false;
			constexpr bool bMSAA = true;

			// Forward
			if (true)
			{
				auto& mainSubpass = passInfo.AddSubpass("Main");

				if(bMSAA)
					mainSubpass.sampling = VK_SAMPLE_COUNT_8_BIT;

				// Color and present attachment.
				auto& colorRT = mainSubpass.AddAttachment("Color");
				colorRT.format = swapchain.GetFormat();
				colorRT.usage = AttachmentUsage::Present;

				if(bDepth)
				{
					auto& depthRT = mainSubpass.AddAttachment("Depth");
					depthRT.format = VK_FORMAT_D16_UNORM;
					depthRT.type = AttachmentType::Depth;
				}
				
				mainSubpass.SetAllAttachmentExtents(swapchain.GetExtents());
			}

			renderPass.Create(device, passInfo);


			// FrameBuffers
			{
				uint32_t num = swapchain.GetImageNum();
				frameBuffers.resize(num);

				for(uint32_t i = 0; i < num; ++i)
					frameBuffers[i].Create(device, renderPass, passInfo, swapchain.GetBackBufferHandle(i));
			}
		}

		// Mesh
		{
			triangle.vertices.AddVertexComponent<VertexPosition>({{0.0f, 0.5f, 0.0f}, {0.5f, -0.5f, 0.0}, {-0.5f, -0.5f, 0.0}});
			triangle.vertices.AddVertexComponent<VertexColor>({Color::red, Color::green, Color::blue});
			triangle.indices.U16({0, 1, 2});


			// Position Buffer
			{
				VkBufferCreateInfo positionBufferInfo{
					.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
					.pNext = nullptr,
					.flags = 0u,
					.size = sizeof(SA::Vec3f) * 3,
					.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
					.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
					.queueFamilyIndexCount = 0u,
					.pQueueFamilyIndices = nullptr,
				};

				vkCreateBuffer(device, &positionBufferInfo, nullptr, &vertexPositionBuffer);


				VkMemoryRequirements memRequirements{};
				vkGetBufferMemoryRequirements(device, vertexPositionBuffer, &memRequirements);

				uint32_t memoryTypeIndex = VK::BufferBase::FindMemoryType(device, memRequirements.memoryTypeBits,
					VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

				VkMemoryAllocateInfo memoryAllocInfo{};
				memoryAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				memoryAllocInfo.pNext = nullptr;
				memoryAllocInfo.allocationSize = memRequirements.size;
				memoryAllocInfo.memoryTypeIndex = memoryTypeIndex;

				vkAllocateMemory(device, &memoryAllocInfo, nullptr, &vertexPositionDeviceMemory);

				vkBindBufferMemory(device, vertexPositionBuffer, vertexPositionDeviceMemory, 0);


				void* data;
				vkMapMemory(device, vertexPositionDeviceMemory, 0, sizeof(SA::Vec3f) * 3, 0, &data);
				
					std::memcpy(data, triangle.vertices.GetVertexComponent<VertexPosition>()->positions.data(), sizeof(SA::Vec3f) * 3);
				
				vkUnmapMemory(device, vertexPositionDeviceMemory);
			}

			// Color buffer
			{
				VkBufferCreateInfo colorBufferInfo{
					.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
					.pNext = nullptr,
					.flags = 0u,
					.size = sizeof(Color) * 3,
					.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
					.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
					.queueFamilyIndexCount = 0u,
					.pQueueFamilyIndices = nullptr,
				};
			
				vkCreateBuffer(device, &colorBufferInfo, nullptr, &vertexColorBuffer);


				VkMemoryRequirements memRequirements{};
				vkGetBufferMemoryRequirements(device, vertexColorBuffer, &memRequirements);

				uint32_t memoryTypeIndex = VK::BufferBase::FindMemoryType(device, memRequirements.memoryTypeBits,
					VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

				VkMemoryAllocateInfo memoryAllocInfo{};
				memoryAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				memoryAllocInfo.pNext = nullptr;
				memoryAllocInfo.allocationSize = memRequirements.size;
				memoryAllocInfo.memoryTypeIndex = memoryTypeIndex;

				vkAllocateMemory(device, &memoryAllocInfo, nullptr, &vertexColorDeviceMemory);

				vkBindBufferMemory(device, vertexColorBuffer, vertexColorDeviceMemory, 0);


				void* data;
				vkMapMemory(device, vertexColorDeviceMemory, 0, sizeof(Color) * 3, 0, &data);
				
					std::memcpy(data, triangle.vertices.GetVertexComponent<VertexColor>()->colors.data(), sizeof(Color) * 3);
				
				vkUnmapMemory(device, vertexColorDeviceMemory);
			}
		}

		// Shaders
		{
			ShaderCompiler compiler;

			compiler.Create();	

			// Vertex
			{
				ShaderCompileInfo vsInfo
				{
					.path = L"Resources/Shaders/Forward/Unlit.hlsl",
					.entrypoint = L"mainVS",
					.target = L"vs_6_5",
				};

				triangle.vertices.AppendDefines(vsInfo.defines);

				ShaderCompileResult vsShaderRes = compiler.CompileSPIRV(vsInfo);
				vsDesc = vsShaderRes.desc;

				vertexShader.Create(device, vsShaderRes.rawSPIRV);
			}


			// Fragment
			{
				ShaderCompileInfo psInfo
				{
					.path = L"Resources/Shaders/Forward/Unlit.hlsl",
					.entrypoint = L"mainPS",
					.target = L"ps_6_5",
				};

				triangle.vertices.AppendDefines(psInfo.defines);

				ShaderCompileResult psShaderRes = compiler.CompileSPIRV(psInfo);
				fsDesc = psShaderRes.desc;

				fragmentShader.Create(device, psShaderRes.rawSPIRV);
			}


			compiler.Destroy();	
		}

		// Pipeline layout
		{
			VkPipelineLayoutCreateInfo info{};
			info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			info.pNext = nullptr;
			info.flags = 0u;
			info.setLayoutCount = 0;
			info.pSetLayouts = nullptr;
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
					.stage = VK_SHADER_STAGE_VERTEX_BIT,
					.module = vertexShader,
					.pName = "mainVS",
					.pSpecializationInfo = nullptr
				},
				{
					.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
					.pNext = nullptr,
					.flags = 0u,
					.stage = VK_SHADER_STAGE_FRAGMENT_BIT,
					.module = fragmentShader,
					.pName = "mainPS",
					.pSpecializationInfo = nullptr
				}
			};

			auto vertInputState = vsDesc.MakePipelineVertexInputStateInfo();
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
				.rasterizationSamples = passInfo.subpasses[0].sampling,
				.sampleShadingEnable = passInfo.subpasses[0].sampling != VK_SAMPLE_COUNT_1_BIT,
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
				.depthWriteEnable = VK_TRUE,
				.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL,
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
				.subpass = 0,
				.basePipelineHandle = VK_NULL_HANDLE,
				.basePipelineIndex = -1,
			};

			pipeline.Create(device, pipelineCreateInfo);
		}
	}
}

void Uninit()
{
	// Render
	{
		device.WaitIdle();

		pipeline.Destroy(device);
		pipLayout.Destroy(device);

		fragmentShader.Destroy(device);
		vertexShader.Destroy(device);

		vkDestroyBuffer(device, vertexPositionBuffer, nullptr);
		vkFreeMemory(device, vertexPositionDeviceMemory, nullptr);
		vkDestroyBuffer(device, vertexColorBuffer, nullptr);
		vkFreeMemory(device, vertexColorDeviceMemory, nullptr);

		for(auto& frameBuffer : frameBuffers)
			frameBuffer.Destroy(device);

		renderPass.Destroy(device);

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

	VK::CommandBuffer& cmd = cmdBuffers[frameIndex];
	VK::FrameBuffer& fbuff = frameBuffers[frameIndex];

	cmd.Begin();

	renderPass.Begin(cmd, fbuff);

	vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

	// Draw
	VkBuffer vkVertexBuffers[] = {vertexPositionBuffer, vertexColorBuffer};
	VkDeviceSize offsets[] = {0, 0};
	vkCmdBindVertexBuffers(cmd, 0, 2, vkVertexBuffers, offsets);

	//vkCmdBindIndexBuffer(cmd, mIndexBuffer, 0, VK_INDEX_TYPE_UINT32);
	vkCmdDraw(cmd, 3, 1, 0, 0);
	//

	renderPass.End(cmd);

	cmd.End();

	swapchain.End(device, {cmd});
}

int main()
{
	Init();

	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		Loop();
	}

	Uninit();

	return 0;
}

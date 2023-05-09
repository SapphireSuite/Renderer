// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Collections/Debug>

#include <SA/Render/LowLevel/Vulkan/VkInstance.hpp>
#include <SA/Render/LowLevel/Vulkan/Device/VkDevice.hpp>
#include <SA/Render/LowLevel/Vulkan/Surface/VkWindowSurface.hpp>
#include <SA/Render/LowLevel/Vulkan/Surface/VkSwapchain.hpp>
#include <SA/Render/LowLevel/Vulkan/Device/Command/VkCommandPool.hpp>
#include <SA/Render/LowLevel/Vulkan/Pass/VkRenderPass.hpp>
#include <SA/Render/RHI/Pass/Descriptors/PassDescriptor.hpp>
using namespace SA::RND;

// Must be included after vulkan.
#include <GLFW/glfw3.h>

GLFWwindow* window = nullptr;

VK::Instance instance;
VK::WindowSurface winSurface;
VK::Device device;
VK::Swapchain swapchain;
VK::CommandPool cmdPool;
VK::RenderPass renderPass;
std::vector<VK::CommandBuffer> cmdBuffers;

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
			
			winSurface.InitializeHandle(std::move(glfwsurface));

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
			RHI::PassDescriptor passDesc;

			constexpr bool bDepth = true;
			constexpr bool bMSAA = true;

			// Forward
			if (false)
			{
				auto& mainSubpassDesc = passDesc.subPassDescs.emplace_back();

				if(bMSAA)
					mainSubpassDesc.sampling = RHI::SampleBits::Sample8Bits;

				// Color and present attachment.
				auto& colorAttachDesc = mainSubpassDesc.attachmentDescs.emplace_back();
				colorAttachDesc.format = RHI::Format::B8G8R8A8_SRGB;

				if(bDepth)
				{
					auto& depthAttachDesc = mainSubpassDesc.attachmentDescs.emplace_back();
					depthAttachDesc.format = RHI::Format::D16_UNORM;
				}
			}
			else if(true) // Deferred
			{
				passDesc.subPassDescs.reserve(2u);

				// PBR Subpass
				{
					auto& pbrSubpassDesc = passDesc.subPassDescs.emplace_back();

					if(bMSAA)
						pbrSubpassDesc.sampling = RHI::SampleBits::Sample8Bits;

					// Deferred position attachment.
					auto& posAttachDesc = pbrSubpassDesc.attachmentDescs.emplace_back();
					posAttachDesc.bInputNext = true;

					// Deferred normal attachment.
					auto& normAttachDesc = pbrSubpassDesc.attachmentDescs.emplace_back();
					normAttachDesc.bInputNext = true;

					// Deferred albedo attachment.
					auto& albedoAttachDesc = pbrSubpassDesc.attachmentDescs.emplace_back();
					albedoAttachDesc.bInputNext = true;

					// Deferred PBR (Metallic, Roughness, Ambiant occlusion) attachment.
					auto& pbrAttachDesc = pbrSubpassDesc.attachmentDescs.emplace_back();
					pbrAttachDesc.bInputNext = true;

					if(bDepth)
					{
						auto& depthAttachDesc = pbrSubpassDesc.attachmentDescs.emplace_back();
						depthAttachDesc.format = RHI::Format::D16_UNORM;
					}
				}

				// Present Subpass
				{
					auto& presentSubpassDesc = passDesc.subPassDescs.emplace_back();

					if(bMSAA)
						presentSubpassDesc.sampling = RHI::SampleBits::Sample8Bits;

					auto& presentAttachDesc = presentSubpassDesc.attachmentDescs.emplace_back();
					presentAttachDesc.format = RHI::Format::B8G8R8A8_SRGB;
				}
			}


			renderPass.Create(device, VK::API_MakeRenderPassDescriptor(passDesc));
		}
	}
}

void Uninit()
{
	// Render
	{
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
	// const uint32_t frameIndex = swapchain.Begin(device);

	// SA::VK::CommandBuffer& cmdBuffer = cmdBuffers[frameIndex];

	// cmdBuffer.Begin();



	// cmdBuffer.End();

	// swapchain.End(device, {cmdBuffer});
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

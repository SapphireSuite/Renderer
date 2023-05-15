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
				auto& mainSubpass = passDesc.subpassDescs.emplace_back();

				if(bMSAA)
					mainSubpass.sampling = RHI::SampleBits::Sample8Bits;

				mainSubpass.DepthDesc.bEnabled = bDepth;

				// Color and present attachment.
				auto& colorRT = mainSubpass.RTDescs.emplace_back();
				colorRT.format = VK::API_GetFormat(swapchain.GetFormat());

				// if(bDepth)
				// {
				// 	auto& depthAttachDesc = mainSubpassDesc.RTDescs.emplace_back();
				// 	depthAttachDesc.format = RHI::Format::D16_UNORM;
				// }
			}
			else if(true) // Deferred
			{
				passDesc.subpassDescs.reserve(2u);

				// PBR Subpass
				{
					auto& pbrSubpass = passDesc.subpassDescs.emplace_back();

					if(bMSAA)
						pbrSubpass.sampling = RHI::SampleBits::Sample8Bits;

					pbrSubpass.DepthDesc.bEnabled = bDepth;

					// Render Targets
					{
						// Deferred position attachment.
						auto& posRT = pbrSubpass.RTDescs.emplace_back();

						// Deferred normal attachment.
						auto& normRT = pbrSubpass.RTDescs.emplace_back();

						// Deferred albedo attachment.
						auto& albedoRT = pbrSubpass.RTDescs.emplace_back();

						// Deferred PBR (Metallic, Roughness, Ambiant occlusion) attachment.
						auto& pbrRT = pbrSubpass.RTDescs.emplace_back();
					}
				}

				// Present Subpass
				{
					auto& presentSubpass = passDesc.subpassDescs.emplace_back();

					if(bMSAA)
						presentSubpass.sampling = RHI::SampleBits::Sample8Bits;

					auto& presentRT = presentSubpass.RTDescs.emplace_back();
					presentRT.format = VK::API_GetFormat(swapchain.GetFormat());
				}
			}


			renderPass.Create(device, passDesc.API_Vulkan());
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

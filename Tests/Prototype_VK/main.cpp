// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Collections/Debug>

#include <SA/Render/LowLevel/Vulkan/VkInstance.hpp>
#include <SA/Render/LowLevel/Vulkan/Device/VkDevice.hpp>
#include <SA/Render/LowLevel/Vulkan/Surface/VkWindowSurface.hpp>
#include <SA/Render/LowLevel/Vulkan/Surface/VkSwapchain.hpp>
#include <SA/Render/LowLevel/Vulkan/Device/Command/VkCommandPool.hpp>

// Must be included after vulkan.
#include <GLFW/glfw3.h>

GLFWwindow* window = nullptr;

SA::VK::Instance instance;
SA::VK::WindowSurface winSurface;
SA::VK::Device device;
SA::VK::Swapchain swapchain;
SA::VK::CommandPool cmdPool;
std::vector<SA::VK::CommandBuffer> cmdBuffers;

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

		SA::VK::DeviceRequirements deviceReqs;

		// Window Surface
		{
			VkSurfaceKHR glfwsurface;
			glfwCreateWindowSurface(instance, window, nullptr, &glfwsurface);
			
			winSurface.InitializeHandle(std::move(glfwsurface));

			deviceReqs.SetWindowSurface(&winSurface);
		}

		// Device
		{
			std::vector<SA::VK::DeviceInfo> deviceInfos = instance.QueryDeviceInfos(deviceReqs);
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
	}
}

void Uninit()
{
	// Render
	{
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

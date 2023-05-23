// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <list>
#include <thread>

#include <SA/Collections/Debug>

#include <SA/Render/RHI/Compatibility/Window.hpp>
#include <SA/Render/RHI/RHIVkRenderInterface.hpp>
#include <SA/Render/RHI/RHID12RenderInterface.hpp>
using namespace SA::RND;

// Must be included after vulkan.
#include <GLFW/glfw3.h>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#endif

void GLFWErrorCallback(int32_t error, const char* description)
{
	SA_LOG((L"GLFW Error [%1]: %2", error, description), Error, SA.Render.Proto.GLFW.API);
}

class WindowHandle : public SA::WND::WHI::Window
{
	GLFWwindow* mHandle = nullptr;

public:
	WindowHandle(GLFWwindow* _handle) noexcept :
		mHandle{ _handle }
	{
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VkSurfaceKHR CreateVkSurfaceKHR(const SA::RND::VK::Instance& _instance) const override final
	{
		VkSurfaceKHR glfwsurface;
		glfwCreateWindowSurface(_instance, mHandle, nullptr, &glfwsurface);

		return glfwsurface;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	HWND GetHWNDHandle() const override final
	{
		return glfwGetWin32Window(mHandle);
	}

#endif
};

class Renderer
{
public:
	GLFWwindow* window = nullptr;

	RHI::RenderInterface* intf = nullptr;
	RHI::Device* device;
	RHI::WindowSurface* winSurface;
	RHI::Context* context;

	struct CreateInfo
	{
		RHI::RenderInterface* intf = nullptr; 
		std::string winName;
		int winPosX = 0;
		int winPosY = 0;
	};

	void Create(const CreateInfo& _info)
	{
		intf = _info.intf;
		intf->Create();

		// GLFW
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			window = glfwCreateWindow(960, 540, _info.winName.c_str(), nullptr, nullptr);
			glfwSetWindowPos(window, _info.winPosX, _info.winPosY + 30);
			SA_ASSERT((Nullptr, window), SA.Render.Proto.GLFW, L"GLFW create window failed!");
		}

		// Win Surface
		{
			WindowHandle winHandle(window);

			winSurface = intf->CreateWindowSurface(&winHandle);
		}

		// Device
		{
			auto infos = intf->QueryDeviceInfos();

			for (auto& info : infos)
				SA_LOG((L"Device found: Name: [%1], ID: [%2], Vendor [%3], Score [%4]", info->GetName(), info->GetID(), info->GetVendorID(), info->GetScore()));

			device = intf->CreateDevice(infos[0].get());
		
		}
		
		{
			context = device->CreateContext();
		}
	}

	void Destroy()
	{
		// Render
		{
			device->DestroyContext(context);

			intf->DestroyWindowSurface(winSurface);
			intf->DestroyDevice(device);

			intf->Destroy();
			delete intf;
		}

		// GLFW
		{
			glfwDestroyWindow(window);
		}
	}

	void Loop()
	{
		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
		}
	}

	static void RenderThread(const CreateInfo& _info)
	{
		Renderer renderer;

		renderer.Create(_info);

		renderer.Loop();

		renderer.Destroy();
	}
};

int main()
{
	SA::Debug::InitDefaultLoggerThread();

	// GLFW
	{
		glfwSetErrorCallback(GLFWErrorCallback);
		glfwInit();
	}


	// Render
	{

		std::list<std::thread> renderThreads;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
		renderThreads.emplace_back(std::thread(Renderer::RenderThread, Renderer::CreateInfo{ new RHI::VkRenderInterface, "Vulkan" }));
#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL
		renderThreads.emplace_back(std::thread(Renderer::RenderThread, Renderer::CreateInfo{ new RHI::D12RenderInterface, "DirectX12", 960, 0 }));
#endif

		for (auto& renderThread : renderThreads)
		{
			if (renderThread.joinable())
				renderThread.join();
		}
	}


	// GLFW
	{
		glfwTerminate();
	}

	return 0;
}

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <VkInstance.hpp>

#include "Debug/VkValidationLayers.hpp"
#include "Device/VkDevice.hpp"

namespace SA::RND::VK
{
	void Instance::Create(std::vector<const char*> _vkExtensions)
	{
		VkApplicationInfo appInfos{};
		appInfos.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfos.pNext = nullptr;
		appInfos.pApplicationName = "Main Application";
		appInfos.applicationVersion = VK_MAKE_VERSION(1, 0, 0); // TODO:
		appInfos.pEngineName = "Sapphire Engine";
		appInfos.engineVersion = VK_MAKE_VERSION(1, 0, 0); // TODO:
		appInfos.apiVersion = VK_API_VERSION_1_0;

	#if SA_VK_VALIDATION_LAYERS

		_vkExtensions.push_back("VK_EXT_debug_utils");

	#endif

		VkInstanceCreateInfo instanceInfos{};
		instanceInfos.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceInfos.pNext = nullptr;
		instanceInfos.flags = 0;
		instanceInfos.pApplicationInfo = &appInfos;

		instanceInfos.enabledLayerCount = 0;
		instanceInfos.ppEnabledLayerNames = nullptr;

		instanceInfos.enabledExtensionCount = static_cast<uint32_t>(_vkExtensions.size());
		instanceInfos.ppEnabledExtensionNames = _vkExtensions.data();

	#if SA_VK_VALIDATION_LAYERS

		// Debug Messenger Info.
		const VkDebugUtilsMessengerCreateInfoEXT debugUtilscreateInfo = ValidationLayers::GetDebugUtilsMessengerCreateInfo();

		instanceInfos.pNext = &debugUtilscreateInfo;

		instanceInfos.enabledLayerCount = ValidationLayers::GetLayerNum();
		instanceInfos.ppEnabledLayerNames = ValidationLayers::GetLayerNames();

	#endif

		SA_VK_API(vkCreateInstance(&instanceInfos, nullptr, &mHandle));

	#if SA_VK_VALIDATION_LAYERS
		{
			auto createDebugFunc = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(mHandle, "vkCreateDebugUtilsMessengerEXT");
			SA_ASSERT((Nullptr, createDebugFunc), SA.Render.Vulkan, L"Extension PFN_vkCreateDebugUtilsMessengerEXT missing!");

			SA_VK_API(createDebugFunc(mHandle, &debugUtilscreateInfo, nullptr, &mDebugMessenger), L"Failed to create vulkan debug messenger!");
		
			SA_LOG(L"Debug Messenger created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mDebugMessenger));
		}
	#endif

		SA_LOG(L"Instance created.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));
	}

	void Instance::Destroy()
	{
		SA_LOG_RAII(L"Instance destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mHandle));

	#if SA_VK_VALIDATION_LAYERS
		{
			SA_LOG_RAII(L"Debug Messenger destroyed.", Info, SA.Render.Vulkan, (L"Handle [%1]", mDebugMessenger));

			auto destroyDebugFunc = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(mHandle, "vkDestroyDebugUtilsMessengerEXT");
			SA_ASSERT((Nullptr, destroyDebugFunc), SA.Render.Vulkan, L"Extension PFN_vkDestroyDebugUtilsMessengerEXT missing!");

			destroyDebugFunc(mHandle, mDebugMessenger, nullptr);
			mDebugMessenger = nullptr;
		}
	#endif

		SA_VK_API(vkDestroyInstance(mHandle, nullptr));
		mHandle = VK_NULL_HANDLE;
	}


	std::vector<DeviceInfo> Instance::QueryDeviceInfos(const DeviceRequirements& _reqs) const
	{
		return Device::QueryDeviceInfos(*this, _reqs);
	}


	Instance::operator VkInstance() const noexcept
	{
		return mHandle;
	}
}

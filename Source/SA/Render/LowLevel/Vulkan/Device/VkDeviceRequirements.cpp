// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <cstring>

#include <Device/VkDeviceRequirements.hpp>

namespace SA::VK
{
//{ Extension

	void DeviceRequirements::AddUniqueExtension(const char* _vkExt)
	{
		for(auto vkReqExt : vkRequiredExtensions)
		{
			if(std::strcmp(vkReqExt, _vkExt) == 0)
				return;
		}

		vkRequiredExtensions.push_back(_vkExt);
	}

	bool DeviceRequirements::RemoveExtension(const char* _vkExt)
	{
		for(auto it = vkRequiredExtensions.begin(); it != vkRequiredExtensions.end(); ++it)
		{
			if(std::strcmp(*it, _vkExt) == 0)
			{
				vkRequiredExtensions.erase(it);
				return true;
			}
		}

		return false;
	}

//}


//{ Window Surface

	WindowSurface* DeviceRequirements::GetWindowSurface() const noexcept
	{
		return mWinSurface;
	}
	
	void DeviceRequirements::SetWindowSurface(WindowSurface* _winSurface, bool bSetPresentQueue)
	{
		if(mWinSurface == _winSurface)
			return;

		mWinSurface = _winSurface;

	//{ Extension support
		static constexpr const char* windowRequieredExts[] =
		{
			// Present to window requires swapchain support.
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		if(mWinSurface)
		{
			// Add Extension.
			for(auto winReqExt : windowRequieredExts)
				AddUniqueExtension(winReqExt);

			if(bSetPresentQueue)
				++queue.presentNum;
		}
		else
		{
			// Remove Extension.
			for(auto winReqExt : windowRequieredExts)
				RemoveExtension(winReqExt);

			if(bSetPresentQueue)
				--queue.presentNum;
		}
	//}
	}

//}
}

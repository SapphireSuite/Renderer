// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_EXCEPTION_VULKAN_GUARD
#define SAPPHIRE_RENDER_EXCEPTION_VULKAN_GUARD

#include <SA/Logger/Exceptions/Exception.hpp>

namespace SA::RND
{
	namespace VK
	{
		class Exception_Vulkan : public Exception
		{
		public:
			Exception_Vulkan(
				BaseInfo _info,
				VkResult _vkRes,
				std::wstring _predStr
			) noexcept;
		};


		/// \cond Internal

		#define __SA_CREATE_EXCEPTION_Vulkan(_baseInfo, _vkFunc) SA::VK::Exception_Vulkan(\
			_baseInfo,\
			_vkFunc,\
			SA_WSTR(_vkFunc)\
		)

		/// \endcond
	}
}

#endif // SAPPHIRE_RENDER_EXCEPTION_VULKAN_GUARD

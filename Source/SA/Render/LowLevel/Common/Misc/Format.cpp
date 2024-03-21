// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Misc/Format.hpp>

namespace SA::RND
{
	uint32_t API_GetChannelNum(Format _format)
	{
		uint32_t uiFormat = static_cast<uint32_t>(_format);

		if ((uiFormat >= static_cast<uint32_t>(Format::R8_UNORM) && uiFormat <= static_cast<uint32_t>(Format::R8_SINT)) ||
			(uiFormat >= static_cast<uint32_t>(Format::R16_UNORM) && uiFormat <= static_cast<uint32_t>(Format::R16_SFLOAT)) ||
			(uiFormat >= static_cast<uint32_t>(Format::R32_UINT) && uiFormat <= static_cast<uint32_t>(Format::R32_SFLOAT)) ||
			(_format == Format::D16_UNORM || _format == Format::D32_SFLOAT))
			return 1u;
		
		if ((uiFormat >= static_cast<uint32_t>(Format::R8G8_UNORM) && uiFormat <= static_cast<uint32_t>(Format::R8G8_SINT)) ||
			(uiFormat >= static_cast<uint32_t>(Format::R16G16_UNORM) && uiFormat <= static_cast<uint32_t>(Format::R16G16_SFLOAT)) ||
			(uiFormat >= static_cast<uint32_t>(Format::R32G32_UINT) && uiFormat <= static_cast<uint32_t>(Format::R32G32_SFLOAT)) ||
			(_format == Format::D24_UNORM_S8_UINT))
			return 2u;
		
		if (uiFormat >= static_cast<uint32_t>(Format::R32G32B32_UINT) && uiFormat <= static_cast<uint32_t>(Format::R32G32B32_SFLOAT))
			return 3u;
		
		if ((uiFormat >= static_cast<uint32_t>(Format::R8G8B8A8_UNORM) && uiFormat <= static_cast<uint32_t>(Format::B8G8R8A8_SRGB)) ||
			(uiFormat >= static_cast<uint32_t>(Format::R16G16B16A16_UNORM) && uiFormat <= static_cast<uint32_t>(Format::R16G16B16A16_SFLOAT)) ||
			(uiFormat >= static_cast<uint32_t>(Format::R32G32B32A32_UINT) && uiFormat <= static_cast<uint32_t>(Format::R32G32B32A32_SFLOAT)))
			return 4u;

		return 0u;
	}
}

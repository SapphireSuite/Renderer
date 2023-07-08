// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include "D12Format.hpp"

namespace SA::RND::DX12
{
	namespace Intl
	{
		DXGI_FORMAT UNORMToSRGBFormat(DXGI_FORMAT _format)
		{
			if (_format == DXGI_FORMAT_R8G8B8A8_UNORM)
				return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

			if (_format == DXGI_FORMAT_B8G8R8A8_TYPELESS)
				return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;

			if (_format == DXGI_FORMAT_B8G8R8X8_TYPELESS)
				return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;

			return _format;
		}

		DXGI_FORMAT SRGBToUNORMFormat(DXGI_FORMAT _format)
		{
			if (_format == DXGI_FORMAT_R8G8B8A8_UNORM_SRGB)
				return DXGI_FORMAT_R8G8B8A8_UNORM;

			if (_format == DXGI_FORMAT_B8G8R8A8_UNORM_SRGB)
				return DXGI_FORMAT_B8G8R8A8_TYPELESS;

			if (_format == DXGI_FORMAT_B8G8R8X8_UNORM_SRGB)
				return DXGI_FORMAT_B8G8R8X8_TYPELESS;

			return _format;
		}
	}
}

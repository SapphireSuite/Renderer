// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_FORMAT_GUARD
#define SAPPHIRE_RENDER_DX12_FORMAT_GUARD

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

namespace SA::RND::DX12
{
	namespace Intl
	{
		DXGI_FORMAT UNORMToSRGBFormat(DXGI_FORMAT _format);

		DXGI_FORMAT SRGBToUNORMFormat(DXGI_FORMAT _format);
	}
}

#endif // SAPPHIRE_RENDER_DX12_FORMAT_GUARD

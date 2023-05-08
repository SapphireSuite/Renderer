// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Debug/Exception_DX12.hpp>

namespace SA::RND::DX12
{
	Exception_DX12::Exception_DX12(
		BaseInfo _info,
		HRESULT _hrRes,
		std::wstring _predStr
	) noexcept :
		Exception(std::move(_info),
			SUCCEEDED(_hrRes),
			std::move(_predStr) + L" => SUCCEEDED")
	{
	}
}

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_EXCEPTION_DXC_GUARD
#define SAPPHIRE_RENDER_EXCEPTION_DXC_GUARD

#include <SA/Logger/Exceptions/Exception.hpp>

#include <SA/Support/API/Windows.hpp>

namespace SA::RND
{
	class Exception_DXC : public Exception
	{
	public:
		Exception_DXC(BaseInfo _info,
			HRESULT _hrRes,
			std::wstring _predStr
		) noexcept;
	};


	/// \cond Internal

	#define __SA_CREATE_EXCEPTION_DXC(_baseInfo, _hrRes) SA::RND::Exception_DXC(\
		_baseInfo,\
		_hrRes,\
		SA_WSTR(_hrRes)\
	)

	/// \endcond
}

#endif // SAPPHIRE_RENDER_EXCEPTION_DXC_GUARD

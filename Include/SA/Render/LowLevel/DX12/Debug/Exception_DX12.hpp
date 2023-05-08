// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_EXCEPTION_DX12_GUARD
#define SAPPHIRE_RENDER_EXCEPTION_DX12_GUARD

#include <SA/Logger/Exceptions/Exception.hpp>

#include <SA/Support/API/Windows.hpp>

namespace SA::RND
{
	namespace DX12
	{
		class Exception_DX12 : public Exception
		{
		public:
			Exception_DX12(BaseInfo _info,
				HRESULT _hrRes,
				std::wstring _predStr
			) noexcept;
		};


		/// \cond Internal

		#define __SA_CREATE_EXCEPTION_DX12(_baseInfo, _hrRes) SA::DX12::Exception_DX12(\
			_baseInfo,\
			_hrRes,\
			SA_WSTR(_hrRes)\
		)

		/// \endcond
	}
}

#endif // SAPPHIRE_RENDER_EXCEPTION_DX12_GUARD

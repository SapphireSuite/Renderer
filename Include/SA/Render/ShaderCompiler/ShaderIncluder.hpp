// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_INCLUDER_GUARD
#define SAPPHIRE_RENDER_SHADER_INCLUDER_GUARD

#include <string>
#include <unordered_set>

#include "DXCAPI.hpp"

namespace SA::RND
{
	class ShaderIncluder : public IDxcIncludeHandler
	{
		CComPtr<IDxcUtils> mUtils;
	public:
		std::unordered_set<std::wstring> includedFiles;

		ShaderIncluder(CComPtr<IDxcUtils> _utils);

		HRESULT STDMETHODCALLTYPE LoadSource(_In_z_ LPCWSTR _pFilename,
			_COM_Outptr_result_maybenull_ IDxcBlob **_ppIncludeSource) override final;

		HRESULT QueryInterface(REFIID riid, void **ppvObject) override final;

		ULONG AddRef() override final;
		ULONG Release() override final;
		// HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject) override;
	};
}

#endif // SAPPHIRE_RENDER_SHADER_INCLUDER_GUARD

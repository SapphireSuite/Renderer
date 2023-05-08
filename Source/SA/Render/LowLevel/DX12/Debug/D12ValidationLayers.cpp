// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include "D12ValidationLayers.hpp"

// Report live objects.
#include <dxgi1_6.h>
#include <DXGIDebug.h>

#include <Debug/Debug.hpp>

namespace SA::RND::DX12
{
	void ValidationLayers::Initialize()
	{
#if SA_DX12_VALIDATION_LAYERS

		ID3D12Debug1* debugController = nullptr;

		if (D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)) == S_OK)
		{
			debugController->EnableDebugLayer();
			debugController->SetEnableGPUBasedValidation(true);

			debugController->Release();

			SA_LOG(L"Validation layer initialized.", Info, SA.Render.DX12);
		}
		else
			SA_LOG(L"Validation layer initialization failed.", Error, SA.Render.DX12);

#endif // SA_DX12_VALIDATION_LAYERS
	}

	void ValidationLayers::Uninitialize()
	{
#if SA_DX12_VALIDATION_LAYERS

		// Report live objects
		IDXGIDebug1* dxgiDebug = nullptr;

		if (DXGIGetDebugInterface1(0, IID_PPV_ARGS(&dxgiDebug)) == S_OK)
		{
			dxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_FLAGS(DXGI_DEBUG_RLO_ALL | DXGI_DEBUG_RLO_IGNORE_INTERNAL));
			dxgiDebug->Release();
			
			SA_LOG(L"Validation layer uninitialized.", Infos, SA.Render.DX12);
		}
		else
			SA_LOG(L"Validation layer uninitialized failed.", Error, SA.Render.DX12);

#endif // SA_DX12_VALIDATION_LAYERS
	}

	void ValidationLayers::DebugCallback(D3D12_MESSAGE_CATEGORY _category,
		D3D12_MESSAGE_SEVERITY _severity,
		D3D12_MESSAGE_ID _ID,
		LPCSTR _description,
		void* _context)
	{
		(void)_context;

		std::wstring categoryStr;

		switch (_category)
		{
		case D3D12_MESSAGE_CATEGORY_APPLICATION_DEFINED:
			categoryStr = L"[Application Defined]";
			break;
		case D3D12_MESSAGE_CATEGORY_MISCELLANEOUS:
			categoryStr = L"[Miscellaneous]";
			break;
		case D3D12_MESSAGE_CATEGORY_INITIALIZATION:
			categoryStr = L"[Initialization]";
			break;
		case D3D12_MESSAGE_CATEGORY_CLEANUP:
			categoryStr = L"[Cleanup]";
			break;
		case D3D12_MESSAGE_CATEGORY_COMPILATION:
			categoryStr = L"[Compilation]";
			break;
		case D3D12_MESSAGE_CATEGORY_STATE_CREATION:
			categoryStr = L"[State Creation]";
			break;
		case D3D12_MESSAGE_CATEGORY_STATE_SETTING:
			categoryStr = L"[State Setting]";
			break;
		case D3D12_MESSAGE_CATEGORY_STATE_GETTING:
			categoryStr = L"[State Getting]";
			break;
		case D3D12_MESSAGE_CATEGORY_RESOURCE_MANIPULATION:
			categoryStr = L"[Resource Manipulation]";
			break;
		case D3D12_MESSAGE_CATEGORY_EXECUTION:
			categoryStr = L"[Category Execution]";
			break;
		case D3D12_MESSAGE_CATEGORY_SHADER:
			categoryStr = L"[Category Shader]";
			break;
		default:
			categoryStr = L"[Unknown]";
			break;
		}

		std::wstring dets = SA::Intl::StringFormat(L"ID [%1]\tCategory [%2]", static_cast<int>(_ID), categoryStr);

		switch (_severity)
		{
		case D3D12_MESSAGE_SEVERITY_CORRUPTION:
			SA_LOG(_description, AssertFailure, SA.Render.DX12.ValidationLayers, std::move(dets));
			break;
		case D3D12_MESSAGE_SEVERITY_ERROR:
			SA_LOG(_description, Error, SA.Render.DX12.ValidationLayers, std::move(dets));
			break;
		case D3D12_MESSAGE_SEVERITY_WARNING:
			SA_LOG(_description, Warning, SA.Render.DX12.ValidationLayers, std::move(dets));
			break;
		case D3D12_MESSAGE_SEVERITY_INFO:
			SA_LOG(_description, Infos, SA.Render.DX12.ValidationLayers, std::move(dets));
			break;
		case D3D12_MESSAGE_SEVERITY_MESSAGE:
		default:
			SA_LOG(_description, Normal, SA.Render.DX12.ValidationLayers, std::move(dets));
			break;
		}
	}
}

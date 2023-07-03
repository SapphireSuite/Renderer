// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/D12Pipeline.hpp>

#include <Device/D12Device.hpp>

#include <Pipeline/D12RootSignature.hpp>

namespace SA::RND::DX12
{
	void Pipeline::Create(const Device& _device, const GraphicsPipelineInfo& _info)
	{
		// TODO: Clean.
		D3D12_RENDER_TARGET_BLEND_DESC rtBlend{
			.BlendEnable = false,
			.LogicOpEnable = false,

			.SrcBlend = D3D12_BLEND_ONE,
			.DestBlend = D3D12_BLEND_ZERO,
			.BlendOp = D3D12_BLEND_OP_ADD,

			.SrcBlendAlpha = D3D12_BLEND_ONE,
			.DestBlendAlpha = D3D12_BLEND_ZERO,
			.BlendOpAlpha = D3D12_BLEND_OP_ADD,

			.LogicOp = D3D12_LOGIC_OP_NOOP,
		
			.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL,
		};

		D3D12_BLEND_DESC blendState{
			.AlphaToCoverageEnable = false,
			.IndependentBlendEnable = false,

			.RenderTarget
			{
				rtBlend,
				rtBlend,
				rtBlend,
				rtBlend,
				rtBlend,
				rtBlend,
				rtBlend,
				rtBlend
			}
		};

		D3D12_DEPTH_STENCIL_DESC depthStencilState{
			.DepthEnable = true,
			.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL,
			.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL,
			.StencilEnable = false,
			.StencilReadMask = 0,
			.StencilWriteMask = 0,
			.FrontFace = {},
			.BackFace = {},
		};
		//

		uint32_t RTNum = 0;
		for (; RTNum < 8; ++RTNum)
		{
			if (_info.rtvFormats[RTNum] == DXGI_FORMAT_UNKNOWN)
				break;
		}


		D3D12_GRAPHICS_PIPELINE_STATE_DESC dxDesc
		{
			.pRootSignature = _info.rootSign->operator->().Get(),

			.VS = _info.shaderStages.vs,
			.PS = _info.shaderStages.ps,
			.GS = _info.shaderStages.gs,

			.StreamOutput = {},

			.BlendState = blendState,

			.SampleMask = UINT_MAX,

			.RasterizerState = _info.raster,
			.DepthStencilState = depthStencilState,

			.InputLayout
			{
				.pInputElementDescs = _info.vertexInputElements.data(),
				.NumElements = static_cast<uint32_t>(_info.vertexInputElements.size()),
			},

			.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,

			.NumRenderTargets = RTNum,
			.RTVFormats
			{
				_info.rtvFormats[0],
				_info.rtvFormats[1],
				_info.rtvFormats[2],
				_info.rtvFormats[3],
				_info.rtvFormats[4],
				_info.rtvFormats[5],
				_info.rtvFormats[6],
				_info.rtvFormats[7],
			},
			.DSVFormat = _info.dsvFormat,

			.SampleDesc
			{
				.Count = _info.sampling,
				.Quality = 0,
			},

			.NodeMask = 0,

			.CachedPSO
			{
				.pCachedBlob = nullptr,
				.CachedBlobSizeInBytes = 0,
			},

			.Flags = D3D12_PIPELINE_STATE_FLAG_NONE,
		};

		Create(_device, dxDesc);
	}

	void Pipeline::Create(const Device& _device, const D3D12_GRAPHICS_PIPELINE_STATE_DESC& _desc)
	{
		SA_DX12_API(_device->CreateGraphicsPipelineState(&_desc, IID_PPV_ARGS(mHandle.GetAddressOf())));
		
		SA_LOG(L"Pipeline created.", Info, SA.Render.DX12, (L"Handle [%1]", mHandle.Get()));
	}
	
	void Pipeline::Destroy()
	{
		if (mHandle)
		{
			SA_LOG_RAII(L"Pipeline destroyed.", Info, SA.Render.DX12, (L"Handle [%1]", mHandle.Get()));

			mHandle.Reset();
		}
	}

	
	DXPipelineT Pipeline::operator->() const
	{
		return mHandle;
	}
}

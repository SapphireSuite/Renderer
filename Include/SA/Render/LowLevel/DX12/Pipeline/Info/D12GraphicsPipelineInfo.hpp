// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_D12_GRAPHICS_PIPELINE_GUARD
#define SAPPHIRE_RENDER_D12_GRAPHICS_PIPELINE_GUARD

#include <vector>

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

namespace SA::RND::DX12
{
	class RootSignature;

	struct GraphicsPipelineShaderStages
	{
		D3D12_SHADER_BYTECODE vs;
		D3D12_SHADER_BYTECODE ps;
		D3D12_SHADER_BYTECODE gs;
	};

	struct GraphicsPipelineInfo
	{
		const RootSignature* rootSign = nullptr;

		GraphicsPipelineShaderStages shaderStages;

		D3D12_RASTERIZER_DESC raster;

		std::vector<D3D12_INPUT_ELEMENT_DESC> vertexInputElements;

		DXGI_FORMAT rtvFormats[8] = { DXGI_FORMAT_R8G8B8A8_UNORM_SRGB };
		DXGI_FORMAT dsvFormat = DXGI_FORMAT_D16_UNORM;

		uint32_t sampling = 1;
	};
}

#endif // SAPPHIRE_RENDER_D12_GRAPHICS_PIPELINE_GUARD

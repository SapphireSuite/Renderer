// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_FRAME_BUFFER_GUARD
#define SAPPHIRE_RENDER_DX12_FRAME_BUFFER_GUARD

#include "Info/D12PassInfo.hpp"

namespace SA::RND::DX12
{
	class Device;

	class FrameBuffer
	{
		std::vector<MComPtr<ID3D12Resource>> mImageBuffers;

		MComPtr<ID3D12DescriptorHeap> mRenderTargetViewHeap = nullptr;

		struct SubpassViewHeap
		{
			/// Number of render target in subapss.
			uint32_t num = 0u;

			D3D12_CPU_DESCRIPTOR_HANDLE colorViewHeap = 0u;

			D3D12_CPU_DESCRIPTOR_HANDLE depthViewHeap = 0u;
		};

		/// Per-subpass render target view heap handle.
		std::vector<SubpassViewHeap> mSubpassViewHeaps;

		uint32_t mCurrSubpassIndex = 0u;

	public:
		void Create(const Device& _device, const PassInfo& _info, MComPtr<ID3D12Resource> _presentImage = nullptr);
		void Destroy();

		void BindNextSubpass();
	};
}

#endif // SAPPHIRE_RENDER_DX12_FRAME_BUFFER_GUARD

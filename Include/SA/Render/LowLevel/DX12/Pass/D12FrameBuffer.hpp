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
		MComPtr<ID3D12DescriptorHeap> mRenderTargetViewHeap = nullptr;
		MComPtr<ID3D12DescriptorHeap> mDepthStencilViewHeap = nullptr;

		uint32_t mRTVDescriptorIncrementSize = 0;
		uint32_t mDSVDescriptorIncrementSize = 0;

	public:
		struct Attachment
		{
			MComPtr<ID3D12Resource> imageBuffer;
			D3D12_CLEAR_VALUE clearValue{};
			D3D12_RESOURCE_STATES state = D3D12_RESOURCE_STATE_COMMON;
		};
		
		struct SubpassViewHeap
		{
			/// Number of render target in subapss.
			uint32_t colorRTNum = 0u;

			D3D12_CPU_DESCRIPTOR_HANDLE colorViewHeap{ 0 };

			D3D12_CPU_DESCRIPTOR_HANDLE depthViewHeap{ 0 };
		};

	private:
		std::vector<Attachment> mAttachments;

		/// Per-subpass render target view heap handle.
		std::vector<SubpassViewHeap> mSubpassViewHeaps;

		uint32_t CountRTOffset(uint32_t _subpassIndex) const;

	public:
		void Create(const Device& _device, const PassInfo& _info, MComPtr<ID3D12Resource> _presentImage = nullptr);
		void Destroy();

		uint32_t GetRTVDescriptorIncrementSize() const;
		uint32_t GetDSVDescriptorIncrementSize() const;

		Attachment* GetSubpassAttachments(uint32_t _subpassIndex);
		const SubpassViewHeap& GetSubpassViewHeap(uint32_t _subpassIndex) const;
	};
}

#endif // SAPPHIRE_RENDER_DX12_FRAME_BUFFER_GUARD

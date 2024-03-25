// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_D12_FRAMEBUFFER_GUARD
#define SAPPHIRE_RENDER_D12_FRAMEBUFFER_GUARD

#include "Info/D12RenderPassInfo.hpp"

namespace SA::RND::DX12
{
	class FrameBuffer
	{
		MComPtr<ID3D12DescriptorHeap> mRenderTargetViewHeap = nullptr;
		MComPtr<ID3D12DescriptorHeap> mDepthStencilViewHeap = nullptr;

		uint32_t mRTVDescriptorIncrementSize = 0;
		uint32_t mDSVDescriptorIncrementSize = 0;

	public:
		struct Attachment
		{
			MComPtr<ID3D12Resource> texture;
			MComPtr<ID3D12Resource> resolved;
			D3D12_CLEAR_VALUE clearValue{};
			mutable D3D12_RESOURCE_STATES state = D3D12_RESOURCE_STATE_COMMON;
		};

		struct SubpassFrame
		{
			std::vector<Attachment> attachments;

			D3D12_CPU_DESCRIPTOR_HANDLE colorViewHeap{ 0 };
			D3D12_CPU_DESCRIPTOR_HANDLE depthViewHeap{ 0 };
		};

	private:
		std::vector<SubpassFrame> mSubpassFrames;

	public:
		void Create(const Device& _device, const RenderPassInfo& _info);
		void Destroy();

		uint32_t GetRTVDescriptorIncrementSize() const;
		uint32_t GetDSVDescriptorIncrementSize() const;

		uint32_t GetSubpassNum() const;
		const SubpassFrame& GetSubpassFrame(uint32_t _subpassIndex) const;
	};
}

#endif // SAPPHIRE_RENDER_D12_FRAMEBUFFER_GUARD

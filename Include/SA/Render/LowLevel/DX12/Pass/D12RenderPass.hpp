// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_RENDER_PASS_GUARD
#define SAPPHIRE_RENDER_DX12_RENDER_PASS_GUARD

#include "Info/D12PassInfo.hpp"

namespace SA::RND::DX12
{
	class Device;
	class CommandList;
	class FrameBuffer;

	class RenderPass
	{
		PassInfo mPassInfo;

		uint32_t mCurrSubpassIndex = 0u;
		DX12::FrameBuffer* mCurrFrameBuffer = nullptr;

	public:
		void Create(const PassInfo& _info);
		void Destroy();

		void Begin(const CommandList& _cmd, FrameBuffer& _fBuff);
		void NextSubpass(const CommandList& _cmd);
		void End(const CommandList& _cmd);
	};
}

#endif // SAPPHIRE_RENDER_DX12_RENDER_PASS_GUARD

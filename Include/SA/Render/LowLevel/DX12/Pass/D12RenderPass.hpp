// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_D12_RENDER_PASS_GUARD
#define SAPPHIRE_RENDER_D12_RENDER_PASS_GUARD

#include "Info/D12RenderPassInfo.hpp"

namespace SA::RND::DX12
{
	class Device;
	class CommandList;
	class FrameBuffer;

	class RenderPass
	{
		uint32_t mCurrSubpassIndex = 0u;
		const DX12::FrameBuffer* mCurrFrameBuffer = nullptr;

	//{ Info

		struct SubpassInfo
		{
			struct AttachInfo
			{
				/// Initial State of the attached resource.
				D3D12_RESOURCE_STATES initialState = D3D12_RESOURCE_STATE_COMMON;

				/// Current rendering state of the attached resoure.
				D3D12_RESOURCE_STATES renderState = D3D12_RESOURCE_STATE_COMMON;

				/// Final state to use to render the attached resource.
				D3D12_RESOURCE_STATES finalState = D3D12_RESOURCE_STATE_COMMON;
			};

			std::vector<AttachInfo> attachInfos;
		};

		std::vector<SubpassInfo> mSubpassInfos;

	//}

	public:
		void Create(const RenderPassInfo& _info);
		void Destroy();

		void Begin(const CommandList& _cmd, const FrameBuffer& _fBuff);
		void NextSubpass(const CommandList& _cmd);
		void End(const CommandList& _cmd);

		operator bool() const noexcept;
	};
}

#endif // SAPPHIRE_RENDER_D12_RENDER_PASS_GUARD

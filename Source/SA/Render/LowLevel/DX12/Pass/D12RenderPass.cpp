// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <Pass/D12RenderPass.hpp>

#include <SA/Collections/Debug>

#include <Pass/D12FrameBuffer.hpp>
#include <Device/Command/D12CommandList.hpp>

namespace SA::RND::DX12
{
	void RenderPass::Create(const RenderPassInfo& _info)
	{
		mSubpassInfos.reserve(_info.subpasses.size());

		for (auto subpassIt = _info.subpasses.begin(); subpassIt != _info.subpasses.end(); ++subpassIt)
		{
			auto& subpassInfo = mSubpassInfos.emplace_back();

			subpassInfo.attachInfos.reserve(subpassIt->attachments.size());

			for (auto& attach : subpassIt->attachments)
			{
				auto& attachInfo = subpassInfo.attachInfos.emplace_back();

				if (IsPresentFormat(_info.textureToDescriptorMap.at(attach.texture).format))
				{
					attachInfo.texture.bPresent = true;
				}
				else if (attach.resolved && IsPresentFormat(_info.textureToDescriptorMap.at(attach.resolved).format))
				{
					attachInfo.resolved.bPresent = true;
				}

				for (auto nextSubpassIt = subpassIt; nextSubpassIt != _info.subpasses.end(); ++nextSubpassIt)
				{
					for (auto& nextInput : nextSubpassIt->inputs)
					{
						if (nextInput == attach.texture)
						{
							attachInfo.texture.bUsedAsInput = true;
						}
						if (nextInput == attach.resolved)
						{
							attachInfo.resolved.bUsedAsInput = true;
						}
					}
				}
			}
		}
	}

	void RenderPass::Destroy()
	{
		mSubpassInfos.clear();
	}


	void RenderPass::Begin(const CommandList& _cmd, const FrameBuffer& _fBuff)
	{
		mCurrSubpassIndex = uint32_t(-1);
		mCurrFrameBuffer = &_fBuff;

		NextSubpass(_cmd);
	}

	void RenderPass::NextSubpass(const CommandList& _cmd)
	{
		++mCurrSubpassIndex;

		std::vector<D3D12_RESOURCE_BARRIER> barriers;
		barriers.reserve(24);

		// Prev Subpass
		const uint32_t prevSubpassIndex = mCurrSubpassIndex - 1;

		if (prevSubpassIndex != uint32_t(-1))
		{
			auto& prevSubpassFrame = mCurrFrameBuffer->GetSubpassFrame(prevSubpassIndex);
			const std::vector<FrameBuffer::Attachment>& prevFBuffAttachs = prevSubpassFrame.attachments;

			// Resolve
			{
				// Transition To Resolve src/dst
				{
					for (auto& fBuffAttach : prevFBuffAttachs)
					{
						if (!fBuffAttach.resolved)
							continue;

						D3D12_RESOURCE_BARRIER& barrier1 = barriers.emplace_back();
						barrier1.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
						barrier1.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
						barrier1.Transition.pResource = fBuffAttach.texture.Get();
						barrier1.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
						barrier1.Transition.StateBefore = fBuffAttach.state;
						barrier1.Transition.StateAfter = D3D12_RESOURCE_STATE_RESOLVE_SOURCE;

						D3D12_RESOURCE_BARRIER& barrier2 = barriers.emplace_back();
						barrier2.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
						barrier2.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
						barrier2.Transition.pResource = fBuffAttach.resolved.Get();
						barrier2.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
						barrier2.Transition.StateBefore = IsPresentFormat(fBuffAttach.resolved->GetDesc().Format) ? D3D12_RESOURCE_STATE_PRESENT : fBuffAttach.state;
						barrier2.Transition.StateAfter = D3D12_RESOURCE_STATE_RESOLVE_DEST;
					}

					if (barriers.size())
					{
						_cmd->ResourceBarrier(static_cast<UINT>(barriers.size()), barriers.data());
						barriers.clear();
					}
				}

				// Resolve
				{
					for (auto& fBuffAttach : prevFBuffAttachs)
					{
						if (!fBuffAttach.resolved)
							continue;

						_cmd->ResolveSubresource(fBuffAttach.resolved.Get(), 0,
							fBuffAttach.texture.Get(), 0,
							fBuffAttach.resolved->GetDesc().Format
						);
					}
				}

				// Transition from Resolve src/dst
				{
					for (auto& fBuffAttach : prevFBuffAttachs)
					{
						if (!fBuffAttach.resolved)
							continue;

						D3D12_RESOURCE_BARRIER& barrier1 = barriers.emplace_back();
						barrier1.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
						barrier1.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
						barrier1.Transition.pResource = fBuffAttach.texture.Get();
						barrier1.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
						barrier1.Transition.StateBefore = D3D12_RESOURCE_STATE_RESOLVE_SOURCE;
						barrier1.Transition.StateAfter = fBuffAttach.state;
					}
				}
			}

			// Transition to next
			{
				// Apply transition to prev subpass.
				for (uint32_t i = 0; i < prevFBuffAttachs.size(); ++i)
					//for (auto& fBuffAttach : prevFBuffAttachs)
				{
					auto& fBuffAttach = prevFBuffAttachs[i];
					auto& attachInfo = mSubpassInfos[prevSubpassIndex].attachInfos[i];

					D3D12_RESOURCE_BARRIER barrier1{};
					barrier1.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
					barrier1.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
					barrier1.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
					barrier1.Transition.pResource = fBuffAttach.texture.Get();
					barrier1.Transition.StateBefore = fBuffAttach.state;

					if (attachInfo.texture.bUsedAsInput)
					{
						barrier1.Transition.StateAfter = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE | D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
					}
					else if (attachInfo.texture.bPresent)
					{
						barrier1.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
					}

					if (barrier1.Transition.StateBefore != barrier1.Transition.StateAfter)
					{
						fBuffAttach.state = barrier1.Transition.StateAfter;
						barriers.emplace_back(barrier1);
					}


					if (fBuffAttach.resolved)
					{
						D3D12_RESOURCE_BARRIER barrier2{};
						barrier2.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
						barrier2.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
						barrier2.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
						barrier2.Transition.pResource = fBuffAttach.resolved.Get();
						barrier2.Transition.StateBefore = D3D12_RESOURCE_STATE_RESOLVE_DEST;

						if (attachInfo.resolved.bUsedAsInput)
						{
							barrier2.Transition.StateAfter = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE | D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
						}
						else if (attachInfo.resolved.bPresent)
						{
							barrier2.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
						}

						if (barrier2.Transition.StateBefore != barrier2.Transition.StateAfter)
						{
							// State only reflect texture attachment state, not resolved one.

							barriers.emplace_back(barrier2);
						}
					}
				}

				// If no currPass: submit prev only barriers.
				if (mCurrSubpassIndex >= mCurrFrameBuffer->GetSubpassNum() && barriers.size())
					_cmd->ResourceBarrier(static_cast<UINT>(barriers.size()), barriers.data());
			}
		}


		// Curr Subpass
		if (mCurrSubpassIndex < mCurrFrameBuffer->GetSubpassNum())
		{
			uint32_t colorAttachNum = 0u;

			auto& currSubpassFrame = mCurrFrameBuffer->GetSubpassFrame(mCurrSubpassIndex);
			const std::vector<FrameBuffer::Attachment>& currFBuffAttachs = currSubpassFrame.attachments;

			// Transition
			{
				for (auto& fBuffAttach : currFBuffAttachs)
				{
					D3D12_RESOURCE_BARRIER barrier{};
					barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
					barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
					barrier.Transition.pResource = fBuffAttach.texture.Get();
					barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
					barrier.Transition.StateBefore = fBuffAttach.state;

					auto desc = fBuffAttach.texture->GetDesc();

					if (desc.Flags & D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET)
					{
						barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
					}
					else if (desc.Flags & D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL)
					{
						barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_DEPTH_WRITE;
					}

					if (barrier.Transition.StateBefore != barrier.Transition.StateAfter)
					{
						fBuffAttach.state = barrier.Transition.StateAfter;
						barriers.emplace_back(barrier);
					}
				}

				// Submit prev and curr barriers.
				if (barriers.size())
					_cmd->ResourceBarrier(static_cast<UINT>(barriers.size()), barriers.data());
			}

			// Clear
			{
				D3D12_CPU_DESCRIPTOR_HANDLE colorDescHandle = currSubpassFrame.colorViewHeap;
				D3D12_CPU_DESCRIPTOR_HANDLE depthDescHandle = currSubpassFrame.depthViewHeap;

				for (auto& fBuffAttach : currFBuffAttachs)
				{
					if (fBuffAttach.clearValue.Color[0] < 0.0f)
						continue;

					auto desc = fBuffAttach.texture->GetDesc();

					if (desc.Flags & D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET)
					{
						++colorAttachNum; // Only count Color Render Targets (no depth).

						_cmd->ClearRenderTargetView(colorDescHandle, fBuffAttach.clearValue.Color, 0, nullptr);
						colorDescHandle.ptr += mCurrFrameBuffer->GetRTVDescriptorIncrementSize();
					}
					else if (desc.Flags & D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL)
					{
						auto& DSClearValue = fBuffAttach.clearValue.DepthStencil;
						_cmd->ClearDepthStencilView(depthDescHandle, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, DSClearValue.Depth, DSClearValue.Stencil, 0, nullptr);
						depthDescHandle.ptr += mCurrFrameBuffer->GetDSVDescriptorIncrementSize();
					}
				}
			}

			// Binding
			{
				_cmd->OMSetRenderTargets(
					colorAttachNum,
					&currSubpassFrame.colorViewHeap,
					true,
					currSubpassFrame.depthViewHeap.ptr ? &currSubpassFrame.depthViewHeap : nullptr
				);
			}
		}
	}

	void RenderPass::End(const CommandList& _cmd)
	{
		// Transition to present.
		NextSubpass(_cmd);

		mCurrSubpassIndex = 0u;
		mCurrFrameBuffer = nullptr;
	}


	RenderPass::operator bool() const noexcept
	{
		return mSubpassInfos.size();
	}
}

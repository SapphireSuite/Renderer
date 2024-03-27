// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#include <Pass/D12RenderPass.hpp>

#include <SA/Collections/Debug>

#include <Pass/D12FrameBuffer.hpp>
#include <Device/Command/D12CommandList.hpp>

namespace SA::RND::DX12
{
	namespace Intl
	{
		D3D12_RESOURCE_STATES GetReadOnlyImageLayout(const TextureDescriptor& _desc)
		{
			D3D12_RESOURCE_STATES state = D3D12_RESOURCE_STATE_COMMON;

			if (_desc.usage & D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET)
				state = D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE;
			else if (_desc.usage & D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL)
				state = D3D12_RESOURCE_STATE_DEPTH_READ;

			return state;
		}

		D3D12_RESOURCE_STATES GetReadWriteImageLayout(const TextureDescriptor& _desc)
		{
			D3D12_RESOURCE_STATES state = D3D12_RESOURCE_STATE_COMMON;

			if (_desc.usage & D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET)
				state = D3D12_RESOURCE_STATE_RENDER_TARGET;
			else if (_desc.usage & D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL)
				state = D3D12_RESOURCE_STATE_DEPTH_WRITE;

			return state;
		}

		D3D12_RESOURCE_STATES FindRenderState(const AttachmentInfo& _attach,
			const TextureDescriptor& _desc)
		{
			if (_desc.usage & D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET)
				return D3D12_RESOURCE_STATE_RENDER_TARGET;
			else if (_desc.usage & D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL)
			{
				switch (_attach.accessMode)
				{
					case AttachmentAccessMode::ReadWrite:
					{
						return D3D12_RESOURCE_STATE_DEPTH_WRITE;
					}
					case AttachmentAccessMode::ReadOnly:
					{
						return D3D12_RESOURCE_STATE_DEPTH_READ;
					}
					default:
					{
						SA_LOG((L"AttachmentAccessMode [%1] not supported yet!", _attach.accessMode), Error, SA.Render.DX12.RenderPass);
						break;
					}
				}
			}

			return D3D12_RESOURCE_STATE_RENDER_TARGET;
		}

		D3D12_RESOURCE_STATES FindNextState(const std::vector<SubpassInfo>& _subpasses,
			std::vector<SubpassInfo>::const_iterator _currSubpassIt,
			const Texture* _texture,
			const TextureDescriptor& _desc,
			D3D12_RESOURCE_STATES initialState)
		{
			D3D12_RESOURCE_STATES nextState = D3D12_RESOURCE_STATE_COMMON;

			for (auto nextSubpassIt = _currSubpassIt + 1; nextSubpassIt != _subpasses.end() && nextState == D3D12_RESOURCE_STATE_COMMON; ++nextSubpassIt)
			{
				// Parse all next subpass attachments (RT).
				for (auto& nextAttach : nextSubpassIt->attachments)
				{
					if (nextAttach.texture == _texture)
					{
						switch (nextAttach.accessMode)
						{
							case AttachmentAccessMode::ReadWrite:
							{
								nextState = GetReadWriteImageLayout(_desc);
								break;
							}
							case AttachmentAccessMode::ReadOnly:
							{
								nextState = GetReadOnlyImageLayout(_desc);
								break;
							}
							default:
							{
								SA_LOG((L"AttachmentAccessMode [%1] not supported yet!", nextAttach.accessMode), Error, SA.Render.DX12.RenderPass);
								break;
							}
						}
					}
				}

				// Next layout already found.
				if (nextState != D3D12_RESOURCE_STATE_COMMON)
					break;

				// Parse all next subpass input attachments.
				for (auto& nextInputTexture : nextSubpassIt->inputs)
				{
					if (nextInputTexture == _texture)
					{
						nextState = GetReadOnlyImageLayout(_desc);
						break;
					}
				}
			}

			if (IsPresentFormat(_desc.format) && _desc.sampling == 1)
			{
				nextState = D3D12_RESOURCE_STATE_PRESENT;
			}

			/**
			* Layer still not found: fallback values.
			* Attachment not used in any next subpasses and not used as present.
			*/
			else if (nextState == D3D12_RESOURCE_STATE_COMMON)
			{
				if (initialState != D3D12_RESOURCE_STATE_COMMON)
				{
					nextState = initialState;
				}
				else if(_desc.usage & D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE)
				{
					// Default read write.
					nextState = GetReadWriteImageLayout(_desc);
				}
				else
				{
					// Default read only if sampled/input is enabled.
					nextState = GetReadOnlyImageLayout(_desc);
				}
			}

			return nextState;
		}
	}


	void RenderPass::Create(const RenderPassInfo& _info)
	{
		mSubpassInfos.reserve(_info.subpasses.size());

		std::unordered_map<const Texture*, D3D12_RESOURCE_STATES> textureToStateMap;

		for (auto inSubpassIt = _info.subpasses.begin(); inSubpassIt != _info.subpasses.end(); ++inSubpassIt)
		{
			auto& subpassInfo = mSubpassInfos.emplace_back();

			for (auto& inAttach : inSubpassIt->attachments)
			{
				const TextureDescriptor& desc = _info.textureToDescriptorMap.at(inAttach.texture);

				auto& attachInfo = subpassInfo.attachInfos.emplace_back();

				D3D12_RESOURCE_STATES initialState = D3D12_RESOURCE_STATE_COMMON;

				auto currStateIt = textureToStateMap.find(inAttach.texture);
				if (currStateIt != textureToStateMap.end())
					initialState = currStateIt->second;

				attachInfo.renderState = Intl::FindRenderState(inAttach, desc);
				attachInfo.finalState = Intl::FindNextState(_info.subpasses, inSubpassIt, inAttach.texture, desc, initialState);
				textureToStateMap[inAttach.texture] = attachInfo.finalState;
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
		barriers.reserve(32);

		// Prev Subpass
		const uint32_t prevSubpassIndex = mCurrSubpassIndex - 1;

		if (prevSubpassIndex != uint32_t(-1))
		{
			auto& prevSubpassFrame = mCurrFrameBuffer->GetSubpassFrame(prevSubpassIndex);
			const std::vector<FrameBuffer::Attachment>& prevFBuffAttachs = prevSubpassFrame.attachments;

			/*
			// Resolve
			if(false)
			{
				// Transition To Resolve src/dst
				{
					for (uint32_t i = 0; i < prevFBuffAttachs.size(); ++i)
					{
						auto& prevFBuffAttach = prevFBuffAttachs[i];

						if (!prevFBuffAttach.resolved)
							continue;

						auto& prevAttachInfo = mSubpassInfos[prevSubpassIndex].attachInfos[i];

						D3D12_RESOURCE_BARRIER& barrier1 = barriers.emplace_back();
						barrier1.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
						barrier1.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
						barrier1.Transition.pResource = prevFBuffAttach.texture.Get();
						barrier1.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
						barrier1.Transition.StateBefore = prevAttachInfo.finalState;
						barrier1.Transition.StateAfter = D3D12_RESOURCE_STATE_RESOLVE_SOURCE;

						D3D12_RESOURCE_BARRIER& barrier2 = barriers.emplace_back();
						barrier2.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
						barrier2.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
						barrier2.Transition.pResource = prevFBuffAttach.resolved.Get();
						barrier2.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
						barrier2.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON; // TODO
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
					for (auto& prevFBuffAttach : prevFBuffAttachs)
					{
						if (!prevFBuffAttach.resolved)
							continue;

						_cmd->ResolveSubresource(prevFBuffAttach.resolved.Get(), 0,
							prevFBuffAttach.texture.Get(), 0,
							prevFBuffAttach.resolved->GetDesc().Format
						);
					}
				}


				// Transition from Resolve src/dst
				{
					for (uint32_t i = 0; i < prevFBuffAttachs.size(); ++i)
					{
						auto& prevFBuffAttach = prevFBuffAttachs[i];

						if (!prevFBuffAttach.resolved)
							continue;

						auto& prevAttachInfo = mSubpassInfos[prevSubpassIndex].attachInfos[i];

						D3D12_RESOURCE_BARRIER& barrier1 = barriers.emplace_back();
						barrier1.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
						barrier1.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
						barrier1.Transition.pResource = prevFBuffAttach.texture.Get();
						barrier1.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
						barrier1.Transition.StateBefore = D3D12_RESOURCE_STATE_RESOLVE_SOURCE;
						barrier1.Transition.StateAfter = prevAttachInfo.finalState;

						// TODO: Resolve barrier?
					}
				}
			}
			*/

			// Transition to next subpass.
			{
				for (uint32_t i = 0; i < prevFBuffAttachs.size(); ++i)
				{
					auto& prevFBuffAttach = prevFBuffAttachs[i];
					auto& prevAttachInfo = mSubpassInfos[prevSubpassIndex].attachInfos[i];

					if (prevAttachInfo.renderState != prevAttachInfo.finalState)
					{
						D3D12_RESOURCE_BARRIER& barrier = barriers.emplace_back();
						barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
						barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
						barrier.Transition.pResource = prevFBuffAttach.texture->GetInternalPtr();
						barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
						barrier.Transition.StateBefore = prevAttachInfo.renderState;
						barrier.Transition.StateAfter = prevAttachInfo.finalState;

						prevFBuffAttach.texture->SetPendingState(prevAttachInfo.finalState);
					}
				}
			}

			// If no currPass: submit prev only barriers.
			if (mCurrSubpassIndex >= mCurrFrameBuffer->GetSubpassNum() && barriers.size())
			{
				_cmd->ResourceBarrier(static_cast<UINT>(barriers.size()), barriers.data());
				barriers.clear();
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
				for(uint32_t i = 0; i < currFBuffAttachs.size(); ++i)
				{
					auto& fBuffAttach = currFBuffAttachs[i];
					auto& attachInfo = mSubpassInfos[mCurrSubpassIndex].attachInfos[i];

					const D3D12_RESOURCE_STATES currState = fBuffAttach.texture->GetState();

					if (currState != attachInfo.renderState)
					{
						D3D12_RESOURCE_BARRIER& barrier = barriers.emplace_back();
						barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
						barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
						barrier.Transition.pResource = fBuffAttach.texture->GetInternalPtr();
						barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
						barrier.Transition.StateBefore = currState;
						barrier.Transition.StateAfter = attachInfo.renderState;

						fBuffAttach.texture->SetPendingState(attachInfo.renderState);
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

					auto desc = fBuffAttach.texture->Get()->GetDesc();

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

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/D12RenderPass.hpp>

#include <Pass/D12FrameBuffer.hpp>
#include <Device/Command/D12CommandList.hpp>

namespace SA::RND::DX12
{
	void RenderPass::Create(const PassInfo& _info)
	{
		mPassInfo = _info;
	}

	void RenderPass::Destroy()
	{
	}


	void RenderPass::Begin(const CommandList& _cmd, FrameBuffer& _fBuff)
	{
		mCurrSubpassIndex = uint32_t(-1);
		mCurrFrameBuffer = &_fBuff;

		NextSubpass(_cmd);
	}

	void RenderPass::NextSubpass(const CommandList& _cmd)
	{
		++mCurrSubpassIndex;

		std::vector<D3D12_RESOURCE_BARRIER> barriers;
		barriers.reserve(16);

		// Prev Subpass
		const uint32_t prevSubpassIndex = mCurrSubpassIndex - 1;
		
		if (prevSubpassIndex != uint32_t(-1))
		{
			// Transition
			{
				SA_ASSERT((OutOfArrayRange, prevSubpassIndex, mPassInfo.subpasses));
				auto& prevSubpassInfo = mPassInfo.subpasses[prevSubpassIndex];

				auto& prevSubpassFrame = mCurrFrameBuffer->GetSubpassFrame(prevSubpassIndex);
				std::vector<FrameBuffer::Attachment>& prevFBuffAttachs = prevSubpassFrame.attachments;

				// Apply transition to prev subpass.
				for (uint32_t fBuffAttachIndex = 0; auto & attachInfo : prevSubpassInfo.attachments)
				{
					auto& fBuffAttach = attachInfo.type == AttachmentType::Depth ? prevSubpassFrame.depthAttachment : prevFBuffAttachs[fBuffAttachIndex++];

					D3D12_RESOURCE_BARRIER barrier;
					barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
					barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
					barrier.Transition.pResource = fBuffAttach.imageBuffer.Get();
					barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
					barrier.Transition.StateBefore = fBuffAttach.state;

					switch (attachInfo.type)
					{
						case AttachmentType::Color:
						{
							switch (attachInfo.usage)
							{
								case AttachmentUsage::InputNext:
								{
									barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE | D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
									break;
								}
								case AttachmentUsage::Present:
								{
									barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
									break;
								}
								default:
								{
									SA_LOG((L"AttachmentUsage [%1] not supported", attachInfo.usage), Error, SA.Render.DX12);
									break;
								}
							}

							break;
						}
						case AttachmentType::Depth:
						{
							if (attachInfo.usage != AttachmentUsage::InputNext)
								continue;

							barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_DEPTH_READ;
							break;
						}
						default:
						{
							SA_LOG((L"AttachmentType [%1] not supported", attachInfo.type), Error, SA.Render.DX12);
							continue;
							break;
						}
					}

					if (barrier.Transition.StateBefore != barrier.Transition.StateAfter)
					{
						fBuffAttach.state = barrier.Transition.StateAfter;
						barriers.emplace_back(barrier);
					}
				}
			
				// If no currPass: submit prev only barriers.
				if (mCurrSubpassIndex >= static_cast<uint32_t>(mPassInfo.subpasses.size()) && barriers.size())
					_cmd->ResourceBarrier(static_cast<UINT>(barriers.size()), barriers.data());
			}
		}


		// Curr Subpass
		if (mCurrSubpassIndex < static_cast<uint32_t>(mPassInfo.subpasses.size()))
		{
			SA_ASSERT((OutOfArrayRange, mCurrSubpassIndex, mPassInfo.subpasses));
			auto& currSubpassInfo = mPassInfo.subpasses[mCurrSubpassIndex];

			auto& currSubpassFrame = mCurrFrameBuffer->GetSubpassFrame(mCurrSubpassIndex);
			std::vector<FrameBuffer::Attachment>& currFBuffAttachs = currSubpassFrame.attachments;

			// Transition
			{
				for(uint32_t fBuffAttachIndex = 0; auto& attachInfo : currSubpassInfo.attachments)
				{
					auto& fBuffAttach = attachInfo.type == AttachmentType::Depth ? currSubpassFrame.depthAttachment : currFBuffAttachs[fBuffAttachIndex++];

					D3D12_RESOURCE_BARRIER barrier;
					barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
					barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
					barrier.Transition.pResource = fBuffAttach.imageBuffer.Get();
					barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
					barrier.Transition.StateBefore = fBuffAttach.state;

					switch (attachInfo.type)
					{
						case AttachmentType::Color:
						{
							barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
							break;
						}
						case AttachmentType::Depth:
						{
							barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_DEPTH_WRITE;
							break;
						}
						default:
						{
							SA_LOG((L"AttachmentType [%1] not supported", attachInfo.type), Error, SA.Render.DX12);
							continue;
							break;
						}
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

				for (uint32_t fBuffAttachIndex = 0; auto & attachInfo : currSubpassInfo.attachments)
				{
					if (!attachInfo.bClearOnLoad)
						continue;

					switch (attachInfo.type)
					{
						case AttachmentType::Color:
						{
							_cmd->ClearRenderTargetView(colorDescHandle, currFBuffAttachs[fBuffAttachIndex++].clearValue.Color, 0, nullptr);
							colorDescHandle.ptr += mCurrFrameBuffer->GetRTVDescriptorIncrementSize();
							break;
						}
						case AttachmentType::Depth:
						{
							auto DSClearValue = currSubpassFrame.depthAttachment.clearValue.DepthStencil;
							_cmd->ClearDepthStencilView(depthDescHandle, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, DSClearValue.Depth, DSClearValue.Stencil, 0, nullptr);
							depthDescHandle.ptr += mCurrFrameBuffer->GetDSVDescriptorIncrementSize();
							break;
						}
						default:
						{
							SA_LOG((L"AttachmentType [%1] not supported", attachInfo.type), Error, SA.Render.DX12);
							break;
						}
					}
				}
			}

			// Binding
			{
				_cmd->OMSetRenderTargets(
					static_cast<uint32_t>(currSubpassFrame.attachments.size()),
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
}

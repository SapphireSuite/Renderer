// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_ATTACHMENT_INFO_GUARD
#define SAPPHIRE_RENDER_RHI_ATTACHMENT_INFO_GUARD

#include <SA/Render/LowLevel/Common/Pass/Info/AttachmentInfoBase.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/Pass/Info/VkAttachmentInfo.hpp>

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	#include <SA/Render/LowLevel/DX12/Pass/Info/D12AttachmentInfo.hpp>

#endif

#include <SA/Render/RHI/Misc/Format.hpp>

#include "RHIAttachmentLoadMode.hpp"

namespace SA::RND::RHI
{
	struct AttachmentInfo : public AttachmentInfoBase
	{
		Format format = Format::R8G8B8A8_UNORM;
		AttachmentLoadMode loadMode = AttachmentLoadMode::Clear;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

		VK::AttachmentInfo API_Vulkan() const;

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

		DX12::AttachmentInfo API_DirectX12() const;

#endif
	};
}

#endif // SAPPHIRE_RENDER_VK_ATTACHMENT_INFO_GUARD

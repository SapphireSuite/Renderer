// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/Info/RHIAttachmentInfo.hpp>

namespace SA::RND::RHI
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VK::AttachmentInfo AttachmentInfo::API_Vulkan() const
	{
		VK::AttachmentInfo vkInfo;

		// Copy base info.
		static_cast<AttachmentInfoBase&>(vkInfo) = *this;

		vkInfo.format = VK::API_GetFormat(format);
		vkInfo.loadMode = VK::API_GetAttachmentLoadOp(loadMode);

		return vkInfo;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	DX12::AttachmentInfo AttachmentInfo::API_DirectX12() const
	{
		DX12::AttachmentInfo d12Info;

		// Copy base info.
		static_cast<AttachmentInfoBase&>(d12Info) = *this;

		d12Info.format = DX12::API_GetFormat(format);
		d12Info.bClearOnLoad = loadMode == AttachmentLoadMode::Clear;

		return d12Info;
	}

#endif
}

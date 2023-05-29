// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/Info/RHIFrontFaceMode.hpp>

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkFrontFace API_GetFrontFaceMode(RHI::FrontFaceMode _mode)
		{
			static constexpr VkFrontFace vkFrontFaceIndexMap[] = {
				VK_FRONT_FACE_CLOCKWISE,
				VK_FRONT_FACE_COUNTER_CLOCKWISE,
			};

			const uint8_t index = static_cast<uint8_t>(_mode);

			SA_ASSERT((OutOfRange, index, 0u, sizeof(vkFrontFaceIndexMap)), SA.Render.RHI.Vulkan,
				(L"FrontFaceMode value [%1] invalid", index));

			return vkFrontFaceIndexMap[index];
		}
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		bool API_GetFrontFaceMode(RHI::FrontFaceMode _mode)
		{
			return _mode == RHI::FrontFaceMode::CounterClockwise;
		}
	}

#endif
}

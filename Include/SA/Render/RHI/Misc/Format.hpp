// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_FORMAT_GUARD
#define SAPPHIRE_RENDER_RHI_FORMAT_GUARD

#include <cstdint>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

#endif

namespace SA::RND
{
	namespace RHI
	{
		/**
		 * @brief 
		 * 
		 * Sources: https://stackoverflow.com/questions/59628956/what-is-the-difference-between-normalized-scaled-and-integer-vkformats
		 */
		enum class Format : uint32_t
		{
			Unknown = 0,

//{ R8

			/// Unsigned normalized float 8-bit 1-channel.
			R8_UNORM,

			/// Signed normalized float 8-bit 1-channel.
			R8_SNORM,

			/// Unsigned int 8-bit 1-channel.
			R8_UINT,
			
			/// Signed int 8-bit 1-channel.
			R8_SINT,

//}


//{ R8G8

			/// Unsigned normalized float 8-bit 2-channel.
			R8G8_UNORM,

			/// Signed normalized float 8-bit 2-channel.
			R8G8_SNORM,

			/// Unsigned int 8-bit 2-channel.
			R8G8_UINT,
			
			/// Signed int 8-bit 2-channel.
			R8G8_SINT,

//}


//{ R8G8B8A8

			/// Unsigned normalized float 8-bit 4-RGBA-channel.
			R8G8B8A8_UNORM,

			/// Signed normalized float 8-bit 4-RGBA-channel.
			R8G8B8A8_SNORM,

			/// Unsigned int 8-bit 4-RGBA-channel.
			R8G8B8A8_UINT,
			
			/// Signed int 8-bit 4-RGBA-channel.
			R8G8B8A8_SINT,

			/// 8-bit 4-RGBA-channel present format.
			R8G8B8A8_SRGB,

//}


//{ B8G8R8A8

			/// Unsigned normalized float 8-bit 4-BGRA-channel.
			B8G8R8A8_UNORM,

			/// Signed normalized float 8-bit 4-BGRA-channel.
			B8G8R8A8_SNORM,

			/// Unsigned int 8-bit 4-BGRA-channel.
			B8G8R8A8_UINT,
			
			/// Signed int 8-bit 4-BGRA-channel.
			B8G8R8A8_SINT,

			/// 8-bit 4-BGRA-channel present format.
			B8G8R8A8_SRGB,

//}



//{ R16

			/// Unsigned normalized float 16-bit 1-channel.
			R16_UNORM,

			/// Signed normalized float 16-bit 1-channel.
			R16_SNORM,

			/// Unsigned int 16-bit 1-channel.
			R16_UINT,
			
			/// Signed int 16-bit 1-channel.
			R16_SINT,

			/// Signed float 16-bit 1-channel.
			R16_SFLOAT,

//}


//{ R16G16

			/// Unsigned normalized 16-bit float 2-channel.
			R16G16_UNORM,

			/// Signed normalized 16-bit float 2-channel.
			R16G16_SNORM,

			/// Unsigned int 16-bit 2-channel.
			R16G16_UINT,
			
			/// Signed int 16-bit 2-channel.
			R16G16_SINT,

			/// Signed float 16-bit 2-channel.
			R16G16_SFLOAT,

//}


//{ R16G16B16A16

			/// Unsigned normalized 16-bit float 4-RGBA-channel.
			R16G16B16A16_UNORM,

			/// Signed normalized 16-bit float 4-RGBA-channel.
			R16G16B16A16_SNORM,

			/// Unsigned int 16-bit 4-RGBA-channel.
			R16G16B16A16_UINT,
			
			/// Signed int 16-bit 4-RGBA-channel.
			R16G16B16A16_SINT,

			/// Signed float 16-bit 4-RGBA-channel.
			R16G16B16A16_SFLOAT,

//}



//{ R32

			/// Unsigned int 32-bit 1-channel.
			R32_UINT,
			
			/// Signed int 32-bit 1-channel.
			R32_SINT,

			/// Signed float 32-bit 1-channel.
			R32_SFLOAT,

//}


//{ R32G32

			/// Unsigned int 32-bit 2-channel.
			R32G32_UINT,
			
			/// Signed int 32-bit 2-channel.
			R32G32_SINT,

			/// Signed float 32-bit 2-channel.
			R32G32_SFLOAT,

//}


//{ R32G32B32

			/// Unsigned int 32-bit 3-RGB-channel.
			R32G32B32_UINT,
			
			/// Signed int 32-bit 3-RGB-channel.
			R32G32B32_SINT,

			/// Signed float 32-bit 3-RGB-channel.
			R32G32B32_SFLOAT,

//}


//{ R32G32B32A32

			/// Unsigned int 32-bit 4-RGBA-channel.
			R32G32B32A32_UINT,
			
			/// Signed int 32-bit 4-RGBA-channel.
			R32G32B32A32_SINT,

			/// Signed float 32-bit 4-RGBA-channel.
			R32G32B32A32_SFLOAT,

//}


//{ Depth

			/// Unsigned normalized 16-bit float 1-Depth-channel.
			D16_UNORM,

			/// Signed float 32-bit 1-Depth-channel.
			D32_SFLOAT,

			/// Unsigned normalized 24-bit float 1-Depth-channel + Unsigned int 8-bit 1-Stencil-channel.
			D24_UNORM_S8_UINT,

//}
		};
	}
	
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		VkFormat API_GetFormat(RHI::Format _rhiFormat);
		RHI::Format API_GetFormat(VkFormat _vkFormat);
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		DXGI_FORMAT API_GetFormat(RHI::Format _rhiFormat);
		RHI::Format API_GetFormat(DXGI_FORMAT _d12Format);
	}

#endif
}

#endif // SAPPHIRE_RENDER_RHI_FORMAT_GUARD

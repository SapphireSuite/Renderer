// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_FORMAT_GUARD
#define SAPPHIRE_RENDER_RHI_FORMAT_GUARD

#include <cstdint>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

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

			/// Unsigned scaled float 8-bit 1-channel.
			R8_USCALED,

			/// Signed scaled float 8-bit 1-channel.
			R8_SSCALED,

			/// Unsigned int 8-bit 1-channel.
			R8_UINT,
			
			/// Signed int 8-bit 1-channel.
			R8_SINT,

			/// 8-bit 1-channel present format.
			R8_SRGB,

//}


//{ R8G8

			/// Unsigned normalized float 8-bit 2-channel.
			R8G8_UNORM,

			/// Signed normalized float 8-bit 2-channel.
			R8G8_SNORM,

			/// Unsigned scaled float 8-bit 2-channel.
			R8G8_USCALED,

			/// Signed scaled float 8-bit 2-channel.
			R8G8_SSCALED,

			/// Unsigned int 8-bit 2-channel.
			R8G8_UINT,
			
			/// Signed int 8-bit 2-channel.
			R8G8_SINT,

			/// 8-bit 2-channel present format.
			R8G8_SRGB,

//}


//{ R8G8B8

			/// Unsigned normalized float 8-bit 3-RGB-channel.
			R8G8B8_UNORM,

			/// Signed normalized float 8-bit 3-RGB-channel.
			R8G8B8_SNORM,

			/// Unsigned scaled float 8-bit 3-RGB-channel.
			R8G8B8_USCALED,

			/// Signed scaled float 8-bit 3-RGB-channel.
			R8G8B8_SSCALED,

			/// Unsigned int 8-bit 3-RGB-channel.
			R8G8B8_UINT,
			
			/// Signed int 8-bit 3-RGB-channel.
			R8G8B8_SINT,

			/// 8-bit 3-RGB-channel present format.
			R8G8B8_SRGB,

//}


//{ B8G8R8

			/// Unsigned normalized float 8-bit 3-BGR-channel.
			B8G8R8_UNORM,

			/// Signed normalized float 8-bit 3-BGR-channel.
			B8G8R8_SNORM,

			/// Unsigned scaled float 8-bit 3-BGR-channel.
			B8G8R8_USCALED,

			/// Signed scaled float 8-bit 3-BGR-channel.
			B8G8R8_SSCALED,

			/// Unsigned int 8-bit 3-BGR-channel.
			B8G8R8_UINT,
			
			/// Signed int 8-bit 3-BGR-channel.
			B8G8R8_SINT,

			/// 8-bit 3-BGR-channel present format.
			B8G8R8_SRGB,

//}


//{ R8G8B8A8

			/// Unsigned normalized float 8-bit 4-RGBA-channel.
			R8G8B8A8_UNORM,

			/// Signed normalized float 8-bit 4-RGBA-channel.
			R8G8B8A8_SNORM,

			/// Unsigned scaled float 8-bit 4-RGBA-channel.
			R8G8B8A8_USCALED,

			/// Signed scaled float 8-bit 4-RGBA-channel.
			R8G8B8A8_SSCALED,

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

			/// Unsigned scaled float 8-bit 4-BGRA-channel.
			B8G8R8A8_USCALED,

			/// Signed scaled float 8-bit 4-BGRA-channel.
			B8G8R8A8_SSCALED,

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

			/// Unsigned scaled float 16-bit 1-channel.
			R16_USCALED,

			/// Signed scaled float 16-bit 1-channel.
			R16_SSCALED,

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

			/// Unsigned scaled 16-bit float 2-channel.
			R16G16_USCALED,

			/// Signed scaled 16-bit float 2-channel.
			R16G16_SSCALED,

			/// Unsigned int 16-bit 2-channel.
			R16G16_UINT,
			
			/// Signed int 16-bit 2-channel.
			R16G16_SINT,

			/// Signed float 16-bit 2-channel.
			R16G16_SFLOAT,

//}


//{ R16G16B16

			/// Unsigned normalized 16-bit float 3-RGB-channel.
			R16G16B16_UNORM,

			/// Signed normalized 16-bit float 3-RGB-channel.
			R16G16B16_SNORM,

			/// Unsigned scaled 16-bit float 3-RGB-channel.
			R16G16B16_USCALED,

			/// Signed scaled 16-bit float 3-RGB-channel.
			R16G16B16_SSCALED,

			/// Unsigned int 16-bit 3-RGB-channel.
			R16G16B16_UINT,
			
			/// Signed int 16-bit 3-RGB-channel.
			R16G16B16_SINT,

			/// Signed float 16-bit 3-RGB-channel.
			R16G16B16_SFLOAT,

//}


//{ R16G16B16A16

			/// Unsigned normalized 16-bit float 4-RGBA-channel.
			R16G16B16A16_UNORM,

			/// Signed normalized 16-bit float 4-RGBA-channel.
			R16G16B16A16_SNORM,

			/// Unsigned scaled 16-bit float 4-RGBA-channel.
			R16G16B16A16_USCALED,

			/// Signed scaled 16-bit float 4-RGBA-channel.
			R16G16B16A16_SSCALED,

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



//{ R64

			/// Unsigned int 64-bit 1-channel.
			R64_UINT,
			
			/// Signed int 64-bit 1-channel.
			R64_SINT,

			/// Signed float 64-bit 1-channel.
			R64_SFLOAT,

//}


//{ R64G64

			/// Unsigned int 64-bit 2-channel.
			R64G64_UINT,
			
			/// Signed int 64-bit 2-channel.
			R64G64_SINT,

			/// Signed float 64-bit 2-channel.
			R64G64_SFLOAT,

//}


//{ R64G64B64

			/// Unsigned int 64-bit 3-RGB-channel.
			R64G64B64_UINT,
			
			/// Signed int 64-bit 3-RGB-channel.
			R64G64B64_SINT,

			/// Signed float 64-bit 3-RGB-channel.
			R64G64B64_SFLOAT,

//}


//{ R64G64B64

			/// Unsigned int 64-bit 3-RGB-channel.
			R64G64B64A64_UINT,
			
			/// Signed int 64-bit 3-RGB-channel.
			R64G64B64A64_SINT,

			/// Signed float 64-bit 3-RGB-channel.
			R64G64B64A64_SFLOAT,

//}


//{ Depth

			/// Unsigned normalized 16-bit float 1-Depth-channel.
			D16_UNORM,

			/// Signed float 32-bit 1-Depth-channel.
			D32_SFLOAT,

			/// Unsigned int 8-bit 1-Stencil-channel.
			S8_UINT,

			/// Unsigned normalized 16-bit float 1-Depth-channel + Unsigned int 8-bit 1-Stencil-channel.
			D16_UNORM_S8_UINT,

			/// Unsigned normalized 24-bit float 1-Depth-channel + Unsigned int 8-bit 1-Stencil-channel.
			D24_UNORM_S8_UINT,

			/// Signed float 32-bit 1-Depth-channel + Unsigned int 8-bit 1-Stencil-channel.
			D32_SFLOAT_S8_UINT,

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
}

#endif // SAPPHIRE_RENDER_RHI_FORMAT_GUARD

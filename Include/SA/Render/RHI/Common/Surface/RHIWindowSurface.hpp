// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_WINDOW_SURFACE_GUARD
#define SAPPHIRE_RENDER_RHI_WINDOW_SURFACE_GUARD

#include <SA/Render/RHI/Common/Compatibility/IRenderWindow.hpp>

namespace SA
{
	namespace RND
	{

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

		namespace VK
		{
			class WindowSurface;
		}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

		namespace DX12
		{
			class WindowSurface;
		}

#endif

		namespace RHI
		{
			class RenderInterface;

			class WindowSurface
			{
			public:
				virtual ~WindowSurface() = default;

				virtual void Create(const RenderInterface* _renderIntf, const IRenderWindow* _window) = 0;
				virtual void Destroy(const RenderInterface* _renderIntf) = 0;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

				virtual const VK::WindowSurface& API_Vulkan() const;

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

				virtual const DX12::WindowSurface& API_DirectX12() const;

#endif
			};
		}
	}
}

#endif // SAPPHIRE_RENDER_RHI_WINDOW_SURFACE_GUARD

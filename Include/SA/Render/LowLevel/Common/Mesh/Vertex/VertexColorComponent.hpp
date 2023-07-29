// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_VERTEX_COLOR_COMPONENT_GUARD
#define SAPPHIRE_RENDER_COMMON_VERTEX_COLOR_COMPONENT_GUARD

#include "VertexComponent.hpp"

#include <SA/Render/LowLevel/Common/Misc/Color.hpp>

namespace SA::RND
{
	class VertexColorComponent : public VertexComponent
	{
	public:
		using DataT = Color;

		std::vector<Color> colors;

		VertexColorComponent() = default;
		inline VertexColorComponent(std::vector<Color>&& _colors) noexcept :
			colors{ std::move(_colors) }
		{
		}

		inline const char* GetData() const noexcept override final { return reinterpret_cast<const char*>(colors.data()); };
		inline uint32_t GetDataSize() const noexcept override final { return static_cast<uint32_t>(sizeof(Color) * colors.size()); }
		inline const char* GetSemanticName() const noexcept override final { return "COLOR"; }
	};

	using VertexColor = VertexColorComponent;
}

#endif // SAPPHIRE_RENDER_COMMON_VERTEX_COLOR_COMPONENT_GUARD

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_VERTEX_UV_COMPONENT_GUARD
#define SAPPHIRE_RENDER_COMMON_VERTEX_UV_COMPONENT_GUARD

#include "VertexComponent.hpp"

#include <SA/Maths/Space/Vector2.hpp>

namespace SA::RND
{
	class VertexUVComponent : public VertexComponent
	{
	public:
		using DataT = Vec2f;

		std::vector<Vec2f> uvs;

		VertexUVComponent() = default;
		inline VertexUVComponent(std::vector<Vec2f>&& _uvs) noexcept :
			uvs{ std::move(_uvs) }
		{
		}

		inline const char* GetData() const noexcept override final { return reinterpret_cast<const char*>(uvs.data()); };
		inline const char* GetSemanticName() const noexcept override final { return "UV"; }
	};

	using VertexUV = VertexUVComponent;
}

#endif // SAPPHIRE_RENDER_COMMON_VERTEX_UV_COMPONENT_GUARD

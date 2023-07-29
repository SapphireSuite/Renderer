// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_VERTEX_POSITION_COMPONENT_GUARD
#define SAPPHIRE_RENDER_COMMON_VERTEX_POSITION_COMPONENT_GUARD

#include "VertexComponent.hpp"

#include <SA/Maths/Space/Vector3.hpp>

namespace SA::RND
{
	class VertexPositionComponent : public VertexComponent
	{
	public:
		using DataT = Vec3f;

		std::vector<Vec3f> positions;

		VertexPositionComponent() = default;
		inline VertexPositionComponent(std::vector<Vec3f>&& _positions) noexcept :
			positions{ std::move(_positions) }
		{
		}

		inline const char* GetData() const noexcept override final { return reinterpret_cast<const char*>(positions.data()); };
		inline uint32_t GetDataSize() const noexcept override final { return static_cast<uint32_t>(sizeof(Vec3f) * positions.size()); }
		inline const char* GetSemanticName() const noexcept override final { return "POSITION"; }
	};

	using VertexPosition = VertexPositionComponent;
}

#endif // SAPPHIRE_RENDER_COMMON_VERTEX_POSITION_COMPONENT_GUARD

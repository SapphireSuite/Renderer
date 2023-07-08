// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_VERTEX_TANGENT_COMPONENT_GUARD
#define SAPPHIRE_RENDER_COMMON_VERTEX_TANGENT_COMPONENT_GUARD

#include "VertexComponent.hpp"

#include <SA/Maths/Space/Vector3.hpp>

namespace SA::RND
{
	class VertexTangentComponent : public VertexComponent
	{
	public:
		using DataT = Vec3f;
		
		std::vector<Vec3f> tangents;

		VertexTangentComponent() = default;
		inline VertexTangentComponent(std::vector<Vec3f>&& _tangents) noexcept :
			tangents{ std::move(_tangents) }
		{
		}

		inline const char* GetData() const noexcept override final { return reinterpret_cast<const char*>(tangents.data()); };
		inline const char* GetSemanticName() const noexcept override final { return "TANGENT"; }
	};

	using VertexTangent = VertexTangentComponent;
}

#endif // SAPPHIRE_RENDER_COMMON_VERTEX_TANGENT_COMPONENT_GUARD

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_VERTEX_BITANGENT_COMPONENT_GUARD
#define SAPPHIRE_RENDER_COMMON_VERTEX_BITANGENT_COMPONENT_GUARD

#include "VertexComponent.hpp"

#include <SA/Maths/Space/Vector3.hpp>

namespace SA::RND
{
	class VertexBitangentComponent : public VertexComponent
	{
	public:
		using DataT = Vec3f;
		
		std::vector<Vec3f> bitangents;

		VertexBitangentComponent() = default;
		inline VertexBitangentComponent(std::vector<Vec3f>&& _bitangents) noexcept :
			bitangents{ std::move(_bitangents) }
		{
		}

		inline const char* GetData() const noexcept override final { return reinterpret_cast<const char*>(bitangents.data()); };
		inline const char* GetSemanticName() const noexcept override final { return "BITANGENT"; }
	};

	using VertexBitangent = VertexBitangentComponent;
}

#endif // SAPPHIRE_RENDER_COMMON_VERTEX_BITANGENT_COMPONENT_GUARD

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_VERTEX_NORMAL_COMPONENT_GUARD
#define SAPPHIRE_RENDER_COMMON_VERTEX_NORMAL_COMPONENT_GUARD

#include "VertexComponent.hpp"

#include <SA/Maths/Space/Vector3.hpp>

namespace SA::RND
{
	class VertexNormalComponent : public VertexComponent
	{
	public:
		using DataT = Vec3f;
		
		std::vector<Vec3f> normals;

		VertexNormalComponent() = default;
		inline VertexNormalComponent(std::vector<Vec3f>&& _normals) noexcept :
			normals{ std::move(_normals) }
		{
		}

		inline const char* GetData() const noexcept override final { return reinterpret_cast<const char*>(normals.data()); };
		inline uint32_t GetDataSize() const noexcept override final { return static_cast<uint32_t>(sizeof(Vec3f) * normals.size()); }
		inline const char* GetSemanticName() const noexcept override final { return "NORMAL"; }
	};

	using VertexNormal = VertexNormalComponent;
}

#endif // SAPPHIRE_RENDER_COMMON_VERTEX_NORMAL_COMPONENT_GUARD

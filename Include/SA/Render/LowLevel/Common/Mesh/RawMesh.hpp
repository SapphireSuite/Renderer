// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_RAW_MESH_GUARD
#define SAPPHIRE_RENDER_COMMON_RAW_MESH_GUARD

#include "Vertex/Verticies.hpp"
#include "RawIndexBuffer.hpp"

#include <SA/Maths/Geometry/AABB3D.hpp>

namespace SA::RND
{
	struct RawMesh
	{
		Verticies vertices;
		RawIndexBuffer indices;

		AABB3Df aabb;
	};
}

#endif // SAPPHIRE_RENDER_COMMON_RAW_MESH_GUARD

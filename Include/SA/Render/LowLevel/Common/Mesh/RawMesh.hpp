// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_RAW_MESH_GUARD
#define SAPPHIRE_RENDER_COMMON_RAW_MESH_GUARD

#include "RawVertexBuffer.hpp"
#include "RawIndexBuffer.hpp"

//#include <SA/Maths/Geometry/AABB3D.hpp>

namespace SA::RND
{
	struct RawMesh
	{
		RawVertexBuffer vertices;
		RawIndexBuffer indices;

		//AABB3Df aabb;
	};
}

#endif // SAPPHIRE_RENDER_COMMON_RAW_MESH_GUARD

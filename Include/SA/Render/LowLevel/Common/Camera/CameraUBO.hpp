// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_CAMERA_UBO_GUARD
#define SAPPHIRE_RENDER_CAMERA_UBO_GUARD

#include <SA/Maths/Space/Vector3.hpp>
#include <SA/Maths/Matrix/Matrix4.hpp>

namespace SA::RND
{
	/**
	* Must match Camera cbuffer in Camera.hlsl.
	*/
	struct CameraUBO
	{
		/// Camera inverse transformation matrix.
		Mat4f inverseView = Mat4f::Identity;

		/// Camera projection matrix.
		Mat4f projection = Mat4f::Identity;

		/// Camera raw position.
		Vec3f position;
	};
}

#endif // SAPPHIRE_RENDER_CAMERA_UBO_GUARD

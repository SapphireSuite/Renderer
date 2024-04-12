// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_CAMERA_GPU_GUARD
#define SAPPHIRE_RENDER_CAMERA_GPU_GUARD

#include <SA/Maths/Space/Vector3.hpp>
#include <SA/Maths/Matrix/Matrix4.hpp>

namespace SA::RND
{
	/**
	* Must match Camera cbuffer in Camera.hlsl.
	*/
	struct Camera_GPU
	{
		/// Camera inverse transformation matrix.
		//Mat4f inverseView = Mat4f::Identity;

		/// Camera projection matrix.
		//Mat4f projection = Mat4f::Identity;

		/**
		*	Camera inverse view projection matrix.
		*	projection * inverseView.
		*/
		Mat4f invViewProj = Mat4f::Identity;

		/// Camera raw position.
		Vec3f position;

		float padding = 0.0f;

		void Update(const Mat4f& _view, const Mat4f& _proj);
	};
}

#endif // SAPPHIRE_RENDER_CAMERA_GPU_GUARD

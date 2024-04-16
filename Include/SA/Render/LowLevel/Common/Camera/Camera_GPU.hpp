// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_CAMERA_GPU_GUARD
#define SAPPHIRE_RENDER_CAMERA_GPU_GUARD

#include <SA/Maths/Space/Vector2.hpp>
#include <SA/Maths/Space/Vector3.hpp>
#include <SA/Maths/Matrix/Matrix4.hpp>

namespace SA::RND
{
	/**
	* Must match Camera cbuffer in Camera.hlsl.
	*/
	struct Camera_GPU
	{
	// { View

		/// Camera transformation matrix.
		//Mat4f view = Mat4f::Identity;

		/// Camera inverse transformation matrix.
		//Mat4f inverseView = Mat4f::Identity;

		/// Camera raw position.
		Vec3f position;

		float padding = 0.0f;

	//}


	//{ Projection

		/// Camera projection matrix.
		//Mat4f projection = Mat4f::Identity;

		/// Camera inverse projection matrix.
		Mat4f inverseProjection = Mat4f::Identity;

		/**
		*	Camera inverse view projection matrix.
		*	projection * inverseView.
		*/
		Mat4f invViewProj = Mat4f::Identity;


		/// Z-Near plane.
		float zNear = 0.1f;

		/// Z-Far plane.
		float zFar = 1000.0f;
		
		/// Screen dimensions.
		Vec2ui screen = Vec2ui::Zero;

	//}

		void UpdatePerspective(const Mat4f& _view, float _FOV, float _zNear, float _zFar, const Vec2ui& _screenDims);
	};
}

#endif // SAPPHIRE_RENDER_CAMERA_GPU_GUARD

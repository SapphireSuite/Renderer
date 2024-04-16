// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Camera/Camera_GPU.hpp>

namespace SA::RND
{
	void Camera_GPU::UpdatePerspective(const Mat4f& _view, float _FOV, float _zNear, float _zFar, const Vec2ui& _screenDims)
	{
		// View
		{
			//view = _view;
			//inverseView = _view.GetInversed();
			position = Vec3f(_view.e03, _view.e13, _view.e23);
		}

		// Projection
		{
			Mat4f projection = Mat4f::MakePerspective(_FOV, _screenDims.x / _screenDims.y, _zNear, _zFar);
			inverseProjection = projection.GetInversed();

			Mat4f inverseView = _view.GetInversed();
			invViewProj = projection * inverseView;

			zNear = _zNear;
			zFar = _zFar;
			screen = _screenDims;
		}
	}
}

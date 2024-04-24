// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Camera/Camera_GPU.hpp>

namespace SA::RND
{
	void Camera_GPU::UpdatePerspective(const Mat4f& _view, float _FOV, float _zNear, float _zFar, const Vec2ui& _screenDims)
	{
		// View
		{
			view = _view;
			inverseView = _view.GetInversed();
		}

		// Projection
		{
			projection = Mat4f::MakePerspective(_FOV, _screenDims.x / float(_screenDims.y), _zNear, _zFar);
			inverseProjection = projection.GetInversed();

			invViewProj = projection * inverseView;

			zNear = _zNear;
			zFar = _zFar;
			screen = _screenDims;
		}
	}
}

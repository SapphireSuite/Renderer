// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Camera/Camera_GPU.hpp>

namespace SA::RND
{
	void Camera_GPU::Update(const Mat4f& _view, const Mat4f& _proj)
	{
		//inverseView = _view.GetInversed();
		Mat4f inverseView = _view.GetInversed();

		//projection = _proj;

		invViewProj = _proj * inverseView;

		position = Vec3f(_view.e03, _view.e13, _view.e23);
	}
}

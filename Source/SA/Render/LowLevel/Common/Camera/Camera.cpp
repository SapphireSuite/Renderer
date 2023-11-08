// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Camera/Camera.hpp>

namespace SA::RND
{
//{ View
		
	bool Camera::IsViewDirty() const noexcept
	{
		return bViewDirty;
	}


	const Vec3f& Camera::GetPosition() const noexcept
	{
		return mTransform.position;
	}

	const Quatf& Camera::GetRotation() const noexcept
	{
		return mTransform.rotation;
	}

	const Vec3f& Camera::GetScale() const noexcept
	{
		return mTransform.scale;
	}

	const TransformPRSf& Camera::GetTransform() const noexcept
	{
		return mTransform;
	}


	void Camera::SetPosition(const Vec3f& _position) noexcept
	{
		bViewDirty = true;
		mTransform.position = _position;
	}

	void Camera::SetRotation(const Quatf& _rotation) noexcept
	{
		bViewDirty = true;
		mTransform.rotation = _rotation;
	}

	void Camera::SetScale(const Vec3f& _scale) noexcept
	{
		bViewDirty = true;
		mTransform.scale = _scale;
	}

	void Camera::SetTransform(const TransformPRSf& _transform) noexcept
	{
		bViewDirty = true;
		mTransform = _transform;
	}


	Mat4f Camera::ComputeInvViewMatrix() noexcept
	{
		bViewDirty = false;
		return mTransform.Matrix().GetInversed();
	}

//}


//{ Proj

	bool Camera::IsProjDirty() const noexcept
	{
		return bProjDirty;
	}


	float Camera::GetFOV() const noexcept
	{
		return mFOV;
	}

	float Camera::GetNear() const noexcept
	{
		return mNear;
	}

	float Camera::GetFar() const noexcept
	{
		return mFar;
	}


	void Camera::SetFOV(float _fov) noexcept
	{
		bProjDirty = true;
		mFOV = _fov;
	}

	void Camera::SetNear(float _near) noexcept
	{
		bProjDirty = true;
		mNear = _near;
	}

	void Camera::SetFar(float _far) noexcept
	{
		bProjDirty = true;
		mFar = _far;
	}


	Mat4f Camera::ComputeProjectionMatrix(float _aspect) noexcept
	{
		bProjDirty = false;
		return Mat4f::MakePerspective(mFOV, _aspect, mNear, mFar);
	}

//}
}

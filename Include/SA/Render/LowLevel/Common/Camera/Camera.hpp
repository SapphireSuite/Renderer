// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_CAMERA_GUARD
#define SAPPHIRE_RENDER_CAMERA_GUARD

#include <SA/Maths/Transform/Transform.hpp>

namespace SA::RND
{
	class Camera
	{
		TransformPRSf mTransform;

		bool bViewDirty = true;


		float mFOV = 90.0f;
		float mNear = 0.1f;
		float mFar = 1000.0f;
		
		bool bProjDirty = true;

	public:
	//{ View
		
		bool IsViewDirty() const noexcept;
	
		const Vec3f& GetPosition() const noexcept;
		const Quatf& GetRotation() const noexcept;
		const Vec3f& GetScale() const noexcept;
		const TransformPRSf& GetTransform() const noexcept;

		void SetPosition(const Vec3f& _position) noexcept;
		void SetRotation(const Quatf& _rotation) noexcept;
		void SetScale(const Vec3f& _scale) noexcept;
		void SetTransform(const TransformPRSf& _transform) noexcept;

		Mat4f ComputeInvViewMatrix() noexcept;

	//}
	

	//{ Proj

		bool IsProjDirty() const noexcept;

		float GetFOV() const noexcept;
		float GetNear() const noexcept;
		float GetFar() const noexcept;

		void SetFOV(float _fov) noexcept;
		void SetNear(float _near) noexcept;
		void SetFar(float _far) noexcept;

		Mat4f ComputeProjectionMatrix(float _aspect) noexcept;

	//}
	};
}

#endif // SAPPHIRE_RENDER_CAMERA_GUARD

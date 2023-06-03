// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COMMON_VERTEX_COMPONENT_GUARD
#define SAPPHIRE_RENDER_COMMON_VERTEX_COMPONENT_GUARD

#include <vector>

namespace SA::RND
{
	class VertexComponent
	{
	public:
		virtual ~VertexComponent() = default;
		
		virtual const char* GetData() const noexcept = 0;
		virtual const char* GetSemanticName() const noexcept = 0;
	};
}

#endif // SAPPHIRE_RENDER_COMMON_VERTEX_COMPONENT_GUARD

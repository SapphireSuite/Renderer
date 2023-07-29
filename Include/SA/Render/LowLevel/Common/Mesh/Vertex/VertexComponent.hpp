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
		virtual uint32_t GetDataSize() const noexcept = 0;
		virtual const char* GetSemanticName() const noexcept = 0;
		virtual const char* GetComponentName() const noexcept { return GetSemanticName(); };
	};
}

#endif // SAPPHIRE_RENDER_COMMON_VERTEX_COMPONENT_GUARD

// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_AABB_GUARD
#define SAPPHIRE_RENDER_SHADER_AABB_GUARD

namespace SA
{
	struct AABB
	{
		float3 min;
	
		float padding1;
	
		float3 max;
	
		float padding2;
	};
}

#endif // SAPPHIRE_RENDER_SHADER_AABB_GUARD

// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_PIPELINE_RENDER_MODES_GUARD
#define SAPPHIRE_RENDER_RHI_PIPELINE_RENDER_MODES_GUARD

#include "CullingMode.hpp"
#include "FrontFaceMode.hpp"
#include "PolygonMode.hpp"

namespace SA::RND
{
	namespace RHI
	{
		struct PipelineRenderModes
		{
			PolygonMode polygon = PolygonMode::Fill;
			CullingMode CullingMode = CullingMode::Back;
			FrontFaceMode frontFace = FrontFaceMode::Clockwise;
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_PIPELINE_RENDER_MODES_GUARD

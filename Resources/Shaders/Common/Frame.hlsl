// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_FRAME_GUARD
#define SAPPHIRE_RENDER_SHADER_FRAME_GUARD

#include "Preprocessors.hlsl"

namespace SA
{
	struct Frame
	{
		uint cameraIndex = 0;
	};

	Frame frame : SA_REG(b, SA_FRAME_ID);
}

#endif // SAPPHIRE_RENDER_SHADER_FRAME_GUARD

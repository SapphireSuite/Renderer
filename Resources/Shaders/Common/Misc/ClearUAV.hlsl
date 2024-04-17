// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_SHADER_CLEAR_UAV_GUARD
#define SAPPHIRE_RENDER_SHADER_CLEAR_UAV_GUARD

//---------- Inputs ----------

#define NUM_THREAD_X 32
#define NUM_THREAD_Y 1
#define NUM_THREAD_Z 1


//---------- Outputs ----------

RWStructuredBuffer<uint> bufferToClear : register(u0);


//-------------------- Compute Shader --------------------

[numthreads(NUM_THREAD_X, NUM_THREAD_Y, NUM_THREAD_Z)]
void main(uint _dispatchThreadID : SV_DispatchThreadID)
{
	if (_dispatchThreadID >= SA_UAV_MAX_SIZE) // must be defined during compilation.
		return;
	
	bufferToClear[_dispatchThreadID] = 0;
}

#endif // SAPPHIRE_RENDER_SHADER_CLEAR_UAV_GUARD

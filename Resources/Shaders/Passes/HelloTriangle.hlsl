// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

//-------------------- Global --------------------

static const float2 positions[3] = {
	float2(0.0, 0.5),
	float2(0.5, -0.5),
	float2(-0.5, -0.5),
};

static const float4 colors[3] = {
	float4(1.0, 0.0, 0.0, 1.0),
	float4(0.0, 1.0, 0.0, 1.0),
	float4(0.0, 0.0, 1.0, 1.0),
};


//-------------------- Vertex Shader --------------------

struct V2P
{
	float4 svPosition : SV_POSITION;

	float4 color : COLOR;
};

V2P mainVS(uint _ID : SV_VertexID)
{
	V2P output;

	output.svPosition = float4(positions[_ID], 0.0, 1.0);

	output.color = colors[_ID];

	return output;
}


//-------------------- Pixel Shader --------------------

float4 mainPS(V2P _input) : SV_TARGET
{
	return _input.color;
}

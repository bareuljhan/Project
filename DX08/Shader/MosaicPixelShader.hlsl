Texture2D map: register(t0);
SamplerState samp :register(s0);

cbuffer ActionBuffer : register(b0)
{
	float2 startPos;
	float2 size;
	float2 imageSize;
	int padding0[2];
}

cbuffer ReversBuffer : register(b1)
{
	int reverse;
	int padding1[3];
}

cbuffer CupMosaicBuffer : register(b2)
{
	int value1;
	int padding2[3];
}

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv: UV;
};

float4 Mosaic(float2 uv)
{
	float x = floor(uv.x * value1);
	float y = floor(uv.y * value1);

	float2 temp;
	temp.x = x / value1;
	temp.y = y / value1;

	return map.Sample(samp, temp);
}

// SV : SystemValue
float4 PS(PixelInput input) : SV_TARGET
{
	input.uv.x = abs(input.uv.x - reverse);

	float2 spriteUV;
	spriteUV.x = input.uv.x * (size.x / imageSize.x) + (startPos.x / imageSize.x);
	spriteUV.y = input.uv.y * (size.y / imageSize.y) + (startPos.y / imageSize.y);

	return Mosaic(spriteUV);

	//return map.Sample(samp, spriteUV);
}
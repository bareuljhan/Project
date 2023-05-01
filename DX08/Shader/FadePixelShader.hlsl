Texture2D map : register(t0);
SamplerState SampleType : register(s0);

cbuffer FadeBuffer : register(b0)
{
    float FadeValue;
    int padding[3];
};

struct PixelInput
{
    float4 Position : SV_POSITION;
    float2 tex : TEXCOORD0;
};

float4 PS(PixelInput input) : SV_TARGET
{
    float4 textureColor = map.Sample(SampleType, input.tex);
    textureColor.rgb *= FadeValue;
    textureColor.a *= FadeValue; // 알파 값에 FadeValue 값을 곱하여 페이드 효과를 적용
    return textureColor;
}
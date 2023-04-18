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
    float2 uv : UV;
};

float4 PS(PixelInput input) : SV_Target
{
    float4 textureColor = map.Sample(SampleType, input.uv);
    textureColor.a *= FadeValue; // ���� ���� FadeValue ���� ���Ͽ� ���̵� ȿ���� ����
    return textureColor;
}
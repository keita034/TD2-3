cbuffer cbuff0 : register(b0)
{
    float lutWidth;
    float lutHeight;
    float lutRed;
    float lutGreen;
    float lutBlue;
    float lutMul;
};

Texture2D<float4> lutTex : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState lutSmp : register(s0); // 0番スロットに設定されたサンプラー
Texture2D<float4> tex : register(t1); // 1番スロットに設定されたテクスチャ
RWTexture2D<float4> dstImg : register(u0);

float3 GetLutColor(float3 colorIN)
{
    float3 color = colorIN;
    
    float2 lutSize = float2(lutWidth, lutHeight);
    float4 lutUV;
    color = saturate(color) * lutMul;
    lutUV.w = floor(color.b + lutBlue);
    lutUV.x = (color.r + lutRed) * lutSize.x;
    lutUV.y = (color.g + lutGreen) * lutSize.y;
    lutUV.x += lutUV.w * lutSize.y;
    lutUV.z = lutUV.x + lutSize.y;
    
    return lerp(lutTex.SampleLevel(lutSmp, lutUV.xy, lutUV.z).rgb, lutTex.SampleLevel(lutSmp, lutUV.zy, lutUV.z).rgb, color.b - lutUV.w);
}

[numthreads(10, 10, 1)]
void main(uint3 dtid : SV_DispatchThreadID)
{
    float3 textureColor = tex[dtid.xy].rgb;
    
    dstImg[dtid.xy] = float4(GetLutColor(textureColor), 1);
}
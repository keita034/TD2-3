#include"ModelBasic.hlsli"

Texture2D<float4> tex : register(t0);//0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);//0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
    float3 light_diffuse = saturate(dot(lightv, input.normal));
    float3 shade_color;
    shade_color = m_ambient; //アンビエント項
    shade_color += m_diffuse * light_diffuse; //ディフューズ項
    float4 texcolor = tex.Sample(smp, input.uv);
    //return float4(texcolor.rgb * shade_color, texcolor.a * m_alpha);
    return float4(texcolor);
}
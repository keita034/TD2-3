cbuffer cbuff0 : register(b0)
{
    float3 color;
    float2 center;
    float power;
    float2 winSize;
    float2 size;
}

Texture2D<float4> tex : register(t0); // 0番スロットに設定されたテクスチャ
RWTexture2D<float4> dstImg : register(u0);

[numthreads(10, 10, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    //テクスチャの色を得る
    float3 textureColor = tex[DTid.xy].rgb;
    
    //UV座標の計算
    float2 uv;
    uv.x = DTid.x / winSize.x;
    uv.y = DTid.y / winSize.y;
    
    //円の範囲を計算
    float vignette = length((uv / size) - center / size);
    vignette = clamp(vignette - 0.2, 0, 1);

    textureColor -= (vignette * power) * color;

    dstImg[DTid.xy] = float4(textureColor, 1);
}
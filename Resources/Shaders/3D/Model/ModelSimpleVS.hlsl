#include"ModelSimple.hlsli"

VSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD, float3 tangent : TANGENT, float4 color : COLOR, uint4 index : BONEINDEX, float4 weight:BONEWEIGHT)
{
    // 法線にワールド行列によるスケーリング・回転を適用
    float4 wnormal = normalize(mul(world, float4(normal, 0)));
    
    VSOutput output = (VSOutput) 0; // ピクセルシェーダーに渡す値
    uint iBone; // 計算するボーンの番号
    float boneWeight; // ボーンウェイト(重み)
    matrix m; // スキニング行列

    // ボーン0
    iBone = index.x;
    boneWeight = weight.x;
    m = boneMat[iBone];
    output.svpos += boneWeight * mul(m, pos);
    output.normal += boneWeight * mul((float3x3) m, normal);

    // ボーン1
    iBone = index.y;
    boneWeight = weight.y;
    m = boneMat[iBone];
    output.svpos += boneWeight * mul(m, pos);
    output.normal += boneWeight * mul((float3x3) m, normal);

    // ボーン2
    iBone = index.z;
    boneWeight = weight.z;
    m = boneMat[iBone];
    output.svpos += boneWeight * mul(m, pos);
    output.normal += boneWeight * mul((float3x3) m, normal);

    // ボーン3
    iBone = index.w;
    boneWeight = weight.w;
    m = boneMat[iBone];
    output.svpos += boneWeight * mul(m, pos);
    output.normal += boneWeight * mul((float3x3) m, normal);
    
    output.svpos = mul(matWorld, output.svpos);
    
    output.normal = wnormal.xyz;
    output.color = color;
    output.uv = uv;
    return output;
}
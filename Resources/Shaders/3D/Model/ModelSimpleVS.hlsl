#include"ModelSimple.hlsli"

VSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD, float3 tangent : TANGENT, float4 color : COLOR)
{
    // �@���Ƀ��[���h�s��ɂ��X�P�[�����O�E��]��K�p
    float4 wnormal = normalize(mul(world, float4(normal, 0)));

    VSOutput output; // �s�N�Z���V�F�[�_�[�ɓn���l
    output.svpos = mul(matWorld, mul(postureMat, pos));
    output.normal = wnormal.xyz;
    output.color = color;
    output.uv = uv;
    return output;
}
#include"Lambert.hlsli"

VSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)
{
    // �@���Ƀ��[���h�s��ɂ��X�P�[�����O�E��]��K�p
    float4 wnormal = normalize(mul(world, float4(normal, 0)));
 
     // �s�N�Z���V�F�[�_�[�ɓn���l
    VSOutput output;
    output.svpos = mul(matWorld, pos);
    output.uv = uv;
    output.color.rgb = dot(lightv, wnormal.xyz) * m_diffuse * lightcolor.rgb;
    output.color.a = m_alpha;
    return output;
}
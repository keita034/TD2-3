#include"ModelSimple.hlsli"

VSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD, float3 tangent : TANGENT, float4 color : COLOR, uint4 index : BONEINDEX, float4 weight:BONEWEIGHT)
{
    // �@���Ƀ��[���h�s��ɂ��X�P�[�����O�E��]��K�p
    float4 wnormal = normalize(mul(world, float4(normal, 0)));
    
    VSOutput output = (VSOutput) 0; // �s�N�Z���V�F�[�_�[�ɓn���l
    uint iBone; // �v�Z����{�[���̔ԍ�
    float boneWeight; // �{�[���E�F�C�g(�d��)
    matrix m; // �X�L�j���O�s��

    // �{�[��0
    iBone = index.x;
    boneWeight = weight.x;
    m = boneMat[iBone];
    output.svpos += boneWeight * mul(m, pos);
    output.normal += boneWeight * mul((float3x3) m, normal);

    // �{�[��1
    iBone = index.y;
    boneWeight = weight.y;
    m = boneMat[iBone];
    output.svpos += boneWeight * mul(m, pos);
    output.normal += boneWeight * mul((float3x3) m, normal);

    // �{�[��2
    iBone = index.z;
    boneWeight = weight.z;
    m = boneMat[iBone];
    output.svpos += boneWeight * mul(m, pos);
    output.normal += boneWeight * mul((float3x3) m, normal);

    // �{�[��3
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
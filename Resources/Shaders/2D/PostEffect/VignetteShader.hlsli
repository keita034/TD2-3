cbuffer cbuff0 : register(b0)
{
    float3 color;
    float2 center;
    float power;
    float2 winSize;
    float2 size;
}

// ���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�ւ̂����Ɏg�p����\����
struct VSOutput
{
    float4 svpos : SV_POSITION; // �V�X�e���p���_���W
    float2 uv : TEXCOORD; // uv�l
    float4 color : COLOR; // �F(RGBA)
};
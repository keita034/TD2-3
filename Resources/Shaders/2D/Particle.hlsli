cbuffer cbuff0 : register(b0)
{
    matrix matWorld; // 
    matrix matBillboard;
};

// ���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�ւ̂����Ɏg�p����\����
struct VSOutput
{
    float4 svpos : SV_POSITION; // �V�X�e���p���_���W
    float4 color : COLOR; // �F(RGBA)
    float scale : SCALE;//�X�P�[��
    float rotation : ROTATION;//��]�p
};

struct GSOutput
{
    float4 svpos : SV_POSITION; // �V�X�e���p���_���W
    float4 color : COLOR; // �F(RGBA)
    float2 uv : TEXCOORD; // uv�l

};
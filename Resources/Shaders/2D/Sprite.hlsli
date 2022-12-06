cbuffer cbuff0 : register(b0)
{
    matrix world; //���[���h�s��
    matrix matWorld; //���[���h���W
    float3 cameraPos; //�J�������W(���[���h���W)
};

// ���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�ւ̂����Ɏg�p����\����
struct VSOutput
{
    float4 svpos : SV_POSITION; // �V�X�e���p���_���W
    float2 uv : TEXCOORD; // uv�l
    float4 color : COLOR; // �F(RGBA)
};
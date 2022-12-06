#include "Particle.hlsli"

float4 rotate(float4 pos, float angle)
{
    return float4(
    pos.x * cos(angle) + pos.y * -sin(angle),
    pos.x * sin(angle) + pos.y * cos(angle),
    pos.z,
    pos.w);
}

//�l�p�`�̒��_
static const uint vnum = 4;

//�Z���^�[����I�t�Z�b�g
static const float4 offset_array[vnum] =
{
    float4(-0.5f, -0.5f, 0, 0), //����
    float4(-0.5f, +0.5f, 0, 0), //����
    float4(+0.5f, -0.5f, 0, 0), //�E��
    float4(+0.5f, +0.5f, 0, 0) //�E��
};

//���オ0,0 �E����1,1

static const float2 uv_array[vnum] =
{
    float2(0, 1), //����
    float2(0, 0), //����
    float2(1, 1), //�E��
    float2(1, 0), //�E��
};

[maxvertexcount(vnum)]

void main(point VSOutput input[1] : SV_POSITION,
	inout TriangleStream<GSOutput> output)
{
    GSOutput element;
    for (uint i = 0; i < vnum; i++)
    {
        //���S����̃I�t�Z�b�g���X�P�[�����O
        float4 offset = offset_array[i] * input[0].scale;

       //���S����̃I�t�Z�b�g�����[�e�[�V����
        offset = rotate(offset, input[0].rotation);

        //���S����̃I�t�Z�b�g���r���{�[�h��]
        offset = mul(matBillboard, offset);

        //�I�t�Z�b�g�����炷
        element.svpos = input[0].svpos + offset;

        //�r���[�v���W�F�N�V�����ϊ�
        element.svpos = mul(matWorld, element.svpos);
        element.uv = uv_array[i];
        element.color = input[0].color;
        output.Append(element);
    }
	
 
}
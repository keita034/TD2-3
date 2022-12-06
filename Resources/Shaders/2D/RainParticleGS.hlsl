#include "RainParticle.hlsli"

float4 rotate(float4 pos, float angle)
{
    return float4(
    pos.x * cos(angle) + pos.y * -sin(angle),
    pos.x * sin(angle) + pos.y * cos(angle),
    pos.z,
    pos.w);
}

//�l�p�`�̒��_
static const uint vnum = 2;

//�Z���^�[����I�t�Z�b�g
static const float4 offset_array[vnum] =
{
    float4(-0.5f, -0.5f, 0, 0), //����
    float4(-0.5f, +0.5f, 0, 0), //����
};

[maxvertexcount(vnum)]

void main(point VSOutput input[1] : SV_POSITION,
	inout LineStream<GSOutput> output)
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
        element.color = input[0].color;
        output.Append(element);
    }
	
 
}
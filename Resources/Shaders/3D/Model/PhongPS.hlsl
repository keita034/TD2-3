#include"Phong.hlsli"

Texture2D<float4> tex : register(t0); //0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0); //0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(VSOutput input) : SV_TARGET
{
    // �e�N�X�`���}�b�s���O
    float4 texcolor = tex.Sample(smp, input.uv);
		
	// ����x
    const float shininess = 4.0f;
	// ���_���王�_�ւ̕����x�N�g��
    float3 eyedir = normalize(cameraPos - input.worldpos.xyz);
    // ���C�g�Ɍ������x�N�g���Ɩ@���̓���
    float3 dotlightnormal = dot(lightv, input.normal);
    // ���ˌ��x�N�g��
    float3 reflect = normalize(-lightv + 2 * dotlightnormal * input.normal);
	// �����ˌ�
    float3 ambient = m_ambient;
    // �g�U���ˌ�
    float3 diffuse = dotlightnormal * m_diffuse;
    // ���ʔ��ˌ�
    float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;
	// �V�F�[�f�B���O�ɂ��F
    float4 shadecolor;
	// �S�ĉ��Z����
    shadecolor.rgb = (ambient + diffuse + specular) * lightcolor.rgb;
    shadecolor.a = m_alpha;
    
	// �V�F�[�f�B���O�ɂ��F�ŕ`��
    return shadecolor * texcolor;
}
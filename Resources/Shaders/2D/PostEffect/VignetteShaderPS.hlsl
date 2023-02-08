#include "VignetteShader.hlsli"

Texture2D<float4> tex : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(VSOutput input) : SV_TARGET
{
     //�e�N�X�`���̐F�𓾂�
   float4 textureColor = tex.Sample(smp, input.uv);
    
    //�~�͈̔͂��v�Z
    float vignette = length((input.uv / size) - center / size);
    vignette = clamp(vignette, 0, 1);

    textureColor -= (vignette * power) * float4(color, 1.0f);

    return float4(textureColor.rgb,1.0);
}
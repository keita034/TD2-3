#include "Particle.hlsli"

VSOutput main(float4 pos : POSITION, float4 col : COLOR, float sca : SCALE, float rot : ROTATION)
{
    VSOutput output; // �s�N�Z���V�F�[�_�[�ɓn���l
    output.svpos =  pos;
    output.color = col;
    output.scale = sca;
    output.rotation = rot;
    return output;
}
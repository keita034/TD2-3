cbuffer cbuff0 : register(b0)
{
    float3 color;
    float2 center;
    float power;
    float2 winSize;
    float2 size;
}

Texture2D<float4> tex : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
RWTexture2D<float4> dstImg : register(u0);

[numthreads(10, 10, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    //�e�N�X�`���̐F�𓾂�
    float3 textureColor = tex[DTid.xy].rgb;
    
    //UV���W�̌v�Z
    float2 uv;
    uv.x = DTid.x / winSize.x;
    uv.y = DTid.y / winSize.y;
    
    //�~�͈̔͂��v�Z
    float vignette = length((uv / size) - center / size);
    vignette = clamp(vignette - 0.2, 0, 1);

    textureColor -= (vignette * power) * color;

    dstImg[DTid.xy] = float4(textureColor, 1);
}
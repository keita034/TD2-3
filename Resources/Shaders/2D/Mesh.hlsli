struct VSOutput
{
    // �V�X�e���p���_���W
    float4 svpos : SV_POSITION;
    // uv�l
    float4 col : COLOR;
};

//3D�ϊ��s��
cbuffer ConstBufferDataTransform : register(b0)
{
    matrix mat; //3D�ϊ��s��
};
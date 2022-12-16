#include"HlslFunc.hlsli"

struct PosNormalUv
{
    float3 pos; //���W
    float3 normal; //�@���x�N�g��
    float2 uv; //uv���W
};

//���̓f�[�^�ɃA�N�Z�X���邽�߂̕ϐ�
StructuredBuffer<PosNormalUv> inputVer : register(t0);

//���̓f�[�^�ɃA�N�Z�X���邽�߂̕ϐ�
StructuredBuffer<PosNormalUv> inputBlendVer : register(t1);

//�o�̓f�[�^�ɃA�N�Z�X���邽�߂̕ϐ�
RWStructuredBuffer<PosNormalUv> outputVer : register(u0);

cbuffer cbuff0 : register(b0)
{
    float t;
};

[numthreads(1, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    uint id = DTid.x;
    outputVer[id].pos = Float3Lerp(inputBlendVer[id].pos, inputVer[id].pos, t);
    outputVer[id].normal = inputVer[id].normal;
    outputVer[id].uv = inputVer[id].uv;

}
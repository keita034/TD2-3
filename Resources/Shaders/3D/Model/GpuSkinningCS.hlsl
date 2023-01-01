// ���_�f�[�^
static const int MAX_BONE = 128;

struct PosNormSkin
{
    float4 pos : POSITION; // ���W
    float3 normal : NORMAL; // �@��
    float2 uv : TEXCOORD; // uv���W
    float3 tangent :TANGENT; // �ڋ��
    float4 color :COLOR; // ���_�F
    uint4 boneIndex : BONEINDICES; // �{�[���̔ԍ�
    float4 boneWeight : BONEWEIGHTS; // �{�[���̏d��

};

cbuffer SkinData : register(b0)
{
    matrix bones[MAX_BONE];
};

//�o�̓f�[�^�\����
struct OutputData
{
    float4 pos; // ���W
    float3 normal; // �@��
    float2 uv; // uv���W
    float3 tangent; // �ڋ��
    float4 color; // ���_�F
};

//���̓f�[�^�ɃA�N�Z�X���邽�߂̕ϐ�
StructuredBuffer<PosNormSkin> input : register(t0);

//�o�̓f�[�^�ɃA�N�Z�X���邽�߂̕ϐ�
RWStructuredBuffer<OutputData> output : register(u0);

//�G���g���[�|�C���g
[numthreads(256, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
     // �[���N���A
    OutputData outputData = (OutputData) 0;

    uint iBone; // �v�Z����{�[���̔ԍ�
    float boneWeight; // �{�[���E�F�C�g(�d��)
    matrix m; // �X�L�j���O�s��

    // �{�[��0
    iBone = input[DTid.x].boneIndex.x;
    boneWeight = input[DTid.x].boneWeight.x;
    m = bones[iBone];
    outputData.pos += boneWeight * mul(m, input[DTid.x].pos);
    outputData.normal += boneWeight * mul((float3x3) m, input[DTid.x].normal);

    // �{�[��1
    iBone = input[DTid.x].boneIndex.y;
    boneWeight = input[DTid.x].boneWeight.y;
    m = bones[iBone];
    outputData.pos += boneWeight * mul(m, input[DTid.x].pos);
    outputData.normal += boneWeight * mul((float3x3) m, input[DTid.x].normal);

    // �{�[��2
    iBone = input[DTid.x].boneIndex.z;
    boneWeight = input[DTid.x].boneWeight.z;
    m = bones[iBone];
    outputData.pos += boneWeight * mul(m, input[DTid.x].pos);
    outputData.normal += boneWeight * mul((float3x3) m, input[DTid.x].normal);

    // �{�[��3
    iBone = input[DTid.x].boneIndex.w;
    boneWeight = input[DTid.x].boneWeight.w;
    m = bones[iBone];
    outputData.pos += boneWeight * mul(m, input[DTid.x].pos);
    outputData.normal += boneWeight * mul((float3x3) m, input[DTid.x].normal);
 
    //outputData.uv = input[DTid.x].uv;
    //outputData.tangent = input[DTid.x].tangent;
    //outputData.color = input[DTid.x].color;
    
    output[DTid.x].pos = outputData.pos;
    output[DTid.x].normal = outputData.normal;

}
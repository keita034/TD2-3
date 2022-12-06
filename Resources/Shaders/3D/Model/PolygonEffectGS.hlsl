#include"ModelBasic.hlsli"

[maxvertexcount(3)]
void main(triangle VSOutput input[3] : SV_POSITION, inout TriangleStream<GSOutput> output)
{
    // �@�����v�Z
    float3 vec1 = input[1].svpos.xyz - input[0].svpos.xyz;
    float3 vec2 = input[2].svpos.xyz - input[0].svpos.xyz;
    float3 normal = normalize(cross(vec1, vec2));
    
    for (uint i = 0; i < 3; i++)
    {
        GSOutput element;
        
        element.normal = input[i].normal;
        element.svpos = input[i].svpos;
        element.uv = input[i].uv;
        
        // �@���x�N�g���ɉ����Ē��_���ړ�
        element.svpos.xyz += normal * velocity;
        output.Append(element);
    }
}
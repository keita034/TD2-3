#include "Material.h"

void Material::Initialize()
{
	pipelineState = std::make_unique<PipelineState>();

	//���_�V�F�[�_��ݒ�
	if (vertexShader)
	{
		pipelineState->SetVertexShader(vertexShader->GetShader());
	}
	
	//�s�N�Z���V�F�[�_��ݒ�
	if (pixelShader)
	{
		pipelineState->SetPixelShader(pixelShader->GetShader());
	}

	//�W�I���g���V�F�[�_��ݒ�
	if (geometryShader)
	{
		pipelineState->SetGeometryShader(geometryShader->GetShader());
	}

	//�n���V�F�[�_��ݒ�
	if (hullShader)
	{
		pipelineState->SetHullShader(hullShader->GetShader());
	}

	//�h���C���V�F�[�_��ݒ�
	if (domainShader)
	{
		pipelineState->SetDomainShader(domainShader->GetShader());
	}

	//���_���C�A�E�g��ݒ�
	pipelineState->SetInputLayout(inputLayouts.data(), inputLayouts.size());

	//�u�����h��ݒ�
	pipelineState->SetBlend(blenddesc);

	//�[�x�t���O��ݒ�
	pipelineState->SetDepthFlag(depthFlag);

	//���[�g�V�O�l�`����ݒ�
	pipelineState->SetRootSignature(rootSignature->GetRootSignature());

	//�v���~�e�B�u�`���ݒ�
	pipelineState->SetPrimitiveType(primitiveType);

	//����
	if (!pipelineState->Create())
	{
		printf("�p�C�v���C���X�e�[�g�������ł��܂���ł���");
		assert(0);
	}
}

#include "PostEffectSprite.h"

void PostEffectSprite::Initialize(ID3D12GraphicsCommandList* commandList, DescriptorHeap* descriptorHeap)
{
	cmdList = commandList;
	srvHeap = descriptorHeap;

	//���_�o�b�t�@�̐���
	vertexBuffer = std::make_unique<VertexBuffer>();
	vertexBuffer->Create(4, sizeof(PosUvColor));

	//�C���f�b�N�X�o�b�t�@�̐���
	indexBuffer = std::make_unique<IndexBuffer>();
	indexBuffer->Create(6);
}

void PostEffectSprite::SetSize(const AliceMathF::Vector2& size)
{
	spriteSize = size;
}

void PostEffectSprite::Draw(Material* material, D3D12_GPU_DESCRIPTOR_HANDLE handle)
{
	// ���_�f�[�^
	PosUvColor vertices[] =
	{//		x		y		z		u	v
		{{-spriteSize.x,spriteSize.y,0.0f},{0.0f,0.0f},{1.0f,1.0f,1.0f,1.0f}},//����C���f�b�N�X0
		{{-spriteSize.x,-spriteSize.y,0.0f},{0.0f,1.0f},{1.0f,1.0f,1.0f,1.0f}},//�����C���f�b�N�X1
		{{spriteSize.x,spriteSize.y,0.0f},{1.0f,0.0f},{1.0f,1.0f,1.0f,1.0f}},//�E��C���f�b�N�X2
		{{spriteSize.x,-spriteSize.y,0.0f},{1.0f,1.0f},{1.0f,1.0f,1.0f,1.0f}},//�E���C���f�b�N�X3
	};

	// �C���f�b�N�X�f�[�^
	uint32_t indices[] =
	{
		1, 0, 3, // �O�p�`1��
		2, 3, 0, // �O�p�`2��
	};

	//���_�o�b�t�@�ւ̃f�[�^�]��
	vertexBuffer->Update(vertices);

	//�C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	indexBuffer->Update(indices);

	D3D12_VERTEX_BUFFER_VIEW vbView = vertexBuffer->GetView();
	D3D12_INDEX_BUFFER_VIEW ibView = indexBuffer->GetView();

	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	cmdList->SetPipelineState(material->pipelineState->GetPipelineState());
	cmdList->SetGraphicsRootSignature(material->rootSignature->GetRootSignature());

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g

	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->IASetIndexBuffer(&ibView);

	// SRV�q�[�v�̐ݒ�R�}���h
	ID3D12DescriptorHeap* descriptorHeaps[] =
	{
		srvHeap->GetHeap(),
	};

	cmdList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

	//// SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^1�Ԃɐݒ�
	cmdList->SetGraphicsRootDescriptorTable(0, handle);

}

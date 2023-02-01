#include "Sprite.h"
#include "DirectX12Core.h"
#include"Sprite2D.h"
#include"Sprite3D.h"

void Sprite::SpriteInitialize()
{
	device = DirectX12Core::GetDeviceSta();
	cmdList = DirectX12Core::GetCommandListSta();
}

void Sprite::SpriteDraw(Transform& transform, Material* material)
{
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

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	cmdList->SetGraphicsRootConstantBufferView(0, transform.GetconstBuff()->GetGPUVirtualAddress());

	// SRV�q�[�v�̐ݒ�R�}���h
	cmdList->SetDescriptorHeaps(1, texture->srvHeap.GetAddressOf());

	//// SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^1�Ԃɐݒ�
	cmdList->SetGraphicsRootDescriptorTable(1, texture->gpuHandle);

	// �`��R�}���h
	cmdList->DrawIndexedInstanced(6, 1, 0, 0, 0);
}

void Sprite::CreatVertexIndexBuffer()
{
	//���_�o�b�t�@�̐���
	vertexBuffer = std::make_unique<VertexBuffer>();
	vertexBuffer->Create(4, sizeof(PosUvColor));

	//�C���f�b�N�X�o�b�t�@�̐���
	indexBuffer = std::make_unique<IndexBuffer>();
	indexBuffer->Create(6);
}

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

void Sprite::SetAnchorPoint(const AliceMathF::Vector2& point)
{
	anchorPoint = point;
}

void Sprite::SetFlipFlag(bool isFlipX, bool isFlipY)
{
	flipX = isFlipX;
	flipY = isFlipY;
}

void Sprite::SetColor(const AliceMathF::Vector4& color)
{
	texture->color = color;
}

void Sprite::SetTextureTrimmingRange(const AliceMathF::Vector2& leftTop, const AliceMathF::Vector2& rightDown)
{
	trimmingRange = { leftTop.x,leftTop.y,rightDown.x,rightDown.y };
}

void Sprite::SetTex(uint32_t handle)
{
	texture = TextureManager::GetTextureData(handle);
	trimmingRange.z = static_cast<float>(texture->width);
	trimmingRange.w = static_cast<float>(texture->height);
	spriteSize.x = static_cast<float>(texture->width);
	spriteSize.y = static_cast<float>(texture->height);
}

void Sprite::SetSize(const AliceMathF::Vector2& size)
{
	spriteSize.x = size.x;
	spriteSize.y = size.y;
}

Sprite2D* Sprite::Create2DSprite(uint32_t handle)
{
	Sprite2D* s2D = new Sprite2D;
	s2D->Initialize(handle);
	return s2D;
}

Sprite3D* Sprite::Create3DSprite(uint32_t handle)
{
	Sprite3D* s3D = new Sprite3D;
	s3D->Initialize(handle);
	return s3D;
}

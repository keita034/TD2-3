#pragma once
#include"ErrorException.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"Material.h"


class PostEffectSprite
{
private:

	//���_�o�b�t�@
	std::unique_ptr<VertexBuffer> vertexBuffer;

	//�C���f�b�N�X�o�b�t�@
	std::unique_ptr<IndexBuffer> indexBuffer;

	ID3D12GraphicsCommandList* cmdList = nullptr;

	DescriptorHeap* srvHeap = nullptr;

	AliceMathF::Vector2 spriteSize;

public:

	void Initialize(ID3D12GraphicsCommandList* commandList, DescriptorHeap* descriptorHeap);

	void SetSize(const AliceMathF::Vector2& size);

	void Draw(Material* material, D3D12_GPU_DESCRIPTOR_HANDLE handle);
};


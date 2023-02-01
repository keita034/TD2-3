#include "VertexBuffer.h"
#include "DirectX12Core.h"

void VertexBuffer::Create(size_t length, size_t singleSize, const void* data)
{
	// �q�[�v�v���p�e�B
	CD3DX12_HEAP_PROPERTIES heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);

	// ���\�[�X�̐ݒ�
	CD3DX12_RESOURCE_DESC resDesc = CD3DX12_RESOURCE_DESC::Buffer(length * singleSize);

	// ���\�[�X�𐶐�
	HRESULT result = DirectX12Core::GetDeviceSta()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(vertexBuffer.ReleaseAndGetAddressOf()));

	if (FAILED(result))
	{
		printf("���_�o�b�t�@���\�[�X�̐����Ɏ��s");
		return;
	}

	// ���_�o�b�t�@�r���[�̐ݒ�
	vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = static_cast<UINT>(length * singleSize);
	vertexBufferView.StrideInBytes = static_cast<UINT>(singleSize);

	result = vertexBuffer->Map(0, nullptr, &bufferMappedPtr);
	if (FAILED(result))
	{
		printf("���_�o�b�t�@�}�b�s���O�Ɏ��s");
		return;
	}

	// �}�b�s���O����
	if (data != nullptr)
	{
		// ���_�f�[�^���}�b�s���O��ɐݒ�
		memcpy(bufferMappedPtr, data, length * singleSize);
	}

	isValid = true;
}

void VertexBuffer::Update(void* data)
{
	if (data == nullptr)
	{
		return;
	}

	// ���_�f�[�^���}�b�s���O��ɐݒ�
	memcpy(bufferMappedPtr, data, vertexBufferView.SizeInBytes);
}

D3D12_VERTEX_BUFFER_VIEW VertexBuffer::GetView() const
{
	return vertexBufferView;
}

bool VertexBuffer::IsValid()
{
	return isValid;
}

ID3D12Resource* VertexBuffer::GetResource()
{
	return vertexBuffer.Get();
}
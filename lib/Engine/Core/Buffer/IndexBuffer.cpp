#include "IndexBuffer.h"
#include"DirectX12Core.h"

void IndexBuffer::Create(size_t length, const uint32_t* data)
{
	bufferLength = length;

	// �q�[�v�v���p�e�B
	CD3DX12_HEAP_PROPERTIES heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);

	// ���\�[�X�̐ݒ�
	CD3DX12_RESOURCE_DESC resDesc = CD3DX12_RESOURCE_DESC::Buffer(length* sizeof(uint32_t));	// ���\�[�X�̐ݒ�

	// ���\�[�X�𐶐�
	HRESULT result = DirectX12Core::GetDeviceSta()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(buffer.ReleaseAndGetAddressOf()));
	if (FAILED(result))
	{
		printf("�C���f�b�N�X�o�b�t�@���\�[�X�̐����Ɏ��s");
		return;
	}

	// �C���f�b�N�X�o�b�t�@�r���[�̐ݒ�
	bufferView = {};
	bufferView.BufferLocation = buffer->GetGPUVirtualAddress();
	bufferView.Format = DXGI_FORMAT_R32_UINT;
	bufferView.SizeInBytes = static_cast<UINT>(length * sizeof(uint32_t));

	result = buffer->Map(0, nullptr, &bufferMappedPtr);
	if (FAILED(result))
	{
		printf("�C���f�b�N�X�o�b�t�@�}�b�s���O�Ɏ��s");
		return;
	}

	// �}�b�s���O����
	if (data != nullptr)
	{
		// �C���f�b�N�X�f�[�^���}�b�s���O��ɐݒ�
		memcpy(bufferMappedPtr, data, length * sizeof(uint32_t));

		// �}�b�s���O����
		buffer->Unmap(0, nullptr);
	}

	isValid = true;
}

bool IndexBuffer::IsValid()
{
	return isValid;
}

D3D12_INDEX_BUFFER_VIEW IndexBuffer::GetView() const
{
	return bufferView;
}

void IndexBuffer::Update(void* data)
{
	memcpy(bufferMappedPtr, data, bufferLength * sizeof(uint32_t));
}

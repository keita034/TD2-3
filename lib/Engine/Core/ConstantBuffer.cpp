#include "ConstantBuffer.h"
#include"DirectX12Core.h"

void ConstantBuffer::Create(size_t size)
{
	bufferSize = size;

	// �q�[�v�v���p�e�B
	CD3DX12_HEAP_PROPERTIES heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);

	// ���\�[�X�̐ݒ�
	CD3DX12_RESOURCE_DESC resDesc = CD3DX12_RESOURCE_DESC::Buffer((bufferSize + 0xff) & ~0xff);

	// ���\�[�X�𐶐�
	HRESULT result = DirectX12Core::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(buffer.ReleaseAndGetAddressOf()));

	if (FAILED(result))
	{
		printf("�萔�o�b�t�@���\�[�X�̐����Ɏ��s\n");
		return;
	}

	result = buffer->Map(0, nullptr, &bufferMappedPtr);

	if (FAILED(result))
	{
		printf("�萔�o�b�t�@�̃}�b�s���O�Ɏ��s\n");
		return;
	}

	constantBufferView = {};
	constantBufferView.BufferLocation = buffer->GetGPUVirtualAddress();
	constantBufferView.SizeInBytes = static_cast<UINT>(resDesc.Width);

	DirectX12Core::GetInstance()->GetDescriptorHeap()->CreateCBV(constantBufferView);

	isValid = true;
}

bool ConstantBuffer::IsValid()
{
	return isValid;
}

D3D12_GPU_VIRTUAL_ADDRESS ConstantBuffer::GetAddress() const
{
	return constantBufferView.BufferLocation;
}

D3D12_CONSTANT_BUFFER_VIEW_DESC ConstantBuffer::GetViewDesc()
{
	return constantBufferView;
}

void ConstantBuffer::Update(void* data)
{
	if (data == nullptr)
	{
		return;
	}

	// ���_�f�[�^���}�b�s���O��ɐݒ�
	memcpy(bufferMappedPtr, data, bufferSize);
}

ID3D12Resource* ConstantBuffer::GetResource()
{
	return buffer.Get();
}

void* ConstantBuffer::GetPtr()
{
	return bufferMappedPtr;
}
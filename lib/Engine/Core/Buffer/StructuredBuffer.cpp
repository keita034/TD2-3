#include "StructuredBuffer.h"
#include"DirectX12Core.h"
void StructuredBuffer::Create(size_t length, size_t singleSize, const void* data)
{
	bufferLength = length;
	bufferSingleSize = singleSize;

	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSingleSize * length);
	desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

	D3D12_HEAP_PROPERTIES prop{};
	prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	prop.CreationNodeMask = 1;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	prop.Type = D3D12_HEAP_TYPE_CUSTOM;
	prop.VisibleNodeMask = 1;
	DirectX12Core::GetDeviceSta()->CreateCommittedResource(
		&prop,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_UNORDERED_ACCESS,
		nullptr,
		IID_PPV_ARGS(buffer.GetAddressOf())
	);

	// �\�����o�b�t�@��CPU����A�N�Z�X�\�ȉ��z�A�h���X��ԂɃ}�b�s���O����B
	buffer->Map(0, nullptr, reinterpret_cast<void**>(&BufferMappedPtr));
	if (data != nullptr)
	{
		memcpy(BufferMappedPtr, data, static_cast<size_t>(singleSize * length));
	}

	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;//�o�b�t�@�Ƃ���
	srvDesc.Buffer.NumElements = static_cast<UINT>(length);//�v�f�̑���
	srvDesc.Buffer.StructureByteStride = static_cast<UINT>(singleSize);//1������̑傫��
	srvDesc.Buffer.FirstElement = 0;
	srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

	structuredBufferHandle.ptr = DirectX12Core::GetInstance()->GetDescriptorHeap()->CreateSRV(srvDesc, buffer.Get());

	isValid = true;
}

void StructuredBuffer::Update(void* data)
{
	if (data)
	{
		// ���_�f�[�^���}�b�s���O��ɐݒ�
		memcpy(BufferMappedPtr, data, static_cast<size_t>(bufferSingleSize * bufferLength));
	}
}

bool StructuredBuffer::IsValid()
{
	return isValid;
}

D3D12_GPU_DESCRIPTOR_HANDLE StructuredBuffer::GetAddress() const
{
	return structuredBufferHandle;
}

D3D12_SHADER_RESOURCE_VIEW_DESC StructuredBuffer::GetViewDesc()
{
	return D3D12_SHADER_RESOURCE_VIEW_DESC();
}

void* StructuredBuffer::GetPtr()const
{
	return BufferMappedPtr;
}
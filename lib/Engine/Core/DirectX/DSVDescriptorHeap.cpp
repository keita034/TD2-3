#include "DSVDescriptorHeap.h"
#include"DirectX12Core.h"

void DSVDescriptorHeap::Initialize()
{
	device = DirectX12Core::GetInstance()->GetDevice().Get();
	HRESULT result = 0;

	// �f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.NumDescriptors = static_cast<UINT>(maxDSV);

	// �ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	result = device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(descriptorHeap.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));

	incrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

	//SRV�q�[�v�̐擪�n���h�����擾
	startCpuHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
}

UINT64 DSVDescriptorHeap::CreateDSV(D3D12_DEPTH_STENCIL_VIEW_DESC& desc, ID3D12Resource* resource)
{
	if (countDSV > maxDSV)
	{
		assert(0);
	}

	D3D12_CPU_DESCRIPTOR_HANDLE	handle{};

	handle.ptr = startCpuHandle.ptr + (static_cast<UINT64>(countDSV) * incrementSize);

	device->CreateDepthStencilView(resource, &desc, handle);
	countDSV++;

	return handle.ptr;
}

ID3D12DescriptorHeap* DSVDescriptorHeap::GetHeap()
{
	return descriptorHeap.Get();
}

UINT DSVDescriptorHeap::GetIncrementSize()
{
	return incrementSize;
}

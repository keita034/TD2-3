#include "RTVDescriptorHeap.h"
#include"DirectX12Core.h"

void RTVDescriptorHeap::Initialize()
{
	device = DirectX12Core::GetInstance()->GetDevice().Get();
	HRESULT result = 0;

	// �f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.NumDescriptors = static_cast<UINT>(maxRTV);

	// �ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	result = device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(descriptorHeap.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));

	incrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	//SRV�q�[�v�̐擪�n���h�����擾
	startCpuHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
}

UINT64 RTVDescriptorHeap::CreateRTV(D3D12_RENDER_TARGET_VIEW_DESC& desc, ID3D12Resource* resource)
{
	if (countRTV > maxRTV)
	{
		assert(0);
	}

	D3D12_CPU_DESCRIPTOR_HANDLE	handle{};

	handle.ptr = startCpuHandle.ptr + (static_cast<UINT64>(countRTV) * incrementSize);

	device->CreateRenderTargetView(resource, &desc, handle);
	countRTV++;

	return handle.ptr;
}

ID3D12DescriptorHeap* RTVDescriptorHeap::GetHeap()
{
	return descriptorHeap.Get();
}

UINT RTVDescriptorHeap::GetIncrementSize()
{
	return incrementSize;
}

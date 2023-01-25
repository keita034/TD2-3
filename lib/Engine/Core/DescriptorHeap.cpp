#include "DescriptorHeap.h"
#include"DirectX12Core.h"

void DescriptorHeap::Initialize()
{
	device = DirectX12Core::GetInstance()->GetDevice();

	// �f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//�V�F�[�_���猩����悤��
	srvHeapDesc.NumDescriptors = static_cast<UINT>(maxSRV + maxUAV + maxCBV);

	// �ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	HRESULT result = device->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(descriptorHeap.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));

	incrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//SRV�q�[�v�̐擪�n���h�����擾
	startCpuHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	startGpuHandle = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
}

UINT64 DescriptorHeap::CreateSRV(D3D12_SHADER_RESOURCE_VIEW_DESC& desc, ID3D12Resource* resource)
{
	if (countSRV > maxSRV)
	{
		assert(0);
	}

	//SRV�q�[�v�̐擪�n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE	cpuHandle{};
	D3D12_GPU_DESCRIPTOR_HANDLE	gpuHandle{};

	//�n���h���̃|�C���^���炵
	cpuHandle.ptr = startCpuHandle.ptr + (static_cast<UINT64>(countSRV) * incrementSize);
	gpuHandle.ptr = startGpuHandle.ptr + (static_cast<UINT64>(countSRV) * incrementSize);

	// �n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
	device->CreateShaderResourceView(resource, &desc, cpuHandle);
	countSRV++;

	return gpuHandle.ptr;
}

DescriptorHeap::DescriptorHeapViewHandle DescriptorHeap::AddSRV()
{
	if (countSRV > maxSRV)
	{
		assert(0);
	}

	DescriptorHeapViewHandle handle{};

	//�n���h���̃|�C���^���炵
	handle.cpuHandle.ptr = startCpuHandle.ptr + (static_cast<UINT64>(countSRV) * incrementSize);
	handle.gpuHandle.ptr = startGpuHandle.ptr + (static_cast<UINT64>(countSRV) * incrementSize);

	countSRV++;

	return handle;
}

UINT64 DescriptorHeap::CreateUAV(D3D12_UNORDERED_ACCESS_VIEW_DESC& desc, ID3D12Resource* resource)
{
	if (countUAV > maxUAV)
	{
		assert(0);
	}

	//SRV�q�[�v�̐擪�n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE	cpuHandle{};
	D3D12_GPU_DESCRIPTOR_HANDLE	gpuHandle{};

	//�n���h���̃|�C���^���炵
	cpuHandle.ptr = startCpuHandle.ptr + (static_cast<UINT64>(maxSRV + countUAV) * incrementSize);
	gpuHandle.ptr = startGpuHandle.ptr + (static_cast<UINT64>(maxSRV + countUAV) * incrementSize);

	// �n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
	device->CreateUnorderedAccessView(resource, nullptr, &desc, cpuHandle);

	countUAV++;

	return gpuHandle.ptr;
}

DescriptorHeap::DescriptorHeapViewHandle DescriptorHeap::AddUAV()
{
	if (countUAV > maxUAV)
	{
		assert(0);
	}

	DescriptorHeapViewHandle handle{};

	//�n���h���̃|�C���^���炵
	handle.cpuHandle.ptr = startCpuHandle.ptr + (static_cast<UINT64>(maxSRV + countUAV) * incrementSize);
	handle.gpuHandle.ptr = startGpuHandle.ptr + (static_cast<UINT64>(maxSRV + countUAV) * incrementSize);

	countUAV++;

	return handle;
}

UINT64 DescriptorHeap::CreateCBV(D3D12_CONSTANT_BUFFER_VIEW_DESC& desc)
{
	if (countCBV > maxCBV)
	{
		assert(0);
	}

	//SRV�q�[�v�̐擪�n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE	cpuHandle{};
	D3D12_GPU_DESCRIPTOR_HANDLE	gpuHandle{};

	//�n���h���̃|�C���^���炵
	cpuHandle.ptr = startCpuHandle.ptr + (static_cast<UINT64>(maxSRV + maxUAV + countCBV) * incrementSize);
	gpuHandle.ptr = startGpuHandle.ptr + (static_cast<UINT64>(maxSRV + maxUAV + countCBV) * incrementSize);

	// �n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
	device->CreateConstantBufferView(&desc, cpuHandle);

	countCBV++;

	return gpuHandle.ptr;
}

DescriptorHeap::DescriptorHeapViewHandle DescriptorHeap::AddCBV()
{
	if (countCBV > maxCBV)
	{
		assert(0);
	}

	DescriptorHeapViewHandle handle{};

	//�n���h���̃|�C���^���炵
	handle.cpuHandle.ptr = startCpuHandle.ptr + (static_cast<UINT64>(maxSRV + maxUAV + countCBV) * incrementSize);
	handle.gpuHandle.ptr = startGpuHandle.ptr + (static_cast<UINT64>(maxSRV + maxUAV + countCBV) * incrementSize);

	countCBV++;

	return handle;
}

ID3D12DescriptorHeap* DescriptorHeap::GetHeap()
{
	return descriptorHeap.Get();
}


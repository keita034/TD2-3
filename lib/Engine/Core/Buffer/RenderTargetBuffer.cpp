#include "RenderTargetBuffer.h"

bool RenderTargetBuffer::Create(UINT w, UINT h, D3D12_RESOURCE_STATES resourceStates, UINT16 mipLevel, UINT16 arraySize, DXGI_FORMAT format, const AliceMathF::Vector4& clearColor)
{
	width = w;
	height = h;
	states = resourceStates;

	CD3DX12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Tex2D(
		format,
		w, h,
		arraySize, mipLevel, 1, 0,
		D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET);

	float col[4] = { clearColor.x,clearColor.y, clearColor.z, clearColor.w };
	CD3DX12_CLEAR_VALUE cleaVal = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, col);

	//���\�[�X���쐬�B
	CD3DX12_HEAP_PROPERTIES heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);;

	HRESULT hr = device->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		resourceStates,
		&cleaVal,
		IID_PPV_ARGS(texture.GetAddressOf())
	);

	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "�����_�[�^�[�Q�b�g�o�b�t�@�̍쐬�Ɏ��s", "�G���[", MB_OK);
		return false;
	}

	//�^�[�Q�b�g�r���[�̐ݒ�
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	//�v�Z���ʂ�SRGB�ɕϊ�
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	handle.ptr = rtvHeap->CreateRTV(rtvDesc, texture.Get());

	return true;
}

bool RenderTargetBuffer::Create(IDXGISwapChain4* swapChain, UINT index)
{
	//�o�b�t�@���擾
	swapChain->GetBuffer(index, IID_PPV_ARGS(texture.ReleaseAndGetAddressOf()));

	//�^�[�Q�b�g�r���[�̐ݒ�
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	//�v�Z���ʂ�SRGB�ɕϊ�
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	handle.ptr = rtvHeap->CreateRTV(rtvDesc, texture.Get());

	return true;
}

RenderTargetBuffer::RenderTargetBuffer(ID3D12Device* d3dDevice, RTVDescriptorHeap* descriptorHeap)
	: device(d3dDevice), rtvHeap(descriptorHeap)
{
}

ID3D12Resource* RenderTargetBuffer::GetTexture() const
{
	return texture.Get();
}

const D3D12_CPU_DESCRIPTOR_HANDLE& RenderTargetBuffer::GetHandle()
{
	return handle;
}

void RenderTargetBuffer::Transition(D3D12_RESOURCE_STATES resourceStates, ID3D12GraphicsCommandList* commandList)
{
	if (states != resourceStates)
	{
		CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(texture.Get(), states, resourceStates);
		commandList->ResourceBarrier(1, &barrier);
		states = resourceStates;
	}
	else
	{
		assert(0);
	}
}



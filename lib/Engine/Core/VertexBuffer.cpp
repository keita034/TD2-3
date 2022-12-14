#include "VertexBuffer.h"
#include "DirectX12Core.h"

void VertexBuffer::Create(size_t length, size_t singleSize, const void* data)
{
	// ヒーププロパティ
	CD3DX12_HEAP_PROPERTIES heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);

	// リソースの設定
	CD3DX12_RESOURCE_DESC resDesc = CD3DX12_RESOURCE_DESC::Buffer(length * singleSize);

	// リソースを生成
	HRESULT result = DirectX12Core::GetDeviceSta()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(vertexBuffer.ReleaseAndGetAddressOf()));

	if (FAILED(result))
	{
		printf("頂点バッファリソースの生成に失敗");
		return;
	}

	// 頂点バッファビューの設定
	vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = static_cast<UINT>(length * singleSize);
	vertexBufferView.StrideInBytes = static_cast<UINT>(singleSize);

	result = vertexBuffer->Map(0, nullptr, &bufferMappedPtr);
	if (FAILED(result))
	{
		printf("頂点バッファマッピングに失敗");
		return;
	}

	// マッピングする
	if (data != nullptr)
	{
		// 頂点データをマッピング先に設定
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

	// 頂点データをマッピング先に設定
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
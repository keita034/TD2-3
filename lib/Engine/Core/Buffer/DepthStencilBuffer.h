#pragma once
#include"ErrorException.h"
#include"DSVDescriptorHeap.h"

class DepthStencilBuffer
{
private:

	//テクスチャ
	Microsoft::WRL::ComPtr<ID3D12Resource> texture;
	//ディスクリプタヒープ
	DSVDescriptorHeap* dsvHeap = nullptr;
	//幅
	UINT width = 0;
	//高さ
	UINT height = 0;
	//デバイス
	ID3D12Device* device = nullptr;
	//ハンドル
	D3D12_CPU_DESCRIPTOR_HANDLE handle{};

public:

	/// <summary>
	/// 生成
	/// </summary>
	/// <param name="w">横幅</param>
	/// <param name="h">縦幅</param>
	/// <param name="format">フォーマット</param>
	bool Create(UINT w, UINT h, DXGI_FORMAT format);

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="d3dDevice">デバイス</param>
	/// <param name="descriptorHeap">デプスステンシル用のデスクプリタヒープ</param>
	DepthStencilBuffer(ID3D12Device* d3dDevice, DSVDescriptorHeap* descriptorHeap);

	/// <summary>
	/// リソースを取得
	/// </summary>
	ID3D12Resource* GetTexture() const;

	/// <summary>
	/// ポインタ番号を取得
	/// </summary>
	const D3D12_CPU_DESCRIPTOR_HANDLE& GetHandle() ;

	~DepthStencilBuffer() = default;

private:

	DepthStencilBuffer() = delete;
};
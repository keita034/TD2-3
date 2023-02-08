#pragma once
#include"ErrorException.h"
#include"DescriptorHeap.h"
#include"DSVDescriptorHeap.h"
#include"RTVDescriptorHeap.h"
#include"RenderTargetBuffer.h"
#include"DepthStencilBuffer.h"

/// <summary>
/// コア
/// </summary>
class DirectX12Core
{
private:

	HRESULT result;
	char PADING[4];
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;

	Microsoft::WRL::ComPtr<ID3D12Fence> fence;

	//RTV用のデスクプリタヒープ
	std::unique_ptr<RTVDescriptorHeap> rtvHeap;

	//SRV用のデスクプリタヒープ
	std::unique_ptr<DescriptorHeap> srvHeap;

	//深度バッファ
	std::unique_ptr<DepthStencilBuffer> depthBuff;

	//DSV用のデスクプリタヒープ
	std::unique_ptr<DSVDescriptorHeap> dsvHeap;

	//バックバッファ
	std::vector<std::unique_ptr<RenderTargetBuffer>> backBuffers;

	//フェンスの生成
	UINT64 fenceVal = 0;

	//スワップチェーンの設定
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	//クリアーカラー
	//FLOAT clearColor[4] = { 0.1f, 0.25f, 0.5f, 0.0f };
	FLOAT clearColor[4] = { 1.0f,1.0f,1.0f,1.0f};

	//ビューポート
	D3D12_VIEWPORT viewport{};

	//シザー矩形
	D3D12_RECT scissorRect{};

	static DirectX12Core* DirectX12Core_;
	
	UINT bbIndex;

	char PADING2[4]{};
public:

	//シングルトンインスタンスの取得
	static DirectX12Core* GetInstance();

	/// <summary>
	/// デバイスの取得(スタティック)
	/// </summary>
	static Microsoft::WRL::ComPtr<ID3D12Device> GetDeviceSta();

	/// <summary>
	/// コマンドリストの取得(スタティック)
	/// </summary>
	static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> GetCommandListSta();
	
	/// <summary>
	/// リソースの状態を変える
	/// </summary>
	/// <param name="resource">リソース</param>
	/// <param name="beforeState">今の状態</param>
	/// <param name="afterState">変えたい状態</param>
	static void ResourceTransition(ID3D12Resource* resource, D3D12_RESOURCE_STATES beforeState, D3D12_RESOURCE_STATES afterState);

	/// <summary>
	/// 初期化
	/// </summary>
	void DirectXInitialize();

	/// <summary>
	/// 描画準備
	/// </summary>
	void BeginDraw();

	/// <summary>
	/// 描画後始末
	/// </summary>
	void EndDraw();

	/// <summary>
	/// コマンド後始末
	/// </summary>
	void ExecuteCommand();

	/// <summary>
	/// 開放
	/// </summary>
	void Destroy();

	//背景の色変え(RGBA)
	void SetBackScreenColor(float red, float green, float blue, float alpha);

	/// <summary>
	/// デバイスの取得
	/// </summary>
	Microsoft::WRL::ComPtr<ID3D12Device> GetDevice();

	/// <summary>
	/// コマンドリスト取得
	/// </summary>
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> GetCommandList();

	/// <summary>
	/// SRV,CBV,URV用デスクプリタヒープ取得
	/// </summary>
	DescriptorHeap* GetSRVDescriptorHeap();

	/// <summary>
	/// RTV用デスクプリタヒープ取得
	/// </summary>
	RTVDescriptorHeap* GetRTVDescriptorHeap();

	/// <summary>
	/// DSV用デスクプリタヒープ取得
	/// </summary>
	DSVDescriptorHeap* GetDSVDescriptorHeap();

	/// <summary>
	/// リソースの状態を変える
	/// </summary>
	/// <param name="resource">リソース</param>
	/// <param name="beforeState">今の状態</param>
	/// <param name="afterState">変えたい状態</param>
	void Transition(ID3D12Resource* resource, D3D12_RESOURCE_STATES beforeState, D3D12_RESOURCE_STATES afterState);

	/// <summary>
	/// バックバッファの数を取得
	/// </summary>
	/// <returns>バックバッファの数</returns>
	size_t GetBackBufferCount() const;

private:

	//DXGIまわり初期化
	HRESULT InitializeDXGIDevice();

	//最終的なレンダーターゲットの生成
	HRESULT CreatFinalRenderTarget();

	//スワップチェインの生成
	HRESULT CreateSwapChain();

	//コマンドまわり初期化
	HRESULT InitializeCommand();

	//フェンス生成
	HRESULT CreateFence();

	//深度関係生成
	HRESULT CreatDepthBuffer();

	//デバッグレイヤーを有効にする
	void EnableDebugLayer();

	//インフォキューを有効にする
	void EnableInfoQueue();

	//コンストラクタ・デストラクタ
	DirectX12Core() = default;
	~DirectX12Core();

	//コピーコンストラクタ・代入演算子削除
	DirectX12Core& operator=(const DirectX12Core&) = delete;
	DirectX12Core(const DirectX12Core&) = delete;
};
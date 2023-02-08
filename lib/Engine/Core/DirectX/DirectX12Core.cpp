#include "DirectX12Core.h"
#include"WindowsApp.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

DirectX12Core* DirectX12Core::DirectX12Core_ = nullptr;

HRESULT DirectX12Core::CreatFinalRenderTarget()
{
	//デスクリプタヒープの生成
	rtvHeap = std::make_unique<RTVDescriptorHeap>();
	rtvHeap->Initialize();

	//バックバッファ
	backBuffers.resize(swapChainDesc.BufferCount);

	//スワップチェーンのバッファを処理
	for (size_t i = 0; i < backBuffers.size(); i++)
	{
		backBuffers[i] = std::make_unique<RenderTargetBuffer>(device.Get(), rtvHeap.get());
		
		//生成
		backBuffers[i]->Create(swapChain.Get(), i);
	}

	return S_OK;
}

HRESULT DirectX12Core::CreateSwapChain()
{
	swapChainDesc.Width = WindowsApp::GetInstance()->GetWindowSize().width;//横幅
	swapChainDesc.Height = WindowsApp::GetInstance()->GetWindowSize().height;//縦幅
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//色情報の書式
	swapChainDesc.SampleDesc.Count = 1;//マルチサンプルなし
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;//バックバッファ用
	swapChainDesc.BufferCount = 2;//バッファ数2
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;//フリップ後は破棄
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//生成
	if (commandQueue != 0)
	{
		Microsoft::WRL::ComPtr<IDXGISwapChain1> tmpSwapChain;
		result = dxgiFactory->CreateSwapChainForHwnd(commandQueue.Get(), WindowsApp::GetInstance()->GetHwnd(), &swapChainDesc, nullptr, nullptr, tmpSwapChain.ReleaseAndGetAddressOf());
		tmpSwapChain.As(&swapChain);

		if (FAILED(result))
		{
			return result;
		}
	}
	else
	{
		assert(SUCCEEDED(0));
	}

	return result;
}

void DirectX12Core::Transition(ID3D12Resource* resource, D3D12_RESOURCE_STATES beforeState, D3D12_RESOURCE_STATES afterState)
{
	auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(resource, beforeState, afterState);
	commandList->ResourceBarrier(1, &barrier);
}

size_t DirectX12Core::GetBackBufferCount() const
{
	return backBuffers.size();
}

HRESULT DirectX12Core::InitializeDXGIDevice()
{
	//対応レベルの配列
	D3D_FEATURE_LEVEL levels[] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	//DXGIファクトリー
	result = CreateDXGIFactory(IID_PPV_ARGS(dxgiFactory.ReleaseAndGetAddressOf()));
	if (FAILED(result))
	{
		return result;
	}

	//アダプター列挙用
	std::vector<Microsoft::WRL::ComPtr<IDXGIAdapter4>> adapters;
	//ここに特定の名前を持つアダプターオブジェクトが入る
	Microsoft::WRL::ComPtr<IDXGIAdapter4> tmpAdapter;

	//パフォーマンスが高いのもから全て列挙
	for (UINT i = 0; dxgiFactory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(tmpAdapter.ReleaseAndGetAddressOf())) != DXGI_ERROR_NOT_FOUND; i++)
	{
		adapters.push_back(tmpAdapter);
	}

	// 妥当なアダプタを選別する
	for (size_t i = 0; i < adapters.size(); i++) {
		DXGI_ADAPTER_DESC3 adapterDesc;
		// アダプターの情報を取得する
		adapters[i]->GetDesc3(&adapterDesc);

		// ソフトウェアデバイスを回避
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
			// デバイスを採用してループを抜ける
			tmpAdapter = adapters[i];
			break;
		}
	}

	//Direct3Dデバイスの初期化
	D3D_FEATURE_LEVEL featureLevel;

	for (size_t i = 0; i < _countof(levels); i++) {
		// 採用したアダプターでデバイスを生成
		result = D3D12CreateDevice(tmpAdapter.Get(), levels[i], IID_PPV_ARGS(device.GetAddressOf()));
		if (result == S_OK) {
			// デバイスを生成できた時点でループを抜ける
			featureLevel = levels[i];
			break;
		}
	}

	return result;
}

HRESULT DirectX12Core::InitializeCommand()
{
	//コマンドアロケータを生成
	result = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(cmdAllocator.ReleaseAndGetAddressOf()));
	if (FAILED(result))
	{
		return result;
	}

	//コマンドリストを生成
	if (cmdAllocator != 0)
	{
		result = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAllocator.Get(), nullptr, IID_PPV_ARGS(commandList.ReleaseAndGetAddressOf()));
		if (FAILED(result))
		{
			return result;
		}
	}
	else
	{
		assert(SUCCEEDED(0));
	}

	//コマンドキューの設定＆生成
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	result = device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(commandQueue.ReleaseAndGetAddressOf()));
	if (FAILED(result))
	{
		return result;
	}

	return result;
}

HRESULT DirectX12Core::CreateFence()
{
	//フェンスの生成
	result = device->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.ReleaseAndGetAddressOf()));

	return result;
}

HRESULT DirectX12Core::CreatDepthBuffer()
{
	//デスクプリタヒープ生成
	dsvHeap = std::make_unique<DSVDescriptorHeap>();
	dsvHeap->Initialize();

	//深度バッファ生成
	depthBuff = std::make_unique<DepthStencilBuffer>(device.Get(),dsvHeap.get());
	depthBuff->Create(WindowsApp::GetInstance()->GetWindowSize().width, WindowsApp::GetInstance()->GetWindowSize().height, DXGI_FORMAT_D32_FLOAT);

	return result;
}

void DirectX12Core::ResourceTransition(ID3D12Resource* resource, D3D12_RESOURCE_STATES beforeState, D3D12_RESOURCE_STATES afterState)
{
	GetInstance()->Transition(resource, beforeState, afterState);
}

void DirectX12Core::DirectXInitialize()
{
#ifdef _DEBUG
	EnableDebugLayer();
#endif

	//DirectX12関連初期化
	if (FAILED(InitializeDXGIDevice()))
	{
		assert(0);
		return;
	}

#ifdef _DEBUG
	EnableInfoQueue();
#endif

	if (FAILED(InitializeCommand()))
	{
		assert(0);
		return;
	}
	if (FAILED(CreateSwapChain()))
	{
		assert(0);
		return;
	}
	if (FAILED(CreatDepthBuffer()))
	{
		assert(0);
		return;
	}
	if (FAILED(CreatFinalRenderTarget()))
	{
		assert(0);
		return;
	}
	if (FAILED(CreateFence()))
	{
		assert(0);
		return;
	}

	//デスクプリタヒープ生成
	srvHeap = std::make_unique<DescriptorHeap>();
	srvHeap->Initialize();
}

void DirectX12Core::EnableDebugLayer()
{
	Microsoft::WRL::ComPtr <ID3D12Debug1> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(debugController.ReleaseAndGetAddressOf()))))
	{
		debugController->EnableDebugLayer();
		//debugController->SetEnableGPUBasedValidation(true);
	}
}

void DirectX12Core::EnableInfoQueue()
{
	Microsoft::WRL::ComPtr<ID3D12InfoQueue> infoQueue;
	result = device->QueryInterface(IID_PPV_ARGS(&infoQueue));
	if (SUCCEEDED(result))
	{
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);
	}

	//抑制するエラー
	D3D12_MESSAGE_ID denyIds[] =
	{
		/*
		*windows11でのDXGIデバッグレイヤーとDX12デバッグレイヤー
		*相互作用バグによるエラーメッセージ
		*/
		D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE

	};
		//抑制する表示レベル
	D3D12_MESSAGE_SEVERITY severities[] = { D3D12_MESSAGE_SEVERITY_INFO };
	D3D12_INFO_QUEUE_FILTER filter{};
	filter.DenyList.NumIDs = _countof(denyIds);
	filter.DenyList.pIDList = denyIds;
	filter.DenyList.NumSeverities = _countof(severities);
	filter.DenyList.pSeverityList = severities;
	//指定したエラーの表示を抑制する
	infoQueue->PushStorageFilter(&filter);
}

DirectX12Core::~DirectX12Core()
{
}

void DirectX12Core::BeginDraw()
{
	//1バックバッファ番号を取得
	bbIndex = swapChain->GetCurrentBackBufferIndex();
	//書き込み可能に変更

	backBuffers[bbIndex]->Transition(D3D12_RESOURCE_STATE_RENDER_TARGET, commandList.Get());

	commandList->OMSetRenderTargets(1, &backBuffers[bbIndex]->GetHandle(), false, &depthBuff->GetHandle());

	//3画面クリア
	commandList->ClearRenderTargetView(backBuffers[bbIndex]->GetHandle(), clearColor, 0, nullptr);
	commandList->ClearDepthStencilView(depthBuff->GetHandle(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
	//ビューポート設定
	viewport.Width = (FLOAT)WindowsApp::GetInstance()->GetWindowSize().width;
	viewport.Height = (FLOAT)WindowsApp::GetInstance()->GetWindowSize().height;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	// ビューポート設定コマンドを、コマンドリストに積む
	commandList->RSSetViewports(1, &viewport);

	// シザー矩形設定
	scissorRect.left = 0; // 切り抜き座標左
	scissorRect.right = scissorRect.left + WindowsApp::GetInstance()->GetWindowSize().width; // 切り抜き座標右
	scissorRect.top = 0; // 切り抜き座標上
	scissorRect.bottom = scissorRect.top + WindowsApp::GetInstance()->GetWindowSize().height; // 切り抜き座標下

	// シザー矩形設定コマンドを、コマンドリストに積む
	commandList->RSSetScissorRects(1, &scissorRect);

}

void DirectX12Core::EndDraw()
{
	//5元に戻す
	backBuffers[bbIndex]->Transition(D3D12_RESOURCE_STATE_PRESENT, commandList.Get());

	ExecuteCommand();
}

void DirectX12Core::ExecuteCommand()
{
	//命令のクローズ
	result = commandList->Close();
	assert(SUCCEEDED(result));
	//コマンドリストの実行
	ID3D12CommandList* commandListts[] = { commandList.Get() };
	commandQueue->ExecuteCommandLists(1, commandListts);

	//フリップ
	result = swapChain->Present(1, 0);
	assert(SUCCEEDED(result));

	//コマンド実行完了を待つ
	commandQueue->Signal(fence.Get(), ++fenceVal);
	if (fence->GetCompletedValue() != fenceVal)
	{
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		fence->SetEventOnCompletion(fenceVal, event);
		if (event != 0)
		{
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}
	}

	//キューをクリア
	result = cmdAllocator->Reset();
	assert(SUCCEEDED(result));
	//コマンドリストを貯める準備
	if (commandList != 0)
	{
		result = commandList->Reset(cmdAllocator.Get(), nullptr);
		assert(SUCCEEDED(result));
	}
	else
	{
		assert(SUCCEEDED(0));
	}
}

void DirectX12Core::Destroy()
{
	delete DirectX12Core_;
}

void DirectX12Core::SetBackScreenColor(float red, float green, float blue, float alpha)
{
	clearColor[0] = red;
	clearColor[1] = green;
	clearColor[2] = blue;
	clearColor[3] = alpha;
}

#pragma region ゲッター

DirectX12Core* DirectX12Core::GetInstance()
{

	if (DirectX12Core_ == nullptr)
	{
		DirectX12Core_ = new DirectX12Core();
	}

	return DirectX12Core_;

}

Microsoft::WRL::ComPtr<ID3D12Device> DirectX12Core::GetDeviceSta()
{
	return GetInstance()->GetDevice();
}

Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> DirectX12Core::GetCommandListSta()
{
	return GetInstance()->GetCommandList();
}

Microsoft::WRL::ComPtr<ID3D12Device> DirectX12Core::GetDevice()
{
	return device;
}

Microsoft::WRL::ComPtr <ID3D12GraphicsCommandList> DirectX12Core::GetCommandList()
{
	return commandList;
}

DescriptorHeap* DirectX12Core::GetSRVDescriptorHeap()
{
	return srvHeap.get();
}

RTVDescriptorHeap* DirectX12Core::GetRTVDescriptorHeap()
{
	return rtvHeap.get();
}

DSVDescriptorHeap* DirectX12Core::GetDSVDescriptorHeap()
{
	return dsvHeap.get();
}
#pragma endregion

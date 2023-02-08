#include "DirectX12Core.h"
#include"WindowsApp.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

DirectX12Core* DirectX12Core::DirectX12Core_ = nullptr;

HRESULT DirectX12Core::CreatFinalRenderTarget()
{
	//�f�X�N���v�^�q�[�v�̐���
	rtvHeap = std::make_unique<RTVDescriptorHeap>();
	rtvHeap->Initialize();

	//�o�b�N�o�b�t�@
	backBuffers.resize(swapChainDesc.BufferCount);

	//�X���b�v�`�F�[���̃o�b�t�@������
	for (size_t i = 0; i < backBuffers.size(); i++)
	{
		backBuffers[i] = std::make_unique<RenderTargetBuffer>(device.Get(), rtvHeap.get());
		
		//����
		backBuffers[i]->Create(swapChain.Get(), i);
	}

	return S_OK;
}

HRESULT DirectX12Core::CreateSwapChain()
{
	swapChainDesc.Width = WindowsApp::GetInstance()->GetWindowSize().width;//����
	swapChainDesc.Height = WindowsApp::GetInstance()->GetWindowSize().height;//�c��
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//�F���̏���
	swapChainDesc.SampleDesc.Count = 1;//�}���`�T���v���Ȃ�
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;//�o�b�N�o�b�t�@�p
	swapChainDesc.BufferCount = 2;//�o�b�t�@��2
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;//�t���b�v��͔j��
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//����
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
	//�Ή����x���̔z��
	D3D_FEATURE_LEVEL levels[] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	//DXGI�t�@�N�g���[
	result = CreateDXGIFactory(IID_PPV_ARGS(dxgiFactory.ReleaseAndGetAddressOf()));
	if (FAILED(result))
	{
		return result;
	}

	//�A�_�v�^�[�񋓗p
	std::vector<Microsoft::WRL::ComPtr<IDXGIAdapter4>> adapters;
	//�����ɓ���̖��O�����A�_�v�^�[�I�u�W�F�N�g������
	Microsoft::WRL::ComPtr<IDXGIAdapter4> tmpAdapter;

	//�p�t�H�[�}���X�������̂�����S�ė�
	for (UINT i = 0; dxgiFactory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(tmpAdapter.ReleaseAndGetAddressOf())) != DXGI_ERROR_NOT_FOUND; i++)
	{
		adapters.push_back(tmpAdapter);
	}

	// �Ó��ȃA�_�v�^��I�ʂ���
	for (size_t i = 0; i < adapters.size(); i++) {
		DXGI_ADAPTER_DESC3 adapterDesc;
		// �A�_�v�^�[�̏����擾����
		adapters[i]->GetDesc3(&adapterDesc);

		// �\�t�g�E�F�A�f�o�C�X�����
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
			// �f�o�C�X���̗p���ă��[�v�𔲂���
			tmpAdapter = adapters[i];
			break;
		}
	}

	//Direct3D�f�o�C�X�̏�����
	D3D_FEATURE_LEVEL featureLevel;

	for (size_t i = 0; i < _countof(levels); i++) {
		// �̗p�����A�_�v�^�[�Ńf�o�C�X�𐶐�
		result = D3D12CreateDevice(tmpAdapter.Get(), levels[i], IID_PPV_ARGS(device.GetAddressOf()));
		if (result == S_OK) {
			// �f�o�C�X�𐶐��ł������_�Ń��[�v�𔲂���
			featureLevel = levels[i];
			break;
		}
	}

	return result;
}

HRESULT DirectX12Core::InitializeCommand()
{
	//�R�}���h�A���P�[�^�𐶐�
	result = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(cmdAllocator.ReleaseAndGetAddressOf()));
	if (FAILED(result))
	{
		return result;
	}

	//�R�}���h���X�g�𐶐�
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

	//�R�}���h�L���[�̐ݒ聕����
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
	//�t�F���X�̐���
	result = device->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.ReleaseAndGetAddressOf()));

	return result;
}

HRESULT DirectX12Core::CreatDepthBuffer()
{
	//�f�X�N�v���^�q�[�v����
	dsvHeap = std::make_unique<DSVDescriptorHeap>();
	dsvHeap->Initialize();

	//�[�x�o�b�t�@����
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

	//DirectX12�֘A������
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

	//�f�X�N�v���^�q�[�v����
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

	//�}������G���[
	D3D12_MESSAGE_ID denyIds[] =
	{
		/*
		*windows11�ł�DXGI�f�o�b�O���C���[��DX12�f�o�b�O���C���[
		*���ݍ�p�o�O�ɂ��G���[���b�Z�[�W
		*/
		D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE

	};
		//�}������\�����x��
	D3D12_MESSAGE_SEVERITY severities[] = { D3D12_MESSAGE_SEVERITY_INFO };
	D3D12_INFO_QUEUE_FILTER filter{};
	filter.DenyList.NumIDs = _countof(denyIds);
	filter.DenyList.pIDList = denyIds;
	filter.DenyList.NumSeverities = _countof(severities);
	filter.DenyList.pSeverityList = severities;
	//�w�肵���G���[�̕\����}������
	infoQueue->PushStorageFilter(&filter);
}

DirectX12Core::~DirectX12Core()
{
}

void DirectX12Core::BeginDraw()
{
	//1�o�b�N�o�b�t�@�ԍ����擾
	bbIndex = swapChain->GetCurrentBackBufferIndex();
	//�������݉\�ɕύX

	backBuffers[bbIndex]->Transition(D3D12_RESOURCE_STATE_RENDER_TARGET, commandList.Get());

	commandList->OMSetRenderTargets(1, &backBuffers[bbIndex]->GetHandle(), false, &depthBuff->GetHandle());

	//3��ʃN���A
	commandList->ClearRenderTargetView(backBuffers[bbIndex]->GetHandle(), clearColor, 0, nullptr);
	commandList->ClearDepthStencilView(depthBuff->GetHandle(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
	//�r���[�|�[�g�ݒ�
	viewport.Width = (FLOAT)WindowsApp::GetInstance()->GetWindowSize().width;
	viewport.Height = (FLOAT)WindowsApp::GetInstance()->GetWindowSize().height;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	// �r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	commandList->RSSetViewports(1, &viewport);

	// �V�U�[��`�ݒ�
	scissorRect.left = 0; // �؂蔲�����W��
	scissorRect.right = scissorRect.left + WindowsApp::GetInstance()->GetWindowSize().width; // �؂蔲�����W�E
	scissorRect.top = 0; // �؂蔲�����W��
	scissorRect.bottom = scissorRect.top + WindowsApp::GetInstance()->GetWindowSize().height; // �؂蔲�����W��

	// �V�U�[��`�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
	commandList->RSSetScissorRects(1, &scissorRect);

}

void DirectX12Core::EndDraw()
{
	//5���ɖ߂�
	backBuffers[bbIndex]->Transition(D3D12_RESOURCE_STATE_PRESENT, commandList.Get());

	ExecuteCommand();
}

void DirectX12Core::ExecuteCommand()
{
	//���߂̃N���[�Y
	result = commandList->Close();
	assert(SUCCEEDED(result));
	//�R�}���h���X�g�̎��s
	ID3D12CommandList* commandListts[] = { commandList.Get() };
	commandQueue->ExecuteCommandLists(1, commandListts);

	//�t���b�v
	result = swapChain->Present(1, 0);
	assert(SUCCEEDED(result));

	//�R�}���h���s������҂�
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

	//�L���[���N���A
	result = cmdAllocator->Reset();
	assert(SUCCEEDED(result));
	//�R�}���h���X�g�𒙂߂鏀��
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

#pragma region �Q�b�^�[

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

#include "DirectX12Core.h"
#include"WindowsApp.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

DirectX12Core* DirectX12Core::DirectX12Core_ = nullptr;

HRESULT DirectX12Core::CreatFinalRenderTarget()
{
	//�f�X�N���v�^�q�[�v�̐ݒ�
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//�����_�[�^�[�Q�b�g�r���[
	rtvHeapDesc.NumDescriptors = swapChainDesc.BufferCount;//�\����2��
	//�f�X�N���v�^�q�[�v�̐���
	device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(rtvHeap.ReleaseAndGetAddressOf()));

	//�o�b�N�o�b�t�@
	backBuffers.resize(swapChainDesc.BufferCount);

	//�X���b�v�`�F�[���̃o�b�t�@������
	for (size_t i = 0; i < backBuffers.size(); i++)
	{
		//�o�b�t�@���擾
		swapChain->GetBuffer((UINT)i, IID_PPV_ARGS(backBuffers[i].ReleaseAndGetAddressOf()));
		//�q�[�v�̃n���h���̏���
		D3D12_CPU_DESCRIPTOR_HANDLE frtHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
		//�����\���ŃA�h���X�������
		frtHandle.ptr += i * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
		//�^�[�Q�b�g�r���[�̐ݒ�
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		//�v�Z���ʂ�SRGB�ɕϊ�
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		//�^�[�Q�b�g�r���[�̐���
		device->CreateRenderTargetView(backBuffers[i].Get(), &rtvDesc, frtHandle);
	}

	return S_OK;
}

HRESULT DirectX12Core::CreateSwapChain()
{
	swapChainDesc.Width = static_cast<UINT>(WindowsApp::GetInstance()->GetWindowSize().width);//����
	swapChainDesc.Height = static_cast<UINT>(WindowsApp::GetInstance()->GetWindowSize().height);//�c��
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
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC depthResourceDesc{};
	depthResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthResourceDesc.Width = static_cast<UINT64>(WindowsApp::GetInstance()->GetWindowSize().width);//�����_�[�^�[�Q�b�g�ɍ��킹��
	depthResourceDesc.Height = static_cast<UINT64>(WindowsApp::GetInstance()->GetWindowSize().height);//�����_�[�^�[�Q�b�g�ɍ��킹��
	depthResourceDesc.DepthOrArraySize = 1;
	depthResourceDesc.Format = DXGI_FORMAT_D32_FLOAT;//�[�x�l�t�H�[�}�b�g
	depthResourceDesc.SampleDesc.Count = 1;
	depthResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;//�f�v�X�X�e���V��

	//�[�x�l�p�q�[�v�v���p�e�B
	D3D12_HEAP_PROPERTIES depthHeapProp{};
	depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	//�[�x�l�̃N���A�ݒ�
	D3D12_CLEAR_VALUE depthClearValue{};
	depthClearValue.DepthStencil.Depth = 1.0f;//�[�x�l1.0f(�ő�l)�ŃN���A
	depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;//�[�x�l�t�H�[�}�b�g

	//���\�[�X����
	result = device->CreateCommittedResource(
		&depthHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&depthResourceDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,//�[�x�l�������݂Ɏg�p
		&depthClearValue,
		IID_PPV_ARGS(depthBuff.ReleaseAndGetAddressOf()));
	if (FAILED(result))
	{
		return result;
	}

	//�[�x�r���[�p�f�X�N�v���^�q�[�v����
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	result = device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(dsvHeap.ReleaseAndGetAddressOf()));
	if (FAILED(result))
	{
		return result;
	}
	//�[�x�r���[�쐬
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	device->CreateDepthStencilView(
		depthBuff.Get(),
		&dsvDesc,
		dsvHeap->GetCPUDescriptorHandleForHeapStart());
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

	descriptorHeap = std::make_unique<DescriptorHeap>();
	descriptorHeap->Initialize();
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

void DirectX12Core::BeginDraw()
{
	//1�o�b�N�o�b�t�@�ԍ����擾
	UINT bbIndex = swapChain->GetCurrentBackBufferIndex();
	//�������݉\�ɕύX

	barrierDesc.Transition.pResource = backBuffers[bbIndex].Get();//�o�b�N�o�b�t�@���w��
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;//�\����Ԃ���
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;//�`���Ԃ�
	commandList->ResourceBarrier(1, &barrierDesc);

	//2�`���ύX
	rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += (static_cast<unsigned long long>(bbIndex)) * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);

	//�[�x�X�e���V���r���[�p�f�X�N�v���^�q�[�v�̃n���h��������
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dsvHeap->GetCPUDescriptorHandleForHeapStart();
	commandList->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

	//3��ʃN���A
	commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	commandList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
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
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;//�`���Ԃ���
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;//�\����Ԃ�
	commandList->ResourceBarrier(1, &barrierDesc);

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

DescriptorHeap* DirectX12Core::GetDescriptorHeap()
{
	return descriptorHeap.get();
}

#pragma endregion

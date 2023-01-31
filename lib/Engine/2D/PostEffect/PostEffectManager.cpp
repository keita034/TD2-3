#include "PostEffectManager.h"
#include "WindowsApp.h"
#include "DefaultMaterial.h"

const float PostEffectManager::clearColor[4] = { 1.0f,1.0f,1.0f,0.0f };

PostEffectManager* PostEffectManager::GetInstance()
{
	static PostEffectManager instance;
	return &instance;
}

void PostEffectManager::Initialize()
{
	device = DirectX12Core::GetDeviceSta();
	cmdList = DirectX12Core::GetCommandListSta();

	width = static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().width);
	height = static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().height);

	CreateWindowTex();

	CreateRenderTarget();

	CreateDepthStencilView();

	//頂点バッファの生成
	vertexBuffer = std::make_unique<VertexBuffer>();
	vertexBuffer->Create(4, sizeof(PosUvColor));

	//インデックスバッファの生成
	indexBuffer = std::make_unique<IndexBuffer>();
	indexBuffer->Create(6);

	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		static_cast<UINT64>(width),
		static_cast<UINT>(height),
		1, 0, 1, 0,
		D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET);

	postwinTex[0].buff.CreateUAV(&texresDesc);
	postwinTex[1].buff.CreateUAV(&texresDesc);

	factory = PostEffectFactory::GetInstance();
}

void PostEffectManager::PostInitialize()
{
}

void PostEffectManager::PostDraw()
{
	for (auto itr = postEffects.begin(); itr != postEffects.end(); itr++)
	{
		if (itr == postEffects.begin())
		{
			//UNORDERED_ACCESSじゃなかったら変更
			if (postwinTex[0].states != D3D12_RESOURCE_STATE_UNORDERED_ACCESS)
			{
				//変更
				DirectX12Core::ResourceTransition(postwinTex[0].buff.GetResource(), postwinTex[0].states, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
				postwinTex[0].states = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
			}

			itr._Ptr->_Myval->PostUpdate(windowTex.gpuHandle, postwinTex[0].buff.GetAddress());
			gpuHandle = postwinTex[0].buff.GetAddress();

			isFlip = true;
		}
		else if (isFlip)
		{
			//PIXEL_SHADER_RESOURCEじゃなかったら変更
			if (postwinTex[0].states != D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE)
			{
				//変更
				DirectX12Core::ResourceTransition(postwinTex[0].buff.GetResource(), postwinTex[0].states, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
				postwinTex[0].states = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
			}

			//UNORDERED_ACCESSじゃなかったら変更
			if (postwinTex[1].states != D3D12_RESOURCE_STATE_UNORDERED_ACCESS)
			{
				//変更
				DirectX12Core::ResourceTransition(postwinTex[1].buff.GetResource(), postwinTex[1].states, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
				postwinTex[1].states = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
			}

			itr._Ptr->_Myval->PostUpdate(postwinTex[0].buff.GetAddress(), postwinTex[1].buff.GetAddress());
			gpuHandle = postwinTex[1].buff.GetAddress();
			isFlip = false;
		}
		else
		{

			//UNORDERED_ACCESSじゃなかったら変更
			if (postwinTex[0].states != D3D12_RESOURCE_STATE_UNORDERED_ACCESS)
			{
				//変更
				DirectX12Core::ResourceTransition(postwinTex[0].buff.GetResource(), postwinTex[0].states, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
				postwinTex[0].states = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
			}

			//PIXEL_SHADER_RESOURCEじゃなかったら変更
			if (postwinTex[1].states != D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE)
			{
				//変更
				DirectX12Core::ResourceTransition(postwinTex[1].buff.GetResource(), postwinTex[1].states, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
				postwinTex[1].states = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
			}

			itr._Ptr->_Myval->PostUpdate(postwinTex[1].buff.GetAddress(), postwinTex[0].buff.GetAddress());
			gpuHandle = postwinTex[0].buff.GetAddress();
			isFlip = true;
		}
	}

	//PIXEL_SHADER_RESOURCEじゃなかったら変更
	if (gpuHandle.ptr == postwinTex[0].buff.GetAddress().ptr && postwinTex[0].states != D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE)
	{
		//変更
		DirectX12Core::ResourceTransition(postwinTex[0].buff.GetResource(), postwinTex[0].states, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
		postwinTex[0].states = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
		gpuHandle = postwinTex[0].buff.GetAddress();
	}
	//PIXEL_SHADER_RESOURCEじゃなかったら変更
	else if (gpuHandle.ptr == postwinTex[1].buff.GetAddress().ptr && postwinTex[1].states != D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE)
	{
		//変更
		DirectX12Core::ResourceTransition(postwinTex[1].buff.GetResource(), postwinTex[1].states, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
		postwinTex[1].states = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
		gpuHandle = postwinTex[1].buff.GetAddress();
	}

	//描画
	Draw();
}

void PostEffectManager::PreDrawScen()
{
	DirectX12Core::ResourceTransition(windowTex.texBuff.Get(), D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET);

	D3D12_CPU_DESCRIPTOR_HANDLE rtvH =
		descHeapRTV->GetCPUDescriptorHandleForHeapStart();

	D3D12_CPU_DESCRIPTOR_HANDLE dsvH =
		descHeapDSV->GetCPUDescriptorHandleForHeapStart();

	cmdList->OMSetRenderTargets(1, &rtvH, false, &dsvH);

	CD3DX12_VIEWPORT viewPort = CD3DX12_VIEWPORT(0.0f, 0.0f, width, height);
	cmdList->RSSetViewports(1, &viewPort);

	CD3DX12_RECT rect = CD3DX12_RECT(0, 0, static_cast<LONG>(width), static_cast<LONG>(height));
	cmdList->RSSetScissorRects(1, &rect);

	cmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);

	cmdList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void PostEffectManager::PostDrawScen()
{
	DirectX12Core::ResourceTransition(windowTex.texBuff.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
}

void PostEffectManager::AddPostEffect(const std::string& postEffectName)
{
	postEffects.push_back(factory->CreatePostEffect(postEffectName));

	isAalid = true;
}

void PostEffectManager::Finalize()
{
	postEffects.clear();
}

bool PostEffectManager::IsAalid()
{
	if (postEffects.size() != 0 )
	{
		isAalid = true;
	}
	else
	{
		isAalid = false;
	}

	return isAalid;
}

void PostEffectManager::SubPostEffect(const std::string& postEffectName)
{
	postEffects.remove_if([&postEffectName](BasePostEffect* postEffect)
		{
			return postEffect->GetType() == postEffectName;
		});
}

void PostEffectManager::CreateWindowTex()
{
	windowTex.width = static_cast<size_t>(WindowsApp::GetInstance()->GetWindowSize().width);
	windowTex.height = static_cast<size_t>(WindowsApp::GetInstance()->GetWindowSize().height);

	windowTex.srvHeap = DirectX12Core::GetInstance()->GetDescriptorHeap()->GetHeap();

	{//テクスチャ
		CD3DX12_CLEAR_VALUE cleaVal = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, clearColor);
		CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
			DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
			static_cast<UINT64>(width),
			static_cast<UINT>(height),
			1, 0, 1, 0,
			D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET);
		CD3DX12_HEAP_PROPERTIES heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);
		result = device->CreateCommittedResource(
			&heapProp,
			D3D12_HEAP_FLAG_NONE,
			&texresDesc,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			&cleaVal,
			IID_PPV_ARGS(windowTex.texBuff.GetAddressOf()));

		assert(SUCCEEDED(result));

		{
			const UINT pixelCount = static_cast<UINT>(width * height);

			const UINT rowPith = sizeof(UINT) * static_cast<UINT>(width);

			const UINT depthch = rowPith * static_cast<UINT>(height);

			UINT* img = new UINT[pixelCount];
			for (size_t i = 0; i < pixelCount; i++)
			{
				img[i] = 0xff0000ff;
			}
			result = windowTex.texBuff->WriteToSubresource(0, nullptr, img, rowPith, depthch);
			assert(SUCCEEDED(result));
			delete[] img;

		}
	}

	{//SRV作成

		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;
		windowTex.gpuHandle.ptr = DirectX12Core::GetInstance()->GetDescriptorHeap()->CreateSRV(srvDesc, windowTex.texBuff.Get());
	}
}

void PostEffectManager::CreateRenderTarget()
{
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeapDesc{};
	rtvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescHeapDesc.NumDescriptors = 1;

	result = device->CreateDescriptorHeap(&rtvDescHeapDesc, IID_PPV_ARGS(descHeapRTV.GetAddressOf()));
	assert(SUCCEEDED(result));

	device->CreateRenderTargetView(windowTex.texBuff.Get(), nullptr, descHeapRTV->GetCPUDescriptorHandleForHeapStart());
}

void PostEffectManager::CreateDepthStencilView()
{
	{//深度バッファ作成
		CD3DX12_RESOURCE_DESC depthResDesc =
			CD3DX12_RESOURCE_DESC::Tex2D(
				DXGI_FORMAT_D32_FLOAT,
				static_cast<UINT64>(width),
				static_cast<UINT>(height),
				1, 0, 1, 0,
				D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);

		CD3DX12_HEAP_PROPERTIES heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
		CD3DX12_CLEAR_VALUE clerVal = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0);
		result = device->CreateCommittedResource(
			&heapProp,
			D3D12_HEAP_FLAG_NONE,
			&depthResDesc,
			D3D12_RESOURCE_STATE_DEPTH_WRITE,
			&clerVal,
			IID_PPV_ARGS(depthBuff.GetAddressOf()));
		assert(SUCCEEDED(result));
	}

	{//DSV制作
		D3D12_DESCRIPTOR_HEAP_DESC DescHeapDesc{};
		DescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		DescHeapDesc.NumDescriptors = 1;
		result = device->CreateDescriptorHeap(&DescHeapDesc, IID_PPV_ARGS(descHeapDSV.GetAddressOf()));
		assert(SUCCEEDED(result));

		D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
		dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
		dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		device->CreateDepthStencilView(depthBuff.Get(),
			&dsvDesc,
			descHeapDSV->GetCPUDescriptorHandleForHeapStart());
	}
}

PostEffectManager::~PostEffectManager()
{
}

void PostEffectManager::Draw()
{
	// 頂点データ
	PosUvColor vertices[] =
	{//		x		y		z		u	v
		{{-1.0f,1.0f,0.0f},{0.0f,0.0f},{windowTex.color.x,windowTex.color.y,windowTex.color.z,windowTex.color.w}},//左上インデックス0
		{{-1.0f,-1.0f,0.0f},{0.0f,1.0f},{windowTex.color.x,windowTex.color.y,windowTex.color.z,windowTex.color.w}},//左下インデックス1
		{{1.0f,1.0f,0.0f},{1.0f,0.0f},{windowTex.color.x,windowTex.color.y,windowTex.color.z,windowTex.color.w}},//右上インデックス2
		{{1.0f,-1.0f,0.0f},{1.0f,1.0f},{windowTex.color.x,windowTex.color.y,windowTex.color.z,windowTex.color.w}},//右下インデックス3
	};

	// インデックスデータ
	uint32_t indices[] =
	{
		1, 0, 3, // 三角形1つ目
		2, 3, 0, // 三角形2つ目
	};

	//頂点バッファへのデータ転送
	vertexBuffer->Update(vertices);

	//インデックスバッファへのデータ転送
	indexBuffer->Update(indices);

	postEffectMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_POST_EFFECT_MATERIAL.get();

	D3D12_VERTEX_BUFFER_VIEW vbView = vertexBuffer->GetView();
	D3D12_INDEX_BUFFER_VIEW ibView = indexBuffer->GetView();

	// パイプラインステートとルートシグネチャの設定コマンド
	cmdList->SetPipelineState(postEffectMaterial->pipelineState->GetPipelineState());
	cmdList->SetGraphicsRootSignature(postEffectMaterial->rootSignature->GetRootSignature());

	// プリミティブ形状の設定コマンド
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト

	// 頂点バッファビューの設定コマンド
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	//インデックスバッファビューの設定コマンド
	cmdList->IASetIndexBuffer(&ibView);

	// SRVヒープの設定コマンド
	cmdList->SetDescriptorHeaps(1, windowTex.srvHeap.GetAddressOf());

	//// SRVヒープの先頭にあるSRVをルートパラメータ1番に設定
	cmdList->SetGraphicsRootDescriptorTable(0, gpuHandle);

	// 描画コマンド
	cmdList->DrawIndexedInstanced(6, 1, 0, 0, 0);
}

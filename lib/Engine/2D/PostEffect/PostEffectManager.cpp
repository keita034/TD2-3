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
	device = DirectX12Core::GetDeviceSta().Get();
	cmdList = DirectX12Core::GetCommandListSta().Get();

	srvHeap = DirectX12Core::GetInstance()->GetSRVDescriptorHeap();
	dsvHeap = DirectX12Core::GetInstance()->GetDSVDescriptorHeap();
	rtvHeap = DirectX12Core::GetInstance()->GetRTVDescriptorHeap();

	width = static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().width);
	height = static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().height);

	mainRenderTarget = std::make_unique<RenderTarget>(device, dsvHeap, rtvHeap, srvHeap, cmdList);

	mainRenderTarget->Initialize(WindowsApp::GetInstance()->GetWindowSize().width, WindowsApp::GetInstance()->GetWindowSize().height, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

	//���_�o�b�t�@�̐���
	vertexBuffer = std::make_unique<VertexBuffer>();
	vertexBuffer->Create(4, sizeof(PosUvColor));

	//�C���f�b�N�X�o�b�t�@�̐���
	indexBuffer = std::make_unique<IndexBuffer>();
	indexBuffer->Create(6);

	factory = PostEffectFactory::GetInstance();
}

void PostEffectManager::PostInitialize()
{
	for (auto itr = postEffects.begin(); itr != postEffects.end(); itr++)
	{
		itr._Ptr->_Myval->Initialize();
	}
}

void PostEffectManager::Update()
{
	for (auto itr = postEffects.begin(); itr != postEffects.end(); itr++)
	{
		itr._Ptr->_Myval->PostUpdate(mainRenderTarget.get());
	}

}

void PostEffectManager::PreDrawScen()
{
	mainRenderTarget->Transition(D3D12_RESOURCE_STATE_RENDER_TARGET);

	mainRenderTarget->SetRenderTarget();

	CD3DX12_VIEWPORT viewPort = CD3DX12_VIEWPORT(0.0f, 0.0f, width, height);
	cmdList->RSSetViewports(1, &viewPort);

	CD3DX12_RECT rect = CD3DX12_RECT(0, 0, static_cast<LONG>(width), static_cast<LONG>(height));
	cmdList->RSSetScissorRects(1, &rect);

	mainRenderTarget->ClearRenderTarget();
}

void PostEffectManager::PostDrawScen()
{
	mainRenderTarget->Transition(D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
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
	if (postEffects.size() != 0)
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





}

void PostEffectManager::CreateRenderTarget()
{

}

void PostEffectManager::CreateDepthStencilView()
{

}

PostEffectManager::~PostEffectManager()
{
}

void PostEffectManager::Draw()
{
	// ���_�f�[�^
	PosUvColor vertices[] =
	{//		x		y		z		u	v
		{{-1.0f,1.0f,0.0f},{0.0f,0.0f},{1.0f,1.0f,1.0f,1.0f}},//����C���f�b�N�X0
		{{-1.0f,-1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f,1.0f,1.0f}},//�����C���f�b�N�X1
		{{1.0f,1.0f,0.0f},{1.0f,0.0f},{1.0f,1.0f,1.0f,1.0f}},//�E��C���f�b�N�X2
		{{1.0f,-1.0f,0.0f},{1.0f,1.0f},{1.0f,1.0f,1.0f,1.0f}},//�E���C���f�b�N�X3
	};

	// �C���f�b�N�X�f�[�^
	uint32_t indices[] =
	{
		1, 0, 3, // �O�p�`1��
		2, 3, 0, // �O�p�`2��
	};

	//���_�o�b�t�@�ւ̃f�[�^�]��
	vertexBuffer->Update(vertices);

	//�C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	indexBuffer->Update(indices);

	postEffectMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_POST_EFFECT_MATERIAL.get();

	D3D12_VERTEX_BUFFER_VIEW vbView = vertexBuffer->GetView();
	D3D12_INDEX_BUFFER_VIEW ibView = indexBuffer->GetView();

	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	cmdList->SetPipelineState(postEffectMaterial->pipelineState->GetPipelineState());
	cmdList->SetGraphicsRootSignature(postEffectMaterial->rootSignature->GetRootSignature());

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g

	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->IASetIndexBuffer(&ibView);

	// SRV�q�[�v�̐ݒ�R�}���h
	ID3D12DescriptorHeap* descriptorHeaps[] =
	{
		srvHeap->GetHeap(),
	};

	cmdList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

	//// SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^1�Ԃɐݒ�
	cmdList->SetGraphicsRootDescriptorTable(0, mainRenderTarget->GetGpuHandle());

	// �`��R�}���h
	cmdList->DrawIndexedInstanced(6, 1, 0, 0, 0);
}

#include "LutPostEffect.h"
#include "DirectX12Core.h"
#include "TextureManager.h"
#include "WindowsApp.h"
#include"DefaultMaterial.h"

LutPostEffect* LutPostEffect::GetInstance()
{
	static LutPostEffect instance;
	return &instance;
}

void LutPostEffect::Initialize()
{
	if (needsInit)
	{

		cmdList = DirectX12Core::GetInstance()->GetCommandList().Get();

		width = static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().width);
		height = static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().height);

		sprite = std::make_unique<PostEffectSprite>();
		sprite->Initialize(DirectX12Core::GetCommandListSta().Get(), DirectX12Core::GetInstance()->GetSRVDescriptorHeap());

		material = std::make_unique<Material>();

		//���_�V�F�[�_�̓ǂݍ���
		material->vertexShader = std::make_unique<Shader>();
		material->vertexShader->Create("Resources/Shaders/2D/PostEffect/LutShaderVS.hlsl");

		//�s�N�Z���V�F�[�_�̓ǂݍ���
		material->pixelShader = std::make_unique<Shader>();
		material->pixelShader->Create("Resources/Shaders/2D/PostEffect/LutShaderPS.hlsl", "main", "ps_5_0");

		//���_���C�A�E�g�ݒ�
		material->inputLayouts =
		{
			// xyz���W
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
			// uv���W
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
			//�J���[
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		};

		material->depthFlag = false;

		material->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̃A���t�@�l
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;// 1.0f-�\�[�X�̃A���t�@�l

		//���[�g�V�O�l�`���ݒ�
		material->rootSignature = std::make_unique<RootSignature>();
		material->rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0
		material->rootSignature->Add(RootSignature::RangeType::SRV, 1);//t1
		material->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
		material->rootSignature->AddStaticSampler(0);//s0
		material->rootSignature->AddStaticSampler(1);//s1
		material->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

		//����
		material->Initialize();

		renderTarget = std::make_unique<RenderTarget>(
			DirectX12Core::GetDeviceSta().Get(),
			DirectX12Core::GetInstance()->GetDSVDescriptorHeap(),
			DirectX12Core::GetInstance()->GetRTVDescriptorHeap(),
			DirectX12Core::GetInstance()->GetSRVDescriptorHeap(), 
			cmdList);

		renderTarget->Initialize(WindowsApp::GetInstance()->GetWindowSize().width, WindowsApp::GetInstance()->GetWindowSize().height, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

		needsInit = false;

		uint32_t handle = TextureManager::Load("Resources/Lut/amoebae-66-multilut1.png");

		lutTexture = TextureManager::GetTextureData(handle);

		lutSizeBuff = std::make_unique<ConstantBuffer>();
		lutSizeBuff->Create(sizeof(lutSize));

		size = { 1.0f / static_cast<float>(lutTexture->width),1.0f / static_cast<float>(lutTexture->height),1.13900006f,0.714969635f ,0.0489999987f,static_cast<float>(lutTexture->width / lutTexture->height) - 3.0f };

		lutSizeBuff->Update(&size);

		type = "LUT";
	}
}

void LutPostEffect::PostUpdate(RenderTarget* mainRenderTarget)
{
	Draw(mainRenderTarget);

	MainRenderTargetDraw(mainRenderTarget);
}

void LutPostEffect::SetLutTexture(uint32_t handle)
{
	lutTexture = TextureManager::GetTextureData(handle);

	size = { 1.0f / static_cast<float>(lutTexture->width),1.0f / static_cast<float>(lutTexture->height),1.139f,1.729f ,0.049f,static_cast<float>(lutTexture->width / lutTexture->height) - 3.0f };

	lutSizeBuff->Update(&size);
}

const std::string& LutPostEffect::GetType() 
{
	return type;
}

void LutPostEffect::Draw(RenderTarget* mainRenderTarget)
{
	renderTarget->Transition(D3D12_RESOURCE_STATE_RENDER_TARGET);

	renderTarget->SetRenderTarget();

	CD3DX12_VIEWPORT viewPort = CD3DX12_VIEWPORT(0.0f, 0.0f, width, height);
	cmdList->RSSetViewports(1, &viewPort);

	CD3DX12_RECT rect = CD3DX12_RECT(0, 0, static_cast<LONG>(width), static_cast<LONG>(height));
	cmdList->RSSetScissorRects(1, &rect);

	//renderTarget->ClearRenderTarget();

	sprite->Draw(material.get(), mainRenderTarget->GetGpuHandle());

	cmdList->SetGraphicsRootDescriptorTable(1, lutTexture->gpuHandle);

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	cmdList->SetGraphicsRootConstantBufferView(2, lutSizeBuff->GetAddress());

	// �`��R�}���h
	cmdList->DrawIndexedInstanced(6, 1, 0, 0, 0);

	renderTarget->Transition(D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
}

void LutPostEffect::MainRenderTargetDraw(RenderTarget* mainRenderTarget)
{
	mainRenderTarget->Transition(D3D12_RESOURCE_STATE_RENDER_TARGET);

	mainRenderTarget->SetRenderTarget();

	CD3DX12_VIEWPORT viewPort = CD3DX12_VIEWPORT(0.0f, 0.0f, width, height);
	cmdList->RSSetViewports(1, &viewPort);

	CD3DX12_RECT rect = CD3DX12_RECT(0, 0, static_cast<LONG>(width), static_cast<LONG>(height));
	cmdList->RSSetScissorRects(1, &rect);

	

	sprite->Draw(DefaultMaterial::GetDefaultMaterial()->DEFAULT_POST_EFFECT_MATERIAL.get(), renderTarget->GetGpuHandle());

	// �`��R�}���h
	cmdList->DrawIndexedInstanced(6, 1, 0, 0, 0);

	mainRenderTarget->Transition(D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
}

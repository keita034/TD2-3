#include "GaussianYBlurPostEffect.h"
#include "DirectX12Core.h"
#include "TextureManager.h"
#include "WindowsApp.h"
#include"DefaultMaterial.h"

void GaussianYBlurPostEffect::Initialize()
{
	if (needsInit)
	{
		cmdList = DirectX12Core::GetInstance()->GetCommandList().Get();

		width = static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().width / 2);
		height = static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().height/2);

		sprite = std::make_unique<PostEffectSprite>();
		sprite->Initialize(DirectX12Core::GetCommandListSta().Get(), DirectX12Core::GetInstance()->GetSRVDescriptorHeap());

		material = std::make_unique<Material>();

		//���_�V�F�[�_�̓ǂݍ���
		material->vertexShader = std::make_unique<Shader>();
		material->vertexShader->Create("Resources/Shaders/2D/PostEffect/GaussianYBlurVS.hlsl");

		//�s�N�Z���V�F�[�_�̓ǂݍ���
		material->pixelShader = std::make_unique<Shader>();
		material->pixelShader->Create("Resources/Shaders/2D/PostEffect/GaussianBlurPS.hlsl", "main", "ps_5_0");

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
		material->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
		material->rootSignature->AddStaticSampler(0);//s0
		material->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

		//����
		material->Initialize();

		renderTarget = std::make_unique<RenderTarget>(
			DirectX12Core::GetDeviceSta().Get(),
			DirectX12Core::GetInstance()->GetDSVDescriptorHeap(),
			DirectX12Core::GetInstance()->GetRTVDescriptorHeap(),
			DirectX12Core::GetInstance()->GetSRVDescriptorHeap(),
			cmdList);

		renderTarget->Initialize(WindowsApp::GetInstance()->GetWindowSize().width / 2, WindowsApp::GetInstance()->GetWindowSize().height/2, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

		weightBuff = std::make_unique<ConstantBuffer>();
		weightBuff->Create(sizeof(weight));
		weightBuff->Update(weight.data());

		needsInit = false;
	}
}

void GaussianYBlurPostEffect::PostUpdate(RenderTarget* mainRenderTarget)
{
	Draw(mainRenderTarget);

	MainRenderTargetDraw(mainRenderTarget);
}

const std::string& GaussianYBlurPostEffect::GetType()
{
	return "�X�e�[�g�����g�������ɑ}�����܂�";
}

void GaussianYBlurPostEffect::SetWeight(std::array<float, 8>& weightPtr)
{
	weight = weightPtr;

	weightBuff->Update(weight.data());
}

void GaussianYBlurPostEffect::Draw(RenderTarget* mainRenderTarget)
{
	renderTarget->Transition(D3D12_RESOURCE_STATE_RENDER_TARGET);

	renderTarget->SetRenderTarget();

	CD3DX12_VIEWPORT viewPort = CD3DX12_VIEWPORT(0.0f, 0.0f, width, height);
	cmdList->RSSetViewports(1, &viewPort);

	CD3DX12_RECT rect = CD3DX12_RECT(0, 0, static_cast<LONG>(width), static_cast<LONG>(height));
	cmdList->RSSetScissorRects(1, &rect);

	renderTarget->ClearRenderTarget();
	sprite->SetSize({ 1.0f,1.0f });

	sprite->Draw(material.get(), mainRenderTarget->GetGpuHandle());

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	cmdList->SetGraphicsRootConstantBufferView(1, weightBuff->GetAddress());

	// �`��R�}���h
	cmdList->DrawIndexedInstanced(6, 1, 0, 0, 0);

	renderTarget->Transition(D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
}

void GaussianYBlurPostEffect::MainRenderTargetDraw(RenderTarget* mainRenderTarget)
{
	mainRenderTarget->Transition(D3D12_RESOURCE_STATE_RENDER_TARGET);

	mainRenderTarget->SetRenderTarget();

	CD3DX12_VIEWPORT viewPort = CD3DX12_VIEWPORT(0.0f, 0.0f, width*2.0f, height * 2.0f);
	cmdList->RSSetViewports(1, &viewPort);

	CD3DX12_RECT rect = CD3DX12_RECT(0, 0, static_cast<LONG>(width * 2.0f), static_cast<LONG>(height * 2.00f));
	cmdList->RSSetScissorRects(1, &rect);
	sprite->SetSize({1.01f,1.01f });
	sprite->Draw(DefaultMaterial::GetDefaultMaterial()->DEFAULT_POST_EFFECT_MATERIAL.get(), renderTarget->GetGpuHandle());

	// �`��R�}���h
	cmdList->DrawIndexedInstanced(6, 1, 0, 0, 0);

	mainRenderTarget->Transition(D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
}

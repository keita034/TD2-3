#include "VignettePostEffect.h"
#include"WindowsApp.h"
#include"DirectX12Core.h"

VignettePostEffect* VignettePostEffect::GetInstance()
{
	static VignettePostEffect instance;
	return &instance;
}

void VignettePostEffect::Initialize()
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
		material->vertexShader->Create("Resources/Shaders/2D/PostEffect/VignetteShaderVS.hlsl");

		//�s�N�Z���V�F�[�_�̓ǂݍ���
		material->pixelShader = std::make_unique<Shader>();
		material->pixelShader->Create("Resources/Shaders/2D/PostEffect/VignetteShaderPS.hlsl", "main", "ps_5_0");

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

		renderTarget->Initialize(WindowsApp::GetInstance()->GetWindowSize().width, WindowsApp::GetInstance()->GetWindowSize().height, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

		needsInit = false;

		vignetteDataBuff = std::make_unique<ConstantBuffer>();
		vignetteDataBuff->Create(sizeof(VignetteData));

		data =
		{
			{1.0f,1.0f,1.0f},
			0,
			{0.5f,0.5f},
			0.8f,
			0,
			{static_cast<float>(WindowsApp::GetWindowsSize().width),static_cast<float>(WindowsApp::GetWindowsSize().height)},
			{1.0f, 1.0f},
		};

		vignetteDataBuff->Update(&data);

		cmdList = DirectX12Core::GetInstance()->GetCommandList().Get();

		type = "VIGNETTE";
	}
}

void VignettePostEffect::PostUpdate(RenderTarget* mainRenderTarget)
{
	Draw(mainRenderTarget);

	MainRenderTargetDraw(mainRenderTarget);
}

void VignettePostEffect::SetVignetteData(const AliceMathF::Vector3& color, const AliceMathF::Vector2& center, float power, const AliceMathF::Vector2& size)
{
	VignettePostEffect::GetInstance()->SetData(color, center, power, size);
}

void VignettePostEffect::SetColor(const AliceMathF::Vector3& color)
{
	VignettePostEffect::GetInstance()->SetCol(color);
}

void VignettePostEffect::SetCenter(const AliceMathF::Vector2& center)
{
	VignettePostEffect::GetInstance()->SetCent(center);
}

void VignettePostEffect::SetPower(float power)
{
	VignettePostEffect::GetInstance()->SetPow(power);
}

void VignettePostEffect::SetSize(const AliceMathF::Vector2& size)
{
	VignettePostEffect::GetInstance()->SetSi(size);
}

const std::string& VignettePostEffect::GetType()
{
	return type;
}

void VignettePostEffect::Draw(RenderTarget* mainRenderTarget)
{
	renderTarget->Transition(D3D12_RESOURCE_STATE_RENDER_TARGET);

	renderTarget->SetRenderTarget();

	CD3DX12_VIEWPORT viewPort = CD3DX12_VIEWPORT(0.0f, 0.0f, width, height);
	cmdList->RSSetViewports(1, &viewPort);

	CD3DX12_RECT rect = CD3DX12_RECT(0, 0, static_cast<LONG>(width), static_cast<LONG>(height));
	cmdList->RSSetScissorRects(1, &rect);

	//renderTarget->ClearRenderTarget();
	sprite->SetSize({ width, height });

	sprite->Draw(material.get(), mainRenderTarget->GetGpuHandle());

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	cmdList->SetGraphicsRootConstantBufferView(1, vignetteDataBuff->GetAddress());

	// �`��R�}���h
	cmdList->DrawIndexedInstanced(6, 1, 0, 0, 0);

	renderTarget->Transition(D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
}

void VignettePostEffect::MainRenderTargetDraw(RenderTarget* mainRenderTarget)
{
	mainRenderTarget->Transition(D3D12_RESOURCE_STATE_RENDER_TARGET);

	mainRenderTarget->SetRenderTarget();

	CD3DX12_VIEWPORT viewPort = CD3DX12_VIEWPORT(0.0f, 0.0f, width, height);
	cmdList->RSSetViewports(1, &viewPort);

	CD3DX12_RECT rect = CD3DX12_RECT(0, 0, static_cast<LONG>(width), static_cast<LONG>(height));
	cmdList->RSSetScissorRects(1, &rect);

	sprite->SetSize({ width, height });
	sprite->Draw(material.get(), renderTarget->GetGpuHandle());

	// �`��R�}���h
	cmdList->DrawIndexedInstanced(6, 1, 0, 0, 0);

	mainRenderTarget->Transition(D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
}

void VignettePostEffect::SetData(const AliceMathF::Vector3& color, const AliceMathF::Vector2& center, float power, const AliceMathF::Vector2& size)
{
	AliceMathF::Vector3 col = { 1.0f,1.0f,1.0f };
	col = col - (color / 255.0f);

	data.color = col;
	data.center = center;
	data.power = power;
	data.winSize = { static_cast<float>(WindowsApp::GetWindowsSize().width),static_cast<float>(WindowsApp::GetWindowsSize().height) };
	data.size = size;
	vignetteDataBuff->Update(&data);
}

void VignettePostEffect::SetCol(const AliceMathF::Vector3& color)
{
	AliceMathF::Vector3 col = { 1.0f,1.0f,1.0f };
	col = col - (color / 255.0f);

	data.color = col;

	vignetteDataBuff->Update(&data);
}

void VignettePostEffect::SetCent(const AliceMathF::Vector2& center)
{
	data.center = center;

	vignetteDataBuff->Update(&data);
}

void VignettePostEffect::SetPow(float power)
{
	data.power = power;

	vignetteDataBuff->Update(&data);
}

void VignettePostEffect::SetSi(const AliceMathF::Vector2& size)
{
	data.size = size;

	vignetteDataBuff->Update(&data);
}

#include "LutPostEffect.h"
#include "DirectX12Core.h"
#include "TextureManager.h"
#include "WindowsApp.h"

LutPostEffect* LutPostEffect::GetInstance()
{
	static LutPostEffect instance;
	return &instance;
}

void LutPostEffect::Initialize()
{
	if (needsInit)
	{
		//���[�g�V�O�l�`���̏�����
		rootSignature = std::make_unique<RootSignature>();

		rootSignature->Add(RootSignature::RootType::CBV, 0);//c0

		rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0
		rootSignature->AddStaticSampler(0);//s0
		rootSignature->Add(RootSignature::RangeType::SRV, 1);//t1


		rootSignature->Add(RootSignature::RangeType::UAV, 0);//u0

		//���[�g�V�O�l�`���̐���
		rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

		//�V�F�[�_�[�̏�����
		shader = std::make_unique<Shader>();
		//�V�F�[�_�[�ǂݍ���
		shader->Create("Resources/Shaders/2D/PostEffect/LutShaderCS.hlsl", "main", "cs_5_0", Shader::ShaderType::CS);

		//�p�C�v���C���X�e�[�g������
		pipelineState = std::make_unique<ComputePipelineState>();
		//�V�F�[�_�[���Z�b�g
		pipelineState->SetShader(*shader->GetShader());
		//���[�g�V�O�l�`���̃Z�b�g
		pipelineState->SetRootSignature(rootSignature.get());
		//�p�C�v���C���X�e�[�g�̐���
		pipelineState->Create(DirectX12Core::GetInstance()->GetDevice().Get());


		needsInit = false;

		uint32_t handle = TextureManager::Load("Resources/Lut/amoebae-66-multilut1.png");

		lutTexture = TextureManager::GetTextureData(handle);

		lutSizeBuff = std::make_unique<ConstantBuffer>();
		lutSizeBuff->Create(sizeof(lutSize));

		size = { 1.0f / static_cast<float>(lutTexture->width),1.0f / static_cast<float>(lutTexture->height),1.13900006f,0.714969635f ,0.0489999987f,static_cast<float>(lutTexture->width / lutTexture->height) - 3.0f };

		lutSizeBuff->Update(&size);

		cmdList = DirectX12Core::GetInstance()->GetCommandList().Get();

		type = "LUT";
	}
}

void LutPostEffect::PostUpdate(D3D12_GPU_DESCRIPTOR_HANDLE& srv,D3D12_GPU_DESCRIPTOR_HANDLE& uav)
{
	if (!needsInit)
	{
		//�f�X�N�v���^�q�[�v���Z�b�g
		ID3D12DescriptorHeap* descriptorHeaps[] =
		{
			DirectX12Core::GetInstance()->GetDescriptorHeap()->GetHeap(),
		};
		cmdList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
		//���[�g�V�O�l�`�����Z�b�g
		cmdList->SetComputeRootSignature(rootSignature->GetRootSignature());
		//�p�C�v���C���X�e�[�g���Z�b�g
		cmdList->SetPipelineState(pipelineState->GetPipelineState());

		cmdList->SetComputeRootConstantBufferView(0, lutSizeBuff->GetAddress());
		cmdList->SetComputeRootDescriptorTable(1, lutTexture->gpuHandle);
		cmdList->SetComputeRootDescriptorTable(2, srv);
		cmdList->SetComputeRootDescriptorTable(3, uav);

		cmdList->Dispatch(static_cast<UINT>(WindowsApp::GetWindowsSize().width / 10), static_cast<UINT>(WindowsApp::GetWindowsSize().height / 10), 1);
	}
	else
	{
		Initialize();

		//�f�X�N�v���^�q�[�v���Z�b�g
		ID3D12DescriptorHeap* descriptorHeaps[] =
		{
			DirectX12Core::GetInstance()->GetDescriptorHeap()->GetHeap(),
		};
		cmdList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
		//���[�g�V�O�l�`�����Z�b�g
		cmdList->SetComputeRootSignature(rootSignature->GetRootSignature());
		//�p�C�v���C���X�e�[�g���Z�b�g
		cmdList->SetPipelineState(pipelineState->GetPipelineState());

		cmdList->SetComputeRootConstantBufferView(0, lutSizeBuff->GetAddress());
		cmdList->SetComputeRootDescriptorTable(1, lutTexture->gpuHandle);
		cmdList->SetComputeRootDescriptorTable(2, srv);
		cmdList->SetComputeRootDescriptorTable(3, uav);

		cmdList->Dispatch(static_cast<UINT>(WindowsApp::GetWindowsSize().width / 10), static_cast<UINT>(WindowsApp::GetWindowsSize().height / 10), 1);
	}
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

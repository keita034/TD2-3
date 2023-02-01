#pragma once
#include"ErrorException.h"
#include"ComputePipelineState.h"
#include"Shader.h"

class BasePostEffect 
{
protected:

	//�p�C�v���C���X�e�[�g
	std::unique_ptr<ComputePipelineState> pipelineState;
	//���[�g�V�O�l�`��
	std::unique_ptr<RootSignature> rootSignature;
	//�V�F�[�_�[
	std::unique_ptr<Shader> shader;
	//���������K�v���ǂ���
	bool needsInit = true;
	char PADING[7]{};

	ID3D12GraphicsCommandList* cmdList = nullptr;

	std::string type;
public:

	virtual ~BasePostEffect();
	BasePostEffect() = default;

	virtual void Initialize() = 0;

	virtual void PostUpdate(D3D12_GPU_DESCRIPTOR_HANDLE& srv, D3D12_GPU_DESCRIPTOR_HANDLE& uav) = 0;

	virtual const std::string& GetType() = 0;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	BasePostEffect& operator=(const BasePostEffect&) = delete;
	BasePostEffect(const BasePostEffect&) = delete;
};


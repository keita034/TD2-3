#pragma once
#include"ErrorException.h"
#include"Shader.h"

/// <summary>
/// �p�C�v���C���X�e�[�g
/// </summary>
class PipelineState
{
private:
	//�p�C�v���C���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	//���[�g�V�O�l�`��
	ID3D12RootSignature* rootSignature = nullptr;
	//���_�V�F�[�_�[�I�u�W�F�N�g
	D3D12_SHADER_BYTECODE* vsByte = nullptr;
	//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g
	D3D12_SHADER_BYTECODE* psByte = nullptr;
	//�W�I���g���V�F�[�_�[�I�u�W�F�N�g
	D3D12_SHADER_BYTECODE* gsByte = nullptr;
	//�n���V�F�[�_�[�I�u�W�F�N�g
	D3D12_SHADER_BYTECODE* hsByte = nullptr;
	//�h���C���V�F�[�_�I�u�W�F�N�g
	D3D12_SHADER_BYTECODE* dsByte = nullptr;
	//�[�x�t���O
	bool depthFlag = true;
	char PADING[7]{};

	//�C���v�b�g���C�A�E�g�f�[�^
	D3D12_INPUT_ELEMENT_DESC* inputLayoutData;
	//�C���v�b�g���C�A�E�g�T�C�Y
	size_t inputLayoutLength;
	//�u�����h�f�X�N
	D3D12_BLEND_DESC blendDesc  = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	
	//�v���~�e�B�u�`��
	D3D12_PRIMITIVE_TOPOLOGY_TYPE primitiveType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	char PADING2[4];

public:

	/// <summary>
	/// �C���v�b�g���C�A�E�g���Z�b�g
	/// </summary>
	/// <param name="desc">�C���v�b�g���C�A�E�g�̐擪�A�h���X</param>
	/// <param name="length">�v�f��</param>
	void SetInputLayout(D3D12_INPUT_ELEMENT_DESC* desc, size_t length);

	/// <summary>
	/// ���[�g�V�O�l�`���̃A�h���X���Z�b�g
	/// </summary>
	/// <param name="pRootSignature">���[�g�V�O�l�`���̃A�h���X</param>
	void SetRootSignature(ID3D12RootSignature* pRootSignature);

	/// <summary>
	/// �u�����h���Z�b�g
	/// </summary>
	/// <param name="desc">�u�����h�f�X�N</param>
	void SetBlend(D3D12_BLEND_DESC& desc);

	/// <summary>
	/// �[�x�e�X�g�̃t���O���Z�b�g
	/// </summary>
	/// <param name="flag">�[�x�e�X�g�̃t���O</param>
	void SetDepthFlag(bool flag);

	/// <summary>
	/// ���_�V�F�[�_���Z�b�g
	/// </summary>
	/// <param name="vsByte">���_�V�F�[�_�I�u�W�F�N�g</param>
	void SetVertexShader(D3D12_SHADER_BYTECODE* pVsByte);

	/// <summary>
	/// �s�N�Z���V�F�[�_���Z�b�g
	/// </summary>
	/// <param name="psByte">�s�N�Z���V�F�[�_�I�u�W�F�N�g</param>
	void SetPixelShader(D3D12_SHADER_BYTECODE* pPsByte);

	/// <summary>
	/// �W�I���g���V�F�[�_���Z�b�g
	/// </summary>
	/// <param name="gsByte">�W�I���g���V�F�[�_�I�u�W�F�N�g</param>
	void SetGeometryShader(D3D12_SHADER_BYTECODE* pGsByte);

	/// <summary>
	/// �n���V�F�[�_���Z�b�g
	/// </summary>
	/// <param name="hsByte">�n���V�F�[�_�I�u�W�F�N�g</param>
	void SetHullShader(D3D12_SHADER_BYTECODE* pHsByte);

	/// <summary>
	/// �h���C���V�F�[�_���Z�b�g
	/// </summary>
	/// <param name="pDsByte">�h���C���V�F�[�_�I�u�W�F�N�g</param>
	void SetDomainShader(D3D12_SHADER_BYTECODE* pDsByte);

	/// <summary>
	/// �v���~�e�B�u�`����Z�b�g
	/// </summary>
	/// <param name="type">�v���~�e�B�u�`��</param>
	void SetPrimitiveType(D3D12_PRIMITIVE_TOPOLOGY_TYPE type);

	/// <summary>
	/// �p�C�v���C���X�e�[�g�𐶐�
	/// </summary>
	/// <returns>�����o������</returns>
	bool Create();

	/// <summary>
	/// �p�C�v���C���X�e�[�g���擾
	/// </summary>
	ID3D12PipelineState* GetPipelineState();


};


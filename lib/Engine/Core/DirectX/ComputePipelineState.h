#pragma once
#include"ErrorException.h"
#include"RootSignature.h"

/// <summary>
/// �v�Z�V�F�[�_�p�p�C�v���C���X�e�[�g
/// </summary>
class ComputePipelineState
{
private:
	//�p�C�v���C���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	
	//�V�F�[�_�[�I�u�W�F�N�g
	D3D12_SHADER_BYTECODE shaderByte;
	
	//���[�g�V�O�l�`��
	RootSignature* rootSignaturePtr;
	
	//�m�[�h�}�X�N
	UINT pipelineNodeMask = 0;
	char PADING1[4];

	//�L���b�V���p�C�v���C��
	D3D12_CACHED_PIPELINE_STATE cachedPipeline;
	
	//�t���O
	D3D12_PIPELINE_STATE_FLAGS  pipelineFlag = D3D12_PIPELINE_STATE_FLAG_NONE;
	char PADING2[4];

public:

public:

	/// <summary>
	/// �V�F�[�_�[���Z�b�g
	/// </summary>
	/// <param name="shader">�V�F�[�_�[</param>
	void SetShader(D3D12_SHADER_BYTECODE& shader);

	/// <summary>
	/// ���[�g�V�O�l�`�����Z�b�g
	/// </summary>
	/// <param name="rootSignature_">���[�g�V�O�l�`��</param>
	void SetRootSignature(RootSignature* rootSignature_);

	/// <summary>
	/// �m�[�h�}�X�N���Z�b�g
	/// </summary>
	/// <param name="nodeMask">�m�[�h�}�X�N</param>
	void SetNodeMask(UINT nodeMask);

	/// <summary>
	/// �L���b�V���p�C�v���C�����Z�b�g
	/// </summary>
	/// <param name="cachedPSO">�L���b�V���p�C�v���C��</param>
	void SetCachedPSO(D3D12_CACHED_PIPELINE_STATE& cachedPSO);

	/// <summary>
	/// �t���O���Z�b�g
	/// </summary>
	/// <param name="flag">�t���O</param>
	void SetFlag(D3D12_PIPELINE_STATE_FLAGS flag);

	/// <summary>
	/// ����
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	void Create(ID3D12Device* device);

	/// <summary>
	/// �p�C�v���C���X�e�[�g���擾
	/// </summary>
	/// <returns>�p�C�v���C���X�e�[�g</returns>
	ID3D12PipelineState* GetPipelineState();
private:

};


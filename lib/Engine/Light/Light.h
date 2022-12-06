#pragma once
#include"ErrorException.h"
#include"AliceMathUtility.h"
#include"ConstantBuffer.h"

/// <summary>
/// ���C�g
/// </summary>

struct LightConstBuffData
{
	AliceMathF::Vector3 lightv;//���C�g�ւ̕����x�N�g��
	AliceMathF::Vector4 lightcolor;//���C�g�̐F
};

class Light
{
private:
	Microsoft::WRL::ComPtr<ID3D12Device>device;
	//�萔�o�b�t�@
	std::unique_ptr<ConstantBuffer>constBuff;
	//�萔�o�b�t�@�̃}�b�v
	LightConstBuffData constMap;
	//���C�g��������(�P�ʃx�N�g��)
	AliceMathF::Vector3 lightdir = {1,0,0};
	//���C�g�̐F
	AliceMathF::Vector4 lightcolor = { 1,1,1,1 };
	//�_�[�e�B�t���O
	bool dirty = false;
	char PADING[7]{};
public:

	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static Light* Create();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �萔�o�b�t�@�փf�[�^�]��
	/// </summary>
	void TransferConstBuffer();

	/// <summary>
	/// ���C�g�����̃Z�b�g
	/// </summary>
	/// <param name="lightdir_">���C�g����</param>
	void SetLightDir(AliceMathF::Vector3& lightdir_);

	/// <summary>
	/// ���C�g�F�̃Z�b�g
	/// </summary>
	/// <param name="lightdir_">���C�g����</param>
	void SetLightColor(AliceMathF::Vector4& lightcolor_);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �萔�o�b�t�@�r���[�̃Z�b�g
	/// </summary>
	/// <param name="cmdlist">�R�}���h���X�g</param>
	/// <param name="rootParameterIndex">�p�����[�^�[�ԍ�</param>
	void SetConstBufferView(ID3D12GraphicsCommandList* cmdList,UINT rootParameterIndex);

	Light() = default; 
	~Light() = default;
private:

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Light& operator=(const Light&) = delete;
	Light(const Light&) = delete;

};
#pragma once
#include"ErrorException.h"

/// <summary>
/// �V�F�[�_�I�u�W�F�N�g
/// </summary>
class Shader
{
public:
	//�^�C�v
	enum class ShaderType
	{
		VS,//�o�[�e�N�X
		PS,//�s�N�Z��
		DS,//�h���C��
		HS,//�n��
		GS,//�W�I���g��
		CS,//�R���s���[�g
	};

private:
	//�^�C�v
	ShaderType type = ShaderType::VS;
	char PADING[4]{};

	//�V�F�[�_�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3DBlob> blob;

	//�V�F�[�_�o�C�g�R�[�h
	D3D12_SHADER_BYTECODE shaderBytecode{};
public:

public:
	/// <summary>
	/// �V�F�[�_�I�u�W�F�N�g�𐶐�
	/// </summary>
	/// <param name="fileName">�V�F�[�_�̃t�@�C����</param>
	/// <param name="entryPoint">�G���g���[�|�C���g(�����l:main)</param>
	/// <param name="target">�V�F�[�_�̃o�[�W����(�����l:vs_5_0)</param>
	/// <param name="type_">�V�F�[�_�̎��(�����l:VS)</param>
	void Create(const std::string& fileName, const std::string& entryPoint = "main", const std::string& target= "vs_5_0", const ShaderType& type_ = ShaderType::VS);

	/// <summary>
	/// �V�F�[�_�I�u�W�F�N�g���擾
	/// </summary>
	/// <returns>�V�F�[�_�I�u�W�F�N�g(D3D12_SHADER_BYTECODE)</returns>
	D3D12_SHADER_BYTECODE* GetShader();

	/// <summary>
	/// �^�C�v
	/// </summary>
	/// <returns>�^�C�v</returns>
	ShaderType GetType();

	/// <summary>
	/// �V�F�[�_�[�f�[�^���R�s�[����
	/// </summary>
	/// <param name="shader">�R�s�[���V�F�[�_�[</param>
	/// <returns>�R�s�[�o������</returns>
	bool Copy(Shader* shader);

private:
};


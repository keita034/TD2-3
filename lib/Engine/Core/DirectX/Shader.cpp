#include "Shader.h"
#include"AliceFunctionUtility.h"

void Shader::Create(const std::string& fileName, const std::string& entryPoint, const std::string& target, const ShaderType& type_)
{
	HRESULT result = S_OK;

	// �G���[�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;

	std::wstring wFileName;
	wFileName = AliceFunctionUtility::StringToWstring(fileName);

	// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		wFileName.c_str(), // �V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
		entryPoint.c_str(), target.c_str(), // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
		0,
		&blob, &errorBlob);

	// �G���[�Ȃ�
	if (FAILED(result))
	{
		// errorBlob����G���[���e��string�^�ɃR�s�[
		std::string error;
		error.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		// �G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(error.c_str());
		assert(0);
	};

	shaderBytecode.pShaderBytecode = blob->GetBufferPointer();
	shaderBytecode.BytecodeLength = blob->GetBufferSize();

	type = type_;
}

D3D12_SHADER_BYTECODE* Shader::GetShader()
{
	return &shaderBytecode;
}

Shader::ShaderType Shader::GetType()
{
	return type;
}

bool Shader::Copy(Shader* shader)
{
	shaderBytecode = shader->shaderBytecode;
	blob = shader->blob;
	type = shader->type;
	return true;
}

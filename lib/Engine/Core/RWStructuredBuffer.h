#pragma once
#include"ErrorException.h"

/// <summary>
/// �������݂Ɠǂݍ��ݗp�\�����o�b�t�@
/// </summary>
class RWStructuredBuffer
{

private:

	// �o�b�t�@�����ɐ���������
	bool isValid = false;
	char PADING[7] = {};

	// �o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> buffer;

	void* BufferMappedPtr = nullptr;

	//��
	size_t bufferLength;

	//�f�[�^����̃T�C�Y
	size_t bufferSingleSize;

	D3D12_GPU_DESCRIPTOR_HANDLE structuredBufferHandle;
public:
	
	/// <summary>
	/// �V�F�[�_�[���\�[�X�r���[�𐶐�
	/// </summary>
	/// <param name="length">�v�f��</param>
	/// <param name="singleSize">�v�f1���̃f�[�^�T�C�Y</param>
	/// <param name="data">�f�[�^</param>
	void CreateSRV(size_t length, size_t singleSize, const void* data = nullptr);

	/// <summary>
	/// �A���I�[�_�[�A�N�Z�X�r���[�𐶐�
	/// </summary>
	/// <param name="length">��</param>
	/// <param name="singleSize">�v�f1���̃f�[�^�T�C�Y</param>
	/// <param name="data">�f�[�^</param>
	void CreateUAV(size_t length, size_t singleSize, const void* data = nullptr);

	/// <summary>
	/// �o�b�t�@�����ɐ�����������Ԃ�
	/// </summary>
	bool IsValid();

	/// <summary>
	/// �o�b�t�@��GPU��̃A�h���X��Ԃ�
	/// </summary>
	/// <returns>�o�b�t�@��GPU��̃A�h���X</returns>
	D3D12_GPU_DESCRIPTOR_HANDLE GetAddress() const;

	/// <summary>
	/// �萔�o�b�t�@�r���[��Ԃ�
	/// </summary>
	/// <returns>�萔�o�b�t�@�r���[</returns>
	D3D12_SHADER_RESOURCE_VIEW_DESC GetViewDesc();

	/// <summary>
	/// �o�b�t�@���擾
	/// </summary>
	ID3D12Resource* GetResource();

	/// <summary>
	/// �萔�o�b�t�@�Ƀ}�b�s���O���ꂽ�|�C���^��Ԃ�
	/// </summary>
	/// <returns>�萔�o�b�t�@�Ƀ}�b�s���O���ꂽ�|�C���^</returns>
	void* GetPtr() const;

	/// <summary>
	/// �f�[�^���X�V
	/// </summary>
	/// <param name="data"></param>
	void Update(void* data);

	~RWStructuredBuffer() = default;
	RWStructuredBuffer() = default;

private:

	RWStructuredBuffer(const RWStructuredBuffer&) = delete;
	void operator = (const RWStructuredBuffer&) = delete;

};
#pragma once
#include"ErrorException.h"

/// <summary>
/// �ǂݎ���p�\�����o�b�t�@
/// </summary>
class StructuredBuffer
{

private:

	// �o�b�t�@�����ɐ���������
	bool isValid = false;
	char PADING[7]={};

	size_t bufferLength;
	size_t bufferSingleSize;

	// �o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> buffer;

	void* BufferMappedPtr = nullptr;

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

	D3D12_GPU_DESCRIPTOR_HANDLE structuredBufferHandle;
public:

	/// <summary>
	/// �o�b�t�@�𐶐�
	/// </summary>
	/// <param name="length">�v�f��</param>
	/// <param name="singleSize">�P�̂̃T�C�Y</param>
	/// <param name="data">�z��̐擪�A�h���X</param>
	void Create(size_t length, size_t singleSize, const void* data = nullptr);

	/// <summary>
	/// �o�b�t�@�����ɐ�����������Ԃ�
	/// </summary>
	/// <returns>�o�b�t�@�����ɐ���������</returns>
	bool IsValid();

	/// <summary>
	/// �o�b�t�@��GPU��̃A�h���X��Ԃ�
	/// </summary>
	/// <returns>�o�b�t�@��GPU��̃A�h���X</returns>
	D3D12_GPU_DESCRIPTOR_HANDLE GetAddress() const;

	/// <summary>
	/// �o�b�t�@�r���[��Ԃ�
	/// </summary>
	/// <returns>�o�b�t�@�r���[</returns>
	D3D12_SHADER_RESOURCE_VIEW_DESC GetViewDesc();

	/// <summary>
	/// �o�b�t�@�Ƀ}�b�s���O���ꂽ�|�C���^��Ԃ�
	/// </summary>
	/// <returns>�o�b�t�@�Ƀ}�b�s���O���ꂽ�|�C���^</returns>
	void* GetPtr() const;

	/// <summary>
	/// �f�[�^�̍X�V
	/// </summary>
	/// <param name="data">�f�[�^</param>
	void Update(void* data);

	~StructuredBuffer() = default;
	StructuredBuffer() = default;

private:

	StructuredBuffer(const StructuredBuffer&) = delete;
	void operator = (const StructuredBuffer&) = delete;

};


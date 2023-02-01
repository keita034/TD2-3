#pragma once
#include"ErrorException.h"

/// <summary>
/// �R���s���[�g�V�F�[�_�[�p���_�o�b�t�@
/// </summary>
class ComputeVertexBuffer
{
private:
	// �o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexBuffer = nullptr;

	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView = {};

	D3D12_GPU_DESCRIPTOR_HANDLE handl = {};

	void* bufferMappedPtr = nullptr;

	// �o�b�t�@�̐����ɐ���������
	bool isValid = false;
	char PADING[7];
public:

	/// <summary>
	/// �o�b�t�@�𐶐�
	/// </summary>
	/// <param name="length">�v�f��</param>
	/// <param name="singleSize">�P�̂̃T�C�Y</param>
	/// <param name="data">�z��̃|�C���^</param>
	void Create(size_t length, size_t singleSize, const void* data = nullptr);

	/// <summary>
	/// ���_�o�b�t�@�r���[���擾
	/// </summary>
	/// <returns>���_�o�b�t�@�r���[</returns>
	D3D12_VERTEX_BUFFER_VIEW GetView() const;

	ID3D12Resource* GetResource();

	/// <summary>
	/// �o�b�t�@�̐����ɐ������������擾
	/// </summary>
	/// <returns>����������</returns>
	bool IsValid();

	/// <summary>
	/// �o�b�t�@��GPU��̃A�h���X��Ԃ�
	/// </summary>
	/// <returns>�o�b�t�@��GPU��̃A�h���X</returns>
	D3D12_GPU_DESCRIPTOR_HANDLE GetAddress() const;

	/// <summary>
	/// �o�b�t�@�̏�Ԃ�ς���
	/// </summary>
	/// <param name="beforeState">���̏��</param>
	/// <param name="afterState">�ς��������</param>
	void Transition(D3D12_RESOURCE_STATES beforeState, D3D12_RESOURCE_STATES afterState);

	/// <summary>
	/// �f�[�^�X�V
	/// </summary>
	/// <param name="data">�f�[�^</param>
	void Update(void* data);

	~ComputeVertexBuffer() = default;
	ComputeVertexBuffer() = default;

private:

	ComputeVertexBuffer(const ComputeVertexBuffer&) = delete;

	void operator = (const ComputeVertexBuffer&) = delete;
};


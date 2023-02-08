#pragma once
#include"ErrorException.h"
#include"DSVDescriptorHeap.h"

class DepthStencilBuffer
{
private:

	//�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D12Resource> texture;
	//�f�B�X�N���v�^�q�[�v
	DSVDescriptorHeap* dsvHeap = nullptr;
	//��
	UINT width = 0;
	//����
	UINT height = 0;
	//�f�o�C�X
	ID3D12Device* device = nullptr;
	//�n���h��
	D3D12_CPU_DESCRIPTOR_HANDLE handle{};

public:

	/// <summary>
	/// ����
	/// </summary>
	/// <param name="w">����</param>
	/// <param name="h">�c��</param>
	/// <param name="format">�t�H�[�}�b�g</param>
	bool Create(UINT w, UINT h, DXGI_FORMAT format);

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="d3dDevice">�f�o�C�X</param>
	/// <param name="descriptorHeap">�f�v�X�X�e���V���p�̃f�X�N�v���^�q�[�v</param>
	DepthStencilBuffer(ID3D12Device* d3dDevice, DSVDescriptorHeap* descriptorHeap);

	/// <summary>
	/// ���\�[�X���擾
	/// </summary>
	ID3D12Resource* GetTexture() const;

	/// <summary>
	/// �|�C���^�ԍ����擾
	/// </summary>
	const D3D12_CPU_DESCRIPTOR_HANDLE& GetHandle() ;

	~DepthStencilBuffer() = default;

private:

	DepthStencilBuffer() = delete;
};
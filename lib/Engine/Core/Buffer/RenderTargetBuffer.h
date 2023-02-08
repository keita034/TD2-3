#pragma once
#include"ErrorException.h"
#include"RTVDescriptorHeap.h"
#include"AliceMathUtility.h"

class RenderTargetBuffer
{
	//�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D12Resource> texture;
	//�f�B�X�N���v�^�q�[�v
	RTVDescriptorHeap* rtvHeap = nullptr;
	//��
	UINT width = 0;
	//����
	UINT height = 0;
	//�f�o�C�X
	ID3D12Device* device = nullptr;
	//�n���h��
	D3D12_CPU_DESCRIPTOR_HANDLE handle{};
	//�X�e�[�^�X
	D3D12_RESOURCE_STATES states;
public:

	/// <summary>
	/// ����
	/// </summary>
	/// <param name="w">����</param>
	/// <param name="h">�c��</param>
	/// <param name="resourceStates">�X�e�[�^�X</param>
	/// <param name="mipLevel">�~�b�v���x��</param>
	/// <param name="arraySize">�z��̃T�C�Y</param>
	/// <param name="format">�t�H�[�}�b�g</param>
	/// <param name="clearColor">�J���[</param>
	bool Create(UINT w, UINT h, D3D12_RESOURCE_STATES resourceStates,UINT16 mipLevel = 0, UINT16 arraySize = 1, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, const AliceMathF::Vector4& clearColor = {1.0f,1.0f,1.0f,1.0f });

	/// <summary>
	/// ����
	/// </summary>
	/// <param name="swapChain4"></param>
	/// <returns></returns>
	bool Create(IDXGISwapChain4* swapChain,UINT index);

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="d3dDevice">�f�o�C�X</param>
	/// <param name="descriptorHeap">�����_�[�^�[�Q�b�g�p�̃f�X�N�v���^�q�[�v</param>
	RenderTargetBuffer(ID3D12Device* d3dDevice, RTVDescriptorHeap* descriptorHeap);

	/// <summary>
	/// ���\�[�X���擾
	/// </summary>
	ID3D12Resource* GetTexture() const;

	/// <summary>
	/// �|�C���^�ԍ����擾
	/// </summary>
	const D3D12_CPU_DESCRIPTOR_HANDLE& GetHandle();

	void Transition(D3D12_RESOURCE_STATES resourceStates, ID3D12GraphicsCommandList* commandList);

	~RenderTargetBuffer() = default;

private:

	RenderTargetBuffer() = delete;

};


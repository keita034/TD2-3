#pragma once
#include"ErrorException.h"
#include"DescriptorHeap.h"

/// <summary>
/// �R�A
/// </summary>
class DirectX12Core
{
private:

	HRESULT result;
	char PADDING[4];
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;

	//�o�b�N�o�b�t�@
	std::vector< Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;

	//�o���A�[�f�X�N
	D3D12_RESOURCE_BARRIER barrierDesc{};

	//�f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};

	//�t�F���X�̐���
	UINT64 fenceVal = 0;

	//�X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;

	//�N���A�[�J���[
	FLOAT clearColor[4] = { 0.1f, 0.25f, 0.5f, 0.0f };

	//�r���[�|�[�g
	D3D12_VIEWPORT viewport{};

	//�V�U�[��`
	D3D12_RECT scissorRect{};

	//�[�x�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;

	//�[�x�r���[�p�f�X�N�v���^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;

	static DirectX12Core* DirectX12Core_;
	
	//�f�X�N�v���^�q�[�v
	std::unique_ptr<DescriptorHeap> descriptorHeap;

public:

	//�V���O���g���C���X�^���X�̎擾
	static DirectX12Core* GetInstance();

	/// <summary>
	/// �f�o�C�X�̎擾(�X�^�e�B�b�N)
	/// </summary>
	static Microsoft::WRL::ComPtr<ID3D12Device> GetDeviceSta();

	/// <summary>
	/// �R�}���h���X�g�̎擾(�X�^�e�B�b�N)
	/// </summary>
	static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> GetCommandListSta();
	
	/// <summary>
	/// ���\�[�X�̏�Ԃ�ς���
	/// </summary>
	/// <param name="resource">���\�[�X</param>
	/// <param name="beforeState">���̏��</param>
	/// <param name="afterState">�ς��������</param>
	static void ResourceTransition(ID3D12Resource* resource, D3D12_RESOURCE_STATES beforeState, D3D12_RESOURCE_STATES afterState);

	/// <summary>
	/// ������
	/// </summary>
	void DirectXInitialize();

	/// <summary>
	/// �`�揀��
	/// </summary>
	void BeginDraw();

	/// <summary>
	/// �`���n��
	/// </summary>
	void EndDraw();

	/// <summary>
	/// �R�}���h��n��
	/// </summary>
	void ExecuteCommand();

	/// <summary>
	/// �J��
	/// </summary>
	void Destroy();

	//�w�i�̐F�ς�(RGBA)
	void SetBackScreenColor(float red, float green, float blue, float alpha);

	/// <summary>
	/// �f�o�C�X�̎擾
	/// </summary>
	Microsoft::WRL::ComPtr<ID3D12Device> GetDevice();

	/// <summary>
	/// �R�}���h���X�g�擾
	/// </summary>
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> GetCommandList();

	/// <summary>
	/// SRV,CBV,URV�p�f�X�N�v���^�q�[�v�擾
	/// </summary>
	DescriptorHeap* GetDescriptorHeap();

	/// <summary>
	/// ���\�[�X�̏�Ԃ�ς���
	/// </summary>
	/// <param name="resource">���\�[�X</param>
	/// <param name="beforeState">���̏��</param>
	/// <param name="afterState">�ς��������</param>
	void Transition(ID3D12Resource* resource, D3D12_RESOURCE_STATES beforeState, D3D12_RESOURCE_STATES afterState);

private:

	//DXGI�܂�菉����
	HRESULT InitializeDXGIDevice();

	//�ŏI�I�ȃ����_�[�^�[�Q�b�g�̐���
	HRESULT CreatFinalRenderTarget();

	//�X���b�v�`�F�C���̐���
	HRESULT CreateSwapChain();

	//�R�}���h�܂�菉����
	HRESULT InitializeCommand();

	//�t�F���X����
	HRESULT CreateFence();

	//�[�x�֌W����
	HRESULT CreatDepthBuffer();

	//�f�o�b�O���C���[��L���ɂ���
	void EnableDebugLayer();

	//�C���t�H�L���[��L���ɂ���
	void EnableInfoQueue();

	//�R���X�g���N�^�E�f�X�g���N�^
	DirectX12Core() = default;
	~DirectX12Core() = default;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	DirectX12Core& operator=(const DirectX12Core&) = delete;
	DirectX12Core(const DirectX12Core&) = delete;
};
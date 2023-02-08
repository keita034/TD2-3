#pragma once
#include"ErrorException.h"
#include"AliceUtility.h"
#include"RenderTargetBuffer.h"
#include"DepthStencilBuffer.h"
#include"DescriptorHeap.h"
class RenderTarget
{
private:

	//�����_�[�^�[�Q�b�g�e�N�X�`��
	std::unique_ptr<RenderTargetBuffer>renderTargetBuffer;
	//�f�v�X�e�N�X�`��
	std::unique_ptr<DepthStencilBuffer>depthStencilBuffer;
	//�R�}���h���X�g
	ID3D12GraphicsCommandList* cmdList;
	//�N���A�[�J���[
	std::array<float, 4> clearColor;

	DescriptorHeap* srvHeap = nullptr;

	D3D12_GPU_DESCRIPTOR_HANDLE handle;

public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(UINT w, UINT h, D3D12_RESOURCE_STATES resourceStates, const AliceMathF::Vector4& col = { 1.0f,1.0f, 1.0f, 1.0f }, DXGI_FORMAT rtFormat = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, DXGI_FORMAT dsFormat = DXGI_FORMAT_D32_FLOAT);

	/// <summary>
	/// �����_�[�^�[�Q�b�g�ƃf�v�X�X�e���V�����Z�b�g���N���A�[
	/// </summary>
	void Begin();

	/// <summary>
	/// �����_�[�^�[�Q�b�g�ƃf�v�X�X�e���V�����Z�b�g
	/// </summary>
	void SetRenderTarget();

	/// <summary>
	/// �����_�[�^�[�Q�b�g�ƃf�v�X�X�e���V�����N���A�[
	/// </summary>
	void ClearRenderTarget();

	/// <summary>
	/// 
	/// </summary>
	void Transition(D3D12_RESOURCE_STATES resourceStates);

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="d3dDevice">�f�o�C�X</param>
	/// <param name="rtvDescriptorHeap">�����_�[�^�[�Q�b�g�e�N�X�`���p�̃f�X�N�v���^�q�[�v</param>
	/// <param name="descriptorHeap">�f�v�X�e�N�X�`���p�̃f�X�N�v���^�q�[�v</param>
	/// <param name="commandList">�R�}���h���X�g</param>
	RenderTarget(ID3D12Device* d3dDevice, DSVDescriptorHeap* dsvDescriptorHeap, RTVDescriptorHeap* rtvDescriptorHeap, DescriptorHeap* srvDescriptorHeap, ID3D12GraphicsCommandList* commandList);

	/// <summary>
	/// �����_�[�^�[�Q�b�g�e�N�X�`�����擾
	/// </summary>
	RenderTargetBuffer* GetRenderTargetBuffer();

	/// <summary>
	/// �f�v�X�e�N�X�`�����擾
	/// </summary>
	DepthStencilBuffer* GetDepthStencilBuffer();

	const D3D12_GPU_DESCRIPTOR_HANDLE& GetGpuHandle();

	const D3D12_CPU_DESCRIPTOR_HANDLE& GetCpuHandle();

private:

	RenderTarget() = delete;
};


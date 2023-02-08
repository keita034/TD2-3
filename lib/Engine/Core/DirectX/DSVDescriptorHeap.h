#pragma once
#include"ErrorException.h"

class DSVDescriptorHeap
{
private:
//�f�o�C�X
	ID3D12Device* device;

	//�f�X�N�v���^�q�[�v
	Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> descriptorHeap;

	size_t maxDSV = 2048;

	size_t countDSV = 0;

	UINT incrementSize;

	char PADING2[4];

	D3D12_CPU_DESCRIPTOR_HANDLE	startCpuHandle;

public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �f�v�X�X�e���V���r���[�𐶐�
	/// </summary>
	/// <param name="desc"> �f�v�X�X�e���V���r���[�f�X�N</param>
	/// <param name="resource">�o�b�t�@</param>
	/// <returns>GPU�n���h��(UINT64)</returns>
	UINT64 CreateDSV(D3D12_DEPTH_STENCIL_VIEW_DESC& desc, ID3D12Resource* resource);

	/// <summary>
	/// �f�X�N�v���^�q�[�v���擾
	/// </summary>
	ID3D12DescriptorHeap* GetHeap();

	UINT GetIncrementSize();

	~DSVDescriptorHeap() = default;

};


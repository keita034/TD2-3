#pragma once
#include"ErrorException.h"

/// <summary>
/// ���[�g�V�O�l�`��
/// </summary>
class RootSignature
{
public:
	/// <summary>
	/// ���[�g�p�����[�^�^�C�v
	/// </summary>
	enum class RootType
	{
		CBV = D3D12_ROOT_PARAMETER_TYPE_CBV,
		SRV = D3D12_ROOT_PARAMETER_TYPE_SRV,
		UAV = D3D12_ROOT_PARAMETER_TYPE_UAV,
	};

	/// <summary>
	/// �����W�^�C�v
	/// </summary>
	enum class RangeType
	{
		SRV = D3D12_DESCRIPTOR_RANGE_TYPE_SRV,
		UAV = D3D12_DESCRIPTOR_RANGE_TYPE_UAV,
		CBV = D3D12_DESCRIPTOR_RANGE_TYPE_CBV,
		Sampler = D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER
	};
	enum class AddressMode
	{
		Wrap = D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		Mirror = D3D12_TEXTURE_ADDRESS_MODE_MIRROR,
		Clamp = D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
		Border = D3D12_TEXTURE_ADDRESS_MODE_BORDER,
		MirrorOnce = D3D12_TEXTURE_ADDRESS_MODE_MIRROR_ONCE
	};

	/// <summary>
	/// ���[�g�p�����[�^��ǉ�
	/// </summary>
	/// <param name="type">���</param>
	/// <param name="shaderRegister">�o�b�t�@�ԍ�</param>
	/// <param name="registerSpace">���W�X�^�[�X�y�[�X(��{�I��0�ł����悤�ȋC������)</param>
	void Add(RootType type, UINT shaderRegister, UINT registerSpace = 0);

	/// <summary>
	/// �����W��ǉ�
	/// </summary>
	/// <param name="type">���</param>
	/// <param name="shaderRegister">�o�b�t�@�ԍ�</param>
	/// <param name="registerSpace">���W�X�^�[�X�y�[�X(��{�I��0�ł����悤�ȋC������)</param>
	/// <param name="descriptorCount">��x�Ɏg���e�N�X�`����萔�o�b�t�@</param>
	void Add(RangeType type, UINT shaderRegister, UINT registerSpace = 0, UINT descriptorCount = 1);

	/// <summary>
	/// �T���v���[��ǉ�
	/// </summary>
	/// <param name="shaderRegister">�o�b�t�@�ԍ�</param>
	/// <param name="registerSpace">���W�X�^�[�X�y�[�X(��{�I��0�ł����悤�ȋC������)</param>
	/// <param name="filter">�t�B���^�[</param>
	/// <param name="addressU">U�̃A�h���X���[�h</param>
	/// <param name="addressV">V�̃A�h���X���[�h</param>
	/// <param name="addressW">W�̃A�h���X���[�h</param>
	void AddStaticSampler(
		UINT shaderRegister,
		UINT registerSpace = 0,
		D3D12_FILTER filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR,
		AddressMode addressU = AddressMode::Wrap,
		AddressMode addressV = AddressMode::Wrap,
		AddressMode addressW = AddressMode::Wrap
	);

	/// <summary>
	/// ����
	/// </summary>
	void Clear();

	/// <summary>
	/// ����
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	void Create(ID3D12Device* device);

	/// <summary>
	/// ���[�g�V�O�l�`���擾
	/// </summary>
	ID3D12RootSignature* GetRootSignature();

	RootSignature() = default;
	~RootSignature() = default;

private:

	/// <summary>
	/// �p�����[�^�[
	/// </summary>
	std::vector<D3D12_ROOT_PARAMETER>params;

	/// <summary>
	/// �����W
	/// </summary>
	std::vector<D3D12_DESCRIPTOR_RANGE>ranges;


	std::vector<UINT>rangeLocation;

	/// <summary>
	/// �T���v���[
	/// </summary>
	std::vector<D3D12_STATIC_SAMPLER_DESC>samplers;

	/// <summary>
	/// ���[�g�V�O�l�`��
	/// </summary>
	Microsoft::WRL::ComPtr<ID3D12RootSignature>rootSignature;
};


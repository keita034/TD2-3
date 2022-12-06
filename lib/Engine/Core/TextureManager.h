#pragma once
#include"ErrorException.h"
#include"AliceUtility.h"
#include"DirectX12Core.h"

class TextureManager
{
private:

	DirectX12Core* directX12Core;

	static TextureManager* textureManager;

	//�e�N�X�`����
	uint32_t nextTexture;

	// �q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES textureHeapProp{};

	enum ImgFileType
	{
		WIC,//png�Ȃ�
		TGA,//tga�Ȃ�
		PSD,//psd�Ȃ�
		ETC,//����ȊO

	};

	static std::vector<std::string>filePaths;

	static std::unordered_map<std::string, std::unique_ptr<TextureData>> textureDatas;

public:

	/// <summary>
	/// �e�N�X�`�������[�h���܂�
	/// </summary>
	/// <param name="filepath">�e�N�X�`���̃t�@�C���p�X</param>
	/// <returns>�e�N�X�`���n���h��</returns>
	uint32_t LoadTexture(const std::string& path);

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �C���X�^���X������
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static TextureManager* GetInstance();

	/// <summary>
	/// �C���X�^���X�����
	/// </summary>
	void Destroy();

	/// <summary>
	/// �e�N�X�`�������[�h���܂�
	/// </summary>
	/// <param name="filepath">�e�N�X�`���̃t�@�C���p�X</param>
	/// <returns>�e�N�X�`���n���h��</returns>
	static uint32_t Load(const std::string& path);

	static TextureData* GetTextureData(uint32_t handle);

private:

	TextureManager() = default;
	~TextureManager() = default;

	Microsoft::WRL::ComPtr<ID3D12Resource>CreateTexBuff(DirectX::TexMetadata& metadata, DirectX::ScratchImage& scratchImg);

	D3D12_GPU_DESCRIPTOR_HANDLE CreateShaderResourceView(ID3D12Resource* texBuff, DirectX::TexMetadata& metadata);

	void LoadFile(const std::string& path, DirectX::TexMetadata& metadata, DirectX::ScratchImage& scratchImg);

	TextureData* FromTextureData(const std::string& path);

	ImgFileType GetFileType(const std::string& path);
};


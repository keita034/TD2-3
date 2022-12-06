#pragma once
#include"ErrorException.h"
#include"AliceMathUtility.h"
#include"Camera.h"
#include"DirectX12Core.h"
#include"Light.h"
#include"Transform.h"
#include"Material.h"
#include"ConstantBuffer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"

enum class ModelShape
{
	Cube,//������
	Sphere,//��
	Capsule,//�J�v�Z��
	Cylinder,//�~��
	Cone,//�~��
};

enum ShaderType
{
	Default,
	Flat,
	Gouraud,
	Lambert,
	Phong,

};

struct ModelData
{
	ModelData() = default;
	~ModelData() = default;

	std::string filePath;

	uint32_t modelHandle;
private:
	char PADING1[4] = {};
public:

	TextureData* textureData;
	//���_�o�b�t�@
	std::unique_ptr<VertexBuffer> vertexBuffer;
	//�C���f�b�N�X�o�b�t�@
	std::unique_ptr<IndexBuffer> indexBuffer;
private:
	char PADING2[4] = {};
public:

	//�C���f�b�N�X�̐�
	UINT maxIndex = 0u;;
private:
	char PADING3[4] = {};
public:

	//���_�̐�
	UINT maxVert = 0u;
	//���[���h�s��
	AliceMathF::Matrix4 matWorld;
	//���_�f�[�^
	std::vector<PosNormalUv>vertices;
	//���_�C���f�b�N�X
	std::vector<uint32_t> indices;
	//���_�@���X���[�W���O�p�f�[�^
	std::unordered_map<uint32_t, std::vector<uint32_t>>smoothData;
	//�}�e���A��
	ModelMaterial modelMaterial{};
	//�萔�o�b�t�@�}�e���A��
	std::unique_ptr<ConstantBuffer> constBuffMaterial;
	std::unique_ptr<ConstantBuffer> constBuffVelocity;
	Material* modelMaterialData;

private:

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	ModelData& operator=(const ModelData&) = delete;
	ModelData(const ModelData&) = delete;
};

class Model
{
protected:

	static Microsoft::WRL::ComPtr<ID3D12Device> device;
	static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList;

	//���C�g
	static Light* light;

	static std::vector<std::string>filePaths;

	static std::unordered_map<std::string, std::unique_ptr<ModelData>> modelDatas;

	static uint32_t modelCount;

	static const uint32_t maxModel = 1024;

	ModelData* modelData;



public:

	/// <summary>
	/// ���[���h�s��̎擾
	/// </summary>
	/// <returns>���[���h�s��</returns>
	AliceMathF::Matrix4& GetMatWorld();

	/// <summary>
	/// ���_���W���擾
	/// </summary>
	/// <returns>���_���W�z��</returns>
	const std::vector<PosNormalUv>GetVertices();

	/// <summary>
	/// �C���f�b�N�X���擾
	/// </summary>
	/// <returns>�C���f�b�N�X���W�z��</returns>
	const std::vector<uint32_t>GetIndices();

	/// <summary>
	/// ���C�g�̃Z�b�g
	/// </summary>
	/// <param name="light">���C�g</param>
	static void SetLight(Light* light_);

	void SetModel(uint32_t modelHandle);

	Model() = default;
	~Model() = default;

	void Draw(Transform* transform, Material* material = nullptr);

	void EffectDraw(Transform* transform, float velocity, Material* material = nullptr);

	static uint32_t CreatePrimitiveModel(ModelShape type);

	static uint32_t CreateObjModel(const std::string& filePath, bool smoothing = false);

	static void CommonInitialize();

private:

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Model& operator=(const Model&) = delete;
	Model(const Model&) = delete;
};
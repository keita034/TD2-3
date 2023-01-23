#pragma once
#include "ErrorException.h"
#include"AliceUtility.h"
#include "Model.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "DefaultMaterial.h"
#include "ConstantBuffer.h"
#include "RootSignature.h"
#include"ComputePipelineState.h"
#include"RWStructuredBuffer.h"
#include"StructuredBuffer.h"
#include"Shader.h"
#include"ComputeVertexBuffer.h"
#include"fbxAnimation.h"

#pragma warning(push)
#pragma warning(disable: 5264)
//�{�[���̍ő吔
constexpr int MAX_BONES = 128;
constexpr int MAX_BONE_INDICES = 4;
#pragma warning(pop)

// ��
struct Bone
{
	//���O
	std::string name;

	AliceMathF::Matrix4 matrix;
	AliceMathF::Matrix4 animationMatrix;
	AliceMathF::Matrix4 offsetMatirx;

	UINT index;

private:
	char PADING[4] = {};

};

struct PosNormUvTangeColSkin
{
	AliceMathF::Vector4 position = { 0.0f,0.f,0.0f,1.0f }; // �ʒu���W
	AliceMathF::Vector3 normal; // �@��
	AliceMathF::Vector2 uv; // uv���W
	AliceMathF::Vector3 tangent; // �ڋ��
	AliceMathF::Vector4 color; // ���_�F

	std::array<UINT, MAX_BONE_INDICES> boneIndex;	// �{�[���̔ԍ�
	std::array<float, MAX_BONE_INDICES> boneWeight;	// �{�[���̏d��
};

struct PosNormUvTangeCol
{
	AliceMathF::Vector4 position = { 0.0f,0.f,0.0f,1.0f }; // �ʒu���W
	AliceMathF::Vector3 normal; // �@��
	AliceMathF::Vector2 uv; // uv���W
	AliceMathF::Vector3 tangent; // �ڋ��
	AliceMathF::Vector4 color; // ���_�F
};

struct PosNormSkin
{
	AliceMathF::Vector4 position; // �ʒu���W
	AliceMathF::Vector3 normal; // �@��

	std::array<UINT, MAX_BONE_INDICES> boneIndex;	// �{�[���̔ԍ�
	std::array<float, MAX_BONE_INDICES> boneWeight;	// �{�[���̏d��
};

struct PosNorm
{
	AliceMathF::Vector4 position; // �ʒu���W
	AliceMathF::Vector3 normal; // �@��
};
//�萔�o�b�t�@�p�f�[�^�\����(�X�L�j���O)
struct SkinData
{
	std::vector<AliceMathF::Matrix4> bones;
};

struct SkinComputeInput
{
	std::vector<PosNormSkin> vertices;
	SkinData bone;
};

struct Node
{
	//���O
	std::string name;
	//���[�J���ό`�s��
	AliceMathF::Matrix4 transform;
	//�O���[�o���ό`�s��
	AliceMathF::Matrix4 globalTransform;
	//�e�m�[�h
	Node* parent = nullptr;
};

struct BoneData
{
	//�{�[���f�[�^
	std::array<AliceMathF::Matrix4, MAX_BONES> boneMat;
};

class ModelMesh
{
private:

public:

	//���O
	std::string name;

	//���O
	std::string nodeName;

	//���_�f�[�^�̔z��
	std::vector<PosNormUvTangeColSkin> vertices;

	//�C���f�b�N�X�̔z��
	std::vector<uint32_t> indices;

	//�e�N�X�`��
	std::vector <TextureData*> textures;

	//�e�N�X�`��
	std::vector <TextureData*> texturesNormal;

	std::unordered_map<std::string, Bone> bones;

	std::vector<Bone> vecBones;

	std::vector< AliceMathF::Matrix4> deformationMat;

	//�L��
	bool enable = false;
	char PADING[3]{};

	// �J���[
	float col[4] = { 1.0f,1.0f,1.0f,1.0f };
	char PADING1[4]{};

	// �}�e���A��
	ModelMaterial material;

	Node* node = nullptr;

	//���_�o�b�t�@
	std::shared_ptr<ComputeVertexBuffer> vertexBuffer;
	//�C���f�b�N�X�o�b�t�@
	std::shared_ptr<IndexBuffer> indexBuffer;
	//�}�e���A���o�b�t�@
	std::shared_ptr<ConstantBuffer> materialBuffer;
	//�{�[��
	std::shared_ptr<ConstantBuffer> constBoneBuffer;

	//�v�Z�V�F�[�_�[�p���_�f�[�^
	std::shared_ptr<StructuredBuffer> computeInputBuff;
	std::shared_ptr<ConstantBuffer> boneBuffer;

	//�`�撸�_�f�[�^
	std::vector<PosNormUvTangeCol> vertice;

	SkinComputeInput skinComputeInput;

	SkinData skinData;

	BoneData bonedata;

	bool dirtyFlag;

	ModelMesh() = default;
	~ModelMesh() = default;
public:

	/// <summary>
	/// �e��o�b�t�@�𐶐�
	/// </summary>
	void CreateBuffer();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList, Transform* transform, Light* light);

	void DrawBgin();

	void Update(ComputeRelation* computeRelation, ID3D12GraphicsCommandList* cmdList);

	void FillVertex();

	void InitializeVertex();

	void InitializeVertexPos();

	/// <summary>
	/// ���_���W���擾
	/// </summary>
	/// <returns>���_���W�z��</returns>
	const std::vector<PosNormUvTangeCol>GetVertices();

	/// <summary>
	/// �C���f�b�N�X���擾
	/// </summary>
	/// <returns>�C���f�b�N�X���W�z��</returns>
	const std::vector<uint32_t>GetIndices();

private:
};
#pragma once
#include"ModelMesh.h"
#include"fbxAnimation.h"
#include"StructuredBuffer.h"

//struct PosNormUvTangeCol
//{
//	AliceMathF::Vector3 position; // �ʒu���W
//	AliceMathF::Vector3 normal; // �@��
//	AliceMathF::Vector2 uv; // uv���W
//	AliceMathF::Vector3 tangent; // �ڋ��
//	AliceMathF::Vector4 color; // ���_�F
//};



class fbxModel:private Model
{

private:

	//���f����
	std::string name;
	//�m�[�h�z��
	std::vector<ModelMesh> meshes;

	//�t�����h�N���X
	friend class FbxLoader;

	std::unique_ptr<ConstantBuffer> postureMatBuff;

	static std::shared_ptr<ComputeRelation> computeRelation;

	const aiScene* mScene = nullptr;

	std::vector<Node> nodes;

	float oldFrame = 0.0f;

	AliceMathF::Matrix4 globalInverseTransform;
	char PADING[4]{};

	static Microsoft::WRL::ComPtr<ID3D12Device> device;
	static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList;
	Material* modelMaterialData;

	bool IsAnime = false;

	bool vertexInitialize = false;

public:

	fbxModel() = default;
	~fbxModel() = default;

	 void Initialize();

	 void Draw(Transform* transform, Material* material = nullptr);

	void AnimationUpdate(const fbxAnimation* animation, float frame);

	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	/// <param name="filePath">�I�u�W�F�N�g�܂ł̃t�@�C���p�X</param>
	void Create(const char* filePath, bool smoothing, bool inverseU = false, bool inverseV = false, bool animeFlag = false);

	static void CommonInitialize();

	bool TransTexture(const std::string& materialName, const std::string& textureName, TextureData* textureData);

	bool TransTexture(const std::string& materialName, size_t textureIndex, TextureData* textureData);

	bool FlipUV(const std::string& materialName,bool inverseU = false, bool inverseV = false);

	bool rotationUV(const std::string& materialName, float angle);
private:

	void ReadNodeHeirarchy(ModelMesh* mesh, const aiAnimation* pAnimation, float AnimationTime, const aiNode* pNode, const AliceMathF::Matrix4& mxParentTransform);
	aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std::string& strNodeName);
	void CalcInterpolatedScaling(AliceMathF::Vector3& mxOut, float AnimationTime, const aiNodeAnim* pNodeAnim);
	bool FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim, UINT& nScalingIndex);
	void CalcInterpolatedRotation(AliceMathF::Vector4& mxOut, float AnimationTime, const aiNodeAnim* pNodeAnim);
	bool FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim, UINT& nRotationIndex);
	void CalcInterpolatedPosition(AliceMathF::Vector3& mxOut, float AnimationTime, const aiNodeAnim* pNodeAnim);
	bool FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim, UINT& nPosIndex);

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	fbxModel& operator=(const fbxModel&) = delete;
	fbxModel(const fbxModel&) = delete;
};


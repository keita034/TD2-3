#pragma once
#include"ErrorException.h"
#include"ModelMesh.h"
#include"StructuredBuffer.h"
#include"AliceMotionData.h"

class AliceModel
{
private:

	//���C�g
	static Light* light;

	//���f����
	std::string name;
	bool canAnimation;

	//�m�[�h�z��
	std::vector<ModelMesh> meshes;

	//�t�����h�N���X
	friend class AliceFileLoad;

	friend class AliceFileStream;

	std::unique_ptr<ConstantBuffer> postureMatBuff;

	static std::unique_ptr<ComputeRelation> computeRelation;

	std::vector<Node> nodes;

	float oldFrame = 0.0f;

	AliceMathF::Matrix4 globalInverseTransform;
	char PADING1[4]{};

	static ID3D12Device* device;
	static ID3D12GraphicsCommandList* cmdList;
	Material* modelMaterialData;

	bool IsAnime = false;

	bool vertexInitialize = false;

	char PADING2[6]{};
public:

	AliceModel() = default;
	~AliceModel() = default;

	void Initialize();

	void Draw(Transform* transform, Material* material = nullptr);

	void AnimationUpdate(const AliceMotionData* animation, float frame);

	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	/// <param name="fileDirectoryPath">�I�u�W�F�N�g�܂ł̃t�@�C���p�X</param>
	void Create(const char* fileDirectoryPath);

	static void CommonInitialize();

	bool TransTexture(const std::string& materialName, const std::string& textureName, TextureData* textureData);

	bool TransTexture(const std::string& materialName, size_t textureIndex, TextureData* textureData);

	bool FlipUV(const std::string& materialName, bool inverseU = false, bool inverseV = false);

	bool rotationUV(const std::string& materialName, float angle);

	void InitializeVertex();

	const std::vector<ModelMesh>& GetMeshs();

private:

	void ReadNodeHeirarchy(ModelMesh* mesh, const AliceMotionData* pAnimation, float AnimationTime, const Node* pNode, const AliceMathF::Matrix4& mxParentTransform);
	const MotionNode* FindNodeAnim(const AliceMotionData* pAnimation, const std::string& strNodeName);
	void CalcInterpolatedScaling(AliceMathF::Vector3& mxOut, float AnimationTime, const MotionNode* pNodeAnim);
	bool FindScaling(float AnimationTime, const MotionNode* pNodeAnim, UINT& nScalingIndex);
	void CalcInterpolatedRotation(AliceMathF::Quaternion& mxOut, float AnimationTime, const MotionNode* pNodeAnim);
	bool FindRotation(float AnimationTime, const MotionNode* pNodeAnim, UINT& nRotationIndex);
	void CalcInterpolatedPosition(AliceMathF::Vector3& mxOut, float AnimationTime, const MotionNode* pNodeAnim);
	bool FindPosition(float AnimationTime, const MotionNode* pNodeAnim, UINT& nPosIndex);

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	AliceModel& operator=(const AliceModel&) = delete;
	AliceModel(const AliceModel&) = delete;
};


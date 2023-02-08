#pragma once
#include"ErrorException.h"
#include"ModelMesh.h"
#include"StructuredBuffer.h"
#include"AliceMotionData.h"

class AliceModelData
{
public:
	AliceModelData();
	~AliceModelData();

private:
	//�t�����h�N���X
	friend class AliceModel;
	friend class AliceFileStream;

	std::string filePath;

	uint32_t modelHandle;

	//���f����
	std::string name;

	//���b�V���z��
	std::vector<ModelMesh> meshes;

	//�p���s��
	std::unique_ptr<ConstantBuffer> postureMatBuff;

	//�m�[�h�z��
	std::vector<Node> nodes;

	AliceMathF::Matrix4 globalInverseTransform;

	//�A�j���[�V��������
	bool IsAnime = false;

	//���_�f�[�^������
	bool vertexInitialize = false;

	//�A�j���[�V�����ł��邩
	bool canAnimation = false;

};


class AliceModel
{
private:

	static ID3D12Device* device;
	static ID3D12GraphicsCommandList* cmdList;

	//���C�g
	static Light* light;

	//�R���s���[�g�V�F�[�_�֘A
	static std::unique_ptr<ComputeRelation> computeRelation;

	static std::vector<std::string>filePaths;

	static std::unordered_map<std::string, std::unique_ptr<AliceModelData>> modelDatas;

	static uint32_t modelCount;

	static const uint32_t maxModel = 1024;

	Material* modelMaterialData = nullptr;

	AliceModelData* modelData = nullptr;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	AliceModel() = default;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~AliceModel() = default;

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="transform">���[���h�ϊ��f�[�^</param>
	/// <param name="material">�}�e���A��(�p�C�v���C��)</param>
	void Draw(Transform* transform, Material* material = nullptr);

	/// <summary>
	/// �A�j���[�V�����̍X�V
	/// </summary>
	/// <param name="animation">�A�j���[�V�����f�[�^</param>
	/// <param name="frame">�t���[��</param>
	void AnimationUpdate(const AliceMotionData* animation, float frame);

	/// <summary>
	/// �e�N�X�`���̕ύX
	/// </summary>
	/// <param name="materialName">�}�e���A���̖��O</param>
	/// <param name="textureIndex">�e�N�X�`���̖��O</param>
	/// <param name="textureData">�e�N�X�`���f�[�^</param>
	/// <returns>�����������ǂ���</returns>
	bool TransTexture(const std::string& materialName, const std::string& textureName, TextureData* textureData);

	/// <summary>
	/// �e�N�X�`���̕ύX
	/// </summary>
	/// <param name="materialName">�}�e���A���̖��O</param>
	/// <param name="textureIndex">�e�N�X�`���̃C���f�b�N�X</param>
	/// <param name="textureData">�e�N�X�`���f�[�^</param>
	/// <returns>�����������ǂ���</returns>
	bool TransTexture(const std::string& materialName, size_t textureIndex, TextureData* textureData);

	/// <summary>
	/// UV���W�𔽓]
	/// </summary>
	/// <param name="materialName">�}�e���A���̖��O</param>
	/// <param name="inverseU">U���W</param>
	/// <param name="inverseV">V���W</param>
	/// <returns>�����������ǂ���</returns>
	bool FlipUV(const std::string& materialName, bool inverseU = false, bool inverseV = false);

	/// <summary>
	/// UV���W����]
	/// </summary>
	/// <param name="materialName">�}�e���A���̖��O</param>
	/// <param name="angle">�p�x</param>
	/// <returns>�����������ǂ���</returns>
	bool rotationUV(const std::string& materialName, float angle);

	/// <summary>
	/// ���_�f�[�^��������
	/// </summary>
	void InitializeVertex();

	/// <summary>
	/// ���b�V���z����擾
	/// </summary>
	/// <returns></returns>
	const std::vector<ModelMesh>& GetMeshs();

	/// <summary>
	/// ���f�����Z�b�g
	/// </summary>
	/// <param name="modelHandle">�n���h��</param>
	void SetModel(uint32_t modelHandle);

	/// <summary>
	/// ���C�g���Z�b�g(����)
	/// </summary>
	/// <param name="lightPtr">���C�g�̃|�C���^</param>
	static void SetLight(Light* lightPtr);

	/// <summary>
	/// ���f������
	/// </summary>
	/// <param name="filePath">�t�@�C���f�B���N�g��</param>
	/// <returns>�n���h��</returns>
	static uint32_t CreateModel(const std::string& fileDirectoryPath);

	/// <summary>
	/// ���ʏ�����
	/// </summary>
	static void CommonInitialize();

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


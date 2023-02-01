#pragma once
#include"ErrorException.h"
#include"AliceMathUtility.h"
#include"Camera.h"
#include"ConstantBuffer.h"
#include"VertexBuffer.h"
#include"AliceUtility.h"
#include"Material.h"

struct VerPosColScaRot
{
	AliceMathF::Vector3 pos;//���W
	AliceMathF::Vector4 color;//�J���[
	float scale;//�X�P�[��
	float rotation;//��]�p
};

struct ParticleConstBuffData
{
	AliceMathF::Matrix4 mat;
	AliceMathF::Matrix4 matBillboard;
};

//�p�[�e�B�N���f�[�^
struct ParticleData
{
	//���W
	AliceMathF::Vector3 position = {};
	//���x
	AliceMathF::Vector3 velocity = {};
	//�����x
	AliceMathF::Vector3 accel = {};

	//���݃t���[��
	UINT frame = 0;
	//�I���t���[��
	UINT numFrame = 0;

	//�X�P�[��
	float scale = 1.0f;
	//�����l
	float sScale = 1.0f;
	//�ŏI�l
	float eScale = 0.0f;

	//��]�p
	float rotation = 0.0f;
	//�����l
	float sRotation = 0.0f;
	//�ŏI�l
	float eRotation = 0.0f;

	//�J���[
	AliceMathF::Vector4 color = {1.0f,1.0f,1.0f,1.0f};
	//�����l
	AliceMathF::Vector4 sColor = { 1.0f,1.0f,1.0f,1.0f };
	//�ŏI�l
	AliceMathF::Vector4 eColor = { 1.0f,1.0f,1.0f,1.0f };
};

class BasicParticle;

class RainParticle;

class Particle
{
protected:
	HRESULT result;
	char PADDING[4];
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr <ID3D12GraphicsCommandList> cmdList = nullptr;

	//���_�o�b�t�@
	std::unique_ptr<VertexBuffer>vertexBuffer;
	//�萔�o�b�t�@
	std::unique_ptr<ConstantBuffer> constBuffTransform = nullptr;
	//�萔�o�b�t�@�̃}�b�s���O�p
	ParticleConstBuffData constMapTransform{};

	//�v���W�F�N�V�����s��
	AliceMathF::Matrix4 matProjection;
	//���_��
	const uint32_t vertexCount = 1024;
	char PADING[4];
	//�p�[�e�B�N���z��
	std::forward_list<ParticleData>particleDatas;

	Material* particleMaterial;

	TextureData* textureData;
public:

	Particle();

	virtual ~Particle();

	//������
	virtual void Initialize() = 0;

	///<summary>
	///�X�V
	///</summary>
	virtual void Update() = 0;

	///<summary>
	///�`��
	///</summary>
	virtual void Draw(Camera* camera, Material* material) = 0;

	/// <summary>
	/// �p�[�e�B�N���̒ǉ�
	/// </summary>
	/// <param name="life">��������</param>
	/// <param name="position">�������W</param>
	/// <param name="velocity">���x</param>
	/// <param name="accel">�����x</param>
	/// <param name="scale">{�J�n���X�P�[��,�I�����X�P�[��}</param>
	/// <param name="rotation">{�J�n����]�p,�I������]�p}</param>
	/// <param name="sColor">�J�n�J���[</param>
	/// <param name="eColor">�I���J���[</param>
	virtual void Add(
		UINT life, const AliceMathF::Vector3& position, const AliceMathF::Vector3& velocity,
		const AliceMathF::Vector3& accel, const AliceMathF::Vector2& scale, const AliceMathF::Vector2& rotation
		, const AliceMathF::Vector4& sColor, const AliceMathF::Vector4& eColor) = 0;

	static BasicParticle* CreateParticle();

	static RainParticle* CreateRainParticle();

	void SetTex(uint32_t handle);

protected:

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Particle& operator=(const Particle&) = delete;
	Particle(const Particle&) = delete;
};
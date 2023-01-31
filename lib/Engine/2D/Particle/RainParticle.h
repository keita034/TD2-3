#pragma once
#include"ErrorException.h"
#include"Particle.h"

class RainParticle : private Particle
{
private:

	AliceMathF::Matrix4 mTrans, mRot, mScale;

	AliceMathF::Vector2 particleScale = { 2.0f,0.0 };

	AliceMathF::Vector2 particleRotation = { 0.0f,0.0 };


public:

	RainParticle() = default;
	~RainParticle();

	//������
	virtual void Initialize()override;

	///<summary>
	///�X�V
	///</summary>
	virtual void Update(const AliceMathF::Vector3& centerPos, const AliceMathF::Vector2& emitRadius, const AliceMathF::Vector4& col, UINT lifeTime);


	///<summary>
	///�r���{�[�h�`��
	///</summary>
	virtual void Draw(Camera* camera, Material* material = nullptr);



private:

	virtual void Update()override;

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
		, const AliceMathF::Vector4& sColor, const AliceMathF::Vector4& eColor)override;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	RainParticle& operator=(const RainParticle&) = delete;
	RainParticle(const RainParticle&) = delete;
};


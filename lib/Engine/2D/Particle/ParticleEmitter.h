#pragma once
#include"ErrorException.h"
#include"AliceMathUtility.h"
#include"BasicParticle.h"

class ParticleEmitter
{
private:

	//��̍��W
	AliceMathF::Vector3 position = { 0,0,0 };
	//�J�n���J���[
	AliceMathF::Vector4 startColor = { 1.0f,0.0f,0.0f,1.0f };
	//�I�����J���[
	AliceMathF::Vector4 endColor = { 0.0f,0.0f,1.0f,1.0f };
	//��̉����x
	AliceMathF::Vector3 particleAccel = {0.0f, 0.001f ,0.0f};
	//��̑��x
	AliceMathF::Vector3 particleVelocity = { 0.1f,0.1f,0.1f };
	//�X�P�[��(�J�n���X�P�[��,�I�����X�P�[��)
	AliceMathF::Vector2 particleScale = {1.0f,0.0f};
	//��]�p(�J�n����]�p,�I������]�p)
	AliceMathF::Vector2 particleRotation = {0.0f,0.0f};

	//��̐�������
	UINT lifeTime = 50;
	//�ő唭���Ԋu
	size_t maxIntervalTime = 60;
	//�����Ԋu
	size_t intervalTime = 0;
	//��x�ɔ��������鐔
	size_t maxIndex = 50;

	//�p�[�e�B�N��
	std::unique_ptr<BasicParticle> particle;

	TextureData* textureData;

public:

	/// <summary>
	/// ��̍��W��ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const AliceMathF::Vector3& pos);

	/// <summary>
	/// �J�n���J���[��ݒ�
	/// </summary>
	/// <param name="color">�J���[</param>
	void SetStartColor(const AliceMathF::Vector4& color);

	/// <summary>
	/// �I�����J���[��ݒ�
	/// </summary>
	/// <param name="color">�J���[</param>
	void SetEndColor(const AliceMathF::Vector4& color);

	/// <summary>
	/// ��̉����x��ݒ�
	/// </summary>
	/// <param name="accel">�����x</param>
	void SetAccel(const AliceMathF::Vector3& accel);

	/// <summary>
	/// ��̑��x��ݒ�
	/// </summary>
	/// <param name="velocity">���x</param>
	void SetVelocity(const AliceMathF::Vector3& velocity);

	/// <summary>
	/// �X�P�[����ݒ�
	/// </summary>
	/// <param name="scale">(�J�n���X�P�[��,�I�����X�P�[��)</param>
	void SetScale(const AliceMathF::Vector2& scale);

	/// <summary>
	/// ��]�p��ݒ�
	/// </summary>
	/// <param name="rotation">(�J�n����]�p,�I������]�p)</param>
	void SetRotation(const AliceMathF::Vector2& rotation);

	/// <summary>
	/// �����Ԋu��ݒ�
	/// </summary>
	/// <param name="time">�����Ԋu</param>
	void SetIntervalTime(size_t time);

	/// <summary>
	/// ��̐������Ԃ�ݒ�
	/// </summary>
	/// <param name="time">��������</param>
	void SetLife(UINT time);

	/// <summary>
	/// ��x�ɔ��������鐔��ݒ�
	/// </summary>
	/// <param name="index">��x�ɔ��������鐔</param>
	void SetIndex(size_t index);

	void SetTex(uint32_t handle);

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void FireWorkUpdate();

	void BasicUpdate();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(Camera* camera, Material* material = nullptr);

	ParticleEmitter() = default;
	~ParticleEmitter() = default;

private:

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	ParticleEmitter& operator=(const ParticleEmitter&) = delete;
	ParticleEmitter(const ParticleEmitter&) = delete;
};


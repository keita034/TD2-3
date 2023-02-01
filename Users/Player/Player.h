#pragma once
#include"Transform.h"
#include"Camera.h"
#include"Model.h"
#include"Input.h"
#include"Vector3.h"
#include"BaseCollider.h"

class Player {

public:
	/// <summary>
	/// �ŏ��Ɏ����������
	/// </summary>
	/// <param name="modelHandl">���f���n���h��</param>
	Player(uint32_t modelHandl);

	/// <summary>
	/// ���Z�b�g�������̏���������
	/// </summary>
	void Initialise();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="camera"></param>
	void Update(Camera* camera);

	/// <summary>
	/// ���ۂ̕`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �v���C���[�̃W�����v
	/// </summary>
	void PlayerJump(Camera* camera);

	/// <summary>
	/// �v���C���[�̈ړ�
	/// </summary>
	void PlayerMove();

	/// <summary>
	/// �v���C���[�̓����蔻��
	/// </summary>
	void PlayerCollider(Camera* camera);

	void PlayerGravitie();

	AliceMathF::Vector3 GetPlayerPos() { return  AliceMathF::GetWorldPosition(worldTransform_); }

    Transform* GetWorldTransform() { return &worldTransform_; }

	AliceMathF::Vector3 bVelocity(AliceMathF::Vector3& velocity, Transform& worldTransform);

	AliceMathF::Vector3 Vector3Transform(const AliceMathF::Vector3& v, const AliceMathF::Matrix4& m);

	void SetCameraRot(AliceMathF::Matrix4 camera) { CameraRot = camera; }

private:

	Transform worldTransform_;
	std::unique_ptr<Model> model;
	Input* input_ = nullptr;

	int jumpFlag = 0;
	int jumpFrame = 0;
	float gravity = 9.0f;
	float playerJumpSpeed = 0;
	float playerSpeed = 0.5f;

	bool ground = false;

	// �R���C�_�[�̒ǉ�
	float radius = 0.3f;
	// �R���C�_�[
	BaseCollider* collider = nullptr;

	bool onGround = true;
	AliceMathF::Vector4 fallV;

	AliceMathF::Vector3 origin = { 0,0,0 };


	int playerSurfacePos = 0;

	int isPlayerNearCorner[6] = { 0 };

	AliceMathF::Matrix4 CameraRot;
};
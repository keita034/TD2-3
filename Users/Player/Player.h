#pragma once
#include"Transform.h"
#include"Camera.h"
#include"Model.h"
#include"Input.h"
#include"Vector3.h"
#include"BaseCollider.h"
#include"AliceModel.h"
#include"AliceMotionData.h"

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
	void PlayerMove(Camera* camera);

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
	void SetCameraRot(AliceMathF::Vector3 camera) { rot = camera; }

	int GetPlayerSurfacePos() { return playerSurfacePos; }

private:

	Transform worldTransform_;
	Transform modelWorldTransform_;
	std::unique_ptr<Model> model;

	std::unique_ptr<AliceModel> aliceModel;
	std::unique_ptr<AliceMotionData> walkMotion;


	Input* input_ = nullptr;

	int jumpFlag = 0;
	int jumpFrame = 0;
	float gravity = 9.0f;
	float playerJumpSpeed = 0;
	float playerSpeed = 0.5f;

	bool ground = false;

	// �R���C�_�[�̒ǉ�
	float radius = 2.0f;
	// �R���C�_�[
	BaseCollider* collider = nullptr;

	bool onGround = true;
	AliceMathF::Vector4 fallV;

	AliceMathF::Vector3 origin = { 0,0,0 };

	AliceMathF::Vector3 rot;

	int playerSurfacePos = 0;

	float frame;

	int isPlayerNearCorner[6] = { 0 };

	AliceMathF::Matrix4 CameraRot;

	AliceMathF::Vector3 PlayerSmoothMoving;

	int smoothMoving = 0;

	float size = 43.0f;
	float sizeX = 43.0f;
	float sizeYTop = 30.0f;
	float sizeYBottom = 54.0f;

	AliceMathF::Vector3 TopLeftTop = { -sizeX,sizeYTop,size };
	AliceMathF::Vector3 TopLeftBottom = { -sizeX,-sizeYBottom,-size };
	AliceMathF::Vector3 TopRightTop = { sizeX,sizeYTop,size };
	AliceMathF::Vector3 TopRightBottom = { sizeX,sizeYBottom,-size };

	AliceMathF::Vector3 RightTopRight = { sizeX,sizeYTop,size };
	AliceMathF::Vector3 RightTopLeft = { sizeX,sizeYTop,-size };
	AliceMathF::Vector3 RightBottomRight = { sizeX,-sizeYBottom,size };
	AliceMathF::Vector3 RightBottomLeft = { sizeX,-sizeYBottom,-size };

};
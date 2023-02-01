#pragma once
#include"Transform.h"
#include"Camera.h"
#include"Model.h"
#include"Input.h"
#include"Vector3.h"


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
	void PlayerJump();

	/// <summary>
	/// �v���C���[�̈ړ�
	/// </summary>
	void PlayerMove();

	AliceMathF::Vector3 Vector3Transform(const AliceMathF::Vector3& v, const AliceMathF::Matrix4& m);

	AliceMathF::Vector3 GetPlayerPos() { return  AliceMathF::GetWorldPosition(worldTransform_); }

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

	AliceMathF::Matrix4 CameraRot;
	
};
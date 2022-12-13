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

private:

	Transform worldTransform_;
	std::unique_ptr<Model> model;
	Input* input_ = nullptr;

	int jumpFlag = 0;
	int jumpFrame = 0;
	float gravity = 9.0f;
	float playerJumpSpeed = 0;
	float playerSpeed = 0.5f;
	
};
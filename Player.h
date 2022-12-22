#pragma once
#include"Transform.h"
#include"Camera.h"
#include"Model.h"
#include"Input.h"
#include"Vector3.h"

#include"CollisionInfo.h"

class Player {

public:
	/// <summary>
	/// �ŏ��Ɏ����������
	/// </summary>
	/// <param name="modelHandl">���f���n���h��</param>
	Player(uint32_t modelHandl);

	virtual ~Player();

	/// <summary>
	/// ���Z�b�g�������̏���������
	/// </summary>
	virtual void Initialise();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="camera"></param>
	virtual void Update(Camera* camera);

	/// <summary>
	/// ���ۂ̕`��
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// �v���C���[�̃W�����v
	/// </summary>
	void PlayerJump();

	/// <summary>
	/// �v���C���[�̈ړ�
	/// </summary>
	void PlayerMove();


	AliceMathF::Vector3 GetPlayerPos() { return  AliceMathF::GetWorldPosition(worldTransform_); }

	void SetCollider(BaseCollider* collider);

	virtual void OnCollision(const CollisionInfo& info){}

protected:
	//�N���X��(�f�o�b�N�p)
	const char* name = nullptr;

	//�R���C�_�[
	BaseCollider* collider = nullptr;


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
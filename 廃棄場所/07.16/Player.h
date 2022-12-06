#pragma once
#include"ModelInterface.h"
#include"ModelCreate.h"
#include"Camera.h"
#include"Input.h"
#include"AliceMath.h"

class Player
{
private:
	ModelInterface* model = nullptr;
	Input* input = nullptr;
	AliceMath::Vector3 move = {0,0,0};
	AliceMath::Vector3 rot;

	//�ڒn�t���O
	bool onGround = true;
	char PADDING2[3]{};
	//�����x�N�g��
	AliceMath::Vector3 fallV;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Player& operator=(const Player&) = delete;
	Player(const Player&) = delete;
public:

	Player() = default;
	~Player() = default;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void DrawModel(Camera* camera);
};


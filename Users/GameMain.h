#pragma once

//#DirectX�̂��
#include"ErrorException.h"


//����.h
#include"GameScene.h"
#include"AliceFramework.h"

class GameMain : public AliceFramework
{
private:

public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �I��
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	void Update() override;;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;;

	GameMain();
	~GameMain();
private:

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	GameMain& operator=(const GameMain&) = delete;
	GameMain(const GameMain&) = delete;
};


#pragma once

//#DirectX�̂��
#include"ErrorException.h"


//����.h
#include"GameScene.h"
#include"PostEffect.h"
#include"AliceFramework.h"

class GameMain : public AliceFramework
{
private:

	std::unique_ptr<PostEffect> postEffect;

	bool post = true;

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

};


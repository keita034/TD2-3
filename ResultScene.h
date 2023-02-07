#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "Input.h"

class ResultScene : public BaseScene
{
private:
	Input* input = nullptr;
	SceneManager* sceneManager = nullptr;

public:
	ResultScene() = default;
	~ResultScene() = default;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize() override;

private:
	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	ResultScene& operator=(const ResultScene&) = delete;
	ResultScene(const ResultScene&) = delete;
};


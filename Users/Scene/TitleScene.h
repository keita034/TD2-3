#pragma once
#include"BaseScene.h"
#include"SceneManager.h"
#include "ErrorException.h"
#include "TextureManager.h"
#include "Transform.h"
#include "Sprite2D.h"
#include "Input.h"

class TitleScene : public BaseScene
{
private:
	Input* input = nullptr;
	SceneManager* sceneManager = nullptr;

	std::unique_ptr<Sprite2D> spriteTitle_;
	uint32_t titleTex_;
	char PADDING[4];

	Transform spriteTransform;

public:

	TitleScene();
	~TitleScene();

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
	TitleScene& operator=(const TitleScene&) = delete;
	TitleScene(const TitleScene&) = delete;
};


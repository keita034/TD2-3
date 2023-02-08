#pragma once
#include"BaseScene.h"
#include "ErrorException.h"
#include "TextureManager.h"
#include "Transform.h"
#include "Sprite2D.h"
#include "Input.h"
#include "CinemaCamera.h"

#include "UserCamera.h"
#include "Stage.h"

class TitleScene : public BaseScene
{
private:
	Input* input = nullptr;

	std::unique_ptr<CinemaCamera> camera_;
	std::unique_ptr<UserCamera> userCamera_;
	int cameraType = 0;

	std::unique_ptr<Stage> stage_;

	std::unique_ptr<Sprite2D> spriteTitle_;
	uint32_t titleTex_ = 0;
	char PADDING[4];

	Transform spriteTransform;

public:

	TitleScene() = default;
	~TitleScene() = default;

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


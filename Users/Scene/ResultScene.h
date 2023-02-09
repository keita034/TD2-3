#pragma once
#include "BaseScene.h"
#include "Input.h"
#include"AudioManager.h"
#include "TextureManager.h"
#include "Sprite2D.h"
#include "Camera.h"
#include "Transform.h"
#include "AliceModel.h"
#include "AliceMotionData.h"

class ResultScene : public BaseScene
{
private:
	Input* input = nullptr;

	// �X�v���C�g
	std::unique_ptr<Sprite2D> sprite;
	uint32_t tex = 0;
	char PADDING[4];
	Transform transform;
	float frame = 0;
	
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


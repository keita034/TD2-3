#pragma once
#include"BaseScene.h"
#include "ErrorException.h"
#include "TextureManager.h"
#include "Sprite.h"

class TitleScene : public BaseScene
{
private:
	std::unique_ptr<Sprite> spriteTitle_;
	TextureData titleTex_;

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
};


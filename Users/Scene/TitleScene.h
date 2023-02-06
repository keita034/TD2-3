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
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize() override;
};


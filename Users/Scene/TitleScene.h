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

private:
	//コピーコンストラクタ・代入演算子削除
	TitleScene& operator=(const TitleScene&) = delete;
	TitleScene(const TitleScene&) = delete;
};


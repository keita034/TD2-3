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


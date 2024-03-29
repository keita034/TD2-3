#pragma once
#include "BaseScene.h"
#include "Input.h"
#include"AudioManager.h"

class ResultScene : public BaseScene
{
private:
	Input* input = nullptr;
	SceneManager* sceneManager = nullptr;

public:
	ResultScene() = default;
	~ResultScene() = default;

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
	ResultScene& operator=(const ResultScene&) = delete;
	ResultScene(const ResultScene&) = delete;
};


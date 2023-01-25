#pragma once

//#DirectXのやつ
#include"ErrorException.h"


//自作.h
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
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 終了
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	void Update() override;;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;;

};


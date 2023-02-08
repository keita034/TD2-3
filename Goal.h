#pragma once
#include"Transform.h"
#include"Camera.h"
#include"Model.h"


class Goal {

public:
	/// <summary>
	/// 最初に持たせるもの
	/// </summary>
	/// <param name="modelHandl">モデルハンドル</param>
	Goal(uint32_t modelHandl);

	/// <summary>
	/// リセットした時の初期化処理
	/// </summary>
	void Initialise();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="camera"></param>
	void Update(Camera* camera);

	/// <summary>
	/// 実際の描画
	/// </summary>
	void Draw();


	/// <summary>
	/// プレイヤーの当たり判定
	/// </summary>
	void Collider(Camera* camera);



private:

	Transform worldTransform_;
	std::unique_ptr<Model> model;

	// コライダーの追加
	float radius = 2.0f;
	// コライダー
	BaseCollider* collider = nullptr;
	
};
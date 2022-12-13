#pragma once
#include"Transform.h"
#include"Camera.h"
#include"Model.h"
#include"Input.h"
#include"Vector3.h"

class Player {

public:
	/// <summary>
	/// 最初に持たせるもの
	/// </summary>
	/// <param name="modelHandl">モデルハンドル</param>
	Player(uint32_t modelHandl);

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
	/// プレイヤーのジャンプ
	/// </summary>
	void PlayerJump();

	/// <summary>
	/// プレイヤーの移動
	/// </summary>
	void PlayerMove();

private:

	Transform worldTransform_;
	std::unique_ptr<Model> model;
	Input* input_ = nullptr;

	int jumpFlag = 0;
	int jumpFrame = 0;
	float gravity = 9.0f;
	float playerJumpSpeed = 0;
	float playerSpeed = 0.5f;
	
};
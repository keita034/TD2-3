#pragma once
#include"Transform.h"
#include"Camera.h"
#include"Model.h"
#include"Input.h"
#include"Vector3.h"

#include"CollisionInfo.h"

class Player {

public:
	/// <summary>
	/// 最初に持たせるもの
	/// </summary>
	/// <param name="modelHandl">モデルハンドル</param>
	Player(uint32_t modelHandl);

	virtual ~Player();

	/// <summary>
	/// リセットした時の初期化処理
	/// </summary>
	virtual void Initialise();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="camera"></param>
	virtual void Update(Camera* camera);

	/// <summary>
	/// 実際の描画
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// プレイヤーのジャンプ
	/// </summary>
	void PlayerJump();

	/// <summary>
	/// プレイヤーの移動
	/// </summary>
	void PlayerMove();


	AliceMathF::Vector3 GetPlayerPos() { return  AliceMathF::GetWorldPosition(worldTransform_); }

	void SetCollider(BaseCollider* collider);

	virtual void OnCollision(const CollisionInfo& info){}

protected:
	//クラス名(デバック用)
	const char* name = nullptr;

	//コライダー
	BaseCollider* collider = nullptr;


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
#pragma once
#include"Transform.h"
#include"Camera.h"
#include"Model.h"
#include"Input.h"
#include"Vector3.h"
#include"BaseCollider.h"

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
	void PlayerJump(Camera* camera);

	/// <summary>
	/// プレイヤーの移動
	/// </summary>
	void PlayerMove();

	/// <summary>
	/// プレイヤーの当たり判定
	/// </summary>
	void PlayerCollider(Camera* camera);

	void PlayerGravitie();

	AliceMathF::Vector3 GetPlayerPos() { return  AliceMathF::GetWorldPosition(worldTransform_); }

    Transform* GetWorldTransform() { return &worldTransform_; }

	AliceMathF::Vector3 bVelocity(AliceMathF::Vector3& velocity, Transform& worldTransform);

	AliceMathF::Vector3 Vector3Transform(const AliceMathF::Vector3& v, const AliceMathF::Matrix4& m);

	void SetCameraRot(AliceMathF::Matrix4 camera) { CameraRot = camera; }

private:

	Transform worldTransform_;
	std::unique_ptr<Model> model;
	Input* input_ = nullptr;

	int jumpFlag = 0;
	int jumpFrame = 0;
	float gravity = 9.0f;
	float playerJumpSpeed = 0;
	float playerSpeed = 0.5f;

	bool ground = false;

	// コライダーの追加
	float radius = 0.3f;
	// コライダー
	BaseCollider* collider = nullptr;

	bool onGround = true;
	AliceMathF::Vector4 fallV;

	AliceMathF::Vector3 origin = { 0,0,0 };


	int playerSurfacePos = 0;

	int isPlayerNearCorner[6] = { 0 };

	AliceMathF::Matrix4 CameraRot;
};
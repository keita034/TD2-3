#include"Player.h"
#include "SphereCollider.h"
#include "CollisionAttribute.h"
#include "CollisionManager.h"

Player::Player(uint32_t modelHandl) {

	model = std::make_unique<Model>();
	model->SetModel(modelHandl);

	input_ = Input::GetInstance();

	worldTransform_.Initialize();

	// コライダーの追加
	float radius = 0.6f;
	//worldTransform_.SetCollider(new SphereCollider(AliceMathF::Vector4(0, radius, 0, 0), radius));

	// コリジョンマネージャに追加
	collider = new SphereCollider(AliceMathF::Vector4(0, radius, 0, 0), radius);
	CollisionManager::GetInstance()->AddCollider(collider);



	collider->Update(worldTransform_.matWorld);
	collider->SetAttribute(COLLISION_ATTR_ALLIES);
}

void Player::Initialise(){

	worldTransform_.translation = { 0,50,0 };


}

void Player::Update(Camera* camera) {

	PlayerJump(camera);
	PlayerCollider(camera);
	PlayerMove();
	worldTransform_.TransUpdate(camera);
}

void Player::PlayerJump(Camera* camera) {

	// 落下処理
	if (!onGround) {
		// 下向き加速度
		const float fallAcc = -0.01f;
		const float fallVYMin = -0.5f;
		// 加速
		fallV.y = max(fallV.y + fallAcc, fallVYMin);
		// 移動
		worldTransform_.translation.x += fallV.x;
		worldTransform_.translation.y += fallV.y;
		worldTransform_.translation.z += fallV.z;
	}
	// ジャンプ操作
	else if (input_->TriggerPush(DIK_SPACE)) {
		onGround = false;
		const float jumpVYFist = 1.2f;
		fallV = { 0, jumpVYFist, 0, 0 };
	}

	worldTransform_.TransUpdate(camera);
	collider->Update(worldTransform_.matWorld);
}

void Player::PlayerMove() {

	AliceMathF::Vector3 playerMovement = { 0,0,0 };

	if (input_->KeepPush(DIK_W)) {
		playerMovement.z = playerSpeed;
	}
	if (input_->KeepPush(DIK_A)) {
		playerMovement.x = -playerSpeed;
	}
	if (input_->KeepPush(DIK_S)) {
		playerMovement.z = -playerSpeed;
	}
	if (input_->KeepPush(DIK_D)) {
		playerMovement.x = playerSpeed;
	}
	worldTransform_.translation += playerMovement;
}

void Player::PlayerCollider(Camera* camera)
{

	SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider);
	assert(sphereCollider);

	sphereCollider->SetRadius(0.5f);

	// クエリーコールバッククラス
	class PlayerQueryCallback : public QueryCallback
	{
	public:
		PlayerQueryCallback(Sphere* sphere) : sphere(sphere) {};

		// 衝突時コールバック関数
		bool OnQueryHit(const QueryHit& info) {

			const AliceMathF::Vector4 up = { 0,1,0,0 };

			AliceMathF::Vector4 rejectDir = info.reject;
			rejectDir.Normalization();
			rejectDir.Dot(up);
			float cos = rejectDir.y;

			// 地面判定しきい値
			const float threshold = cosf(DirectX::XMConvertToRadians(30.0f));

			if (-threshold < cos && cos < threshold) {
				sphere->center += info.reject;
				move += info.reject;
			}

			return true;
		}

		Sphere* sphere = nullptr;
		AliceMathF::Vector4 move = {};
	};

	PlayerQueryCallback callback(sphereCollider);

	// 球と地形の交差を全検索
	CollisionManager::GetInstance()->QuerySphere(*sphereCollider, &callback, COLLISION_ATTR_LANDSHAPE, &worldTransform_.matWorld);
	// 交差による排斥分動かす
	worldTransform_.translation.x += callback.move.x;
	worldTransform_.translation.y += callback.move.y;
	worldTransform_.translation.z += callback.move.z;
	// ワールド行列更新
	worldTransform_.TransUpdate(camera);
	collider->Update(worldTransform_.matWorld);

	//地面メッシュコライダー
	{
		// 球の上端から球の下端までのレイキャスト
		Ray Groundray;
		Groundray.start = sphereCollider->center;
		Groundray.start.y += sphereCollider->GetRadius();
		Groundray.dir = { 0,-1,0,0 };
		RaycastHit raycastHit;

		// 接地状態
		if (onGround) {
			// スムーズに坂を下る為の吸着距離
			const float adsDistance = 0.2f;
			// 接地を維持
			if (CollisionManager::GetInstance()->Raycast(Groundray, COLLISION_ATTR_LANDSHAPE, &raycastHit, sphereCollider->GetRadius() * 2.0f + adsDistance)) {
				onGround = true;
				worldTransform_.translation.y -= (raycastHit.distance - sphereCollider->GetRadius() * 2.0f);
			}
			// 地面がないので落下
			else {
				onGround = false;
				fallV = {};
			}
		}
		// 落下状態
		else if (fallV.y <= 0.0f) {
			if (CollisionManager::GetInstance()->Raycast(Groundray, COLLISION_ATTR_LANDSHAPE, &raycastHit, sphereCollider->GetRadius() * 2.0f)) {
				// 着地
				onGround = true;
				worldTransform_.translation.y -= (raycastHit.distance - sphereCollider->GetRadius() * 2.0f);
			}
		}
	}

	{
		//横メッシュコライダー
		Ray wall;
		wall.start = sphereCollider->center;
		wall.start.y += sphereCollider->GetRadius();
		wall.dir = { 0,0,1,0 };
		RaycastHit wallRaycastHit;
		// スムーズに坂を下る為の吸着距離
		const float adsDistance = 0.2f;

		// 接地を維持
		if (CollisionManager::GetInstance()->Raycast(wall, COLLISION_ATTR_LANDSHAPE, &wallRaycastHit, sphereCollider->GetRadius())) {
			worldTransform_.translation.z += (wallRaycastHit.distance - sphereCollider->GetRadius());
		}

	}

	{
		//横メッシュコライダー
		Ray wall;
		wall.start = sphereCollider->center;
		wall.start.y += sphereCollider->GetRadius();
		wall.dir = { 0,0,-1,0 };
		RaycastHit wallRaycastHit;
		// スムーズに坂を下る為の吸着距離
		const float adsDistance = 0.2f;

		// 接地を維持
		if (CollisionManager::GetInstance()->Raycast(wall, COLLISION_ATTR_LANDSHAPE, &wallRaycastHit, sphereCollider->GetRadius())) {
			worldTransform_.translation.z -= (wallRaycastHit.distance - sphereCollider->GetRadius());
		}

	}


	{
		//横メッシュコライダー
		Ray wall;
		wall.start = sphereCollider->center;
		wall.start.y += sphereCollider->GetRadius();
		wall.dir = { 1,0,0,0 };
		RaycastHit wallRaycastHit;
		// スムーズに坂を下る為の吸着距離
		const float adsDistance = 0.2f;

		// 接地を維持
		if (CollisionManager::GetInstance()->Raycast(wall, COLLISION_ATTR_LANDSHAPE, &wallRaycastHit, sphereCollider->GetRadius())) {
			worldTransform_.translation.x += (wallRaycastHit.distance - sphereCollider->GetRadius());
		}

	}

	{
		//横メッシュコライダー
		Ray wall;
		wall.start = sphereCollider->center;
		wall.start.y += sphereCollider->GetRadius();
		wall.dir = { -1,0,0,0 };
		RaycastHit wallRaycastHit;
		// スムーズに坂を下る為の吸着距離
		const float adsDistance = 0.2f;

		// 接地を維持
		if (CollisionManager::GetInstance()->Raycast(wall, COLLISION_ATTR_LANDSHAPE, &wallRaycastHit, sphereCollider->GetRadius())) {
			worldTransform_.translation.x -= (wallRaycastHit.distance - sphereCollider->GetRadius());
		}

	}

}

void Player::Draw() {

	model->Draw(worldTransform_);
}
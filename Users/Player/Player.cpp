#include"Player.h"
#include "SphereCollider.h"
#include "CollisionAttribute.h"
#include "CollisionManager.h"

Player::Player(uint32_t modelHandl) {

	model = std::make_unique<Model>();
	model->SetModel(modelHandl);

	input_ = Input::GetInstance();

	worldTransform_.Initialize();

	float a = 8.5f;

	worldTransform_.scale = { a,a,a };


	//worldTransform_.SetCollider(new SphereCollider(AliceMathF::Vector4(0, radius, 0, 0), radius));

	// コリジョンマネージャに追加
	collider = new SphereCollider(AliceMathF::Vector4(0, radius, 0, 0), radius);
	CollisionManager::GetInstance()->AddCollider(collider);



	collider->Update(worldTransform_.matWorld);
	collider->SetAttribute(COLLISION_ATTR_ALLIES);
}

void Player::Initialise() {

	worldTransform_.translation = { 0,100,0 };


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

		PlayerGravitie();

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

void Player::PlayerGravitie() {

	playerSurfacePos = 0;

	AliceMathF::Vector3 origin = { 0,0,0 };

	AliceMathF::Vector3 TopLeftTop = { -30.0f,30.0f,30.0f };
	AliceMathF::Vector3 TopLeftBottom = { -30.0f,30.0f,-30.0f };
	AliceMathF::Vector3 TopRightTop = { 30.0f,30.0f,30.0f };
	AliceMathF::Vector3 TopRightBottom = { 30.0f,30.0f,-30.0f };

	AliceMathF::Vector3 RightTopRight = { 30.0f,30.0f,30.0f };
	AliceMathF::Vector3 RightTopLeft = { 30.0f,30.0f,-30.0f };
	AliceMathF::Vector3 RightBottomRight = { 30.0f,-30.0f,30.0f };
	AliceMathF::Vector3 RightBottomLeft = { 30.0f,-30.0f,-30.0f };

	//どこの面にイルカ

	if (TopLeftTop.x < AliceMathF::GetWorldPosition(worldTransform_).x && AliceMathF::GetWorldPosition(worldTransform_).x < TopRightTop.x) {
		if (TopLeftTop.z > AliceMathF::GetWorldPosition(worldTransform_).z && AliceMathF::GetWorldPosition(worldTransform_).z > TopRightBottom.z) {
			if (origin.y < AliceMathF::GetWorldPosition(worldTransform_).y) {
				// 下向き加速度
				const float fallAcc = -0.01f;
				const float fallVYMin = -0.5f;
				// 加速
				fallV.x = 0;
				fallV.y = max(fallV.y + fallAcc, fallVYMin);
				fallV.z = 0;

				// 移動
				worldTransform_.translation.x += fallV.x;
				worldTransform_.translation.y += fallV.y;
				worldTransform_.translation.z += fallV.z;
			}
		}
	}
	else {
		// 移動
		worldTransform_.translation.x += fallV.x;
		worldTransform_.translation.y += fallV.y;
		worldTransform_.translation.z += fallV.z;
	}
	if (RightTopLeft.z < AliceMathF::GetWorldPosition(worldTransform_).z && AliceMathF::GetWorldPosition(worldTransform_).z < RightTopRight.z) {
		if (RightBottomRight.y < AliceMathF::GetWorldPosition(worldTransform_).y && AliceMathF::GetWorldPosition(worldTransform_).y < RightTopRight.y) {
			if (origin.x < AliceMathF::GetWorldPosition(worldTransform_).x) {
				// 横向き加速度
				const float fallAcc = -0.01f;
				const float fallVYMin = -0.5f;
				// 加速
				fallV.x = max(fallV.x + fallAcc, fallVYMin);
				fallV.y = 0;
				fallV.z = 0;

				// 移動
				worldTransform_.translation.x += fallV.x;
				worldTransform_.translation.y += fallV.y;
				worldTransform_.translation.z += fallV.z;
			}
		}
	}
	else {
		// 移動
		worldTransform_.translation.x += fallV.x;
		worldTransform_.translation.y += fallV.y;
		worldTransform_.translation.z += fallV.z;
	}
	if (TopLeftTop.x < AliceMathF::GetWorldPosition(worldTransform_).x && AliceMathF::GetWorldPosition(worldTransform_).x < TopRightTop.x) {
		if (TopLeftTop.z > AliceMathF::GetWorldPosition(worldTransform_).z && AliceMathF::GetWorldPosition(worldTransform_).z > TopRightBottom.z) {
			if (origin.y > AliceMathF::GetWorldPosition(worldTransform_).y) {
				// 上向き加速度
				const float fallAcc = 0.01f;
				const float fallVYMin = 0.5f;
				// 加速
				fallV.x = 0;
				fallV.y = max(fallV.y + fallAcc, fallVYMin);
				fallV.z = 0;

				// 移動
				worldTransform_.translation.x += fallV.x;
				worldTransform_.translation.y += fallV.y;
				worldTransform_.translation.z += fallV.z;
			}
		}
	}
	else {
		// 移動
		worldTransform_.translation.x += fallV.x;
		worldTransform_.translation.y += fallV.y;
		worldTransform_.translation.z += fallV.z;
	}
	if (RightTopLeft.z < AliceMathF::GetWorldPosition(worldTransform_).z && AliceMathF::GetWorldPosition(worldTransform_).z < RightTopRight.z) {
		if (RightBottomRight.y < AliceMathF::GetWorldPosition(worldTransform_).y && AliceMathF::GetWorldPosition(worldTransform_).y < RightTopRight.y) {
			if (origin.x > AliceMathF::GetWorldPosition(worldTransform_).x) {
				// 横向き加速度
				const float fallAcc = 0.01f;
				const float fallVYMin = 0.5f;
				// 加速
				fallV.x = max(fallV.x + fallAcc, fallVYMin);
				fallV.y = 0;
				fallV.z = 0;

				// 移動
				worldTransform_.translation.x += fallV.x;
				worldTransform_.translation.y += fallV.y;
				worldTransform_.translation.z += fallV.z;
			}
		}
	}
	else {
		// 移動
		worldTransform_.translation.x += fallV.x;
		worldTransform_.translation.y += fallV.y;
		worldTransform_.translation.z += fallV.z;
	}
	if (TopLeftTop.x < AliceMathF::GetWorldPosition(worldTransform_).x && TopRightTop.x > AliceMathF::GetWorldPosition(worldTransform_).x) {
		if (TopLeftTop.y > AliceMathF::GetWorldPosition(worldTransform_).y && TopLeftBottom.y < AliceMathF::GetWorldPosition(worldTransform_).y) {
			if (origin.z < AliceMathF::GetWorldPosition(worldTransform_).z) {
				// 横向き加速度
				const float fallAcc = -0.01f;
				const float fallVYMin = -0.5f;
				// 加速
				fallV.x = 0;
				fallV.y = 0;
				fallV.z = max(fallV.z + fallAcc, fallVYMin);

				// 移動
				worldTransform_.translation.x += fallV.x;
				worldTransform_.translation.y += fallV.y;
				worldTransform_.translation.z += fallV.z;
			}
		}
	}
	else {
		// 移動
		worldTransform_.translation.x += fallV.x;
		worldTransform_.translation.y += fallV.y;
		worldTransform_.translation.z += fallV.z;
	}
	if (TopLeftTop.x < AliceMathF::GetWorldPosition(worldTransform_).x && TopRightTop.x > AliceMathF::GetWorldPosition(worldTransform_).x) {
		if (TopLeftTop.y > AliceMathF::GetWorldPosition(worldTransform_).y && TopLeftBottom.y < AliceMathF::GetWorldPosition(worldTransform_).y) {
			if (origin.z > AliceMathF::GetWorldPosition(worldTransform_).z) {
				// 横向き加速度
				const float fallAcc = 0.01f;
				const float fallVYMin = 0.5f;
				// 加速
				fallV.x = 0;
				fallV.y = 0;
				fallV.z = max(fallV.z + fallAcc, fallVYMin);

				// 移動
				worldTransform_.translation.x += fallV.x;
				worldTransform_.translation.y += fallV.y;
				worldTransform_.translation.z += fallV.z;
			}
		}
	}
	else {
		// 移動
		worldTransform_.translation.x += fallV.x;
		worldTransform_.translation.y += fallV.y;
		worldTransform_.translation.z += fallV.z;
	}



	//if (TopLeftTop.y < AliceMathF::GetWorldPosition(worldTransform_).y) {
	//	// 下向き加速度
	//	const float fallAcc = -0.01f;
	//	const float fallVYMin = -0.5f;
	//	// 加速
	//	fallV.x = 0;
	//	fallV.y = max(fallV.y + fallAcc, fallVYMin);
	//	fallV.z = 0;

	//	// 移動
	//	worldTransform_.translation.x += fallV.x;
	//	worldTransform_.translation.y += fallV.y;
	//	worldTransform_.translation.z += fallV.z;
	//}

	//if (TopRightTop.x < AliceMathF::GetWorldPosition(worldTransform_).x) {
	//	// 横向き加速度
	//	const float fallAcc = -0.01f;
	//	const float fallVYMin = -0.5f;
	//	// 加速
	//	fallV.x = max(fallV.x + fallAcc, fallVYMin);
	//	fallV.y = 0;
	//	fallV.z = 0;

	//	// 移動
	//	worldTransform_.translation.x += fallV.x;
	//	worldTransform_.translation.y += fallV.y;
	//	worldTransform_.translation.z += fallV.z;
	//}

	//if (RightBottomRight.y > AliceMathF::GetWorldPosition(worldTransform_).y) {
	//	// 上向き加速度
	//	const float fallAcc = 0.01f;
	//	const float fallVYMin = 0.5f;
	//	// 加速
	//	fallV.x = 0;
	//	fallV.y = max(fallV.y + fallAcc, fallVYMin);
	//	fallV.z = 0;

	//	// 移動
	//	worldTransform_.translation.x += fallV.x;
	//	worldTransform_.translation.y += fallV.y;
	//	worldTransform_.translation.z += fallV.z;
	//}

	//if (TopLeftTop.x > AliceMathF::GetWorldPosition(worldTransform_).x) {
	//	// 横向き加速度
	//	const float fallAcc = 0.01f;
	//	const float fallVYMin = 0.5f;
	//	// 加速
	//	fallV.x = max(fallV.x + fallAcc, fallVYMin);
	//	fallV.y = 0;
	//	fallV.z = 0;

	//	// 移動
	//	worldTransform_.translation.x += fallV.x;
	//	worldTransform_.translation.y += fallV.y;
	//	worldTransform_.translation.z += fallV.z;
	//}

	//if (RightTopRight.z < AliceMathF::GetWorldPosition(worldTransform_).z) {
	//	// 横向き加速度
	//	const float fallAcc = -0.01f;
	//	const float fallVYMin = -0.5f;
	//	// 加速
	//	fallV.x = 0;
	//	fallV.y = 0;
	//	fallV.z = max(fallV.z + fallAcc, fallVYMin);

	//	// 移動
	//	worldTransform_.translation.x += fallV.x;
	//	worldTransform_.translation.y += fallV.y;
	//	worldTransform_.translation.z += fallV.z;
	//}

	//if (RightTopLeft.z > AliceMathF::GetWorldPosition(worldTransform_).z) {
	//	// 横向き加速度
	//	const float fallAcc = 0.01f;
	//	const float fallVYMin = 0.5f;
	//	// 加速
	//	fallV.x = 0;
	//	fallV.y = 0;
	//	fallV.z = max(fallV.z + fallAcc, fallVYMin);

	//	// 移動
	//	worldTransform_.translation.x += fallV.x;
	//	worldTransform_.translation.y += fallV.y;
	//	worldTransform_.translation.z += fallV.z;
	//}

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

	sphereCollider->SetRadius(radius);

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
				ground = true;
				worldTransform_.translation.y -= (raycastHit.distance - sphereCollider->GetRadius() * 2.0f);
			}
			// 地面がないので落下
			else {
				ground = true;
				onGround = false;
				fallV = {};
			}
		}
		// 落下状態
		else if (fallV.y <= 0.0f) {
			if (CollisionManager::GetInstance()->Raycast(Groundray, COLLISION_ATTR_LANDSHAPE, &raycastHit, sphereCollider->GetRadius() * 2.0f)) {
				// 着地
				onGround = true;
				ground = true;
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
		//const float adsDistance = 0.2f;

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
		//const float adsDistance = 0.2f;

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
		//const float adsDistance = 0.2f;

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
		//const float adsDistance = 0.2f;

		// 接地を維持
		if (CollisionManager::GetInstance()->Raycast(wall, COLLISION_ATTR_LANDSHAPE, &wallRaycastHit, sphereCollider->GetRadius())) {
			worldTransform_.translation.x -= (wallRaycastHit.distance - sphereCollider->GetRadius());
		}

	}

}

void Player::Draw() {

	model->Draw(worldTransform_);
}

AliceMathF::Vector3 Player::bVelocity(AliceMathF::Vector3& velocity, Transform& worldTransform) {

	AliceMathF::Vector3 result = { 0, 0, 0 };

	result.x = velocity.x * worldTransform.matWorld.m[0][0] +
		velocity.y * worldTransform.matWorld.m[1][0] +
		velocity.z * worldTransform.matWorld.m[2][0];

	result.y = velocity.x * worldTransform.matWorld.m[0][1] +
		velocity.y * worldTransform.matWorld.m[1][1] +
		velocity.z * worldTransform.matWorld.m[2][1];

	result.z = velocity.x * worldTransform.matWorld.m[0][2] +
		velocity.y * worldTransform.matWorld.m[1][2] +
		velocity.z * worldTransform.matWorld.m[2][2];


	return result;
}

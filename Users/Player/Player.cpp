#include"Player.h"
#include "SphereCollider.h"
#include "CollisionAttribute.h"
#include "CollisionManager.h"

Player::Player(uint32_t modelHandl)
{

	input_ = Input::GetInstance();

	worldTransform_.Initialize();


	float PlayerScale = 8.5f;

	worldTransform_.scale = { PlayerScale,PlayerScale,PlayerScale };


	//worldTransform_.SetCollider(new SphereCollider(AliceMathF::Vector4(0, radius, 0, 0), radius));

	// �R���W�����}�l�[�W���ɒǉ�
	collider = new SphereCollider(AliceMathF::Vector4(0, radius, 0, 0), radius);
	CollisionManager::GetInstance()->AddCollider(collider);

	uint32_t handl = AliceModel::CreateModel("Resources/Kaede/model");

	aliceModel = std::make_unique<AliceModel>();
	aliceModel->SetModel(handl);

	handl = AliceMotionData::CreateMotion("Resources/Kaede/walk");
	walkMotion = std::make_unique<AliceMotionData>();
	walkMotion->SetMotion(handl);

	handl = AliceMotionData::CreateMotion("Resources/Kaede/stand");
	standMotion = std::make_unique<AliceMotionData>();
	standMotion->SetMotion(handl);

	worldTransform_.translation = { 90,-30,0 };

	//worldTransform_.translation = { -80,0,0 };

	collider->Update(worldTransform_.matWorld);
	collider->SetAttribute(COLLISION_ATTR_ALLIES);
}

void Player::Initialise()
{



}

void Player::Update(Camera* camera)
{

	frame += 0.017f;

	PlayerJump(camera);
	PlayerCollider(camera);
	PlayerMove(camera);
	worldTransform_.TransUpdate(camera);
	worldTransform_.translation;
	worldTransform_.scale = { 0.1,0.1,0.1 };
	if (topORbottom == 1)
	{
		rot = { 0,rot.y,rot.z };
	}
	if (playerSideMove == 1)
	{
		rot = { 0,0,rot.z };
	}
	worldTransform_.rotation = rot + worldTransform_.rotation;
	worldTransform_.TransUpdate(camera);

	if (isWalk)
	{
		aliceModel->AnimationUpdate(walkMotion.get(), frame);
	}
	else
	{
		aliceModel->AnimationUpdate(standMotion.get(), frame);
	}

}

void Player::PlayerJump(Camera* camera)
{

// ��������

	PlayerGravitie();

	//// �W�����v����
	//if (input_->TriggerPush(DIK_SPACE)) {
	//	const float jumpVYFist = 0.5f;
	//	worldTransform_.translation.y += jumpVYFist;
	//}

	worldTransform_.TransUpdate(camera);
	collider->Update(worldTransform_.matWorld);
}

void Player::PlayerGravitie()
{

	AliceMathF::Vector3 origin = { 0,0,0 };


	//�ǂ��̖ʂɃC���J

	if (TopLeftTop.x < AliceMathF::GetWorldPosition(worldTransform_).x && AliceMathF::GetWorldPosition(worldTransform_).x < TopRightTop.x)
	{
		if (TopLeftTop.z > AliceMathF::GetWorldPosition(worldTransform_).z && AliceMathF::GetWorldPosition(worldTransform_).z > TopRightBottom.z)
		{
			if (TopLeftTop.y < AliceMathF::GetWorldPosition(worldTransform_).y)
			{

				playerSurfacePos = 0;
			}
		}
	}
	if (RightTopLeft.z < AliceMathF::GetWorldPosition(worldTransform_).z && AliceMathF::GetWorldPosition(worldTransform_).z < RightTopRight.z)
	{
		if (RightBottomRight.y < AliceMathF::GetWorldPosition(worldTransform_).y && AliceMathF::GetWorldPosition(worldTransform_).y < RightTopRight.y)
		{
			if (TopRightTop.x < AliceMathF::GetWorldPosition(worldTransform_).x)
			{

				playerSurfacePos = 1;
			}
		}
	}
	if (TopLeftTop.x < AliceMathF::GetWorldPosition(worldTransform_).x && AliceMathF::GetWorldPosition(worldTransform_).x < TopRightTop.x)
	{
		if (TopLeftTop.z > AliceMathF::GetWorldPosition(worldTransform_).z && AliceMathF::GetWorldPosition(worldTransform_).z > TopRightBottom.z)
		{
			if (RightBottomRight.y > AliceMathF::GetWorldPosition(worldTransform_).y)
			{

				playerSurfacePos = 2;
			}
		}
	}
	if (RightTopLeft.z < AliceMathF::GetWorldPosition(worldTransform_).z && AliceMathF::GetWorldPosition(worldTransform_).z < RightTopRight.z)
	{
		if (RightBottomRight.y < AliceMathF::GetWorldPosition(worldTransform_).y && AliceMathF::GetWorldPosition(worldTransform_).y < RightTopRight.y)
		{
			if (TopLeftTop.x > AliceMathF::GetWorldPosition(worldTransform_).x)
			{

				playerSurfacePos = 3;
			}
		}
	}
	if (TopLeftTop.x < AliceMathF::GetWorldPosition(worldTransform_).x && TopRightTop.x > AliceMathF::GetWorldPosition(worldTransform_).x)
	{
		if (TopLeftTop.y > AliceMathF::GetWorldPosition(worldTransform_).y && TopLeftBottom.y < AliceMathF::GetWorldPosition(worldTransform_).y)
		{
			if (RightTopRight.z < AliceMathF::GetWorldPosition(worldTransform_).z)
			{

				playerSurfacePos = 4;
			}
		}
	}
	if (TopLeftTop.x < AliceMathF::GetWorldPosition(worldTransform_).x && TopRightTop.x > AliceMathF::GetWorldPosition(worldTransform_).x)
	{
		if (TopLeftTop.y > AliceMathF::GetWorldPosition(worldTransform_).y && TopLeftBottom.y < AliceMathF::GetWorldPosition(worldTransform_).y)
		{
			if (RightTopLeft.z > AliceMathF::GetWorldPosition(worldTransform_).z)
			{

				playerSurfacePos = 5;
			}
		}
	}


	if (TopLeftTop.y < AliceMathF::GetWorldPosition(worldTransform_).y)
	{
// �����������x
		const float fallAcc = -0.01f;
		const float fallVYMin = -0.5f;
		// ����
		fallV.x = 0;
		fallV.y = max(fallV.y + fallAcc, fallVYMin);
		fallV.z = 0;

		// �ړ�
		worldTransform_.translation.x += fallV.x;
		worldTransform_.translation.y += fallV.y;
		worldTransform_.translation.z += fallV.z;

		//playerSurfacePos = 0;
	}

	if (TopRightTop.x < AliceMathF::GetWorldPosition(worldTransform_).x)
	{

// �����������x
		const float fallAcc = -0.01f;
		const float fallVYMin = -0.5f;
		// ����
		fallV.x = max(fallV.x + fallAcc, fallVYMin);
		fallV.y = 0;
		fallV.z = 0;

		// �ړ�
		worldTransform_.translation.x += fallV.x;
		worldTransform_.translation.y += fallV.y;
		worldTransform_.translation.z += fallV.z;

		//playerSurfacePos = 1;

	}

	if (RightBottomRight.y > AliceMathF::GetWorldPosition(worldTransform_).y)
	{
// ����������x
		const float fallAcc = 0.01f;
		const float fallVYMin = 0.5f;
		// ����
		fallV.x = 0;
		fallV.y = max(fallV.y + fallAcc, fallVYMin);
		fallV.z = 0;

		// �ړ�
		worldTransform_.translation.x += fallV.x;
		worldTransform_.translation.y += fallV.y;
		worldTransform_.translation.z += fallV.z;

		//playerSurfacePos = 2;
	}

	if (TopLeftTop.x > AliceMathF::GetWorldPosition(worldTransform_).x)
	{
// �����������x
		const float fallAcc = 0.01f;
		const float fallVYMin = 0.5f;
		// ����
		fallV.x = max(fallV.x + fallAcc, fallVYMin);
		fallV.y = 0;
		fallV.z = 0;

		// �ړ�
		worldTransform_.translation.x += fallV.x;
		worldTransform_.translation.y += fallV.y;
		worldTransform_.translation.z += fallV.z;

		//playerSurfacePos = 3;
	}

	if (RightTopRight.z < AliceMathF::GetWorldPosition(worldTransform_).z)
	{
// �����������x
		const float fallAcc = -0.01f;
		const float fallVYMin = -0.5f;
		// ����
		fallV.x = 0;
		fallV.y = 0;
		fallV.z = max(fallV.z + fallAcc, fallVYMin);

		// �ړ�
		worldTransform_.translation.x += fallV.x;
		worldTransform_.translation.y += fallV.y;
		worldTransform_.translation.z += fallV.z;

		//playerSurfacePos = 4;
	}

	if (RightTopLeft.z > AliceMathF::GetWorldPosition(worldTransform_).z)
	{
// �����������x
		const float fallAcc = 0.01f;
		const float fallVYMin = 0.5f;
		// ����
		fallV.x = 0;
		fallV.y = 0;
		fallV.z = max(fallV.z + fallAcc, fallVYMin);

		// �ړ�
		worldTransform_.translation.x += fallV.x;
		worldTransform_.translation.y += fallV.y;
		worldTransform_.translation.z += fallV.z;

		//playerSurfacePos = 5;
	}

}

void Player::PlayerMove(Camera* camera)
{

	AliceMathF::Vector3 playerMovement = { 0,0,0 };

	topORbottom = 0;
	playerSideMove = 0;

	isWalk = false;

	if (input_->KeepPush(DIK_W))
	{
		isWalk = true;
	}
	else if (input_->KeepPush(DIK_A))
	{
		isWalk = true;
	}
	else if (input_->KeepPush(DIK_S))
	{
		isWalk = true;
	}
	else if (input_->KeepPush(DIK_D))
	{
		isWalk = true;
	}


	if (playerSurfacePos == 0)
	{
		if (input_->KeepPush(DIK_W))
		{
			playerMovement.z = -playerSpeed;
			worldTransform_.rotation = { 0,0,0 };
		}
		else if (input_->KeepPush(DIK_A))
		{
			playerMovement.x = playerSpeed;
			worldTransform_.rotation = { 0,-90 * AliceMathF::Deg2Rad,0 };
		}
		else if (input_->KeepPush(DIK_S))
		{
			playerMovement.z = playerSpeed;
			worldTransform_.rotation = { 0,180 * AliceMathF::Deg2Rad,0 };
		}
		else if (input_->KeepPush(DIK_D))
		{
			playerMovement.x = -playerSpeed;
			worldTransform_.rotation = { 0,90 * AliceMathF::Deg2Rad,0 };
		}
		topORbottom = 1;
	}
	else if (playerSurfacePos == 1)
	{
		if (RightBottomRight.y < AliceMathF::GetWorldPosition(worldTransform_).y && AliceMathF::GetWorldPosition(worldTransform_).y < RightTopRight.y)
		{
			if (input_->KeepPush(DIK_W))
			{
				playerMovement.y = playerSpeed;
				worldTransform_.rotation = { 90 * AliceMathF::Deg2Rad,90 * AliceMathF::Deg2Rad,0 };
			}
			else if (input_->KeepPush(DIK_A))
			{
				playerMovement.x = playerSpeed;
				worldTransform_.rotation = { 0 * AliceMathF::Deg2Rad,0,-90 * AliceMathF::Deg2Rad };
			}
			else if (input_->KeepPush(DIK_S))
			{
				playerMovement.y = -playerSpeed;
				worldTransform_.rotation = { -90 * AliceMathF::Deg2Rad,-90 * AliceMathF::Deg2Rad,0 };
			}
			else if (input_->KeepPush(DIK_D))
			{
				playerMovement.x = -playerSpeed;
				worldTransform_.rotation = { 180 * AliceMathF::Deg2Rad,0,-90 * AliceMathF::Deg2Rad };
			}
			playerSideMove = 1;
		}
	}
	else if (playerSurfacePos == 2)
	{
		if (input_->KeepPush(DIK_W))
		{
			playerMovement.z = playerSpeed;
			worldTransform_.rotation = { 0,180 * AliceMathF::Deg2Rad,180 * AliceMathF::Deg2Rad };
		}
		else if (input_->KeepPush(DIK_A))
		{
			playerMovement.x = playerSpeed;
			worldTransform_.rotation = { 0,-90 * AliceMathF::Deg2Rad,180 * AliceMathF::Deg2Rad };
		}
		else if (input_->KeepPush(DIK_S))
		{
			playerMovement.z = -playerSpeed;
			worldTransform_.rotation = { 0,0,180 * AliceMathF::Deg2Rad };
		}
		else if (input_->KeepPush(DIK_D))
		{
			playerMovement.x = -playerSpeed;
			worldTransform_.rotation = { 0,90 * AliceMathF::Deg2Rad,180 * AliceMathF::Deg2Rad };
		}
		topORbottom = 1;
	}
	else if (playerSurfacePos == 3)
	{
		if (RightBottomRight.y < AliceMathF::GetWorldPosition(worldTransform_).y && AliceMathF::GetWorldPosition(worldTransform_).y < RightTopRight.y)
		{
			if (input_->KeepPush(DIK_W))
			{
				playerMovement.y = playerSpeed;
				worldTransform_.rotation = { 90 * AliceMathF::Deg2Rad,-90 * AliceMathF::Deg2Rad,0 };
			}
			else if (input_->KeepPush(DIK_A))
			{
				playerMovement.x = playerSpeed;
				worldTransform_.rotation = { 180 * AliceMathF::Deg2Rad,0,90 * AliceMathF::Deg2Rad };
			}
			else if (input_->KeepPush(DIK_S))
			{
				playerMovement.y = -playerSpeed;
				worldTransform_.rotation = { -90 * AliceMathF::Deg2Rad,90 * AliceMathF::Deg2Rad,0 };
			}
			else if (input_->KeepPush(DIK_D))
			{
				playerMovement.x = -playerSpeed;
				worldTransform_.rotation = { 0,0,90 * AliceMathF::Deg2Rad };
			}
			playerSideMove = 1;
		}

	}
	else if (playerSurfacePos == 4)
	{//��
		if (RightBottomRight.y < AliceMathF::GetWorldPosition(worldTransform_).y && AliceMathF::GetWorldPosition(worldTransform_).y < RightTopRight.y)
		{
			if (input_->KeepPush(DIK_W))
			{
				playerMovement.y = playerSpeed;
				worldTransform_.rotation = { 90 * AliceMathF::Deg2Rad,0,0 };
			}
			else if (input_->KeepPush(DIK_A))
			{
				playerMovement.x = playerSpeed;
				worldTransform_.rotation = { 0,-90 * AliceMathF::Deg2Rad,-90 * AliceMathF::Deg2Rad };
			}
			else if (input_->KeepPush(DIK_S))
			{
				playerMovement.y = -playerSpeed;
				worldTransform_.rotation = { -90 * AliceMathF::Deg2Rad,0,180 * AliceMathF::Deg2Rad };
			}
			else if (input_->KeepPush(DIK_D))
			{
				playerMovement.x = -playerSpeed;
				worldTransform_.rotation = { 0,90 * AliceMathF::Deg2Rad,90 * AliceMathF::Deg2Rad };
			}
			playerSideMove = 1;
		}
	}
	else if (playerSurfacePos == 5)
	{
		if (input_->KeepPush(DIK_W))
		{
			playerMovement.y = playerSpeed;
			worldTransform_.rotation = { 90 * AliceMathF::Deg2Rad,180 * AliceMathF::Deg2Rad,0 };
		}
		else if (input_->KeepPush(DIK_A))
		{
			playerMovement.x = playerSpeed;
			worldTransform_.rotation = { 0,90 * AliceMathF::Deg2Rad,-90 * AliceMathF::Deg2Rad };
		}
		else if (input_->KeepPush(DIK_S))
		{
			playerMovement.y = -playerSpeed;
			worldTransform_.rotation = { -90 * AliceMathF::Deg2Rad,0,0 };
		}
		else if (input_->KeepPush(DIK_D))
		{
			playerMovement.x = -playerSpeed;
			worldTransform_.rotation = { 0,-90 * AliceMathF::Deg2Rad,90 * AliceMathF::Deg2Rad };
		}
		playerSideMove = 1;
	}


	if (input_->KeepPush(DIK_UP))
	{
		playerMovement.y = playerSpeed;
	}
	if (input_->KeepPush(DIK_DOWN))
	{
		playerMovement.y = -playerSpeed;
	}


	playerMovement = Vector3Transform(playerMovement, CameraRot);
	if (playerSurfacePos == 0)
	{
		playerMovement.y = 0;

	}
	else if (playerSurfacePos == 1)
	{
		playerMovement.x = 0;

	}
	else if (playerSurfacePos == 2)
	{
		playerMovement.y = 0;
	}
	else if (playerSurfacePos == 3)
	{
		playerMovement.x = 0;
	}
	else if (playerSurfacePos == 4)
	{
		playerMovement.z = 0;
	}
	else
	{
		playerMovement.z = 0;
	}
	PlayerSmoothMoving = worldTransform_.translation;

	worldTransform_.translation += playerMovement;
	worldTransform_.TransUpdate(camera);

	//����
	if (TopRightTop.x < AliceMathF::GetWorldPosition(worldTransform_).x)
	{
		if (playerSurfacePos == 0)
		{
			worldTransform_.translation.x = PlayerSmoothMoving.x;
			worldTransform_.translation.y = PlayerSmoothMoving.y;
			worldTransform_.translation.z = PlayerSmoothMoving.z;
			playerMovement.x = 0;

			if (input_->KeepPush(DIK_S))
			{
				playerMovement.y = -playerSpeed;
				playerSurfacePos = 1;
			}
			worldTransform_.translation += playerMovement;
		}
	}
	if (RightTopRight.z < AliceMathF::GetWorldPosition(worldTransform_).z)
	{
		if (playerSurfacePos == 0)
		{
			worldTransform_.translation.x = PlayerSmoothMoving.x;
			worldTransform_.translation.y = PlayerSmoothMoving.y;
			worldTransform_.translation.z = PlayerSmoothMoving.z;
			playerMovement.z = 0;

			if (input_->KeepPush(DIK_S))
			{
				playerMovement.y = -playerSpeed;
				playerSurfacePos = 4;
			}
			worldTransform_.translation += playerMovement;
		}
	}
	if (TopLeftTop.x > AliceMathF::GetWorldPosition(worldTransform_).x)
	{
		if (playerSurfacePos == 0)
		{
			worldTransform_.translation.x = PlayerSmoothMoving.x;
			worldTransform_.translation.y = PlayerSmoothMoving.y;
			worldTransform_.translation.z = PlayerSmoothMoving.z;
			playerMovement.x = 0;

			if (input_->KeepPush(DIK_S))
			{
				playerMovement.y = -playerSpeed;
				playerSurfacePos = 3;
			}
			worldTransform_.translation += playerMovement;
		}
	}
	if (RightTopLeft.z > AliceMathF::GetWorldPosition(worldTransform_).z)
	{
		if (playerSurfacePos == 0)
		{
			worldTransform_.translation.x = PlayerSmoothMoving.x;
			worldTransform_.translation.y = PlayerSmoothMoving.y;
			worldTransform_.translation.z = PlayerSmoothMoving.z;
			playerMovement.z = 0;

			if (input_->KeepPush(DIK_S))
			{
				playerMovement.y = -playerSpeed;
				playerSurfacePos = 5;
			}
			worldTransform_.translation += playerMovement;
		}
	}

	//�����
	if (TopRightTop.x < AliceMathF::GetWorldPosition(worldTransform_).x)
	{
		if (playerSurfacePos == 2)
		{
			worldTransform_.translation.x = PlayerSmoothMoving.x;
			worldTransform_.translation.y = PlayerSmoothMoving.y;
			worldTransform_.translation.z = PlayerSmoothMoving.z;
			playerMovement.x = 0;

			if (input_->KeepPush(DIK_W))
			{
				playerMovement.y = playerSpeed;
				playerSurfacePos = 1;
			}
			worldTransform_.translation += playerMovement;
		}
	}
	if (RightTopRight.z < AliceMathF::GetWorldPosition(worldTransform_).z)
	{
		if (playerSurfacePos == 2)
		{
			worldTransform_.translation.x = PlayerSmoothMoving.x;
			worldTransform_.translation.y = PlayerSmoothMoving.y;
			worldTransform_.translation.z = PlayerSmoothMoving.z;
			playerMovement.z = 0;

			if (input_->KeepPush(DIK_W))
			{
				playerMovement.y = playerSpeed;
				playerSurfacePos = 4;
			}
			worldTransform_.translation += playerMovement;
		}
	}
	if (TopLeftTop.x > AliceMathF::GetWorldPosition(worldTransform_).x)
	{
		if (playerSurfacePos == 2)
		{
			worldTransform_.translation.x = PlayerSmoothMoving.x;
			worldTransform_.translation.y = PlayerSmoothMoving.y;
			worldTransform_.translation.z = PlayerSmoothMoving.z;
			playerMovement.x = 0;

			if (input_->KeepPush(DIK_W))
			{
				playerMovement.y = playerSpeed;
				playerSurfacePos = 3;
			}
			worldTransform_.translation += playerMovement;
		}
	}
	if (RightTopLeft.z > AliceMathF::GetWorldPosition(worldTransform_).z)
	{
		if (playerSurfacePos == 2)
		{
			worldTransform_.translation.x = PlayerSmoothMoving.x;
			worldTransform_.translation.y = PlayerSmoothMoving.y;
			worldTransform_.translation.z = PlayerSmoothMoving.z;
			playerMovement.z = 0;

			if (input_->KeepPush(DIK_W))
			{
				playerMovement.y = playerSpeed;
				playerSurfacePos = 5;
			}
			worldTransform_.translation += playerMovement;
		}
	}

	//Right
	if (TopRightTop.z < AliceMathF::GetWorldPosition(worldTransform_).z)
	{
		if (playerSurfacePos == 1)
		{
			worldTransform_.translation.x = PlayerSmoothMoving.x;
			worldTransform_.translation.y = PlayerSmoothMoving.y;
			worldTransform_.translation.z = PlayerSmoothMoving.z;
			playerMovement.z = 0;

			if (input_->KeepPush(DIK_D))
			{
				playerMovement.x = -playerSpeed;
				playerSurfacePos = 4;
			}
			worldTransform_.translation += playerMovement;
		}
	}
	if (RightTopLeft.z > AliceMathF::GetWorldPosition(worldTransform_).z)
	{
		if (playerSurfacePos == 1)
		{
			worldTransform_.translation.x = PlayerSmoothMoving.x;
			worldTransform_.translation.y = PlayerSmoothMoving.y;
			worldTransform_.translation.z = PlayerSmoothMoving.z;
			playerMovement.z = 0;

			if (input_->KeepPush(DIK_A))
			{
				playerMovement.x = -playerSpeed;
				playerSurfacePos = 5;
			}
			worldTransform_.translation += playerMovement;
		}
	}
	//Left
	if (RightTopLeft.z > AliceMathF::GetWorldPosition(worldTransform_).z)
	{
		if (playerSurfacePos == 3)
		{
			worldTransform_.translation.x = PlayerSmoothMoving.x;
			worldTransform_.translation.y = PlayerSmoothMoving.y;
			worldTransform_.translation.z = PlayerSmoothMoving.z;
			playerMovement.z = 0;

			if (input_->KeepPush(DIK_D))
			{
				playerMovement.x = playerSpeed;
				playerSurfacePos = 5;
			}
			worldTransform_.translation += playerMovement;
		}
	}
	if (TopRightTop.z < AliceMathF::GetWorldPosition(worldTransform_).z)
	{
		if (playerSurfacePos == 3)
		{
			worldTransform_.translation.x = PlayerSmoothMoving.x;
			worldTransform_.translation.y = PlayerSmoothMoving.y;
			worldTransform_.translation.z = PlayerSmoothMoving.z;
			playerMovement.z = 0;

			if (input_->KeepPush(DIK_A))
			{
				playerMovement.x = playerSpeed;
				playerSurfacePos = 4;
			}
			worldTransform_.translation += playerMovement;
		}
	}

	//��O
	if (TopRightTop.x < AliceMathF::GetWorldPosition(worldTransform_).x)
	{
		if (playerSurfacePos == 5)
		{
			worldTransform_.translation.x = PlayerSmoothMoving.x;
			worldTransform_.translation.y = PlayerSmoothMoving.y;
			worldTransform_.translation.z = PlayerSmoothMoving.z;
			playerMovement.x = 0;

			if (input_->KeepPush(DIK_D))
			{
				playerMovement.z = playerSpeed;
				playerSurfacePos = 1;
			}
			worldTransform_.translation += playerMovement;
		}
	}
	if (TopLeftTop.x > AliceMathF::GetWorldPosition(worldTransform_).x)
	{
		if (playerSurfacePos == 5)
		{
			worldTransform_.translation.x = PlayerSmoothMoving.x;
			worldTransform_.translation.y = PlayerSmoothMoving.y;
			worldTransform_.translation.z = PlayerSmoothMoving.z;
			playerMovement.x = 0;

			if (input_->KeepPush(DIK_A))
			{
				playerMovement.z = playerSpeed;
				playerSurfacePos = 3;
			}
			worldTransform_.translation += playerMovement;
		}
	}
	//��O
	if (TopLeftTop.x > AliceMathF::GetWorldPosition(worldTransform_).x)
	{
		if (playerSurfacePos == 4)
		{
			worldTransform_.translation.x = PlayerSmoothMoving.x;
			worldTransform_.translation.y = PlayerSmoothMoving.y;
			worldTransform_.translation.z = PlayerSmoothMoving.z;
			playerMovement.x = 0;

			if (input_->KeepPush(DIK_D))
			{
				playerMovement.z = -playerSpeed;
				playerSurfacePos = 3;
			}
			worldTransform_.translation += playerMovement;
		}
	}
	if (TopRightTop.x < AliceMathF::GetWorldPosition(worldTransform_).x)
	{
		if (playerSurfacePos == 4)
		{
			worldTransform_.translation.x = PlayerSmoothMoving.x;
			worldTransform_.translation.y = PlayerSmoothMoving.y;
			worldTransform_.translation.z = PlayerSmoothMoving.z;
			playerMovement.x = 0;

			if (input_->KeepPush(DIK_A))
			{
				playerMovement.z = -playerSpeed;
				playerSurfacePos = 1;
			}
			worldTransform_.translation += playerMovement;
		}
	}

}

void Player::PlayerCollider(Camera* camera)
{

	SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider);
	assert(sphereCollider);

	sphereCollider->SetRadius(radius);

	// �N�G���[�R�[���o�b�N�N���X
	class PlayerQueryCallback : public QueryCallback
	{
	public:
		PlayerQueryCallback(Sphere* sphere) : sphere(sphere)
		{
		};

			  // �Փˎ��R�[���o�b�N�֐�
		bool OnQueryHit(const QueryHit& info)
		{

			const AliceMathF::Vector4 up = { 0,1,0,0 };

			AliceMathF::Vector4 rejectDir = info.reject;
			rejectDir.Normalization();
			rejectDir.Dot(up);
			float cos = rejectDir.y;

			// �n�ʔ��肵�����l
			const float threshold = cosf(DirectX::XMConvertToRadians(30.0f));

			if (-threshold < cos && cos < threshold)
			{
				sphere->center += info.reject;
				move += info.reject;
			}

			return true;
		}

		Sphere* sphere = nullptr;
		AliceMathF::Vector4 move = {};
	};

	PlayerQueryCallback callback(sphereCollider);

	// ���ƒn�`�̌�����S����
	CollisionManager::GetInstance()->QuerySphere(*sphereCollider, &callback, COLLISION_ATTR_LANDSHAPE, &worldTransform_.matWorld);
	// �����ɂ��r�˕�������
	worldTransform_.translation.x += callback.move.x;
	worldTransform_.translation.y += callback.move.y;
	worldTransform_.translation.z += callback.move.z;
	// ���[���h�s��X�V
	worldTransform_.TransUpdate(camera);
	collider->Update(worldTransform_.matWorld);

	float RayPos = -1.0f;

	//�n�ʃ��b�V���R���C�_�[
	{
		// ���̏�[���狅�̉��[�܂ł̃��C�L���X�g
		Ray Groundray;
		Groundray.start = sphereCollider->center;
		Groundray.start.y += sphereCollider->GetRadius();
		Groundray.dir = { 0,-1,0,0 };
		RaycastHit raycastHit;


		// �ڒn���
		if (onGround)
		{
// �X���[�Y�ɍ������ׂ̋z������
			const float adsDistance = 0.2f;
			// �ڒn���ێ�
			if (CollisionManager::GetInstance()->Raycast(Groundray, COLLISION_ATTR_LANDSHAPE, &raycastHit, sphereCollider->GetRadius() * 2.0f + adsDistance))
			{
				onGround = true;
				ground = true;
				worldTransform_.translation.y -= (raycastHit.distance - sphereCollider->GetRadius() * 2.0f);
			}
			// �n�ʂ��Ȃ��̂ŗ���
			else
			{
				ground = true;
				onGround = false;
				fallV = {};
			}
		}
		// �������
		else if (fallV.y <= 0.0f)
		{
			if (CollisionManager::GetInstance()->Raycast(Groundray, COLLISION_ATTR_LANDSHAPE, &raycastHit, sphereCollider->GetRadius() * 2.0f))
			{
// ���n
				onGround = true;
				ground = true;
				worldTransform_.translation.y -= (raycastHit.distance - sphereCollider->GetRadius() * 2.0f);
			}
		}
	}

	{
		//�����b�V���R���C�_�[
		Ray wall;
		wall.start = sphereCollider->center;
		wall.start.y += RayPos;
		wall.dir = { 0,0,1,0 };
		RaycastHit wallRaycastHit;
		// �X���[�Y�ɍ������ׂ̋z������
		//const float adsDistance = 0.2f;

		// �ڒn���ێ�
		if (CollisionManager::GetInstance()->Raycast(wall, COLLISION_ATTR_LANDSHAPE, &wallRaycastHit, sphereCollider->GetRadius()))
		{
			worldTransform_.translation.z += (wallRaycastHit.distance - sphereCollider->GetRadius());
		}

	}

	{
		//�����b�V���R���C�_�[
		Ray wall;
		wall.start = sphereCollider->center;
		wall.start.y += RayPos;
		wall.dir = { 0,0,-1,0 };
		RaycastHit wallRaycastHit;
		// �X���[�Y�ɍ������ׂ̋z������
		//const float adsDistance = 0.2f;

		// �ڒn���ێ�
		if (CollisionManager::GetInstance()->Raycast(wall, COLLISION_ATTR_LANDSHAPE, &wallRaycastHit, sphereCollider->GetRadius()))
		{
			worldTransform_.translation.z -= (wallRaycastHit.distance - sphereCollider->GetRadius());
		}

	}


	{
		//�����b�V���R���C�_�[
		Ray wall;
		wall.start = sphereCollider->center;
		wall.start.y += RayPos;
		wall.dir = { 1,0,0,0 };
		RaycastHit wallRaycastHit;
		// �X���[�Y�ɍ������ׂ̋z������
		//const float adsDistance = 0.2f;

		// �ڒn���ێ�
		if (CollisionManager::GetInstance()->Raycast(wall, COLLISION_ATTR_LANDSHAPE, &wallRaycastHit, sphereCollider->GetRadius()))
		{
			worldTransform_.translation.x += (wallRaycastHit.distance - sphereCollider->GetRadius());
		}

	}

	{
		//�����b�V���R���C�_�[
		Ray wall;
		wall.start = sphereCollider->center;
		wall.start.y += RayPos;
		wall.dir = { -1,0,0,0 };
		RaycastHit wallRaycastHit;
		// �X���[�Y�ɍ������ׂ̋z������
		//const float adsDistance = 0.2f;

		// �ڒn���ێ�
		if (CollisionManager::GetInstance()->Raycast(wall, COLLISION_ATTR_LANDSHAPE, &wallRaycastHit, sphereCollider->GetRadius()))
		{
			worldTransform_.translation.x -= (wallRaycastHit.distance - sphereCollider->GetRadius());
		}

	}

}

void Player::Draw()
{

	aliceModel->Draw(&worldTransform_);
}

AliceMathF::Vector3 Player::bVelocity(AliceMathF::Vector3& velocity, Transform& worldTransform)
{

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

AliceMathF::Vector3 Player::Vector3Transform(const AliceMathF::Vector3& v, const AliceMathF::Matrix4& m)
{

	AliceMathF::Vector3 result{
		  v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0],
		  v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1],
		  v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2]
	};

	return result;
}
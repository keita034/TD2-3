#include "Player.h"

#include "Input.h"
#include"2d/DebugText.h"
#include"SphereCollider.h"
#include"3d/ParticleManager.h"

using namespace DirectX;

Player* Player::Create(Model* model)
{
	Player* instance = new Player();
	if (instance == nullptr) {
		return nullptr;
	}

	if (!instance->Initialize()) {
		delete instance;
		assert(0);
	}
	if (model) {
		instance->SetModel(model);
	}
	return instance;
}

bool Player::Initialize()
{
	if (!Object3d::Initialize()) {
		return false;
	}

	float radius = 0.6f;

	SetCollider(new SphereCollider(DirectX::XMVECTOR({ 0,radius,0,0 }), radius));

	return true;

}

void Player::Update()
{
	Input* input = Input::GetInstance();

	if (input->PushKey(DIK_A)) {
		rotation.y -= 2.0f;
	}
	if (input->PushKey(DIK_D)) {
		rotation.y += 2.0f;
	}

	XMVECTOR move = { 0,0,0.1f,0 };
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(rotation.y));
	move = XMVector3TransformNormal(move, matRot);

	if (input->PushKey(DIK_S)) {
		position.x -= move.m128_f32[0];
		position.y -= move.m128_f32[1];
		position.z -= move.m128_f32[2];
	}
	if (input->PushKey(DIK_W)) {
		position.x += move.m128_f32[0];
		position.y += move.m128_f32[1];
		position.z += move.m128_f32[2];
	}

	Object3d::Update();

}

void Player::OnCollision(const CollisionInfo& info)
{
	
	DebugText::GetInstance()->Printf("Collision detected");

	for (int i = 0; i < 1; ++i) {
		const float rnd_vel = 0.1f;
		XMFLOAT3 vel{};

		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

		ParticleManager::GetInstance()->Add(10, XMFLOAT3(info.inter.m128_f32), vel, XMFLOAT3(), 0.0f, 1.0f);
	}

}

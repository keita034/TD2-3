#include "Goal.h"
#include "SphereCollider.h"
#include "CollisionAttribute.h"
#include "CollisionManager.h"

Goal::Goal(uint32_t modelHandl)
{
	model = std::make_unique<Model>();
	model->SetModel(modelHandl);

	worldTransform_.Initialize();

	float PlayerScale = 3.0f;
	worldTransform_.scale = { PlayerScale,PlayerScale,PlayerScale };

	collider = new SphereCollider(AliceMathF::Vector4(0, radius, 0, 0), radius);
	CollisionManager::GetInstance()->AddCollider(collider);

	worldTransform_.translation = { 20,30,-20 };

	collider->Update(worldTransform_.matWorld);
	collider->SetAttribute(COLLISION_ATTR_ALLIES);

}

void Goal::Initialise()
{
}

void Goal::Update(Camera* camera)
{
	worldTransform_.TransUpdate(camera);
	collider->Update(worldTransform_.matWorld);
}

void Goal::Draw()
{
	model->Draw(worldTransform_);
}

void Goal::Collider(Camera* camera)
{
}

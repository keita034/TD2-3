#include "TouchableObject.h"
#include "MeshCollider.h"
#include "CollisionAttribute.h"

TouchableObject* TouchableObject::Create(uint32_t modelHandle, Transform* transform)
{
	// オブジェクトのインスタンスを生成
	TouchableObject* instance = new TouchableObject();
	if (instance == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!instance->Initialize(modelHandle, transform)) {
		delete instance;
		assert(0);
	}

	return instance;
}

bool TouchableObject::Initialize(uint32_t modelHandle, Transform* transform)
{
	trans = transform;
	SetModel(modelHandle);

	// コライダーの追加
	MeshCollider* collider = new MeshCollider;
	trans->SetCollider(collider);
	collider->ConstructTriangles(this);
	collider->SetAttribute(COLLISION_ATTR_LANDSHAPE);

	return true;
}

#include "TouchableObject.h"
#include "MeshCollider.h"
#include "CollisionAttribute.h"

TouchableObject* TouchableObject::Create(uint32_t modelHandle, Transform* transform)
{
	// �I�u�W�F�N�g�̃C���X�^���X�𐶐�
	TouchableObject* instance = new TouchableObject();
	if (instance == nullptr) {
		return nullptr;
	}

	// ������
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

	// �R���C�_�[�̒ǉ�
	MeshCollider* collider = new MeshCollider;
	trans->SetCollider(collider);
	collider->ConstructTriangles(this);
	collider->SetAttribute(COLLISION_ATTR_LANDSHAPE);

	return true;
}

#include "CollisionManager.h"
#include "BaseCollider.h"
#include "Collision.h"
#include "MeshCollider.h"

using namespace DirectX;

CollisionManager* CollisionManager::GetInstance()
{
	static CollisionManager instance;
	return &instance;
}

void CollisionManager::CheckAllCollisions(DirectX::XMMATRIX PlayerMatWorldPos)
{
	std::forward_list<BaseCollider*>::iterator itA;
	std::forward_list<BaseCollider*>::iterator itB;

	// �S�Ă̑g�ݍ��킹�ɂ��đ�����`�F�b�N
	itA = colliders.begin();
	for (; itA != colliders.end(); ++itA) {
		itB = itA;
		++itB;
		for (; itB != colliders.end(); ++itB) {
			BaseCollider* colA = *itA;
			BaseCollider* colB = *itB;

			// �Ƃ��ɋ�
			if (colA->GetShapeType() == COLLISIONSHAPE_SPHERE &&
				colB->GetShapeType() == COLLISIONSHAPE_SPHERE) {
				Sphere* SphereA = dynamic_cast<Sphere*>(colA);
				Sphere* SphereB = dynamic_cast<Sphere*>(colB);
				DirectX::XMVECTOR inter;
				if (Collision::CheckSphere2Sphere(*SphereA, *SphereB, &inter)) {
					
				}
			}
			else if (colA->GetShapeType() == COLLISIONSHAPE_MESH &&
				colB->GetShapeType() == COLLISIONSHAPE_SPHERE) {
				MeshCollider* meshCollider = dynamic_cast<MeshCollider*>(colA);
				Sphere* sphere = dynamic_cast<Sphere*>(colB);
				DirectX::XMVECTOR inter;
				if (meshCollider->CheckCollisionSphere(*sphere, &inter, nullptr)) {
					
				}
			}
			else if (colA->GetShapeType() == COLLISIONSHAPE_SPHERE &&
				colB->GetShapeType() == COLLISIONSHAPE_MESH) {
				MeshCollider* meshCollider = dynamic_cast<MeshCollider*>(colB);
				Sphere* sphere = dynamic_cast<Sphere*>(colA);
				DirectX::XMVECTOR inter;
				if (meshCollider->CheckCollisionSphere(*sphere, &inter, nullptr)) {
					
				}
			}
		}
	}
}

bool CollisionManager::Raycast(const Ray& ray, RaycastHit* hitInfo, float maxDistance, DirectX::XMMATRIX* MatWorldPos)
{
	return Raycast(ray, 0xffff, hitInfo, maxDistance, MatWorldPos);
}

bool CollisionManager::Raycast(const Ray& ray, unsigned short attribute, RaycastHit* hitInfo, float maxDistance,DirectX::XMMATRIX* MatWorldPos)
{
	bool result = false;
	std::forward_list<BaseCollider*>::iterator it;
	std::forward_list<BaseCollider*>::iterator it_hit;
	float distance = maxDistance;
	XMVECTOR inter;

	// �S�ẴR���C�_�[�Ƒ�����`�F�b�N
	it = colliders.begin();
	for (; it != colliders.end(); ++it) {
		BaseCollider* colA = *it;

		// ����������Ȃ���΃X�L�b�v
		if (!(colA->attribute & attribute)) {
			continue;
		}

		if (colA->GetShapeType() == COLLISIONSHAPE_SPHERE) {
			Sphere* sphere = dynamic_cast<Sphere*>(colA);

			float tempDistance;
			XMVECTOR tempInter;

			if (!Collision::CheckRay2Sphere(ray, *sphere, &tempDistance, &tempInter)) continue;
			if (tempDistance >= distance) continue;

			result = true;
			distance = tempDistance;
			inter = tempInter;
			it_hit = it;
		}
		else if (colA->GetShapeType() == COLLISIONSHAPE_MESH) {
			MeshCollider* meshCollider = dynamic_cast<MeshCollider*>(colA);

			float tempDistance;
			DirectX::XMVECTOR tempInter;
			/// <summary>
			/// //���Ԃ񂱂�
			/// </summary>
			/// <param name="ray"></param>
			/// <param name="attribute"></param>
			/// <param name="hitInfo"></param>
			/// <param name="maxDistance"></param>
			/// <param name="MatWorldPos"></param>
			/// <returns></returns>
			if (!meshCollider->CheckCollisionRay(ray, &tempDistance, &tempInter)) continue;
			if (tempDistance >= distance) continue;

			result = true;
			distance = tempDistance;
			inter = tempInter;
			it_hit = it;
		}
	}

	if (result && hitInfo) {
		hitInfo->distance = distance;
		hitInfo->inter = inter;
		hitInfo->collider = *it_hit;
	}

	return result;
}

void CollisionManager::QuerySphere(const Sphere& sphere, QueryCallback* callback, unsigned short attribute,XMMATRIX* worldPos)
{
	assert(callback);

	std::forward_list<BaseCollider*>::iterator it;

	// �S�ẴR���C�_�[�Ƒ�����`�F�b�N
	it = colliders.begin();
	for (; it != colliders.end(); ++it) {
		BaseCollider* col = *it;

		// ����������Ȃ���΃X�L�b�v
		if (!(col->attribute & attribute)) {
			continue;
		}

		// ��
		if (col->GetShapeType() == COLLISIONSHAPE_SPHERE) {
			Sphere* sphereB = dynamic_cast<Sphere*>(col);

			XMVECTOR tempInter;
			XMVECTOR tempReject;
			if (!Collision::CheckSphere2Sphere(sphere, *sphereB, &tempInter, &tempReject)) continue;

			// ���������Z�b�g
			QueryHit info;
			info.collider = col;
			info.inter = tempInter;
			info.reject = tempReject;

			// �N�G���[�R�[���o�b�N�Ăяo��
			if (!callback->OnQueryHit(info)) {
				// �߂�l��false�̏ꍇ�A�p�������I��
				return;
			}
		}
		// ���b�V��
		else if (col->GetShapeType() == COLLISIONSHAPE_MESH) {
			MeshCollider* meshCollider = dynamic_cast<MeshCollider*>(col);

			XMVECTOR tempInter;
			XMVECTOR tempReject;
			if (!meshCollider->CheckCollisionSphere(sphere, &tempInter, &tempReject)) continue;

			// ���������Z�b�g
			QueryHit info;
			info.collider = col;
			info.inter = tempInter;
			info.reject = tempReject;

			// �N�G���[�R�[���o�b�N�Ăяo��
			if (!callback->OnQueryHit(info)) {
				// �߂�l��false�̏ꍇ�A�p�������I��
				return;
			}
		}
	}
}
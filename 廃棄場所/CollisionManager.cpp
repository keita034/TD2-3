#include "CollisionManager.h"
#include"BaseCollider.h"
#include"Collision.h"
#include"MeshCollider.h"

CollisionManager* CollisionManager::GetInstance()
{
	static CollisionManager instance;
	return &instance;
}

void CollisionManager::AddCollider(BaseCollider* collider)
{
	colliders.push_front(collider);
}

void CollisionManager::RemoveCollider(BaseCollider* collider)
{
	colliders.remove(collider);
}

void CollisionManager::CheckAllCollisions()
{
	std::forward_list<BaseCollider*>::iterator itA;
	std::forward_list<BaseCollider*>::iterator itB;

	//�S�Ă̑g�ݍ��킹�ɂ��đ�������`�F�b�N
	itA = colliders.begin();
	for (; itA != colliders.end(); ++itA)
	{
		itB = itA;
		itB++;
		for (; itB != colliders.end(); ++itB)
		{
			BaseCollider* colA = *itA;
			BaseCollider* colB = *itB;

			//�Ƃ��ɋ�
			if (colA->GetShapeType() == CollisionShapeSphere &&
				colB->GetShapeType() == CollisionShapeSphere)
			{
				Sphere2Sphere(colA, colB);
			}
			else if (colA->GetShapeType() == CollisionShapeMesh &&
				colB->GetShapeType() == CollisionShapeSphere)
			{
				MeshCollider* meshCollider = dynamic_cast<MeshCollider*>(colA);
				Sphere* sphere = dynamic_cast<Sphere*>(colB);
				AliceMath::Vector3 inter;
				if (meshCollider->CheckCollisionSphere(*sphere, &inter))
				{
					colA->OnCollision(CollisionInfo(colB->GetModel(), colB, inter));
					colB->OnCollision(CollisionInfo(colA->GetModel(), colA, inter));
				}
			}
			else if (colA->GetShapeType() == CollisionShapeSphere &&
				colB->GetShapeType() == CollisionShapeMesh)
			{
				MeshCollider* meshCollider = dynamic_cast<MeshCollider*>(colB);
				Sphere* sphere = dynamic_cast<Sphere*>(colA);
				AliceMath::Vector3 inter;
				if (meshCollider->CheckCollisionSphere(*sphere, &inter))
				{
					colA->OnCollision(CollisionInfo(colB->GetModel(), colB, inter));
					colB->OnCollision(CollisionInfo(colA->GetModel(), colA, inter));
				}
			}
		}
	}
}

bool CollisionManager::Raycast(Ray& ray, RaycastHit* hitinfo, float maxDistance)
{
	//�S�����L���ɂ��đ����ł����s
	return Raycast(ray, 0xffff, hitinfo, maxDistance);
}

bool CollisionManager::Raycast(Ray& ray, uint16_t attribute, RaycastHit* hitinfo, float maxDistance)
{
	bool result = false;
	//�{���p�̃C�e���[�^
	std::forward_list<BaseCollider*>::iterator it;
	//���܂ň�ԋ߂��R���C�_�[���L�^����C�e���[�^
	std::forward_list<BaseCollider*>::iterator it_hit;
	//���܂ň�ԋ߂��R���C�_�[�̋���
	float distance = maxDistance;
	//�ł��߂��R���C�_�[�̌�_
	AliceMath::Vector3 inter;
	//�S�ẴR���C�_�[�Ƒ�������`�F�b�N
	it = colliders.begin();
	for (; it != colliders.end(); ++it)
	{
		BaseCollider* colA = *it;

		//����������Ȃ���΃X�L�b�v
		if (!(colA->attribute & attribute))
		{
			continue;
		}

		//���̏ꍇ
		if (colA->GetShapeType() == CollisionShapeSphere)
		{
			Sphere* sphere = dynamic_cast<Sphere*>(colA);
			float tempDistance;
			AliceMath::Vector3 templnter;

			//������Ȃ���Ώ��O
			if (!Collision::CheckRay2Sphere(ray, *sphere, &tempDistance, &templnter))
			{
				continue;
			}

			//�������ŏ��łȂ���Ώ��O
			if (tempDistance >= distance)
			{
				continue;
			}

			//���܂łōł��߂��̂ŋL�^�����
			result = true;
			distance = tempDistance;
			inter = templnter;
			it_hit = it;
		}
		else if (colA->GetShapeType() == CollisionShapeMesh)
		{
			MeshCollider* meshCollider = dynamic_cast<MeshCollider*>(colA);

			float tempDistance = 0.0;
			AliceMath::Vector3 tmplnter;
			if (!meshCollider->CheckCollisionRay(ray, &tempDistance, &tmplnter))
			{
				continue;
			}

			//�������ŏ��łȂ���Ώ��O
			if (tempDistance >= distance)
			{
				continue;
			}

			result = true;
			distance = tempDistance;
			inter = tmplnter;
			it_hit = it;
		}
	}

	if (result && hitinfo)
	{
		hitinfo->distance = distance;
		hitinfo->inter = inter;
		hitinfo->collider = *it_hit;
		hitinfo->model = hitinfo->collider->GetModel();
	}

	return result;
}

void CollisionManager::QuerySphere(Sphere& sphere, QueryCallback* callback, uint16_t attribute)
{
	assert(callback);
	std::forward_list<BaseCollider*>::iterator it;

	//�S�Ă̂̃R���C�_�[�Ƒ�������`�F�b�N
	it = colliders.begin();
	for (; it != colliders.end(); ++it)
	{
		BaseCollider* col = *it;

		//����������Ȃ���΃X�L�b�v
		if (!(col->attribute & attribute))
		{
			continue;
		}

		if (col->GetShapeType() == CollisionShapeSphere)
		{
			Sphere* sphereB = dynamic_cast<Sphere*>(col);

			AliceMath::Vector3 templnter;
			AliceMath::Vector3 tempReject;
			if (!Collision::CheakSphere2Sphere(sphere, *sphereB, &templnter, &tempReject))
			{
				continue;
			}

			//���������Z�b�g
			QueryHit info;
			info.collider = col;
			info.model = col->GetModel();
			info.inter = templnter;
			info.reject = tempReject;

			//�N�G���[�R�[���o�b�N�Ăяo��
			if (!callback->OnQueryHit(info))
			{
				//�߂�l��false�̏ꍇ�A�p�������ɏI��
				return;
			}
		}
		else if (col->GetShapeType() == CollisionShapeMesh)
		{
			MeshCollider* meshcollider = dynamic_cast<MeshCollider*>(col);

			AliceMath::Vector3 templnter;
			AliceMath::Vector3 tempReject;
			if (!meshcollider->CheckCollisionSphere(sphere, &templnter, &tempReject))
			{
				continue;
			}

			//���������Z�b�g
			QueryHit info;
			info.collider = col;
			info.model = col->GetModel();
			info.inter = templnter;
			info.reject = tempReject;

			//�N�G���[�R�[���o�b�N�Ăяo��
			if (!callback->OnQueryHit(info))
			{
				//�߂�l��false�̏ꍇ�A�p�������ɏI��
				return;
			}

		}

	}
}

void CollisionManager::Sphere2Sphere(BaseCollider* SphereA, BaseCollider* SphereB)
{
	Sphere* sphereA = dynamic_cast<Sphere*>(SphereA);
	Sphere* sphereB = dynamic_cast<Sphere*>(SphereB);
	AliceMath::Vector3 inter;

	if (Collision::CheakSphere2Sphere(*sphereA, *sphereB, &inter))
	{
		SphereA->OnCollision(CollisionInfo(SphereB->GetModel(), SphereB, inter));
		SphereB->OnCollision(CollisionInfo(SphereA->GetModel(), SphereA, inter));
	}

}

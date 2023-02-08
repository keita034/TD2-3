#pragma once

#include"CollisionPrimitive.h"
#include "RaycastHit.h"

#include "QueryCallback.h"

#include"AliceMathUtility.h"

class BaseCollider;

class CollisionManager {
public:
	static CollisionManager* GetInstance();

public://�����o�֐�

	inline void AddCollider(BaseCollider* collider) {
		colliders.push_front(collider);
	}

	/// <summary>
	/// ���Ƃ��Ƃ��铖���蔻���ς���
	/// </summary>
	/// <param name="chengeMeshCount">�ς���������̏ꏊ</param>
	/// <param name="collider">�����蔻�������</param>
	void ChangeCollider(int chengeMeshCount, BaseCollider* collider) {

		std::forward_list<BaseCollider*>::iterator itr;

		itr = colliders.begin();

		for (int i = 0; i < chengeMeshCount - 1; i++) {
			itr++;
		}
		colliders.emplace_after(itr);
		colliders.insert_after(itr, collider);

	}

	inline void RemoveCollider(BaseCollider* collide) {
		colliders.remove(collide);
	}

	void CheckAllCollisions();

	bool Raycast(const Ray& ray, RaycastHit* hitInfo = nullptr, float maxDistance = D3D12_FLOAT32_MAX);


	//���C�L���X�g�I�[�o�[���[�h
	bool Raycast(const Ray& ray, unsigned short attribute, RaycastHit* hitInfo = nullptr, float maxDistance = D3D12_FLOAT32_MAX);

	void QuerySphere(const Sphere& sphere, QueryCallback* callback, unsigned short attribute = (unsigned short)0xffffffff, AliceMathF::Matrix4* worldPos = nullptr);


	bool GetIsGoal() { return isGoal; }

	void SetGoal(bool x) { isGoal = x; }

private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	~CollisionManager() = default;
	CollisionManager& operator = (const CollisionManager&) = delete;

	//�R���C�_�[�̃��X�g
	std::forward_list<BaseCollider*> colliders;

	int GoalCount = 0;

	bool isGoal = false;

};
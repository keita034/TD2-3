#pragma once

#include"CollisionPrimitive.h"
#include "RaycastHit.h"

#include "QueryCallback.h"

#include"AliceMathUtility.h"

class BaseCollider;

class CollisionManager {
public:
	static CollisionManager* GetInstance();

public://メンバ関数

	inline void AddCollider(BaseCollider* collider) {
		colliders.push_front(collider);
	}

	/// <summary>
	/// もともとある当たり判定を変える
	/// </summary>
	/// <param name="chengeMeshCount">変えたい判定の場所</param>
	/// <param name="collider">当たり判定を入れる</param>
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


	//レイキャストオーバーロード
	bool Raycast(const Ray& ray, unsigned short attribute, RaycastHit* hitInfo = nullptr, float maxDistance = D3D12_FLOAT32_MAX);

	void QuerySphere(const Sphere& sphere, QueryCallback* callback, unsigned short attribute = (unsigned short)0xffffffff, AliceMathF::Matrix4* worldPos = nullptr);


	bool GetIsGoal() { return isGoal; }

	void SetGoal(bool x) { isGoal = x; }

private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	~CollisionManager() = default;
	CollisionManager& operator = (const CollisionManager&) = delete;

	//コライダーのリスト
	std::forward_list<BaseCollider*> colliders;

	int GoalCount = 0;

	bool isGoal = false;

};
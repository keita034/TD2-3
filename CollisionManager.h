#pragma once

#include<forward_list>

#include"CollisionPrimitive.h"
#include "RaycastHit.h"

#include<d3d12.h>
#include "QueryCallback.h"

class BaseCollider;

class CollisionManager {
public:
	static CollisionManager* GetInstance();

public://�����o�֐�

	inline void AddCollider(BaseCollider* collider) {
		colliders.push_front(collider);
	}

	inline void RemoveCollider(BaseCollider* collide) {
		colliders.remove(collide);
	}

	void CheckAllCollisions(DirectX::XMMATRIX PlayerMatWorldPos);

	bool Raycast(const Ray& ray, RaycastHit* hitInfo = nullptr, float maxDistance = D3D12_FLOAT32_MAX, DirectX::XMMATRIX* MatWorldPos = nullptr);


	//���C�L���X�g�I�[�o�[���[�h
	bool Raycast(const Ray& ray, unsigned short attribute, RaycastHit* hitInfo = nullptr, float maxDistance = D3D12_FLOAT32_MAX, DirectX::XMMATRIX* MatWorldPos= nullptr);

	void QuerySphere(const Sphere& sphere, QueryCallback* callback, unsigned short attribute = (unsigned short)0xffffffff, DirectX::XMMATRIX* worldPos = nullptr);

private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	~CollisionManager() = default;
	CollisionManager& operator = (const CollisionManager&) = delete;

	//�R���C�_�[�̃��X�g
	std::forward_list<BaseCollider*> colliders;

};
#pragma once
#include"ErrorException.h"
#include"RaycastHit.h"
#include"CollisionPrimitive.h"
#include"QueryCallback.h"

class BaseCollider;

class CollisionManager
{
private:
	//�R���C�_�[�̃��X�g
	std::forward_list<BaseCollider*> colliders;

public:
	static CollisionManager* GetInstance();

	/// <summary>
	/// �R���C�_�[�̒ǉ�
	/// </summary>
	/// <param name="collider">�R���C�_�[</param>
	void AddCollider(BaseCollider* collider);

	/// <summary>
	/// �R���C�_�[�̍폜
	/// </summary>
	/// <param name="collider">�R���C�_�[</param>
	void RemoveCollider(BaseCollider* collider);

	/// <summary>
	/// �S�Ă̏Փ˃`�F�b�N
	/// </summary>
	void CheckAllCollisions();

	/// <summary>
	/// ���C�L���X�g
	/// </summary>
	/// <param name="ray">���C</param>
	/// <param name="hitinfo">�Փˏ��</param>
	/// <param name="maxDistance">�ő勗��</param>
	/// <returns>���C���R���C�_�[�ɓ������Ă��邩</returns>
	bool Raycast( Ray& ray, RaycastHit* hitinfo = nullptr, float maxDistance = D3D12_FLOAT32_MAX);

	/// <summary>
	/// ���C�L���X�g
	/// </summary>
	/// <param name="ray">���C</param>
	/// <param name="attribute">�Ώۂ̏Փˑ���</param>
	/// <param name="hitinfo">�Փˏ��</param>
	/// <param name="maxDistance">�ő勗��</param>
	/// <returns>���C���R���C�_�[�ɓ������Ă��邩</returns>
	bool Raycast(Ray& ray, uint16_t attribute, RaycastHit* hitinfo = nullptr, float maxDistance = D3D12_FLOAT32_MAX);

	/// <summary>
	/// ���ɂ��ՓˑS����
	/// </summary>
	/// <param name="sphere">��</param>
	/// <param name="callback">�Փˎ��R�[���o�b�N</param>
	/// <param name="attribute">�Ώۂ̏Փˑ���</param>
	void QuerySphere(Sphere& sphere,QueryCallback* callback, uint16_t attribute = static_cast<uint16_t>(0xffffffff));

private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = default;
	~CollisionManager() = default;
	CollisionManager& operator=(const CollisionManager&) = default;

	//���Ƌ�
	void Sphere2Sphere(BaseCollider* SphereA, BaseCollider* SphereB);


};


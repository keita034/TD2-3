#pragma once

#include "CollisionPrimitive.h"
#include "RaycastHit.h"
#include "QueryCallback.h"

class BaseCollider;

class CollisionManager
{
public:// �ÓI�����o�֐�
	static CollisionManager* GetInstance();

public:// �����o�֐�
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
	/// <param name="hitInfo">�Փˏ��</param>
	/// <param name="maxDistance">�ő勗��</param>
	/// <returns>���C���C�ӂ̃R���C�_�[�ƌ����ꍇ��true�A����ȊO��false</returns>
	bool Raycast(Ray& ray, RaycastHit* hitInfo = nullptr, float maxDistance = D3D12_FLOAT32_MAX);

	/// <summary>
	/// ���C�L���X�g
	/// </summary>
	/// <param name="ray">���C</param>
	/// <param name="hitInfo">�Ώۂ̏Փˑ���</param>
	/// <param name="hitInfo">�Փˏ��</param>
	/// <param name="maxDistance">�ő勗��</param>
	/// <returns>���C���C�ӂ̃R���C�_�[�ƌ����ꍇ��true�A����ȊO��false</returns>
	bool Raycast(Ray& ray, uint16_t attribute, RaycastHit* hitInfo = nullptr, float maxDistance = D3D12_FLOAT32_MAX);

	/// <summary>
	/// ���ɂ��ՓˑS����
	/// </summary>
	/// <param name="sphere">��</param>
	/// <param name="callback">�Փˎ��R�[���o�b�N</param>
	/// <param name="attribute">�Ώۂ̏Փˑ���</param>
	void QuerySphere(Sphere& sphere, QueryCallback* callback, uint16_t attribute = static_cast<uint16_t>(0xffffffff));

private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	~CollisionManager() = default;
	CollisionManager& operator=(const CollisionManager&) = delete;

	// �R���C�_�[�̃��X�g
	std::forward_list<BaseCollider*> colliders;
};


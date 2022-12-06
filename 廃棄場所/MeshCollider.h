#pragma once
#include "BaseCollider.h"
#include"CollisionPrimitive.h"
#include"AliceMath.h"
#include"ModelInterface.h"

/// <summary>
/// ���b�V���Փ˔���I�u�W�F�N�g
/// </summary>
class MeshCollider : public BaseCollider
{
private:
	std::vector<Triangle>triangle;
	//���[���h�s��
	AliceMath::Matrix4 invMatWorld;
public:
	MeshCollider();

	/// <summary>
	/// �O�p�`�̔z����\�z����
	/// </summary>
	void CnnstructTriangles(ModelInterface* model);

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update()override;

	virtual void SetModel(ModelInterface* model)override;

	virtual ModelInterface* GetModel()override;

	virtual CollisionShapeType GetShapeType()override;

	virtual void OnCollision(const CollisionInfo& info)override;

	/// <summary>
	/// ���Ƃ̓����蔻��
	/// </summary>
	/// <param name="sphere">��</param>
	/// <param name="inter">��_(�o�͗p)</param>
	/// <returns>�������Ă��邩</returns>
	bool CheckCollisionSphere(Sphere& sphere, AliceMath::Vector3* inter = nullptr, AliceMath::Vector3* reject = nullptr);

	/// <summary>
	/// ���C�Ƃ̓����蔻��
	/// </summary>
	/// <param name="ray">���C</param>
	/// <param name="distance">����(�o�͗p)</param>
	/// <param name="inter">��_(�o�͗p)</param>
	/// <returns>�������Ă��邩</returns>
	bool CheckCollisionRay(Ray& ray, float* distance = nullptr, AliceMath::Vector3* inter = nullptr);

	virtual void SetAttribute(uint16_t attribute_)override;

	virtual void AddAttribute(uint16_t attribute_)override;

	virtual void RemoveAttribute(uint16_t attribute_)override;

};


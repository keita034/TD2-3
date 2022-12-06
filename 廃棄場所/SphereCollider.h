#pragma once
#include"BaseCollider.h"
#include"AliceMath.h"
#include"CollisionInfo.h"
#include"CollisionPrimitive.h"
#include"ModelInterface.h"

class SphereCollider : public BaseCollider,public Sphere
{
private:
	// �I�u�W�F�N�g���S����̃I�t�Z�b�g
	AliceMath::Vector3 offset;
	// ���a
	float radius;

public:
	SphereCollider(AliceMath::Vector3 offset = { 0,0,0 }, float radius = 1.0f);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	void SetRadius(float radius_);

	virtual void SetModel(ModelInterface* model_)override;

	virtual ModelInterface* GetModel()override;

	virtual CollisionShapeType GetShapeType()override;

	virtual void OnCollision(const CollisionInfo& info)override;

	virtual void SetAttribute(uint16_t attribute_)override;

	virtual void AddAttribute(uint16_t attribute_)override;

	virtual void RemoveAttribute(uint16_t attribute_)override;

	AliceMath::Vector3& GetOffset();

	void SetOffset(AliceMath::Vector3& offset_);

	float GetRadius();
};


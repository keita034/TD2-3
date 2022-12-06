#pragma once

#include "CollisionShapeType.h"
#include"CollisionInfo.h"
class ModelInterface;

/// <summary>
/// �R���C�_�[���N���X
/// </summary>
class BaseCollider
{
public:
	BaseCollider() = default;
	virtual ~BaseCollider() = default;

	virtual void SetModel(ModelInterface* model) = 0;

	virtual ModelInterface* GetModel() = 0;

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() = 0;

	virtual CollisionShapeType GetShapeType() = 0;

	virtual void OnCollision(const CollisionInfo& info) = 0;

	friend class CollisionManager;

	virtual void SetAttribute(uint16_t attribute_) = 0;
	
	virtual void AddAttribute(uint16_t attribute_) = 0;

	virtual void RemoveAttribute(uint16_t attribute_) = 0;

protected:
	ModelInterface* model = nullptr;

	//�`��^�C�v
	CollisionShapeType shapeType = ShapeUnknown;

	//�����蔻�葮��
	uint16_t attribute = static_cast<uint16_t>(0b111111111111111111);

	char PADDING[2]{};
};
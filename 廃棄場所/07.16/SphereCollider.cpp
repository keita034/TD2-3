#include "SphereCollider.h"

SphereCollider::SphereCollider(AliceMath::Vector4 offset, float radius) :
	offset(offset),
	radius(radius)
{
	// ���`����Z�b�g
	shapeType = CollisionShapeSphere;
}

void SphereCollider::Update()
{
	// ���[���h�s�񂩂���W�𒊏o
	const AliceMath::Matrix4 matWorld = model->GetMatWorld();

	// ���̃����o�ϐ����X�V
	center =
	{
		matWorld.m[3][0] + offset.x,
		matWorld.m[3][1] + offset.y,
		matWorld.m[3][2] + offset.z,
		matWorld.m[3][3] + offset.w
	};

	radius = radius;
}

void SphereCollider::SetRadius(float radius_)
{
	radius = radius_;
}

void SphereCollider::SetModel(ModelInterface* model_)
{
	model = model_;
}

ModelInterface* SphereCollider::GetModel()
{
	return model;


CollisionShapeType SphereCollider::GetShapeType()
{
	return shapeType;
}

void SphereCollider::OnCollision(const CollisionInfo& info)
{
	model->OnCollision(info);
}

void SphereCollider::SetAttribute(uint16_t attribute_)
{
	attribute = attribute_;
}

void SphereCollider::AddAttribute(uint16_t attribute_)
{
	attribute |= attribute_;
}

void SphereCollider::RemoveAttribute(uint16_t attribute_)
{
	attribute &= !attribute_;
}

AliceMath::Vector4& SphereCollider::GetOffset()
{
	return offset;
}

void SphereCollider::SetOffset(AliceMath::Vector4& offset_)
{
	offset = offset_;
}

float SphereCollider::GetRadius()
{
	return radius;
}

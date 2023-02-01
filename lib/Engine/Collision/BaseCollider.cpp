#include "BaseCollider.h"

CollisionShapeType BaseCollider::GetShapeType()
{
	return shapeType;
}

void BaseCollider::SetAttribute(unsigned short attr)
{
	attribute = attr;
}

void BaseCollider::AddAttribute(unsigned short attr)
{
	attribute |= attr;
}

void BaseCollider::RemoveAttribute(unsigned short attr)
{
	attribute &= !attr;
}



#include "CollisionInfo.h"

CollisionInfo::CollisionInfo(BaseCollider* coll, const AliceMathF::Vector4& inte)
{
	collider = coll;
	inter = inte;
}

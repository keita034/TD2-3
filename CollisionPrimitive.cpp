#include "CollisionPrimitive.h"

using namespace DirectX;

void Triangle::ComputeNormal()
{

	AliceMathF::Vector4 p0_p1 = p1 - p0;
	AliceMathF::Vector4 p0_p2 = p2 - p0;

	normal = p0_p1.Vector3Cross(p0_p2);
	normal = normal.Vector3Normal();

}

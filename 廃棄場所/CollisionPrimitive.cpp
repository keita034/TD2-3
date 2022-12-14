#include"CollisionPrimitive.h"

void Triangle::ComputeNormal()
{
	AliceMath::Vector3 p0_p1 = p1 - p0;
	AliceMath::Vector3 p0_p2 = p2 - p0;

	//外積により、2辺に垂直なベクトルを算出する
	normal = p0_p1.cross(p0_p2);
	normal.normalization();

}
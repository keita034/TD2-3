#include "SphereCollider.h"
//#include "Object3d.h"

using namespace DirectX;

void SphereCollider::Update(const AliceMathF::Matrix4& worldPos)
{
	// ワールド行列から座標を抽出
	const AliceMathF::Matrix4& matWorld = worldPos;

	// 球のメンバ変数を更新
	Sphere::center = AliceMathF::Vector4(matWorld.m[3][0], matWorld.m[3][1], matWorld.m[3][2], matWorld.m[3][3]) + offset;
	Sphere::radius = radius;
}

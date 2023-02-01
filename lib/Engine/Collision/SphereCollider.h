#pragma once

#include "BaseCollider.h"
#include "CollisionPrimitive.h"

#include "AliceMathUtility.h"

/// <summary>
/// 球衝突判定オブジェクト
/// </summary>
class SphereCollider : public BaseCollider, public Sphere
{
public:
	SphereCollider(AliceMathF::Vector4 offset = {0,0,0,0}, float radius = 1.0f) :
		offset(offset),
		radius(radius)
	{
		// 球形状をセット
		shapeType = COLLISIONSHAPE_SPHERE;
	}

	/// <summary>
	/// 更新
	/// </summary>
	void Update(const AliceMathF::Matrix4& worldPos) override;

	void SetRadius(float radius);

	const AliceMathF::Vector4& GetOffset();
	void SetOffset(const AliceMathF::Vector4& off);
	float GetRadius();

private:
	// オブジェクト中心からのオフセット
	AliceMathF::Vector4 offset;
	// 半径
	float radius;
};


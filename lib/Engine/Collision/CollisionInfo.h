#pragma once

#include "AliceMathUtility.h"

class BaseCollider;

/// <summary>
/// 衝突情報
/// </summary>
struct CollisionInfo
{
public:
	CollisionInfo(BaseCollider* coll, const AliceMathF::Vector4& inte);

	// 衝突相手のコライダー
	BaseCollider* collider = nullptr;
	// 衝突点
	AliceMathF::Vector4 inter;
};


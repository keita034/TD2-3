#pragma once

#include <DirectXMath.h>

class BaseCollider;

/// <summary>
/// 衝突情報
/// </summary>
struct CollisionInfo
{
public:
	CollisionInfo(BaseCollider* collider, const DirectX::XMVECTOR& inter) {
		this->collider = collider;
		this->inter = inter;
	}

	// 衝突相手のコライダー
	BaseCollider* collider = nullptr;
	// 衝突点
	DirectX::XMVECTOR inter;
};


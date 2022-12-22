#pragma once

#include "CollisionTypes.h"
#include "CollisionInfo.h"
#include "Player.h"

/// <summary>
/// コライダー基底クラス
/// </summary>
class BaseCollider
{
public:
	BaseCollider() = default;
	virtual ~BaseCollider() = default;

	inline void SetObject(Player* player) {
		this->player = player;
	}

	inline Player* GetObject3d() {
		return player;
	}

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

	inline CollisionShapeType GetShapeType() { return shapeType; }
	
	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	/// <param name="info">衝突情報</param>
	inline void OnCollision(const CollisionInfo& info) {
		player->OnCollision(info);
	}

protected:
	Player* player = nullptr;
	// 形状タイプ
	CollisionShapeType shapeType = SHAPE_UNKNOWN;
};


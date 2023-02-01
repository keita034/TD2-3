#pragma once

#include "CollisionTypes.h"
#include "CollisionInfo.h"
#include"AliceMathUtility.h"

/// <summary>
/// コライダー基底クラス
/// </summary>
class BaseCollider
{
public:
	friend class CollisionManager;
	BaseCollider() = default;
	virtual ~BaseCollider() = default;


	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update(const AliceMathF::Matrix4& worldPos) = 0;

	CollisionShapeType GetShapeType();

	/// <summary>
	/// 当たり判定属性をセット
	/// </summary>
	/// <param name="attribute">当たり判定属性</param>
	void SetAttribute(unsigned short attr);

	/// <summary>
	/// 当たり判定属性を追加
	/// </summary>
	/// <param name="attribute">当たり判定属性</param>
	void AddAttribute(unsigned short attr);
		
	/// <summary>
	/// 当たり判定属性を削除
	/// </summary>
	/// <param name="attribute">当たり判定属性</param>
	void RemoveAttribute(unsigned short attr);

protected:
	// 形状タイプ
	CollisionShapeType shapeType = SHAPE_UNKNOWN;
	// 当たり判定属性
	unsigned short attribute = 0b1111111111111111;

	char PADING[2]{};
};


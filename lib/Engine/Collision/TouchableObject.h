#pragma once
#include "Model.h"
#include "CollisionAttribute.h"

class TouchableObject :
	public Model
{
private:

	Transform* trans;

public:
	/// <summary>
	/// オブジェクト生成
	/// </summary>
	/// <returns></returns>
	static TouchableObject* Create(uint32_t modelHandle, Transform* transform);

	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>成否</returns>
	bool Initialize(uint32_t modelHandle, Transform* transform);
};


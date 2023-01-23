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
	/// �I�u�W�F�N�g����
	/// </summary>
	/// <returns></returns>
	static TouchableObject* Create(uint32_t modelHandle, Transform* transform);

	/// <summary>
	/// ������
	/// </summary>
	/// <returns>����</returns>
	bool Initialize(uint32_t modelHandle, Transform* transform);
};


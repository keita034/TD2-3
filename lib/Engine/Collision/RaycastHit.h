#pragma once

#include "BaseCollider.h"
#include<DirectXMath.h>


struct RaycastHit{

	BaseCollider* collider = nullptr; 

	AliceMathF::Vector4 inter;

	float distance = 0.0f;

};
#pragma once

#include "BaseCollider.h"
#include<DirectXMath.h>


struct RaycastHit{

	BaseCollider* collider = nullptr; 

	DirectX::XMVECTOR inter;

	float distance = 0.0f;

};
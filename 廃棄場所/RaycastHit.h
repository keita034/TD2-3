#pragma once
#include"BaseCollider.h"
#include"ModelInterface.h"
#include"AliceMath.h"

struct RaycastHit
{
	//�Փˑ���̃I�u�W�F�N�g
	ModelInterface* model = nullptr;
	//�Փˑ���̃R���C�_�[
	BaseCollider* collider = nullptr;
	//�Փ˓_
	AliceMath::Vector3 inter;
	//�Փ˓_�܂ł̋���
	float distance = 0.0f;

};

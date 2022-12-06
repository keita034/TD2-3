#pragma once
#include"AliceMath.h"

class ModelInterface;
class BaseCollider;

// <summary>
/// �Փˏ��
/// </summary>
struct CollisionInfo
{
	CollisionInfo(ModelInterface* object, BaseCollider* collider, const AliceMath::Vector3& inter);

	// �Փˑ���̃I�u�W�F�N�g
	ModelInterface* object = nullptr;
	// �Փˑ���̃R���C�_�[
	BaseCollider* collider = nullptr;
	// �Փ˓_
	AliceMath::Vector3 inter;
	char PADDING[4]{};
};
#pragma once
#include "BaseCollider.h"

class ModelInterface;

/// <summary>
/// ���C�L���X�g�ɂ����𓾂�ׂ̍\����
/// </summary>
struct RaycastHit
{
	// �Փˑ���̃I�u�W�F�N�g
	ModelInterface* object = nullptr;
	// �Փˑ���̃R���C�_�[
	BaseCollider* collider = nullptr;
	// �Փ˓_
	AliceMath::Vector4 inter;
	// �Փ˓_�܂ł̋���
	float distance = 0.0f;
	char PADDING[4]{};
};
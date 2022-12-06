#pragma once
#include"AliceMath.h"
#include"ModelInterface.h"

/// <summary>
/// �N�G���[�ɂ����𓾂�ׂ̍\����
/// </summary>
struct QueryHit
{
	// �Փˑ���̃I�u�W�F�N�g
	ModelInterface* object = nullptr;
	// �Փˑ���̃R���C�_�[
	BaseCollider* collider = nullptr;
	// �Փ˓_
	AliceMath::Vector4 inter;
	// �r�˃x�N�g��
	AliceMath::Vector4 reject;
};

/// <summary>
/// �N�G���[�Ō��������o�������̓�����K�肷��N���X
/// </summary>
class QueryCallback
{
public:
	QueryCallback() = default;
	virtual ~QueryCallback() = default;

	/// <summary>
	/// �������R�[���o�b�N
	/// </summary>
	/// <param name="info">�������</param>
	/// <returns>�N�G���[�𑱂���Ȃ�true�A�ł��؂�Ȃ�false��Ԃ�</returns>
	virtual bool OnQueryHit(QueryHit& info) = 0;
};


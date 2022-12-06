#pragma once
#include"AliceMath.h"

class ModelInterface;
class BaseCollider;

/// <summary>
/// �N�G���[�ɂ����𓾂邽�߂̍\����
/// </summary>
struct QueryHit
{
	//�Փˑ���̃I�u�W�F�N�g
	ModelInterface* model = nullptr;
	//�Փˑ���̃R���C�_�[
	BaseCollider* collider = nullptr;
	//���˓_
	AliceMath::Vector3 inter;
	//�r�˃x�N�g��
	AliceMath::Vector3 reject;
};

/// <summary>
/// �N�G���[�Ō��������o�������̓�������肷��N���X
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
	/// <returns>�N�G���[�𑱂���Ȃ�true,�ł��؂�Ȃ�false��Ԃ�</returns>
	virtual bool OnQueryHit(QueryHit& info) = 0;

};
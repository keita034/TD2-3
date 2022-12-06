#pragma once
#include"ErrorException.h"
#include"AliceMathUtility.h"
#include"Camera.h"
#include"ConstantBuffer.h"
#include"AliceUtility.h"

class Transform
{
private:
	// �萔�o�b�t�@
	std::shared_ptr<ConstantBuffer> constBuff;
	//�萔�o�b�t�@�̃}�b�s���O�p�|�C���^
	worldViewpojCamera constBuffMap;

	//�������p�̃r���[�s��v�Z
	static AliceMathF::Matrix4 defaultViewMat;

	//�������p�̃v���W�F�N�V�����s��v�Z
	static AliceMathF::Matrix4 defaultProjectionMat;


public:
	// ���[�J�����W
	AliceMathF::Vector3 translation = { 0.0f, 0.0f, 0.0f };
	// X,Y,Z�����̃��[�J����]�p
	AliceMathF::Vector3 rotation = { 0.0f, 0.0f, 0.0f };
	// ���[�J���X�P�[��
	AliceMathF::Vector3 scale = { 1.0f, 1.0f, 1.0f };

	AliceMathF::Matrix4 matWorld;

	// �e�ƂȂ郏�[���h�ϊ��ւ̃|�C���^
	const Transform* parent = nullptr;

public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �s���]������
	/// </summary>
	void TransUpdate(Camera* camera);

	void Update();

	void MakeWorldMatrix();

	ID3D12Resource* GetconstBuff();

	worldViewpojCamera* GetWorldViewpojCamera();
};

namespace AliceMathF
{
	Matrix4 MakeWorldMatrix4(Transform& transform);

	/// <summary>
	/// ���[���h���W�擾
	/// </summary>
	Vector3 GetWorldPosition(Transform& transform);
}
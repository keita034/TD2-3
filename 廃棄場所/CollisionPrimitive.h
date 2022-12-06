#pragma once
/// <summary>
///�����蔻��v���~�e�B�u
/// </summary>

#include"AliceMath.h"

/// <summary>
/// ��
/// </summary>
struct Sphere
{
	//���S���W
	AliceMath::Vector3 center = { 0.0f,0.0f,0.0f };
	//���a
	float radius = 1.0f;
};

/// <summary>
/// ����
/// </summary>
struct Plane
{
	//�@���x�N�g��
	AliceMath::Vector3 normal = { 0.0f,1.0f,0.0f };
	//���_�_(0,0,0)����̋���
	float distane = 0.0f;
};

/// <summary>
/// �@���t���O�p�`(���v��肪�\��)
/// </summary>
struct Triangle
{
	//���_���W3��
	AliceMath::Vector3 p0;
	AliceMath::Vector3 p1;
	AliceMath::Vector3 p2;
	//�@���x�N�g��
	AliceMath::Vector3 normal;

	/// <summary>
	/// �@���̌v�Z
	/// </summary>
	void ComputeNormal();
};

/// <summary>
/// ���C(������)
/// </summary>
struct Ray
{
	//�n�_���W
	AliceMath::Vector3 start = { 0,0,0 };
	//����
	AliceMath::Vector3 dir = { 1,0,0 };
};
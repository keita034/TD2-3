#pragma once
#include"ErrorException.h"
#include"Vector4.h"
#include"Vector3.h"
#include"Matrix4.h"
namespace AliceMathF
{
	class Quaternion
	{
	public:
		float x;
		float y;
		float z;
		float w;

		//�N�I�[�^�j�I�����쐬
		Quaternion(float x = 0.0f, float y = 0.0f, float z = 9.0f, float w = 1.0f);
		Quaternion(const Vector3& v, float angle);
		Quaternion(const Matrix4& m);
		Quaternion(const aiQuaternion& q);
		Quaternion(const Vector4& v);

		//���ς����߂�
		float Dot(const Quaternion& q);

		//�m���������߂�
		float Length();
		//���K������
		Quaternion Normalize();
		//�P�����Z�q�I�[�o�[���[�h
		Quaternion operator + ()const;
		Quaternion operator - ()const;
		//������Z�q�I�[�o�[���[�h
		Quaternion& operator += (const Quaternion& q);
		Quaternion& operator -= (const Quaternion& q);
		Quaternion& operator *= (float s);
		Quaternion& operator /= (float s);
		Quaternion& operator *= (const Quaternion& q);

		Quaternion Slerp(const Quaternion& q, float t);
		Quaternion Lerp(const Quaternion& q, float t);
		Matrix4 Rotate();

		Vector3 GetAxis();

		Vector4 GetElement();
	};



	//2�����Z�q�I�[�o�[���[�h
	const Quaternion operator + (const Quaternion& q1, const Quaternion& q2);
	const Quaternion operator - (const Quaternion& q1, const Quaternion& q2);
	const Quaternion operator * (const Quaternion& q1, const Quaternion& q2);
	const Quaternion operator * (const Quaternion& q, float s);
	const Quaternion operator * (float s, const Quaternion& q);
	const Quaternion operator / (const Quaternion& q, float s);

	void QuaternionSlerp(Vector4& vOut, const aiQuaternion& qStart, const aiQuaternion& qEnd, float t);
}
#pragma once
#include"Vector3.h"
#include"Matrix4.h"

class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	//�N�I�[�^�j�I�����쐬

	//�������w�肵�� �N�H�[�^�j�I�����쐬
	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);

	//�C�ӎ��܂��̉�]�̎w�肩��N�H�[�^�j�I�����쐬
	Quaternion(const Vector3& v, float angle);

	//��]�s�񂩂�N�H�[�^�j�I�����쐬
	Quaternion(const Matrix4& m);

	//�x�N�g������x�N�g���̊p�x
	Quaternion(const Vector3& u, const Vector3& v);

	//���ς����߂�
	float Dot(const Quaternion& q)const;

	//�m���������߂�
	float Norm()const;

	//���K������
	Quaternion Normalize() const;

	//�P�ʃN�I�[�^�j�I��
	Quaternion Identity() const;

	// �����N�I�[�^�j�I��
	Quaternion Conjugate() const;

	// �t�N�I�[�^�j�I��
	Quaternion Inverse() const;

	//�N�I�[�^�j�I�����ʐ��`���
	Quaternion Slerp(const Quaternion& q, float t);

	//�N�I�[�^�j�I�����`���
	Quaternion Lerp(const Quaternion& q, float t);

	//�N�I�[�^�j�I�������]�s������߂�
	Matrix4 Rotate();

	//��]���̎Z�o
	Vector3 GetAxis();

	//�I�C���[�p�ɕϊ�
	Vector3 GetEulerAngles();

	//�I�C���[�p����N�I�[�^�j�I���ɕϊ�
	void SeTEuler(const Vector3& rot);

	//�P�����Z�q�I�[�o�[���[�h
	Quaternion operator + ();
	Quaternion operator - ()const;

	//������Z�q�I�[�o�[���[�h
	Quaternion& operator += (const Quaternion& q);
	Quaternion& operator -= (const Quaternion& q);
	Quaternion& operator *= (float s);
	Quaternion& operator /= (float s);
	Quaternion& operator *= (const Quaternion& q);

};

//2�����Z�q�I�[�o�[���[�h
const Quaternion operator + (const Quaternion& q1, const Quaternion& q2);
const Quaternion operator - (const Quaternion& q1, const Quaternion& q2);
const Quaternion operator * (const Quaternion& q1, const Quaternion& q2);
const Quaternion operator * (const Quaternion& q, float s);
const Quaternion operator * (float s, const Quaternion& q);
const Quaternion operator / (const Quaternion& q, float s);
const Vector3 operator*(Quaternion q, Vector3 vec);
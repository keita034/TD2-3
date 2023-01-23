#pragma once
#include"ErrorException.h"

namespace AliceMathF
{
	//3�����x�N�g��
	class Vector3
	{
	public:
		float x;//x����
		float y;//y����
		float z;//z����

	public:
		//�R���X�g���N�^
		Vector3();//��x�N�g��
		Vector3(float x, float y, float z);//�������w�肵�Đ���
		Vector3(aiVector3D& aiVector);

		float Length()const;//�m���������߂�
		Vector3 Normalization()const;//���K������
		Vector3& Normal();//���K������
		float Dot(const Vector3& v)const;//���ς����߂�
		Vector3 Cross(const Vector3& v)const;//�O�ς����߂�

		//�P�����Z�q�I�[�o�[���[�h
		Vector3 operator+() const;
		Vector3 operator-() const;

		// ������Z�q�I�[�o�[���[�h
		Vector3& operator+=(const Vector3& v);
		Vector3& operator-=(const Vector3& v);
		Vector3& operator-=(float s);
		Vector3& operator*=(float s);
		Vector3& operator/=(float s);
		bool operator==(const Vector3& v)const;
		bool operator!=(const Vector3& v) const;
	};

	//2�����Z�q�I�[�o�[���[�h
	//�������Ȉ����̃p�^�[���ɑΉ�(�����̏���)���邽�߁A�ȉ��̂悤�ɏ������Ă�
	const Vector3 operator+(const Vector3& v1, const Vector3& v2);
	const Vector3 operator-(const Vector3& v1, const Vector3& v2);
	const Vector3 operator-(const Vector3& v, float s);
	const Vector3 operator*(const Vector3& v, float s);
	const Vector3 operator*(float s, const Vector3& v);
	const Vector3 operator/(const Vector3& v, float s);

	/// <summary>
	/// �����𔽓]
	/// </summary>
	Vector3 Negate(const Vector3& vec);


}


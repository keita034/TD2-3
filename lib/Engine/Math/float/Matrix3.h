#pragma once
#include"ErrorException.h"
#include"Vector2.h"

namespace AliceMathF
{

	class Matrix3
	{
	public:
		std::array<std::array<float, 3>, 3>m;

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <returns>�P�ʍs��Ƃ��ď���������܂�</returns>
		Matrix3();

		Matrix3(
			float m00, float m01, float m02,
			float m10, float m11, float m12,
			float m20, float m21, float m22
		);

		Matrix3(const Vector2& scale, float angle, const Vector2& trans);

		Matrix3(const aiMatrix3x3& mat);

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		Matrix3(const DirectX::XMFLOAT3X3& Matrix3);

		/// <summary>
		/// �g��s����쐬
		/// </summary>
		/// <param name="scale"> : �g�嗦</param>
		void MakeScaling(const Vector2& scale);

		/// <summary>
		/// �g��s����쐬
		/// </summary>
		/// <param name="x,y"> : �g�嗦</param>
		void MakeScaling(float x, float y);

		/// <summary>
		/// ���s�ړ��s����쐬
		/// </summary>
		/// <param name="trans"> : ���s�ړ�</param>
		void MakeTranslation(const Vector2& trans);

		/// <summary>
		/// ���s�ړ��s����쐬
		/// </summary>
		/// <param name="x,y"> : ���s�ړ�</param>
		void MakeTranslation(float x, float y);

		/// <summary>
		/// X������̉�]�s����쐬
		/// </summary>
		/// <param name="angle"> : ��]�p�x(�P�ʁF���W�A��)</param>
		void MakeRotation(float angle);

		/// <summary>
		/// DirectX::XMMATRIX�^�ւ̈Öق̌^�ϊ��B
		/// </summary>
		operator DirectX::XMFLOAT3X3() const;

		/// <summary>
		/// ������Z�q
		/// </summary>
		Matrix3& operator=(const Matrix3& _m);
		const Matrix3& operator=(Matrix3& _m);
		/// <summary>
		/// ���Z
		/// </summary>
		Matrix3& operator+=(const Matrix3& mat);

		/// <summary>
		/// ���Z
		/// </summary>
		Matrix3& operator-=(const Matrix3& mat);

		/// <summary>
		/// ��Z
		/// </summary>
		Matrix3& operator*=(const Matrix3& mat);

		/// <summary>
		/// ���Z
		/// </summary>
		Matrix3 operator+(const Matrix3& mat) const;

		/// <summary>
		/// ���Z
		/// </summary>
		Matrix3 operator-(const Matrix3& mat) const;

		/// <summary>
		/// ��Z
		/// </summary>
		Matrix3 operator*(const Matrix3& mat) const;

		Matrix3 Transpose();
	};

	/// <summary>
	/// �P�ʍs��
	/// </summary>
	Matrix3 MakeMat3Identity();

	/// <summary>
	/// �t�s������߂�
	/// </summary>
	/// <param name="mat">�t�s��ɂ������s��</param>
	/// <returns>�t�s��or�P�ʍs��</returns>
	Matrix3 MakeInverse(const Matrix3* mat);
}


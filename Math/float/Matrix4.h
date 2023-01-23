#pragma once
#include"ErrorException.h"
#include"Vector3.h"

namespace AliceMathF
{
	class Quaternion;

	class Matrix4
	{
	public:
		float m[4][4];

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <returns>�P�ʍs��Ƃ��ď���������܂�</returns>
		Matrix4();

		Matrix4(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);

		Matrix4(const Vector3& scale, Quaternion& rotat, const Vector3& trans);

		Matrix4(const aiMatrix4x4& mat);

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		Matrix4(const DirectX::XMMATRIX& Matrix4);

		/// <summary>
		/// �g��s����쐬
		/// </summary>
		/// <param name="scale"> : �g�嗦</param>
		void MakeScaling(const Vector3& scale);

		/// <summary>
		/// �g��s����쐬
		/// </summary>
		/// <param name="x,y,z"> : �g�嗦</param>
		void MakeScaling(float x, float y, float z);

		/// <summary>
		/// ���s�ړ��s����쐬
		/// </summary>
		/// <param name="trans"> : ���s�ړ�</param>
		void MakeTranslation(const Vector3& trans);

		/// <summary>
		/// ���s�ړ��s����쐬
		/// </summary>
		/// <param name="x,y,z"> : ���s�ړ�</param>
		void MakeTranslation(float x, float y, float z);

		/// <summary>
		/// Y������̉�]�s����쐬
		/// </summary>
		/// <param name="angle"> : ��]�p�x(�P�ʁF���W�A��)</param>
		void MakeRotationY(float angle);

		/// <summary>
		/// Z������̉�]�s����쐬
		/// </summary>
		/// <param name="angle"> : ��]�p�x(�P�ʁF���W�A��)</param>
		void MakeRotationZ(float angle);

		/// <summary>
		/// X������̉�]�s����쐬
		/// </summary>
		/// <param name="angle"> : ��]�p�x(�P�ʁF���W�A��)</param>
		void MakeRotationX(float angle);

		/// <summary>
		/// X������̉�]�s����쐬
		/// </summary>
		/// <param name="Rotat"> : ��]�p�x(�P�ʁF���W�A��)</param>
		void MakeRotation(const Vector3& Rotat);

		/// <summary>
		/// X������̉�]�s����쐬
		/// </summary>
		/// <param name="x,y,z"> : ��]�p�x(�P�ʁF���W�A��)</param>
		void MakeRotation(float x, float y, float z);

		/// <summary>
		/// DirectX::XMMATRIX�^�ւ̈Öق̌^�ϊ��B
		/// </summary>
		operator DirectX::XMMATRIX() const;

		/// <summary>
		/// ������Z�q
		/// </summary>
		Matrix4& operator=(const Matrix4& _m);
		const Matrix4& operator=(Matrix4& _m);
		/// <summary>
		/// ���Z
		/// </summary>
		Matrix4& operator+=(const Matrix4& mat);

		/// <summary>
		/// ���Z
		/// </summary>
		Matrix4& operator-=(const Matrix4& mat);

		/// <summary>
		/// ��Z
		/// </summary>
		Matrix4& operator*=(const Matrix4& mat);

		/// <summary>
		/// ���Z
		/// </summary>
		Matrix4 operator+(const Matrix4& mat) const;

		/// <summary>
		/// ���Z
		/// </summary>
		Matrix4 operator-(const Matrix4& mat) const;

		/// <summary>
		/// ��Z
		/// </summary>
		Matrix4 operator*(const Matrix4& mat) const;

		Matrix4& Transpose();
	};

	/// <summary>
	/// �P�ʍs��
	/// </summary>
	Matrix4 MakeIdentity();

	/// <summary>
	/// �t�s������߂�
	/// </summary>
	/// <param name="mat">�t�s��ɂ������s��</param>
	/// <returns>�t�s��or�P�ʍs��</returns>
	Matrix4 MakeInverse(const Matrix4* mat);

	/// <summary>
	/// ���s���e�ϊ��s��𐶐�(����n)
	/// </summary>
	/// <param name="left"> : ����</param>
	/// <param name="right"> : �E��</param>
	/// <param name="bottom"> : ����</param>
	/// <param name="top"> : �㑤</param>
	/// <param name="near_"> : �j�A�N���b�v����</param>
	/// <param name="far_"> : �t�@�[�N���b�v����</param>
	/// <param name="matrix"> : �������s��</param>
	void MakeOrthogonalL(float left, float right, float bottom, float top, float near_, float far_, Matrix4& matrix);

	/// <summary>
	/// ���s���e�ϊ��s��𐶐�(�E��n)
	/// </summary>
	/// <param name="left"> : ����</param>
	/// <param name="right"> : �E��</param>
	/// <param name="bottom"> : ����</param>
	/// <param name="top"> : �㑤</param>
	/// <param name="near_"> : �j�A�N���b�v����</param>
	/// <param name="far_"> : �t�@�[�N���b�v����</param>
	/// <param name="matrix"> : �������s��</param>
	void MakeOrthogonalR(float left, float right, float bottom, float top, float near_, float far_, Matrix4& matrix);

	/// <summary>
	/// �������e�ϊ��s��𐶐�(����n)
	/// </summary>
	/// <param name="fovAngleY"> : �㉺��p</param>
	/// <param name="aspect"> : �A�X�y�N�g��(��ʉ���/��ʏc��)</param>
	/// <param name="near_"> : �j�A�N���b�v����</param>
	/// <param name="far_"> : �t�@�[�N���b�v����</param>
	/// <param name="matrix"> : �������s��</param>
	void MakePerspectiveL(float fovAngleY, float aspect, float near_, float far_, Matrix4& matrix);

	/// <summary>
	/// �������e�ϊ��s��𐶐�(�E��n)
	/// </summary>
	/// <param name="fovAngleY"> : �㉺��p</param>
	/// <param name="aspect"> : �A�X�y�N�g��(��ʉ���/��ʏc��)</param>
	/// <param name="near_"> : �j�A�N���b�v����</param>
	/// <param name="far_"> : �t�@�[�N���b�v����</param>
	/// <param name="matrix"> : �������s��</param>
	void MakePerspectiveR(float fovAngleY, float aspect, float near_, float far_, Matrix4& matrix);

	/// <summary>
	/// �x�N�g���ƍs��̊|���Z
	/// </summary>
	/// <param name="x">�|������x�N�g����X���W</param>
	/// <param name="y">�|������x�N�g����Y���W</param>
	/// <param name="z">�|������x�N�g����Z���W</param>
	/// <param name="mat">�|����s��</param>
	void CoordinateTransformation3D(float& x, float& y, float& z, Matrix4& mat);

	/// <summary>
	/// �r���[�ϊ��s��𐶐�
	/// </summary>
	/// <param name="eye"></param>
	/// <param name="target"></param>
	/// <param name="up"></param>
	void MakeLookL(const Vector3& eye, const Vector3& target, const Vector3& up, Matrix4& mat);
}


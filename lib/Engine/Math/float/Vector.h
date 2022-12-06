#pragma once
#include"Vector2.h"
#include"Vector3.h"
#include"Vector4.h"
#include"Matrix4.h"

namespace AliceMathF
{
	const Vector4 operator+(const Vector3& v1, const Vector4& v2);

	/// <summary>
	/// Vector4��Vector3�ɕϊ�
	/// </summary>
	/// <param name="vec">�ϊ�����x�N�g��</param>
	/// <returns>Vector3</returns>
	Vector3 TrnsVec3(const Vector4& vec);

	/// <summary>
	/// Vector3��Vector4�ɕϊ�
	/// </summary>
	/// <param name="vec">�ϊ�����x�N�g��</param>
	/// <param name="matFlag">w��1�ɂ��邩�ǂ���</param>
	/// <returns>Vector4</returns>
	Vector4 TrnsVec4(const Vector3& vec, bool matFlag = false);

	/// <summary>
	/// �x�N�g���ƍs��̊|���Z
	/// </summary>
	/// <param name="vec">�x�N�g��</param>
	/// <param name="mat">�s��</param>
	/// <returns>�v�Z���ꂽ�l</returns>
	Vector3 Vec3Mat4Mul(const Vector3& vec, const Matrix4& mat);

	/// <summary>
	/// �x�N�g���ƍs��̊|���Z(W���Z)
	/// </summary>
	/// <param name="vec">�x�N�g��</param>
	/// <param name="mat">�s��</param>
	/// <returns>�v�Z���ꂽ�l</returns>
	Vector3& Vec3Mat4MulWdiv(const Vector3& vec, const Matrix4& mat);

	/// <summary>
	/// �x�N�g���ƍs��̊|���Z
	/// </summary>
	/// <param name="vec">�x�N�g��</param>
	/// <param name="mat">�s��</param>
	/// <returns>�v�Z���ꂽ�l</returns>
	Vector4 Vec4Mat4Mul(const Vector4& vec, const Matrix4& mat);

	Vector3 Vector3Lerp(const Vector3& src1, const Vector3& src2, float t);
}
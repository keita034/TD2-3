#include "Vector.h"
namespace AliceMathF
{
	const Vector4 operator+(const Vector3& v1, const Vector4& v2)
	{
		Vector4 tmp(v2);
		tmp.x += v1.x;
		tmp.y += v1.y;
		tmp.z += v1.z;
		tmp.w += 0;
		return tmp;
	}

	// Vector4��Vector3�ɕϊ�
	Vector3 TrnsVec3(const Vector4& vec)
	{
		return { vec.x,vec.y ,vec.z };
	}

	// Vector3��Vector4�ɕϊ�
	Vector4 TrnsVec4(const Vector3& vec, bool matFlag)
	{
		if (matFlag)
		{
			return { vec.x,vec.y,vec.z,1.0f };
		}
		return { vec.x,vec.y,vec.z,0.0f };
	}

	// �x�N�g���ƍs��̊|���Z
	Vector3 Vec3Mat4Mul(const Vector3& vec, const Matrix4& mat)
	{
		Vector3 retVec = {};

		retVec.x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0];

		retVec.y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1];

		retVec.z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2];

		return retVec;
	}

	Vector3& Vec3Mat4MulWdiv(const Vector3& vec, const Matrix4& mat)
	{
		Vector4 retVec = {};

		retVec.x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + 1 * mat.m[3][0];

		retVec.y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + 1 * mat.m[3][1];

		retVec.z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + 1 * mat.m[3][2];

		retVec.w = vec.x * mat.m[0][3] + vec.y * mat.m[1][3] + vec.z * mat.m[2][3] + 1 * mat.m[3][3];

		Vector3 tmp = { retVec.x, retVec.y, retVec.z };

		return tmp /= tmp.z;
	}

	// �x�N�g���ƍs��̊|���Z
	Vector4 Vec4Mat4Mul(const Vector4& vec, const Matrix4& mat)
	{
		Vector4 retVec = {};

		retVec.x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + vec.w * mat.m[3][0];

		retVec.y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + vec.w * mat.m[3][1];

		retVec.z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + vec.w * mat.m[3][2];

		return retVec;
	}

	Vector3 Vector3Lerp(const Vector3& src1, const Vector3& src2, float t)
	{
		Vector3 dest;

		dest.x = src1.x + (src2.x - src1.x) * t;
		dest.y = src1.y + (src2.y - src1.y) * t;
		dest.z = src1.z + (src2.z - src1.z) * t;

		return dest;
	}
}
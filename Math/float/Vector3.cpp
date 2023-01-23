#include "Vector3.h"
#include"AliceMathF.h"

namespace AliceMathF
{
	Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f)
	{}

	Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
	{}

	Vector3::Vector3(aiVector3D& aiVector)
	{
		x = aiVector.x;
		y = aiVector.y;
		z = aiVector.z;
	}

	float Vector3::Length() const
	{
		return Sqrt(x * x + y * y + z * z);
	}

	Vector3& Vector3::Normal()
	{
		float len = Length();
		if (len != 0)
		{
			return *this /= len;
		}

		return *this;
	}

	Vector3 Vector3::Normalization() const
	{
		Vector3 tmp(*this);

		float len = Length();
		if (len != 0)
		{
			return tmp /= len;
		}

		return tmp;
	}

	float Vector3::Dot(const Vector3& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	Vector3 Vector3::Cross(const Vector3& v) const
	{
		Vector3 w;
		w.x = y * v.z - z * v.y;
		w.y = z * v.x - x * v.z;
		w.z = x * v.y - y * v.x;

		return w;
	}

	Vector3 Vector3::operator+() const
	{
		return *this;
	}

	Vector3 Vector3::operator-() const
	{
		return  Vector3(-x, -y, -z);
	}

	Vector3& Vector3::operator+=(const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	Vector3& Vector3::operator-=(float s)
	{
		x -= s;
		y -= s;
		z -= s;

		return *this;
	}

	Vector3& Vector3::operator*=(float s)
	{
		x *= s;
		y *= s;
		z *= s;

		return *this;
	}

	Vector3& Vector3::operator/=(float s)
	{
		x /= s;
		y /= s;
		z /= s;

		return *this;
	}

	bool Vector3::operator==(const Vector3& v) const
	{
		if (Approximately(this->x, v.x) && Approximately(this->y, v.y) && Approximately(this->z, v.z))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Vector3::operator!=(const Vector3& v) const
	{
		if (Approximately(this->x, v.x) && Approximately(this->y, v.y) && Approximately(this->z, v.z))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	const Vector3 operator+(const Vector3& v1, const Vector3& v2)
	{
		Vector3 temp(v1);
		return temp += v2;
	}

	const Vector3 operator-(const Vector3& v1, const Vector3& v2)
	{
		Vector3 temp(v1);
		return temp -= v2;
	}

	const Vector3 operator-(const Vector3& v, float s)
	{
		Vector3 temp(v);
		return temp -= s;
	}

	const Vector3 operator*(const Vector3& v, float s)
	{
		Vector3 temp(v);
		return temp *= s;
	}

	const Vector3 operator*(float s, const Vector3& v)
	{
		return v * s;
	}

	const Vector3 operator/(const Vector3& v, float s)
	{
		Vector3 temp(v);
		return temp /= s;
	}

	Vector3 Negate(const Vector3& vec)
	{
		Vector3 retVec;
		retVec.x = -vec.x;
		retVec.y = -vec.y;
		retVec.z = -vec.z;

		return retVec;
	}

}
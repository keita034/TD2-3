#include "AliceMathF.h"
#include"AliceMathUtility.h"

namespace AliceMathF
{
#pragma region sin,cos,tan�֐�

#pragma region sin�֐�

	//sin�֐�
	float Sin(float sin)
	{
		return std::sinf(sin);
	}

	//asin�֐�
	float Asin(float sin)
	{
		return std::asinf(sin);
	}

#pragma endregion sin�֐�

#pragma region cos�֐�

	//cos�֐�
	float Cos(float cos)
	{
		return std::cosf(cos);
	}

	//acos�֐�
	float Acos(float cos)
	{
		return std::acosf(cos);
	}

#pragma endregion cos�֐�

#pragma region tan�֐�

	//tan�֐�
	float Tan(float tan)
	{
		return std::tanf(tan);
	}

	//atan�֐�
	float Atan(float tan)
	{
		return std::atanf(tan);
	}


	//atan2�֐�
	float Atan2(float y, float x)
	{
		return std::atan2f(y, x);
	}

#pragma endregion tan�֐�

	//sin�Acos�𗼕��o��
	void SinCos(float& sin_, float& cos_, float angle)
	{
		sin_ = Sin(angle);
		cos_ = Cos(angle);
	}

#pragma endregion sin,cos,tan�֐�

#pragma region �p�x�ϊ�

//�x���@���烉�W�A���ϊ�
	float ChangeRadians(const float& angle)
	{
		float radian = angle * Deg2Rad;
		return radian;
	}

	// ���W�A������x���@�ϊ�
	float ChangeDira(const float& angle)
	{
		float degree = angle * Rad2Deg;
		return degree;
	}


#pragma endregion �p�x�ϊ�

#pragma region sqrt�֐�

	//sqrt�֐�
	float Sqrt(float sqrt)
	{
		return std::sqrtf(sqrt);
	}

#pragma endregion sqrt�֐�

#pragma region pow�֐�

	//pow�֐�
	float Pow(float pow, float powNum)
	{
		return std::powf(pow, powNum);
	}

#pragma endregion pow�֐�

#pragma region exp�֐�

	//exp�֐�
	float Exp(float exp)
	{
		return std::expf(exp);
	}

#pragma endregion exp�֐�

#pragma region log�֐�

	//log�֐�
	float Log(float log)
	{
		return std::logf(log);
	}

	//log10�֐�
	float Log10(float log)
	{
		return std::log10f(log);
	}

#pragma endregion log�֐�

#pragma region ��Βl�̌v�Z

	//��Βl�̌v�Z
	float Abs(float abs)
	{
		return 	std::fabsf(abs);
	}

#pragma endregion ��Βl�̌v�Z

#pragma region ceil�֐�

	//ceil�֐�
	float Ceil(float ceil)
	{
		return std::ceilf(ceil);
	}

#pragma endregion ceil�֐�

#pragma region floor�֐�

	//floor�֐�
	float Floor(float floor)
	{
		return std::floorf(floor);
	}

#pragma endregion floor�֐�

#pragma region round�֐�

	//round�֐�
	float Round(float round)
	{
		return std::roundf(round);
	}

#pragma endregion round�֐�

	// �l�̕�����Ԃ�
	float Sign(float sign)
	{
		return (sign >= 0.0f) ? 1.0f : (-1.0f);
	}

	// �l��͈͓��ɔ[�߂�
	float Clamp(float Value, const float low, const float high)
	{
		if (high < Value)
		{
			Value = high;
		}

		if (Value < low)
		{
			Value = low;
		}

		return Value;
	}

	// 0��1�̊Ԃɒl��[�߁A���̒l��Ԃ�
	float Clamp01(float Value)
	{
		if (Value < 0.0f)
		{
			return 0.0f;
		}

		if (Value > 1.0f)
		{
			return 1.0f;
		}

		return Value;
	}

	// ���`���(0�`1)
	float Lerp(float a, float b, float t)
	{
		return a + (b - a) * Clamp01(t);
	}

	Vector3 Lerp(const Vector3& a, const Vector3& b, float t)
	{
		Vector3 tmp;
		tmp.x = a.x + (b.x - a.x) * Clamp01(t);
		tmp.y = a.y + (b.y - a.y) * Clamp01(t);
		tmp.z = a.z + (b.z - a.z) * Clamp01(t);
		return tmp;
	}

	Vector3 Slerp(const Vector3& v1, const Vector3& v2, float t)
	{
		Vector3 tmp1 = v1.Normalization();
		Vector3 tmp2 = v2.Normalization();
		float omega = Acos(tmp1.Dot(tmp2));

		float sinOmega = Sin(omega);

		Vector3 termOne = v1 * (Sin(omega * (1.0f - t)) / sinOmega);
		Vector3 termTwo = v2 * (Sin(omega * (t)) / sinOmega);

		return termOne + termTwo;
	}

	// ���`���(0�`)
	float LerpUnclamped(float a, float b, float t)
	{
		return a + (b - a) * t;
	}

	// Lerp�̊p�x��(0�`1)
	float LerpAngle(float a, float b, float t)
	{
		float num = Repeat(b - a, 360.0f);

		if (num > 180.0f)
		{
			num -= 360.0f;
		}

		return a + num * Clamp01(t);
	}

	// t��length���傫���͂Ȃ炸0��菬�����Ȃ炸�A���̊Ԃ����[�v(float)
	float Repeat(float t, float length)
	{
		return Clamp(t - Floor(t / length) * length, 0.0f, length);
	}

	// ���ݒn����ړI�n�܂ň�葬�x�ňړ�
	float MoveTowards(float current, float target, float maxDelta)
	{
		if (Abs(target - current) <= maxDelta)
		{
			return target;
		}

		return current + Sign(target - current) * maxDelta;
	}

	// ���݂̊p�x����ړI�̊p�x�܂ň�葬�x�ňړ�
	float MoveTowardsAngle(float current, float target, float maxDelta)
	{
		float num = DeltaAngle(current, target);

		if (0.0f - maxDelta < num && num < maxDelta)
		{
			return target;
		}

		target = current + num;
		return MoveTowards(current, target, maxDelta);
	}

	// �p�x�̍���Ԃ�(�x���@)
	float DeltaAngle(float current, float target)
	{
		float num = Repeat(target - current, 360.0f);

		if (num > 180.0f)
		{
			num -= 360.0f;
		}

		return num;
	}

	// �X���[�W���O���
	float SmoothStep(float from, float to, float t)
	{
		t = Clamp01(t);
		t = -2.0f * t * t * t + 3.0f * t * t;
		return to * t + from * (1.0f - t);
	}

	// �K���}�␳(float)
	float Gamma(float value, float absmax, float gamma)
	{
		bool flag = value < 0.0f;
		float num = Abs(value);
		if (num > absmax)
		{
			return flag ? (0.0f - num) : num;
		}

		float num2 = Pow(num / absmax, gamma) * absmax;
		return flag ? (0.0f - num2) : num2;
	}

	// ���������ɉ��b�Ŏw�肵�ăI�u�W�F�N�g���ړ�������
	float SmoothDamp(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
	{
		smoothTime = AliceMathUtility::Max(0.0001f, smoothTime);
		float num = 2.0f / smoothTime;
		float num2 = num * deltaTime;
		float num3 = 1.0f / (1.0f + num2 + 0.48f * num2 * num2 + 0.235f * num2 * num2 * num2);
		float value = current - target;
		float num4 = target;
		float num5 = maxSpeed * smoothTime;
		value = Clamp(value, 0.0f - num5, num5);
		target = current - value;
		float num6 = (currentVelocity + num * value) * deltaTime;
		currentVelocity = (currentVelocity - num * num6) * num3;
		float num7 = target + (value + num6) * num3;
		if (num4 - current > 0.0f == num7 > num4)
		{
			num7 = num4;
			currentVelocity = (num7 - num4) / deltaTime;
		}

		return num7;
	}

	// t��0��length�̊Ԃŉ�������(0�`length)
	float PingPong(float t, float length)
	{
		t = Repeat(t, length * 2.0f);
		return length - Abs(t - length);
	}

	// lerp�̕�Ԓl���o��
	float InverseLerp(float a, float b, float value)
	{
		if (a != b)
		{
			return Clamp01((value - a) / (b - a));
		}

		return 0.0f;
	}

	// 2�{�̐��̌�_���v�Z
	bool LineIntersection(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4, Vector2& result)
	{
		float num = p2.x - p1.x;
		float num2 = p2.y - p1.y;
		float num3 = p4.x - p3.x;
		float num4 = p4.y - p3.y;
		float num5 = num * num4 - num2 * num3;
		if (num5 == 0.0f)
		{
			return false;
		}

		float num6 = p3.x - p1.x;
		float num7 = p3.y - p1.y;
		float num8 = (num6 * num4 - num7 * num3) / num5;
		result.x = p1.x + num8 * num;
		result.y = p1.y + num8 * num2;
		return true;
	}

	bool LineSegmentIntersection(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4, Vector2& result)
	{
		float num = p2.x - p1.x;
		float num2 = p2.y - p1.y;
		float num3 = p4.x - p3.x;
		float num4 = p4.y - p3.y;
		float num5 = num * num4 - num2 * num3;
		if (num5 == 0.0f)
		{
			return false;
		}

		float num6 = p3.x - p1.x;
		float num7 = p3.y - p1.y;
		float num8 = (num6 * num4 - num7 * num3) / num5;
		if (num8 < 0.0f || num8 > 1.0f)
		{
			return false;
		}

		float num9 = (num6 * num2 - num7 * num) / num5;
		if (num9 < 0.0f || num9 > 1.0f)
		{
			return false;
		}

		result.x = p1.x + num8 * num;
		result.y = p1.y + num8 * num2;
		return true;
	}

	// ��̒l���قړ�������
	bool Approximately(float a, float b)
	{
		float tmp = 1e-06f * AliceMathUtility::Max(Abs(a), Abs(b));

		float tmp2 = EPSILON * 8.0f;

		if (Abs(b - a) < AliceMathUtility::Max(tmp, tmp2))
		{
			return true;
		}

		return false;
	}

	// �����_���Ȓl���擾
	float GetRand(float min, float max)
	{
		// ����������
		static std::random_device rd;
		static std::default_random_engine eng(rd());

		// ���z������
		std::uniform_real_distribution<float> get_rand_uni_real(min, max);

		// �����𐶐�
		return get_rand_uni_real(eng);
	}

	void Complement(float& x1, float x2, float flame)
	{
		float distanceX = x2 - x1;//�������o��
		float dividedDistanceX = distanceX / flame;//������flame�Ŋ������l

		x1 += dividedDistanceX;//������flame�Ŋ������l�𑫂�
	}
	
	Vector3 HermiteGetPoint(const Vector3& p0, const Vector3& p1, const Vector3& v0, const Vector3& v1, float t)
	{
		Vector3 c0 = 2.0f * p0 + -2.0f * p1 + v0 + v1;
		Vector3 c1 = -3.0f * p0 + 3.0f * p1 + -2.0f * v0 - v1;
		Vector3 c2 = v0;
		Vector3 c3 = p0;

		float t2 = t * t;
		float t3 = t2 * t;
		return c0 * t3 + c1 * t2 + c2 * t + c3;
	}

	Vector3 CatmullRomSpline(std::vector<Vector3>& points, float t)
	{

		float length = static_cast<float>(points.size());
		float progress = (length - 1) * t;
		float index = std::floor(progress);
		float weight = progress - index;

		if (Approximately(weight, 0.0f) && index >= length - 1)
		{
			index = length - 2;
			weight = 1;
		}

		Vector3 p0 = points[static_cast<size_t>(index)];
		Vector3 p1 = points[static_cast<size_t>(index + 1.0f)];
		Vector3 p2;
		Vector3 p3;

		if (index > 0.0f)
		{
			p2 = 0.5f * (points[static_cast<size_t>(index + 1.0f)] - points[static_cast<size_t>(index - 1.0f)]);
		}
		else
		{
			p2 = points[static_cast<size_t>(index + 1.0f)] - points[static_cast<size_t>(index)];
		}

		if (index < length - 2.0f)
		{
			p3 = 0.5f * (points[static_cast<size_t>(index + 2.0f)] - points[static_cast<size_t>(index)]);
		}
		else
		{
			p3 = points[static_cast<size_t>(index + 1.0f)] - points[static_cast<size_t>(index)];
		}

		return HermiteGetPoint(p0, p1, p2, p3, weight);
	}

	// �������ɓ��e���ꂽ���������瓊�e���������Z�o
	float LenSegOnSeparateAxis(const Vector3* Sep, const Vector3* e1, const Vector3* e2, const Vector3* e3)
	{
	   // 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
	   // ������Sep�͕W��������Ă��邱��
		float r1 = AliceMathF::Abs(Sep->Dot(*e1));
		float r2 = AliceMathF::Abs(Sep->Dot(*e2));
		float r3 = e3 ? (AliceMathF::Abs(Sep->Dot(*e3))) : 0;
		return r1 + r2 + r3;
	}
}
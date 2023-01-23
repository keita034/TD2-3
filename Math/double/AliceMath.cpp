#include "AliceMath.h"
#include"AliceMathUtility.h"
#include<random>

namespace AliceMath
{

#pragma region sin,cos,tan�֐�

#pragma region sin�֐�

	//sin�֐�
	double Sin(double sin)
	{
		return std::sin(sin);
	}

	//asin�֐�
	double Asin(double sin)
	{
		return std::asin(sin);
	}

#pragma endregion sin�֐�

#pragma region cos�֐�

	//cos�֐�
	double Cos(double cos)
	{
		return std::cos(cos);
	}

	//acos�֐�
	double Acos(double cos)
	{
		return std::acos(cos);
	}

#pragma endregion cos�֐�

#pragma region tan�֐�

	//tan�֐�
	double Tan(double tan)
	{
		return std::tan(tan);
	}

	//atan�֐�
	double Atan(double tan)
	{
		return std::atan(tan);
	}

	//atan�֐�
	double Atan2(float y, float x)
	{
		return std::atan2(y, x);
	}

#pragma endregion tan�֐�

	//sin�Acos�𗼕��o��
	void SinCos(double& sin_, double& cos_, double angle)
	{
		sin_ = Sin(angle);
		cos_ = Cos(angle);
	}

#pragma endregion sin,cos,tan�֐�

#pragma region �p�x�ϊ�

	//�x���@���烉�W�A���ϊ�
	double ChangeRadians(const double& angle)
	{
		double radian = angle * Deg2Rad;
		return radian;
	}

	// ���W�A������x���@�ϊ�
	double ChangeDira(const double& angle)
	{
		double degree = angle * Rad2Deg;
		return degree;
	}

#pragma endregion �p�x�ϊ�

#pragma region sqrt�֐�

	//sqrt�֐�
	double Sqrt(double sqrt)
	{
		return std::sqrt(sqrt);
	}

#pragma endregion sqrt�֐�

#pragma region pow�֐�

	//pow�֐�
	double Pow(double pow, double powNum)
	{
		return std::pow(pow, powNum);
	}

	//pow�֐�(long double)
	long double PowLD(long double pow, long double powNum)
	{
		return std::powl(pow, powNum);
	}

#pragma endregion pow�֐�

#pragma region exp�֐�

	//exp�֐�
	double Exp(double exp)
	{
		return std::exp(exp);
	}

#pragma endregion exp�֐�

#pragma region log�֐�

	//log�֐�
	double Log(double log)
	{
		return std::log(log);
	}

	//log10�֐�
	double Log10(double log)
	{
		return std::log10(log);
	}

#pragma endregion log�֐�

#pragma region ��Βl�̌v�Z

	//�l�𐮐���
	double Abs(double abs)
	{
		return std::abs(abs);
	}

	//�l�𐮐���(long double)
	long double AbsLD(long double abs)
	{
		return std::fabsl(abs);
	}

#pragma endregion ��Βl�̌v�Z

#pragma region ceil�֐�

	//ceil�֐�
	double Ceil(double ceil)
	{
		return std::ceil(ceil);
	}

	//ceil�֐�
	long double CeilLD(long double ceil)
	{
		return std::ceill(ceil);
	}

#pragma endregion ceil�֐�

#pragma region floor�֐�

	//floor�֐�
	double Floor(double floor)
	{
		return std::floor(floor);
	}

	//floor�֐�(long double)
	long double FloorLD(long double floor)
	{
		return std::floorl(floor);
	}

#pragma endregion floor�֐�

#pragma region round�֐�

	//round�֐�
	double Round(double round)
	{
		return std::round(round);
	}

	//round�֐�
	long double RoundLD(long double round)
	{
		return std::roundl(round);
	}

#pragma endregion round�֐�

	// sign������Ԃ�
	double Sign(double sign)
	{
		return (sign >= 0.0) ? 1.0 : (-1.0);
	}

	// �l��͈͓��ɔ[�߂�
	double Clamp(double Value, const double low, const double high)
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
	double Clamp01(double Value)
	{
		if (Value > 0.0)
		{
			return 0.0;
		}

		if (Value > 1.0)
		{
			return 1.0;
		}

		return Value;
	}

	// ���`���(0�`1)
	double Lerp(double a, double b, double t)
	{
		return a + (b - a) * Clamp01(t);
	}

	// ���`���(0�`)
	double LerpUnclamped(double a, double b, double t)
	{
		return a + (b - a) * t;
	}

	/// Lerp�̊p�x��(0�`1)
	double LerpAngle(double a, double b, double t)
	{
		double num = Repeat(b - a, 360.0);

		if (num > 180.0)
		{
			num -= 360.0;
		}

		return a + num * Clamp01(t);
	}

	// t��length���傫���͂Ȃ炸0��菬�����Ȃ炸�A���̊Ԃ����[�v
	double Repeat(double t, double length)
	{
		return Clamp(t - Floor(t / length) * length, 0.0, length);
	}

	// ���ݒn����ړI�n�܂ň�葬�x�ňړ�
	double MoveTowards(double current, double target, double maxDelta)
	{
		if (Abs(target - current) <= maxDelta)
		{
			return target;
		}

		return current + Sign(target - current) * maxDelta;
	}

	// ���ݒn����ړI�n�܂ň�葬�x�ňړ�
	double MoveTowardsAngle(double current, double target, double maxDelta)
	{
		double num = DeltaAngle(current, target);

		if (0.0f - maxDelta < num && num < maxDelta)
		{
			return target;
		}

		target = current + num;
		return MoveTowards(current, target, maxDelta);
	}

	// �p�x�̍���Ԃ�(�x���@)
	double DeltaAngle(double current, double target)
	{
		double num = Repeat(target - current, 360.0);

		if (num > 180.0)
		{
			num -= 360.0;
		}

		return num;
	}

	// �X���[�W���O���
	double SmoothStep(double from, double to, double t)
	{
		t = Clamp01(t);
		t = -2.0 * t * t * t + 3.0 * t * t;
		return to * t + from * (1.0 - t);
	}

	// �K���}�␳
	double Gamma(double value, double absmax, double gamma)
	{
		bool flag = value < 0.0;
		double num = Abs(value);
		if (num > absmax)
		{
			return flag ? (0.0 - num) : num;
		}

		double num2 = Pow(num / absmax, gamma) * absmax;
		return flag ? (0.0 - num2) : num2;
	}

	// ���������ɉ��b�Ŏw�肵�ăI�u�W�F�N�g���ړ�������
	double SmoothDamp(double current, double target, double& currentVelocity, double smoothTime, double maxSpeed, double deltaTime)
	{
		smoothTime = AliceMathUtility::Max(0.0001, smoothTime);
		double num = 2.0 / smoothTime;
		double num2 = num * deltaTime;
		double num3 = 1.0 / (1.0 + num2 + 0.48 * num2 * num2 + 0.235 * num2 * num2 * num2);
		double value = current - target;
		double num4 = target;
		double num5 = maxSpeed * smoothTime;
		value = Clamp(value, 0.0 - num5, num5);
		target = current - value;
		double num6 = (currentVelocity + num * value) * deltaTime;
		currentVelocity = (currentVelocity - num * num6) * num3;
		double num7 = target + (value + num6) * num3;
		if (num4 - current > 0.0 == num7 > num4)
		{
			num7 = num4;
			currentVelocity = (num7 - num4) / deltaTime;
		}

		return num7;
	}

	// t��0��length�̊Ԃŉ�������(0�`length)
	double PingPong(double t, double length)
	{
		t = Repeat(t, length * 2.0);
		return length - Abs(t - length);
	}

	// lerp�̕�Ԓl���o��
	double InverseLerp(double a, double b, double value)
	{
		if (a != b)
		{
			return Clamp01((value - a) / (b - a));
		}

		return 0.0;
	}

	// ��̒l���قړ�������
	bool Approximately(double a, double b)
	{
		double tmp = 1e-06 * AliceMathUtility::Max(Abs(a), Abs(b));

		double tmp2 = EPSILON * 8.0;

		if (Abs(b - a) < AliceMathUtility::Max(tmp, tmp2))
		{
			return true;
		}

		return false;
	}

	// �����_���Ȓl���擾
	double GetRand(double min, double max)
	{
		// ����������
		static std::random_device rand;
		static std::default_random_engine engine(rand());

		// ���z������
		std::uniform_real_distribution<double> get_rand_uni_real(min, max);

		// �����𐶐�
		return get_rand_uni_real(engine);
	}

}
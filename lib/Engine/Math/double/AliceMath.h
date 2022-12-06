#pragma once
#include"ErrorException.h"

namespace AliceMath
{
#pragma region �萔
#pragma warning(push)
#pragma warning(disable: 5264)
	// ��
	constexpr double AX_PI = 3.141592654;

	//��/2
	constexpr double AX_PIHalf = 3.141592654 / 2.0;

	// 2��
	constexpr double AX_2PI = 6.283185307;

	//��
	constexpr double EPSILON = 2.2204460492503131E-16;

	//�x���烉�W�A���ɕϊ�����萔
	constexpr double Deg2Rad = AX_PI / 180.0f;

	//���W�A������x�ɕϊ�����萔
	constexpr double Rad2Deg = 57.29578;
#pragma warning(pop)

#pragma endregion �萔

#pragma region sin,cos,tan�֐�

#pragma region sin�֐�	

	//sin�֐�
	double Sin(double sin);

	//asin�֐�
	double Asin(double sin);

#pragma endregion sin�֐�

#pragma region cos�֐�

	//cos�֐�
	double Cos(double cos);

	//cos�֐�
	double Acos(double cos);

#pragma endregion cos�֐�

#pragma region tan�֐�

	//tan�֐�
	double Tan(double tan);

	//atan�֐�
	double Atan(double tan);

	//atan�֐�
	double Atan2(float y, float x);

#pragma endregion tan�֐�

	/// <summary>
	/// Sin�ACos�𗼕��o��
	/// </summary>
	/// <param name="sin_"> : sin�̌��ʂ�������</param>
	/// <param name="cos_"> : cos�̌��ʂ�������</param>
	/// <param name="angle"> : ���W�A���p</param>
	void SinCos(double& sin_, double& cos_, double angle);

#pragma endregion sin,cos,tan�֐�

#pragma region �p�x�ϊ�

	/// <summary>
	/// �x���@���烉�W�A���ϊ�
	/// </summary>
	/// <param name="angle"> : �p�x</param>
	double ChangeRadians(const double& angle);

	/// <summary>
	/// ���W�A������x���@�ϊ�
	/// </summary>
	/// <param name="angle"> : �p�x</param>
	double ChangeDira(const double& angle);

#pragma endregion �p�x�ϊ�

#pragma region sqrt�֐�

	//sqrt�֐�
	double Sqrt(double sqrt);

#pragma endregion sqrt�֐�

#pragma region pow�֐�

	//pow�֐�
	double Pow(double pow, double powNum);

	//pow�֐�(long double)
	long double PowLD(long double pow, long double powNum);

#pragma endregion pow�֐�

#pragma region exp�֐�

	//exp�֐�
	double Exp(double exp);

#pragma endregion exp�֐�

#pragma region log�֐�

	//log�֐�
	double Log(double log);

	//log10�֐�
	double Log10(double log);

#pragma endregion log�֐�

#pragma region ��Βl�̌v�Z

	//��Βl�̌v�Z
	double Abs(double abs);

	//��Βl�̌v�Z(long double)
	long double AbsLD(long double abs);

#pragma endregion ��Βl�̌v�Z

#pragma region ceil�֐�

	//ceil�֐�
	double Ceil(double ceil);

	//ceil�֐�
	long double CeilLD(long double ceil);

#pragma endregion ceil�֐�

#pragma region floor�֐�

	//floor�֐�
	double Floor(double floor);

	//floor�֐�
	long double FloorLD(long double floor);

#pragma endregion floor�֐�

#pragma region round�֐�

	//round�֐�
	double Round(double round);

	//round�֐�
	long double RoundLD(long double round);

#pragma endregion round�֐�

	/// <summary>
	/// �l�̕�����Ԃ�
	/// </summary>
	/// <returns>�l������0�̏ꍇ��1���A���̏ꍇ��-1��Ԃ�</returns>
	double Sign(double sign);

	/// <summary>
	/// �l��͈͓��ɔ[�߂�
	/// </summary>
	/// <param name="Value">�l</param>
	/// <param name="low">�Œ�l</param>
	/// <param name="high">�ō��l</param>
	double Clamp(double Value, const double low, const double high);

	/// <summary>
	/// 0��1�̊Ԃɒl��[�߁A���̒l��Ԃ�
	/// </summary>
	/// <param name="Value">�l</param>
	double Clamp01(double Value);

	/// <summary>
	/// ���`���(0�`1)
	/// </summary>
	/// <param name="a">�J�n�l</param>
	/// <param name="b">�I���l</param>
	/// <param name="t">��Ԓl</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	double Lerp(double a, double b, double t);

	/// <summary>
	/// ���`���(0�`)
	/// </summary>
	/// <param name="a">�J�n�l</param>
	/// <param name="b">�I���l</param>
	/// <param name="t">��Ԓl</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	double LerpUnclamped(double a, double b, double t);

	/// <summary>
	/// Lerp�̊p�x��(0�`1)
	/// </summary>
	/// <param name="a">�J�n�l</param>
	/// <param name="b">�I���l</param>
	/// <param name="t">��Ԓl</param>
	/// <returns>��Ԃ��ꂽ�p�x</returns>
	double LerpAngle(double a, double b, double t);

	/// <summary>
	/// t��length���傫���͂Ȃ炸0��菬�����Ȃ炸�A���̊Ԃ����[�v
	/// </summary>
	/// <param name="t">�l</param>
	/// <param name="length">�w��l</param>
	double Repeat(double t, double length);

	/// <summary>
	/// ���ݒn����ړI�n�܂ň�葬�x�ňړ�
	/// </summary>
	/// <param name="current">���ݒn</param>
	/// <param name="target">�ړI�n</param>
	/// <param name="maxDelta">���x</param>
	double MoveTowards(double current, double target, double maxDelta);

	/// <summary>
	/// ���݂̊p�x����ړI�̊p�x�܂ň�葬�x�ňړ�
	/// </summary>
	/// <param name="current">���݂̊p�x</param>
	/// <param name="target">�ړI�̊p�x</param>
	/// <param name="maxDelta">���x</param>
	double MoveTowardsAngle(double current, double target, double maxDelta);

	/// <summary>
	/// �p�x�̍���Ԃ�(�x���@)
	/// </summary>
	/// <param name="current">���݂̊p�x</param>
	/// <param name="target">�ڕW�ƂȂ�p�x</param>
	double DeltaAngle(double current, double target);

	/// <summary>
	/// �X���[�W���O���
	/// </summary>
	/// <param name="from">�J�n�l</param>
	/// <param name="to">�I���l</param>
	/// <param name="t">��Ԓl</param>
	/// <returns>��Ԃ��ꂽ�p�x</returns>
	double SmoothStep(double from, double to, double t);

	/// <summary>
	/// �K���}�␳
	/// </summary>
	double Gamma(double value, double absmax, double gamma);

	/// <summary>
	/// ���������ɉ��b�Ŏw�肵�ăI�u�W�F�N�g���ړ�������
	/// </summary>
	/// <param name="current">���ݒn</param>
	/// <param name="target">�ړI�n</param>
	/// <param name="currentVelocity">���O�ɏ������������x</param>
	/// <param name="smoothTime">�ړI�܂ł̓��B����</param>
	/// <param name="maxSpeed">�ō����x</param>
	/// <param name="deltaTime">�֐����O����s����Ă���̌o�ߎ���</param>
	double SmoothDamp(double current, double target, double& currentVelocity, double smoothTime, double maxSpeed, double deltaTime);

	/// <summary>
	/// t��0��length�̊Ԃŉ�������(0�`length)
	/// </summary>
	double PingPong(double t, double length);

	/// <summary>
	/// lerp�̕�Ԓl���o��
	/// </summary>
	/// <param name="a">�J�n�l</param>
	/// <param name="b">�I���l</param>
	/// <param name="value">�J�n�ƏI���̊Ԃ̒l</param>
	/// <returns>��Ԓl</returns>
	double InverseLerp(double a, double b, double value);

	/// <summary>
	/// ��̒l���قړ�������
	/// </summary>
	bool Approximately(double a, double b);

	/// <summary>
	/// �����_���Ȓl���擾
	/// </summary>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	double GetRand(double min, double max);
}


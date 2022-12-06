#pragma once
#include"Vector2.h"
#include"Vector3.h"
#include"Vector4.h"
#include"Vector.h"
#include"Matrix4.h"
#include"Quaternion.h"

namespace AliceMathF
{
#pragma region �萔
#pragma warning(push)
#pragma warning(disable: 5264)
	//��
	constexpr float AX_PI = 3.1415926535897931f;

	//��/2
	constexpr float AX_PIHalf = 3.1415926535897931f / 2.0f;

	// 2��
	constexpr float AX_2PI = 3.1415926535897931f * 2;

	//���W�A������x�ɕϊ�����萔
	constexpr float Rad2Deg = 57.29578f;

	//�x���烉�W�A���ɕϊ�����萔
	constexpr float Deg2Rad = AX_PI / 180.0f;

	//��
	constexpr float EPSILON = 2.2204460492503131E-16f;
#pragma warning(pop)

#pragma endregion �萔

#pragma region sin,cos,tan�֐�

#pragma region sin�֐�

	//sin�֐�
	float Sin(float sin);

	//asin�֐�
	float Asin(float sin);

#pragma endregion sin�֐�

#pragma region cos�֐�

	//cos�֐�
	float Cos(float cos);

	//cos�֐�
	float Acos(float cos);

#pragma endregion cos�֐�

#pragma region tan�֐�

	//tan�֐�
	float Tan(float tan);

	//atan�֐�
	float Atan(float tan);

	//atan2�֐�
	float Atan2(float y, float x);

#pragma endregion tan�֐�

	/// <summary>
	/// sin�Acos�𗼕��o��
	/// </summary>
	/// <param name="sin_"> : sin�̌��ʂ�������</param>
	/// <param name="cos_"> : cos�̌��ʂ�������</param>
	/// <param name="angle"> : ���W�A���p</param>
	void SinCos(float& sin_, float& cos_, float angle);

#pragma endregion sin,cos,tan�֐�

#pragma region �p�x�ϊ�

	/// <summary>
	/// �x���@���烉�W�A���ϊ�
	/// </summary>
	/// <param name="angle"> : �p�x</param>
	float ChangeRadians(const float& angle);

	/// <summary>
	/// ���W�A������x���@�ϊ�
	/// </summary>
	/// <param name="angle"> : �p�x</param>
	float ChangeDira(const float& angle);

#pragma endregion �p�x�ϊ�

#pragma region sqrt�֐�

	//sqrt�֐�
	float Sqrt(float sqrt);


#pragma endregion sqrt�֐�

#pragma region pow�֐�

	//pow�֐�
	float Pow(float pow, float powNum);

#pragma endregion pow�֐�

#pragma region exp�֐�

	//exp�֐�
	float Exp(float exp);

#pragma endregion exp�֐�

#pragma region log�֐�

	//log�֐�
	float Log(float log);

	//log10�֐�
	float Log10(float log);

#pragma endregion log�֐�

#pragma region ��Βl�̌v�Z

	//��Βl�̌v�Z
	float Abs(float abs);

#pragma endregion ��Βl�̌v�Z

#pragma region ceil�֐�

	//ceil�֐�
	float Ceil(float ceil);

#pragma endregion ceil�֐�

#pragma region floor�֐�

	//floor�֐�
	float Floor(float floor);

#pragma endregion floor�֐�

#pragma region round�֐�

	//round�֐�
	float Round(float round);

#pragma endregion round�֐�

	/// <summary>
	/// �l�̕�����Ԃ�
	/// </summary>
	/// <returns>�l������0�̏ꍇ��1���A���̏ꍇ��-1��Ԃ�</returns>
	float Sign(float sign);

	/// <summary>
	/// �l��͈͓��ɔ[�߂�
	/// </summary>
	/// <param name="Value">�l</param>
	/// <param name="low">�Œ�l</param>
	/// <param name="high">�ō��l</param>
	float Clamp(float Value, const float low, const float high);

	/// <summary>
	/// 0��1�̊Ԃɒl��[�߁A���̒l��Ԃ�
	/// </summary>
	/// <param name="Value">�l</param>
	float Clamp01(float Value);

	/// <summary>
	/// ���`���(0�`1)
	/// </summary>
	/// <param name="a">�J�n�l</param>
	/// <param name="b">�I���l</param>
	/// <param name="t">��Ԓl</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float Lerp(float a, float b, float t);

	/// <summary>
	/// ���`���(0�`1)
	/// </summary>
	/// <param name="a">�J�n�l</param>
	/// <param name="b">�I���l</param>
	/// <param name="t">��Ԓl</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Vector3 Lerp(const Vector3& a, const Vector3& b, float t);

	/// <summary>
	/// ���`���(0�`1)
	/// </summary>
	/// <param name="a">�J�n�l</param>
	/// <param name="b">�I���l</param>
	/// <param name="t">��Ԓl</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	Vector4 Lerp(const Vector4& a, const Vector4& b, float t);

	Vector3 Slerp(const Vector3& v1, const Vector3& v2, float t);

	/// <summary>
	/// ���`���(0�`)
	/// </summary>
	/// <param name="a">�J�n�l</param>
	/// <param name="b">�I���l</param>
	/// <param name="t">��Ԓl</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	float LerpUnclamped(float a, float b, float t);

	/// <summary>
	/// Lerp�̊p�x��(0�`1)
	/// </summary>
	/// <param name="a">�J�n�l</param>
	/// <param name="b">�I���l</param>
	/// <param name="t">��Ԓl</param>
	/// <returns>��Ԃ��ꂽ�p�x</returns>
	float LerpAngle(float a, float b, float t);

	/// <summary>
	/// t��length���傫���͂Ȃ炸0��菬�����Ȃ炸�A���̊Ԃ����[�v
	/// </summary>
	/// <param name="t">�l</param>
	/// <param name="length">�w��l</param>
	float Repeat(float t, float length);

	/// <summary>
	/// ���ݒn����ړI�n�܂ň�葬�x�ňړ�
	/// </summary>
	/// <param name="current">���ݒn</param>
	/// <param name="target">�ړI�n</param>
	/// <param name="maxDelta">���x</param>
	float MoveTowards(float current, float target, float maxDelta);

	/// <summary>
	/// ���݂̊p�x����ړI�̊p�x�܂ň�葬�x�ňړ�
	/// </summary>
	/// <param name="current">���݂̊p�x</param>
	/// <param name="target">�ړI�̊p�x</param>
	/// <param name="maxDelta">���x</param>
	float MoveTowardsAngle(float current, float target, float maxDelta);

	/// <summary>
	/// �p�x�̍���Ԃ�(�x���@)
	/// </summary>
	/// <param name="current">���݂̊p�x</param>
	/// <param name="target">�ڕW�ƂȂ�p�x</param>
	float DeltaAngle(float current, float target);

	/// <summary>
	/// �X���[�W���O���
	/// </summary>
	/// <param name="from">�J�n�l</param>
	/// <param name="to">�I���l</param>
	/// <param name="t">��Ԓl</param>
	/// <returns>��Ԃ��ꂽ�p�x</returns>
	float SmoothStep(float from, float to, float t);

	/// <summary>
	/// �K���}�␳
	/// </summary>
	float Gamma(float value, float absmax, float gamma);

	/// <summary>
	/// ���������ɉ��b�Ŏw�肵�ăI�u�W�F�N�g���ړ�������
	/// </summary>
	/// <param name="current">���ݒn</param>
	/// <param name="target">�ړI�n</param>
	/// <param name="currentVelocity">���O�ɏ������������x</param>
	/// <param name="smoothTime">�ړI�܂ł̓��B����</param>
	/// <param name="maxSpeed">�ō����x</param>
	/// <param name="deltaTime">�֐����O����s����Ă���̌o�ߎ���</param>
	float SmoothDamp(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);

	/// <summary>
	/// t��0��length�̊Ԃŉ�������(0�`length)
	/// </summary>
	float PingPong(float t, float length);

	/// <summary>
	/// lerp�̕�Ԓl���o��
	/// </summary>
	/// <param name="a">�J�n�l</param>
	/// <param name="b">�I���l</param>
	/// <param name="value">�J�n�ƏI���̊Ԃ̒l</param>
	/// <returns>��Ԓl</returns>
	float InverseLerp(float a, float b, float value);

	/// <summary>
	/// 2�{�̐��̌�_���v�Z
	/// </summary>
	/// <param name="p1">�n�_1</param>
	/// <param name="p2">�I�_1</param>
	/// <param name="p3">�n�_2</param>
	/// <param name="p4">�I�_2</param>
	/// <param name="result">����(�o�͗p)</param>
	/// <returns>�������Ă��邩</returns>
	bool LineIntersection(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4, Vector2& result);

	bool LineSegmentIntersection(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4, Vector2& result);

	/// <summary>
	/// ��̒l���قړ�������
	/// </summary>
	bool Approximately(float a, float b);

	/// <summary>
	/// �����_���Ȓl���擾
	/// </summary>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	float GetRand(float min, float max);

	//�⊮�֐�
	void Complement(float& x1, float x2, float flame);

		/// <summary>
	/// �G���~�[�g�Ȑ�
	/// </summary>
	/// <param name="p0">����_</param>
	/// <param name="p1">����_</param>
	/// <param name="v0">����_</param>
	/// <param name="v1">����_</param>
	/// <param name="t">����(0.0�`1.0)</param>
	/// <returns></returns>
	Vector3 HermiteGetPoint(const Vector3& p0, const Vector3& p1, const Vector3& v0, const Vector3& v1, float t);

	/// <summary>
	/// �L���b�g�����[�����X�v���C�� 
	/// </summary>
	/// <param name="points">����_</param>
	/// <param name="t">����(0.0�`1.0)</param>
	Vector3 CatmullRomSpline(std::vector<Vector3>& points, float t);

	// �������ɓ��e���ꂽ���������瓊�e���������Z�o
	float LenSegOnSeparateAxis(const Vector3* Sep, const Vector3* e1, const Vector3* e2, const Vector3* e3 = 0);

	/// <summary>
	/// �Ίp�����o��
	/// </summary>
	/// <param name="width">����</param>
	/// <param name="height">�c��</param>
	/// <returns>�Ίp��</returns>
	float GetDiagonal(float width, float height);
};


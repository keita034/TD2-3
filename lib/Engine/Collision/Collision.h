#pragma once

#include "CollisionPrimitive.h"
#include"AliceMathUtility.h"

/// <summary>
/// �����蔻��w���p�[�N���X
/// </summary>
class Collision
{
public:
	/// <summary>
	/// �_�ƎO�p�`�̍ŋߐړ_�����߂�
	/// </summary>
	/// <param name="point">�_</param>
	/// <param name="triangle">�O�p�`</param>
	/// <param name="closest">�ŋߐړ_�i�o�͗p�j</param>
	static void ClosestPtPoint2Triangle( AliceMathF::Vector4& point,  Triangle& triangle, AliceMathF::Vector4* closest);

	/// <summary>
	/// ���Ƌ��̓����蔻��
	/// </summary>
	/// <param name="sphereA">��A</param>
	/// <param name="sphereB">��B</param>
	/// <param name="inter">��_�i�o�͗p�j</param>
	/// <param name="reject">�r�˃x�N�g���i�o�͗p�j</param>
	/// <returns></returns>
	static bool CheckSphere2Sphere( Sphere& sphereA,  Sphere& sphereB, AliceMathF::Vector4* inter = nullptr, AliceMathF::Vector4* reject = nullptr);

	/// <summary>
	/// ���ƕ��ʂ̓����蔻��
	/// </summary>
	/// <param name="sphere">��</param>
	/// <param name="plane">����</param>
	/// <param name="inter">��_�i���ʏ�̍ŋߐړ_�j</param>
	/// <returns>�������Ă��邩�ۂ�</returns>
	static bool CheckSphere2Plane( Sphere& sphere,  Plane& plane, AliceMathF::Vector4* inter = nullptr);

	/// <summary>
	/// ���Ɩ@���t���O�p�`�̓����蔻��
	/// </summary>
	/// <param name="sphere">��</param>
	/// <param name="triangle">�O�p�`</param>
	/// <param name="inter">��_�i�O�p�`��̍ŋߐړ_�j</param>
	/// <param name="reject">�r�˃x�N�g���i�o�͗p�j</param>
	/// <returns>�������Ă��邩�ۂ�</returns>
	static bool CheckSphere2Triangle( Sphere& sphere,  Triangle& triangle, AliceMathF::Vector4* inter = nullptr, AliceMathF::Vector4* reject = nullptr);

	/// <summary>
	/// ���C�ƕ��ʂ̓����蔻��
	/// </summary>
	/// <param name="lay">���C</param>
	/// <param name="plane">����</param>
	/// <param name="inter">�����i�o�͗p�j</param>
	/// <param name="inter">��_�i�o�͗p�j</param>
	/// <returns>�������Ă��邩�ۂ�</returns>
	static bool CheckRay2Plane( Ray& lay,  Plane& plane, float* distance = nullptr, AliceMathF::Vector4* inter = nullptr);

	/// <summary>
	/// ���C�Ɩ@���t���O�p�`�̓����蔻��
	/// </summary>
	/// <param name="lay">���C</param>
	/// <param name="triangle">�O�p�`</param>
	/// <param name="inter">�����i�o�͗p�j</param>
	/// <param name="inter">��_�i�o�͗p�j</param>
	/// <returns>�������Ă��邩�ۂ�</returns>
	static bool CheckRay2Triangle( Ray& lay,  Triangle& triangle, float* distance = nullptr, AliceMathF::Vector4* inter = nullptr);

	/// <summary>
	/// ���C�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="lay">���C</param>
	/// <param name="sphere">��</param>
	/// <param name="sphere">�����i�o�͗p�j</param>
	/// <param name="inter">��_�i�o�͗p�j</param>
	/// <returns>�������Ă��邩�ۂ�</returns>
	static bool CheckRay2Sphere( Ray& lay,  Sphere& sphere, float* distance = nullptr, AliceMathF::Vector4* inter = nullptr);

	/// <summary>
	/// ���C�L���X�g�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="lay">���C</param>
	/// <param name="sphere">��</param>
	/// <param name="sphere">�����i�o�͗p�j</param>
	/// <param name="inter">��_�i�o�͗p�j</param>
	/// <returns>�������Ă��邩�ۂ�</returns>
	static bool CheckRayCast2Sphere( RayCast& lay,  Sphere& sphere, float* distance = nullptr, AliceMathF::Vector4* inter = nullptr);

	/// <summary>
	/// OBB��OBB�̓����蔻��
	/// </summary>
	/// <param name="obb1">OBB</param>
	/// <param name="obb2">OBB</param>
	/// <returns>�������Ă��邩�ۂ�</returns>
	static bool CheckOBB2OBB(OBB& obb1, OBB& obb2);

};
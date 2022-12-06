#pragma once
#include"CollisionPrimitive.h"
#include"ErrorException.h"

class Collision
{

private:

public:

	/// <summary>
	/// ���ƕ��ʂ̓����蔻��
	/// </summary>
	/// <param name="sphere">��</param>
	/// <param name="plane">����</param>
	/// <param name="inter">��_(���ʏ�̍ŋߐړ_)</param>
	/// <returns>�������Ă邩</returns>
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane& plane, AliceMath::Vector3* inter = nullptr);

	/// <summary>
	/// ���Ƌ��̓����蔻��
	/// </summary>
	/// <param name="sphereA">��1</param>
	/// <param name="sphereB">��2</param>
	/// <param name="inter">��_(���ʏ�̍ŋߐړ_)</param>
	/// <returns>�������Ă邩</returns>
	static bool CheakSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, AliceMath::Vector3* inter = nullptr, AliceMath::Vector3* reject = nullptr);

	/// <summary>
	/// �_�ƎO�p�`�̍ŋߐړ_�����߂�
	/// </summary>
	/// <param name="point">�_</param>
	/// <param name="triangle">�O�p�`</param>
	/// <param name="closest">�ŋߐړ_(�o�͗p)</param>
	static void ClosestPtPoint2Triangl(const AliceMath::Vector3& point,const Triangle& triangle, AliceMath::Vector3* closest);

	/// <summary>
	/// ���Ɩ@���t���O�p�`�̓�����`�F�b�N
	/// </summary>
	/// <param name="sphere">��</param>
	/// <param name="triangle">�O�p�`</param>
	/// <param name="inter">��_(�O�p�`��̍ŋߐړ_)</param>
	/// <returns>�������Ă��邩</returns>
	static bool CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, AliceMath::Vector3* inter = nullptr, AliceMath::Vector3* reject = nullptr);

	/// <summary>
	/// ���C�ƕ��ʂ̓����蔻��
	/// </summary>
	/// <param name="ray">���C</param>
	/// <param name="plane">����</param>
	/// <param name="distance">����(�o�͗p)</param>
	/// <param name="inter">��_(�o�͗p)</param>
	/// <returns>�������Ă��邩</returns>
	static bool CheckRay2Plane(const Ray& ray,const Plane& plane,float* distance = nullptr, AliceMath::Vector3* inter = nullptr);

	/// <summary>
	/// ���C�ƎO�p�`�̓����蔻��
	/// </summary>
	/// <param name="ray">���C</param>
	/// <param name="plane">�O�p�`</param>
	/// <param name="distance">����(�o�͗p)</param>
	/// <param name="inter">��_(�o�͗p)</param>
	/// <returns>�������Ă��邩</returns>
	static bool CheckRay2Triangle(const Ray& ray, const Triangle& triangle, float* distance = nullptr, AliceMath::Vector3* inter = nullptr);

	/// <summary>
	/// ���C�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="ray">���C</param>
	/// <param name="plane">��</param>
	/// <param name="distance">����(�o�͗p)</param>
	/// <param name="inter">��_(�o�͗p)</param>
	/// <returns>�������Ă��邩</returns>
	static bool CheckRay2Sphere(const Ray& ray, const Sphere& sphere, float* distance = nullptr, AliceMath::Vector3* inter = nullptr);
};


#include "Collision.h"

bool Collision::CheckSphere2Plane(const Sphere& sphere, const Plane& plane, AliceMath::Vector3* inter)
{
	//���W�n�̌��_���狅�̒��S���W�ւ̋���
	float dist = sphere.center.dot(plane.normal);

	//���ʂ̌��_���������Z���邱�ƂŁA���ʂƋ��̒��S�Ƃ̋������o��
	dist = dist - plane.distane;

	//�����̐�Βl�����a���傫����Γ����Ă��Ȃ�
	if (std::fabsf(dist) > sphere.radius)
	{
		return false;
	}

	//�[����_���v�Z
	if (inter)
	{
		//���ʏ�̍ŋߐړ_���A�[����_�Ƃ���
		*inter = -dist * plane.normal + sphere.center;
	}

	return true;
}

bool Collision::CheakSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, AliceMath::Vector3* inter, AliceMath::Vector3* reject)
{
	//2�_�Ԃ̋���
	float dist = 
		(sphereB.center.x - sphereA.center.x) * 2 + 
		(sphereB.center.y - sphereA.center.y) * 2 + 
		(sphereB.center.z - sphereA.center.z) * 2;
	//�`�F�b�N
	if (std::fabsf(dist) > sphereA.radius + sphereB.radius)
	{
		return false;
	}

	//�^����_���v�Z
	if (inter)
	{

	}

	//�����o���x�N�g�����v�Z
	if (reject)
	{
		float rejectLen = sphereA.radius + sphereB.radius - std::sqrtf(dist);
		*reject = sphereA.center - sphereB.center;
		reject->normalization();
		*reject *= rejectLen;
	}
	return true;
}

void Collision::ClosestPtPoint2Triangl(const AliceMath::Vector3& point, const Triangle& triangle, AliceMath::Vector3* closest)
{
	// point��p0�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	AliceMath::Vector3 p0_p1 = triangle.p1 - triangle.p0;
	AliceMath::Vector3 p0_p2 = triangle.p2 - triangle.p0;
	AliceMath::Vector3 p0_pt = point - triangle.p0;

	float d1 = p0_p1.dot(p0_pt);
	float d2 = p0_p2.dot(p0_pt);

	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// p0���ŋߖT
		*closest = triangle.p0;
		return;
	}

	// point��p1�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	AliceMath::Vector3 p1_pt = point - triangle.p1;

	float d3 = p0_p1.dot(p1_pt);
	float d4 = p0_p2.dot(p1_pt);

	if (d3 >= 0.0f && d4 <= d3)
	{
		// p1���ŋߖT
		*closest = triangle.p1;
		return;
	}

	// point��p0_p1�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p1��ɑ΂���ˉe��Ԃ�
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float v = d1 / (d1 - d3);
		*closest = triangle.p0 + v * p0_p1;
		return;
	}

	// point��p2�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	AliceMath::Vector3 p2_pt = point - triangle.p2;

	float d5 = p0_p1.dot(p2_pt);
	float d6 = p0_p2.dot(p2_pt);
	if (d6 >= 0.0f && d5 <= d6)
	{
		*closest = triangle.p2;
		return;
	}

	// point��p0_p2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p2��ɑ΂���ˉe��Ԃ�
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		float w = d2 / (d2 - d6);
		*closest = triangle.p0 + w * p0_p2;
		return;
	}

	// point��p1_p2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p1_p2��ɑ΂���ˉe��Ԃ�
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		*closest = triangle.p1 + w * (triangle.p2 - triangle.p1);
		return;
	}

	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	*closest = triangle.p0 + p0_p1 * v + p0_p2 * w;
}

bool Collision::CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, AliceMath::Vector3* inter, AliceMath::Vector3* reject)
{
	AliceMath::Vector3 p;
	// ���̒��S�ɑ΂���ŋߐړ_�ł���O�p�`��ɂ���_p��������
	ClosestPtPoint2Triangl(sphere.center, triangle, &p);
	// �_p�Ƌ��̒��S�̍����x�N�g��
	AliceMath::Vector3 v = p - sphere.center;
	// �����̓������߂�
	//�i�����x�N�g�����m�̓��ς͎O�����̒藝�̃��[�g�����̎��ƈ�v����j
	float distanceSquare = v.dot(v);
	// ���ƎO�p�`�̋��������a�ȉ��Ȃ瓖�����Ă��Ȃ�
	if (distanceSquare > sphere.radius * sphere.radius)	return false;
	// �[����_���v�Z
	if (inter) {
		// �O�p�`��̍ŋߐړ_p���^����_�Ƃ���
		*inter = p;
	}
	// �����o���x�N�g�����v�Z
	if (reject) {
		float ds = triangle.normal.dot(sphere.center);
		float dt = triangle.normal.dot(triangle.p0);
		float rejectLen = dt - ds + sphere.radius;
		*reject = rejectLen * triangle.normal;
	}
	return true;
}

bool Collision::CheckRay2Plane(const Ray& ray, const Plane& plane, float* distance, AliceMath::Vector3* inter)
{
	//�덷���e�͈�
	const float epsilon = 1.0e-5f;

	//�ʖ@���ƃ��C�̕����x�N�g���̓���
	float d1 = plane.normal.dot(ray.dir);

	//���ʂɂ͓�����Ȃ�
	if (d1 > -epsilon)
	{
		return false;
	}
	//�n�_�ƌ��_�̋���(���ʂ̖@������)
	//�ʖ@���ƃ��C�̎n�_���W(�ʒu�x�N�g��)�̓���
	float d2 = plane.normal.dot(ray.start);

	//�n�_�ƕ��ʂ̋���(���ʂ̖@������)
	float dist = d2 - plane.distane;

	//�n�_�ƕ��ʂ̋���(���C����)
	float t = dist / -d1;

	//��_���n�_�����ɂ���̂ŁA������Ȃ�
	if (t < 0)
	{
		return false;
	}

	//��������������
	if (distance)
	{
		*distance = t;
	}

	//��_���v�Z
	if (inter)
	{
		*inter = ray.start + t * ray.dir;
	}

	return true;
}

bool Collision::CheckRay2Triangle(const Ray& ray, const Triangle& triangle, float* distance, AliceMath::Vector3* inter)
{
	//�O�p�`������Ă��镽�ʂ��Z�o
	Plane plane;
	AliceMath::Vector3 interPlane;
	plane.normal = triangle.normal;
	plane.distane = triangle.normal.dot(triangle.p0);

	//���C�ƕ��ʂ��������Ă��Ȃ���΁A�������Ă��Ȃ�
	if (!CheckRay2Plane(ray, plane, distance, &interPlane))
	{
		return false;
	}

	//���C�ƕ��ʂ��������Ă����̂ŁA�����ƌ�_���������܂ꂽ
	//���C�ƕ��ʂ̌�_���O�p�`�̓����ɂ��邩����
	const float epsilon = 1.0e-5f;//�ꂳ�z���p�̔����Ȓl

	AliceMath::Vector3 m;
	//��p0_p1�ɂ���
	AliceMath::Vector3 pt_p0 = triangle.p0 - interPlane;
	AliceMath::Vector3 p0_p1 = triangle.p1 - triangle.p0;
	m = pt_p0.cross(p0_p1);

	//�ӂ̊O���ł���Γ������Ă��Ȃ��̂Ŕ����ł��؂�
	if (m.dot(triangle.normal)< -epsilon)
	{
		return false;
	}



	//��p1_p2�ɂ���
	AliceMath::Vector3 pt_p1 = triangle.p1 - interPlane;
	AliceMath::Vector3 p1_p2 = triangle.p2 - triangle.p1;
	m = pt_p1.cross( p1_p2);

	//�ӂ̊O���ł���Γ������Ă��Ȃ��̂Ŕ����ł��؂�
	if (m.dot( triangle.normal) < -epsilon)
	{
		return false;
	}


	//��p0_p1�ɂ���
	AliceMath::Vector3 pt_p2 = triangle.p2 - interPlane;
	AliceMath::Vector3 p2_p0 = triangle.p0 - triangle.p2;
	m = pt_p2.cross (p2_p0);

	//�ӂ̊O���ł���Γ������Ă��Ȃ��̂Ŕ����ł��؂�
	if (m.dot( triangle.normal)< -epsilon)
	{
		return false;
	}


	//�����Ȃ̂ŁA�������Ă���
	if (inter)
	{
		*inter = interPlane;
	}
	return true;
}

bool Collision::CheckRay2Sphere(const Ray& ray, const Sphere& sphere, float* distance, AliceMath::Vector3* inter)
{
	AliceMath::Vector3 m = ray.start - sphere.center;
	float b = m.dot(ray.dir);
	float c = m.dot(m);
	//ray�̎n�_��sphere�̊O���ɂ���(c>0)�Aray��sphere���痣��Ă����������w���Ă���ꍇ(b>0),������Ȃ�
	if (c > 0.0f && b > 0.0f)
	{
		return false;
	}

	float discr = b * b - c;
	//���̔��ʎ��̓��C�������O��Ă��邱�ƂɈ�v
	if (discr < 0.0f)
	{
		return false;
	}

	//���C�͋��ƌ������Ă���
	//��������ŏ��̒lt���v�Z
	float t = -b - std::sqrt(discr);
	//t�����ł���ꍇ�A���C�͋��̓�������J�n���Ă���̂�t��0�ɃN�����v
	if (t<0)
	{
		t = 0.0f;
	}
	if (distance)
	{
		*distance = t;
	}

	if (inter)
	{
		*inter = ray.start + t * ray.dir;
	}

	return true;
}
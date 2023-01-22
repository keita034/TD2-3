#pragma once
#pragma once
/// <summary>
///�����蔻��v���~�e�B�u
/// </summary>


#include<DirectXMath.h>

struct Sphere {
	DirectX::XMVECTOR center = { 0,0,0,1 };

	float radius = 1.0f;

};

struct Plane {
	DirectX::XMVECTOR normal = { 0,1,0,0 };

	float distance = 0.0f;

};

class Triangle {
public:
	DirectX::XMVECTOR p0;
	DirectX::XMVECTOR p1;
	DirectX::XMVECTOR p2;

	DirectX::XMVECTOR normal;

	void ComputeNormal();

};

struct Ray
{
	DirectX::XMVECTOR start = { 0,0,0,1 };

	DirectX::XMVECTOR dir = { 1,0,0,0 };

};


//class BaseCollsion
//{
//protected:
//
//	uint32_t collisionAttribute = 0xffffffff;
//	//�Փ˃}�X�N(����)
//	uint32_t CollisionMask = 0xffffffff;
//
//	//���O(����)
//	std::string collsionName;
//	//���O(����)
//	char opponentCollsionName[256];
//
//	virtual ~BaseCollsion() = default;
//
//public:
//	//�Փˎ��ɌĂ΂��֐�
//	virtual void OnCollision() = 0;
//	//�Փˑ���(����)���擾
//	const uint32_t GetCollisionAttribute();
//	//�Փˑ���(����)���擾
//	void SetCollisionAttribute(uint32_t collisionAttribute_);
//	//�Փˑ���(����)���擾
//	const uint32_t GetCollisionMask();
//	//�Փˑ���(����)��ݒ�
//	void SetCollisionMask(uint32_t CollisionMask_);
//
//	void SetCollsionName(std::string name);
//	std::string GetCollsionName();
//
//	void SetOpponentCollsionName(std::string name);
//	std::string GetOpponentCollsionName();
//};
//
///// <summary>
///// ��
///// </summary>
//class Sphere : public BaseCollsion
//{
//public:
//
//	//���S���W
//	AliceMathF::Vector4 center = { 0.0f,0.0f,0.0f,1.0f };
//	//���a
//	float radius = 1.0f;
//private:
//	char PADING[4]{};
//
//public:
//
//	//���a���擾
//	const float GetRadius();
//	//���a����ݒ�
//	void SetRadius(float radius_);
//	//���S���W���擾
//	const AliceMathF::Vector4& GetCenter();
//	//���S���W����ݒ�
//	void SetCenter(AliceMathF::Vector4& center_);
//	//�Փˎ��ɌĂ΂��֐�
//	virtual void OnCollision()
//	{
//	};
//};
//
///// <summary>
///// ����
///// </summary>
//class Plane : public BaseCollsion
//{
//protected:
//	//�@���x�N�g��
//	AliceMathF::Vector4 normal = { 0.0f,1.0f,0.0f,0.0f };
//	//���_�_(0,0,0)����̋���
//	float distance = 0.0f;
//private:
//	char PADING[4]{};
//public:
//	//���_�_(0,0,0)����̋������擾
//	const float GetDistance();
//	//���_�_(0,0,0)����̋�����ݒ�
//	void SetDistance(float distance_);
//	//�@���x�N�g�����擾
//	const AliceMathF::Vector4& GetNormal();
//	//�@���x�N�g����ݒ�
//	void SetNormal(AliceMathF::Vector4& normal_);
//	//�Փˎ��ɌĂ΂��֐�
//	virtual void OnCollision()
//	{
//	};
//};
//
///// <summary>
///// �@���t���O�p�`(���v��肪�\��)
///// </summary>
//class Triangle : public BaseCollsion
//{
//public:
//
//	//���_���W3��
//	AliceMathF::Vector4 p0;
//	AliceMathF::Vector4 p1;
//	AliceMathF::Vector4 p2;
//	//�@���x�N�g��
//	AliceMathF::Vector4 normal;
//
//public:
//	/// <summary>
//	/// �@���̌v�Z
//	/// </summary>
//	void ComputeNormal();
//
//	//���_���W1�ڎ擾
//	const AliceMathF::Vector4& GetP0();
//	//���_���W1�ڂ�ݒ�
//	void SetP0(AliceMathF::Vector4& p0_);
//
//	//���_���W2�ڂ��擾
//	const AliceMathF::Vector4& GetP1();
//	//���_���W2�ڂ�ݒ�
//	void SetP1(AliceMathF::Vector4& p1_);
//
//	//���_���W3�ڂ��擾
//	const AliceMathF::Vector4& GetP2();
//	//���_���W3�ڂ�ݒ�
//	void SetP2(AliceMathF::Vector4& p2_);
//
//	//�@���x�N�g�����擾
//	const AliceMathF::Vector4& GetNormal();
//	//�@���x�N�g����ݒ�
//	void SetNormal(AliceMathF::Vector4& normal_);
//	//�Փˎ��ɌĂ΂��֐�
//	virtual void OnCollision()
//	{
//	};
//};
//
///// <summary>
///// ���C(������)
///// </summary>
//class Ray : public BaseCollsion
//{
//public:
//
//	//�n�_���W
//	AliceMathF::Vector4 start = { 0,0,0,1 };
//	//����
//	AliceMathF::Vector4 dir = { 1,0,0,0 };
//
//	//�n�_���W
//	DirectX::XMVECTOR Xstart = { 0,0,0,1 };
//	//����
//	DirectX::XMVECTOR Xdir = { 1,0,0,0 };
//
//public:
//
//	//�n�_���W���擾
//	const AliceMathF::Vector4& GetStart();
//	//�n�_���W��ݒ�
//	void SetStart(AliceMathF::Vector4& start_);
//
//	//�������擾
//	const AliceMathF::Vector4& GetDir();
//	//������ݒ�
//	void SetDir(AliceMathF::Vector4& dir_);
//	//�Փˎ��ɌĂ΂��֐�
//	virtual void OnCollision()
//	{
//	};
//};
//
//class RayCast : public Ray
//{
//protected:
//	//����
//	float range = 0.0f;
//private:
//	char PADING[4]{};
//public:
//	//���a���擾
//	const float GetRange();
//	//���a����ݒ�
//	void SetRange(float range_);
//};
//
//class OBB : public BaseCollsion
//{
//protected:
//	AliceMathF::Vector3 center = {};//�ʒu
//	AliceMathF::Vector3 normaDirect[3];//�����x�N�g��
//	float Length[3]{};// �e�������̒���
//private:
//	char PADING[4]{};
//public:
//	const AliceMathF::Vector3 GetDirect(uint16_t elem);//�w�莲�ԍ��̕����x�N�g�����擾
//	const float GetLen(uint16_t elem);// �w�莲�����̒������擾
//	const AliceMathF::Vector3 GetCenter();// �ʒu���擾
//	//�Փˎ��ɌĂ΂��֐�
//	virtual void OnCollision()
//	{
//	};
//
//	void CreateOBB(std::vector<PosNormalUv> vertex_, Transform& transform);
//
//	void UpdateOBB(Transform& transform);
//};
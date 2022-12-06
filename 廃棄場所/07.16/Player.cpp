#include "Player.h"
#include"SphereCollider.h"
#include"CollisionAttribute.h"
#include"RaycastHit.h"

void Player::Initialize()
{
	model = ModelCreate::CreateModel("Resources/player");
	input = Input::GetInstance();

	float radius = 0.6f;
	model->SetCollider(new SphereCollider(AliceMath::Vector4{ 0,radius ,0,0 },radius));
}

void Player::Update()
{

	//�ړ�
	if (input->KeepPush(DIK_UP))
	{
		move.x -= AliceMath::ChangeRadians(1.0f);
	}
	else if (input->KeepPush(DIK_DOWN))
	{
		move.x += AliceMath::ChangeRadians(1.0f);
	}
	if (input->KeepPush(DIK_RIGHT))
	{
		move.z -= AliceMath::ChangeRadians(1.0f);
	}
	else if (input->KeepPush(DIK_LEFT))
	{
		move.z += AliceMath::ChangeRadians(1.0f);
	}
	//��]
	if (input->KeepPush(DIK_A))
	{
		rot.y -= AliceMath::ChangeRadians(1.0f);
	}
	else if (input->KeepPush(DIK_D))
	{
		rot.y += AliceMath::ChangeRadians(1.0f);
	}

	////��������
	//if (!onGround)
	//{
	//	//�����������x
	//	const float fallAcc = -0.01f;
	//	const float fallVYMin = -0.5f;
	//	//����
	//	fallV.y = max(fallV.y + fallAcc, fallVYMin);
	//	//�ړ�
	//	move.x += fallV.x;
	//	move.y += fallV.y;
	//	move.z += fallV.z;
	//}
	//else if (input->TriggerPush(DIK_SPACE))
	//{
	//	onGround = false;
	//	//�W�����v�����������
	//	const float jumpVYFist = 0.2f;
	//	fallV = { 0,jumpVYFist,0 };
	//}

	//model->Update(move, rot);

	////���R���C�_�[������
	//SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(model->GetCollider());
	//assert(sphereCollider);

	////�N�G���[�R�[���o�b�N�N���X��`
	//class PlayerQueryCallback :public QueryCallback
	//{
	//public:
	//	PlayerQueryCallback(Sphere* sphere) : sphere(sphere)
	//	{
	//	};
	//	~PlayerQueryCallback()
	//	{
	//	};
	//	virtual bool OnQueryHit(QueryHit& info)override
	//	{
	//		//���[���h�̏����
	//		const AliceMath::Vector4 up = { 0,1,0,0 };
	//		//�r�˕���
	//		AliceMath::Vector4 rejectDir = info.reject.normalization();
	//		//������Ɣr�˕����̊p�x���̃R�T�C���l
	//		float cos_ = rejectDir.dot(up);

	//		//�n�ʔ��肵�����l
	//		float threshold = std::cos(AliceMath::ChangeRadians(30.0f));
	//		//�p�x���ɂ���ēV��܂��͒n�ʂƔ��肳���ꍇ��`����
	//		if (-threshold < cos_ && cos_ < threshold)
	//		{
	//			//����r��(�����o��)
	//			sphere->center += info.reject;
	//			move += info.reject;
	//		}

	//		return true;
	//	}

	//	//�N�G���[�Ɏg�p���鋅
	//	Sphere* sphere = nullptr;
	//	//�r�˂ɂ��ړ���(�ݐϒl)
	//	AliceMath::Vector4 move = {};

	//};

	////�N�G���[�R�[���o�b�N�̊֐��I�u�W�F�N�g
	//PlayerQueryCallback callback(sphereCollider);

	////���ƒn�`�̌�����S����
	//CollisionManager::GetInstance()->QuerySphere(*sphereCollider, &callback, CollisionAttrLandshape);
	////�����ɂ��r�˕�������
	//move.x += callback.move.x;
	//move.y += callback.move.y;
	//move.z += callback.move.z;

	//model->Update(move, rot);

	////���̏�[���狅�̉��[�܂ł̃��C�L���X�g�p���C������
	//Ray ray;
	//ray.start = sphereCollider->center;
	//ray.start.y += sphereCollider->GetRadius();
	//ray.dir = { 0,-1,0,0 };
	//RaycastHit raycastHit;

	////�ݒu���
	//if (onGround)
	//{
	//	//�X���[�Y�ɍ�����邽�߂̋z������
	//	const float adsDistace = 0.2f;
	//	//�ݒu���ێ�
	//	if (CollisionManager::GetInstance()->Raycast(ray, CollisionAttrLandshape, &raycastHit, sphereCollider->GetRadius() * 2.0f + adsDistace))
	//	{
	//		onGround = true;

	//		move.y -= (raycastHit.distance - sphereCollider->GetRadius() * 2.0f);
	//		model->Update(move, rot);
	//	}
	//	else
	//	{
	//		onGround = false;
	//		fallV = {};
	//	}
	//}
	//else if (fallV.y <= 0.0f)
	//{
	//	if (CollisionManager::GetInstance()->Raycast(ray, CollisionAttrLandshape, &raycastHit, sphereCollider->GetRadius() * 2.0f))
	//	{
	//		//���n
	//		onGround = true;
	//		move.y -= (raycastHit.distance - sphereCollider->GetRadius() * 2.0f);
	//		model->Update(move, rot);
	//	}
	//}

	model->Update(move, rot);
}


void Player::DrawModel(Camera* camera)
{
	camera->SetTarget(move.x, move.y, move.z);
	model->Draw(camera);
}

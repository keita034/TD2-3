#include "MeshCollider.h"
#include"Collision.h"

MeshCollider::MeshCollider()
{
	//���b�V���`����Z�b�g
	shapeType = CollisionShapeMesh;
}

void MeshCollider::CnnstructTriangles(ModelInterface* model_)
{
	//�O�p�`���X�g���N���A
	triangle.clear();
	//�C���f�b�N�X�́A�O�p�`�̐��~3����̂�
	//�������烁�b�V�����̎O�p�`�̐����t�Z����
	size_t triangleNum = model_->GetIndices().size() / 3;
	triangle.resize(triangleNum);
	for (size_t i = 0; i < triangleNum; i++)
	{
		//������v�Z����O�p�`�̎Q��
		Triangle& tri = triangle[i];
		uint64_t idx0 = model_->GetIndices()[i * 3 + 0];
		uint64_t idx1 = model_->GetIndices()[i * 3 + 1];
		uint64_t idx2 = model_->GetIndices()[i * 3 + 2];
		//�O�p�`��3���_�̍��W����
		tri.p0 = { model_->GetVertices()[idx0].pos.x,model_->GetVertices()[idx0].pos.y,model_->GetVertices()[idx0].pos.z };
		tri.p1 = { model_->GetVertices()[idx1].pos.x,model_->GetVertices()[idx1].pos.y,model_->GetVertices()[idx1].pos.z };
		tri.p2 = { model_->GetVertices()[idx2].pos.x,model_->GetVertices()[idx2].pos.y,model_->GetVertices()[idx2].pos.z };
		//3���_����@�����v�Z
		tri.ComputeNormal();
	}
}

void MeshCollider::Update()
{
	//���[���h�s��̋t�s����v�Z
	invMatWorld = AliceMath::MakeInverse(&GetModel()->GetMatWorld());
}

void MeshCollider::SetModel(ModelInterface* model_)
{
	model = model_;
}

ModelInterface* MeshCollider::GetModel()
{
	return model;
}

CollisionShapeType MeshCollider::GetShapeType()
{
	return shapeType;
}

void MeshCollider::OnCollision(const CollisionInfo& info)
{
	static_cast<void>(info);
}

bool MeshCollider::CheckCollisionSphere(Sphere& sphere, AliceMath::Vector3* inter, AliceMath::Vector3* reject)
{
	Sphere localSphere;
	AliceMath::Vector4 tmp = { sphere.center.x,sphere.center.y,sphere.center.z,1.0f};
	tmp = AliceMath::Vector4Trns(tmp, invMatWorld);
	localSphere.center = { tmp.x,tmp.y,tmp.z };
	AliceMath::Vector4 vec = { invMatWorld.m[0][0],invMatWorld.m[0][1] ,invMatWorld.m[0][2] ,invMatWorld.m[0][3] };
	localSphere.radius *= vec.length();

	//���[�J�����W�n�Ō������`�F�b�N
	std::vector<Triangle>::const_iterator it = triangle.cbegin();

	for (; it != triangle.cend(); ++it)
	{
		const Triangle& triangle_ = *it;

		//���ƎO�p�`�̓����蔻��
		if (Collision::CheckSphere2Triangle(localSphere, triangle_, inter, reject))
		{
			if (inter)
			{
				AliceMath::Matrix4& matWorld = GetModel()->GetMatWorld();
				//���[���h���W�ł̌�_�𓾂�
				tmp = {inter->x,inter->y,inter->z,1.0f };
				tmp = AliceMath::Vector4Trns(tmp, matWorld);
				*inter = { tmp.x,tmp.y,tmp.z };
			}
			if (reject)
			{
				AliceMath::Matrix4 matWorld = GetModel()->GetMatWorld();
				//���[���h���W�n�ł̔r�˃x�N�g���ɕϊ�
				tmp = { reject->x,reject->y,reject->z,1.0f };
				tmp = AliceMath::Vector4Trns(tmp, matWorld);
				*reject = { tmp.x,tmp.y,tmp.z };
			}

			return true;
		}
	}
	return false;
}

bool MeshCollider::CheckCollisionRay(Ray& ray, float* distance, AliceMath::Vector3* inter)
{
	//�I�u�W�F�N�g�̃��[�J�����W�n�ł̃��C�𓾂�
	Ray localRay;
	AliceMath::Vector4 tmp = { ray.start.x,ray.start.y,ray.start.z,1.0f };
	tmp = AliceMath::Vector4Trns(tmp, invMatWorld);
	localRay.start = { tmp.x,tmp.y,tmp.z };
	localRay.dir = AliceMath::Vector3Trns(ray.dir, invMatWorld);
	localRay.dir.normalization();

	//���[�J�����W�n�Ō������`�F�b�N
	std::vector<Triangle>::const_iterator it = triangle.cbegin();

	for (; it != triangle.cend(); ++it)
	{
		const Triangle& triangle_ = *it;
		AliceMath::Vector3 templnter;

		//���C�ƎO�p�`�̓����蔻��
		if (Collision::CheckRay2Triangle(localRay, triangle_, nullptr, &templnter))
		{
			AliceMath::Matrix4& matWorld = GetModel()->GetMatWorld();
			//���[���h���W�ł̌�_�𓾂�
			tmp = { templnter.x,templnter.y,templnter.z,1.0f };
			tmp = AliceMath::Vector4Trns(tmp, matWorld);
			templnter = { tmp.x,tmp.y,tmp.z };

			if (distance)
			{
				//��_�ƃ��C�n�_�̋������v�Z
				AliceMath::Vector3 sub = templnter - ray.start;
				*distance = sub.dot(ray.dir);
			}

			if (inter)
			{
				*inter = templnter;
			}

			return true;
		}
	}

	return false;
}

void MeshCollider::SetAttribute(uint16_t attribute_)
{
	attribute = attribute_;
}

void MeshCollider::AddAttribute(uint16_t attribute_)
{
	attribute |= attribute_;
}

void MeshCollider::RemoveAttribute(uint16_t attribute_)
{
	attribute &= !attribute_;
}

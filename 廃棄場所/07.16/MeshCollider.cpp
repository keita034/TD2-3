#include "MeshCollider.h"
#include "Collision.h"
#include"ModelInterface.h"
#include"ModelCreate.h"
MeshCollider::MeshCollider()
{
	//���b�V���`����Z�b�g
	shapeType = CollisionShapeMesh;
}

void MeshCollider::ConstructTriangles(ModelInterface* model_)
{
	//�O�p�`���X�g���N���A
	triangles.clear();

	//�C���f�b�N�X�́A�O�p�`�̐��~3����̂�
	//�������烁�b�V�����̎O�p�`�̐����t�Z����
	size_t triangleNum = model_->GetIndices().size() / 3;
	triangles.resize(triangleNum);

	for (size_t i = 0; i < triangleNum; i++)
	{
		//������v�Z����O�p�`�̎Q��
		Triangle& tri = triangles[i];
		uint64_t idx0 = model_->GetIndices()[i * 3 + 0];
		uint64_t idx1 = model_->GetIndices()[i * 3 + 1];
		uint64_t idx2 = model_->GetIndices()[i * 3 + 2];
		//�O�p�`��3���_�̍��W����
		tri.p0 = { model_->GetVertices()[idx0].pos.x,model_->GetVertices()[idx0].pos.y,model_->GetVertices()[idx0].pos.z,1 };
		tri.p1 = { model_->GetVertices()[idx1].pos.x,model_->GetVertices()[idx1].pos.y,model_->GetVertices()[idx1].pos.z,1 };
		tri.p2 = { model_->GetVertices()[idx2].pos.x,model_->GetVertices()[idx2].pos.y,model_->GetVertices()[idx2].pos.z,1 };
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

bool MeshCollider::CheckCollisionSphere(Sphere& sphere, AliceMath::Vector4* inter, AliceMath::Vector4* reject)
{
	// �I�u�W�F�N�g�̃��[�J�����W�n�ł̋��𓾂�i���a��X�X�P�[�����Q��)
	Sphere localSphere;
	localSphere.center = AliceMath::Vector4Trns(sphere.center, invMatWorld);
	//localSphere.center = sphere.center;

	AliceMath::Vector4 tmp = { invMatWorld.m[0][0],invMatWorld.m[0][1] ,invMatWorld.m[0][2] ,invMatWorld.m[0][3] };
	localSphere.radius *= tmp.length();

	std::vector<Triangle>::const_iterator it = triangles.cbegin();
	int i = 0;
	for (; it != triangles.cend(); ++it)
	{
		const Triangle& triangle = *it;

		if (Collision::CheckSphere2Triangle(localSphere, triangle, inter, reject))
		{
			if (inter)
			{
				AliceMath::Matrix4& matWorld = GetModel()->GetMatWorld();

				*inter = AliceMath::Vector4Trns(*inter, matWorld);
			}
			if (reject)
			{
				AliceMath::Matrix4& matWorld = GetModel()->GetMatWorld();

				*reject = AliceMath::Vector4Trns(*reject, matWorld);
			}
			return true;
		}
		i++;
	}

	return false;
}

bool MeshCollider::CheckCollisionRay(Ray& ray, float* distance, AliceMath::Vector4* inter)
{
	// �I�u�W�F�N�g�̃��[�J�����W�n�ł̃��C�𓾂�
	Ray localRay;
	localRay.start = AliceMath::Vector4Trns(ray.start, invMatWorld);
	localRay.dir = AliceMath::Vector4Trns(ray.dir, invMatWorld);
	localRay.dir.normalization();

	std::vector<Triangle>::const_iterator it = triangles.cbegin();

	for (; it != triangles.cend(); ++it)
	{
		const Triangle& triangle = *it;

		AliceMath::Vector4 tempInter;

		if (Collision::CheckRay2Triangle(localRay, triangle, nullptr, &tempInter))
		{

			AliceMath::Matrix4& matWorld = GetModel()->GetMatWorld();

			tempInter = AliceMath::Vector4Trns(tempInter, matWorld);

			if (distance)
			{
				AliceMath::Vector4 sub = tempInter - ray.start;
				*distance = sub.dot(ray.dir);
			}

			if (inter)
			{
				*inter = tempInter;
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
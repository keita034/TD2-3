#pragma once
#include"ErrorException.h"
#include"Model.h"

class PrimitiveModel
{
private:
	//�L���[�u�̃C���f�b�N�X���ƒ��_��
	static 	const UINT cubeMaxIndex = 36;
	static const UINT cubeMaxVert = 24;

	//�~���̃C���f�b�N�X���ƒ��_��
	static const UINT coneMaxIndex = 191;
	static const UINT coneMaxVert = 66;

	//�V�����_�[�̃C���f�b�N�X���ƒ��_��
	static const UINT cylinderMaxIndex = 384;
	static const UINT cylinderMaxVert = 132;

	//���̃C���f�b�N�X���ƒ��_��
	static const UINT sphereMaxIndex = 3072;
	static const UINT sphereMaxVert = 560;

public:

	//������
	static void Create(ModelShape shape,ModelData* data);

private:

	static void CubeCreate(ModelData* data);

	static void ConeCreate(ModelData* data);

	static void CylinderCreate(ModelData* data);

	static void SphereCreate(ModelData* data);

	PrimitiveModel& operator=(const PrimitiveModel&) = delete;
	PrimitiveModel(const PrimitiveModel&) = delete;
};

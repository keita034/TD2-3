#pragma once
#include"ErrorException.h"
#include "Model.h"
#include "Transform.h"
#include "Camera.h"
#include "fbxModel.h"
#include "VerticalFold.h"
#include"FieldConstant.h"
#include"BesideFold.h"
#include"SurfaceFold.h"
#include"MeshCollider.h"

class Stage
{
private:

	//�ǂ��̖ʂ���ނ�
	FieldIndex FieldSurfaceIndex;

	//�ǂ̕����ɏ�ނ̂�
	FoldIndex foldDirection;

	bool fieldPlaneDrawFlag = false;

	std::array<std::array<FieldElement, 4>, 6> field;

	std::unique_ptr<VerticalFold> verticalFold_;

	std::unique_ptr<BesideFold> besideFold_;

	std::unique_ptr<SurfaceFold> surfaceFold_;

	//��̊p�x
	float standardAngle_;

	// �R���C�_�[�̒ǉ�
	MeshCollider* collider = new MeshCollider;
	MeshCollider* collider2 = new MeshCollider;
	MeshCollider* collider3 = new MeshCollider;
	MeshCollider* collider4 = new MeshCollider;
	MeshCollider* collider5 = new MeshCollider;


public:
	Stage() = default;
	~Stage() = default;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(Camera* camera);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	void FieldPlaneFoldStart(FieldIndex fieldIndex, FoldIndex foldIndex);

private:

	// �R�s�[�R���X�g���N�^���֎~
	Stage(const Stage& p) = delete;
	// �R�s�[������Z�q���֎~
	void operator=(const Stage& p) = delete;
};
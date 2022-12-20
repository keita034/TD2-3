#pragma once
#include"ErrorException.h"
#include "Model.h"
#include "Transform.h"
#include "Camera.h"
#include "fbxModel.h"

enum FieldIndex
{
	Top,//��
	Left,
	CenterLeft,
	CenterRight,
	Right,
	Bottom,//��
};

//��
enum class Field
{

	a,
	b,
	c,
	d,
	e,
	f,
	g,

};

enum class FoldIndex
{
	Vertical,//�c
	Beside//��
};

enum FieldElementIndex
{
	LeftTop,
	LeftBottom,
	RightTop,
	RightBottom,
};

struct FieldElement
{
	TextureData* textureData;
	Field field;
};

class Stage
{
private:
	// ���[���h�ϊ��f�[�^
	Transform fieldPlaneTrans_;
	// ���f��
	std::unique_ptr<Model> surfaceModel_;

	uint32_t surfaceModelHandle_;
	uint32_t besideFoldFbxmodelHandle_;

	Transform surfaceModelTrans_;

	//���܂胂�f��
	std::unique_ptr<fbxModel> besideFoldFbxmodel_;
	//���܂�A�j���[�V����
	std::unique_ptr<fbxAnimation> besideFoldFbxmodelAnime_;

	//���܂胂�f��
	std::unique_ptr<fbxModel> verticalFoldFbxmodel_;
	//���܂�A�j���[�V����
	std::unique_ptr<fbxAnimation> verticalFoldFbxmodelAnime_;

	//�ǂ��̖ʂ���ނ�
	FieldIndex FieldSurfaceIndex;

	//�ǂ̕����ɏ�ނ̂�
	FoldIndex foldDirection;

	float fieldPlaneAnimeFlam = 0.0f;
	bool fieldPlaneDrawFlag = false;
	bool fieldFoldFlag = true;

	std::array<std::array<FieldElement, 4>, 6> field;

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

	/// <summary>
	/// ��ފ�{����
	/// </summary>
	void InitializeFold();

	void FieldPlaneFoldStart(FieldIndex fieldIndex, FoldIndex foldIndex);

private:

	void FieldPlaneFold();
};
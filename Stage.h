#pragma once
#include"ErrorException.h"
#include "Model.h"
#include "Transform.h"
#include "Camera.h"
#include "fbxModel.h"

enum FieldIndex
{
	//����������
	//����������
	//����������

	Top,//��
	Left,//��
	CenterLeft,//�^�񒆍�
	CenterRight,//�^�񒆉E
	Right,//�E
	Bottom,//��

	TopToLeft,//��ƍ�
	TopToCenterLeft,//��Ɛ^�񒆍�
	TopToCenterRight,//��Ɛ^�񒆉E
	TopToRight,//��ƉE

	LeftToTop,//���Ə�
	LeftToTopToCenterLeft,//���Ɛ^�񒆍�
	LeftToRight,//���ƉE
	LeftToBottom,//���Ɖ�

	CenterLeftToTop,//�^�񒆍��Ə�
	CenterLeftToLeft,//�^�񒆍��ƍ�
	CenterLeftToCenterRight,//�^�񒆍��Ɛ^�񒆉E
	CenterLeftToBottom,//�^�񒆍��Ɖ�

	CenterRightToTop,//�^�񒆉E�Ə�
	CenterRightToCenterLeft,//�^�񒆉E�Ɛ^�񒆍�
	CenterRightToRight,//�^�񒆉E�ƉE
	CenterRightToBottom,//�^�񒆉E�Ɖ�

	RightToTop,//�E�Ə�
	RightToLeft,//�E�Ɖ�
	RightToCenterRight,//�E�Ɛ^�񒆉E
	RightToBottom,//�E�Ɖ�

	BottomToLeft,//���ƍ�
	BottomToCenterLeft,//���Ɛ^�񒆍�
	BottomToCenterRight,//���Ɛ^�񒆉E
	BottomToRight,//���ƉE

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
	h,
	i,
	j,
	k,
	l,
	n,
	m,
	o,
	p,
	q,
	r,
	s,
	t,
	u,
	v,
	w,
	x,
	y,
	z,
};

enum class FoldIndex
{
	Vertical,//�c
	Beside,//��
	Surface,//�ʂƖ�
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
	//�e�N�X�`��
	TextureData* textureData;
	//���ʗp
	Field field;
	//�ʂ̈ꕔ���f��
	std::unique_ptr<Model> surfacePartsModel;
	//���f���n���h��
	uint32_t surfacePartsModelHandle;
	//���[���h�ϊ�
	Transform surfacePartsModelTrans;
	bool isDraw = true;

	void Draw();
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

	//�c�܂胂�f��
	std::unique_ptr<fbxModel> verticalFoldFbxmodel_;
	//�c�܂�A�j���[�V����
	std::unique_ptr<fbxAnimation> verticalFoldFbxmodelAnime_;

	//�ʐ܂胂�f��
	std::unique_ptr<fbxModel> surfaceFoldFbxmodel_;
	//�ʐ܂�A�j���[�V����
	std::unique_ptr<fbxAnimation> surfaceFoldFbxmodelAnime_;

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

	void FieldPlaneFoldStart(FieldIndex fieldIndex, FoldIndex foldIndex);

private:

	void FieldPlaneFold();
};
#pragma once
#include"ErrorException.h"
#include"Model.h"

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
	LeftToCenterLeft,//���Ɛ^�񒆍�
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
	//�ʂ̈ꕔ���f��
	std::unique_ptr<Model> surfacePartsModel;
	//���f���n���h��
	uint32_t surfacePartsModelHandle;
	//���[���h�ϊ�
	Transform surfacePartsModelTrans;
	//
	float angle_;
	//���ʗp
	Field field;
	//�`�悷�邩
	bool isDraw = true;

	void Draw();
};
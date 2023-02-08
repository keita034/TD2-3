#include "SurfaceFoldTop2.h"
#include "MeshCollider.h"
#include "CollisionAttribute.h"
#include "CollisionManager.h"

#include "ChangeCollider.h"

void SurfaceFoldTop2::StartTopTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, AliceModel* surfaceFoldFbxmodel_)
{
	field[Top][LeftTop].isDraw = false;
	field[Top][RightTop].isDraw = false;
	field[Top][LeftBottom].isDraw = false;
	field[Top][RightBottom].isDraw = false;

	switch (fieldIndex)
	{

#pragma region ��ƍ�

	case TopToLeft:

		//��]
		fieldPlaneTrans_.rotation = { 0.0f * AliceMathF::Deg2Rad,-90.0f * AliceMathF::Deg2Rad,0.0f * AliceMathF::Deg2Rad };

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Top][RightBottom].textureData);

		//���UV��]
		surfaceFoldFbxmodel_->rotationUV("Material.003", (field[Top][LeftTop].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", (field[Top][RightTop].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", (field[Top][LeftBottom].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", (field[Top][RightBottom].angle_ - 90.0f) * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[Left][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Material.005", (-90 - field[Left][LeftTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.006", (-90 - field[Left][RightTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", (-90 - field[Left][LeftBottom].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.008", (-90 - field[Left][RightBottom].angle_) * AliceMathF::Deg2Rad);

		field[Left][LeftTop].isDraw = false;
		field[Left][RightTop].isDraw = false;
		field[Left][LeftBottom].isDraw = false;
		field[Left][RightBottom].isDraw = false;

		break;
#pragma endregion

#pragma region ��Ɛ^�񒆍�
	case TopToCenterLeft:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Top][RightBottom].textureData);

		//���UV��]
		surfaceFoldFbxmodel_->rotationUV("Material.001", (field[Top][LeftTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", (field[Top][RightTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.003", (field[Top][LeftBottom].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", (field[Top][RightBottom].angle_) * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[CenterLeft][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Material.005", (-field[CenterRight][LeftTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.006", (-field[CenterRight][RightTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", (-field[CenterRight][LeftBottom].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.008", (-field[CenterRight][RightBottom].angle_) * AliceMathF::Deg2Rad);

		//��]
		fieldPlaneTrans_.rotation = { 0.0f,180.0f * AliceMathF::Deg2Rad,0.0f };

		field[CenterLeft][LeftTop].isDraw = false;
		field[CenterLeft][RightTop].isDraw = false;
		field[CenterLeft][LeftBottom].isDraw = false;
		field[CenterLeft][RightBottom].isDraw = false;

		break;
#pragma endregion

#pragma region  ��Ɛ^�񒆉E

	case TopToCenterRight:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Top][RightBottom].textureData);

		//���UV��]
		surfaceFoldFbxmodel_->rotationUV("Material.003", (90.0f + field[Top][LeftTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", (90.0f + field[Top][RightTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", (90.0f + field[Top][LeftBottom].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", (90.0f + field[Top][RightBottom].angle_) * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[CenterRight][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Material.005", (field[CenterRight][LeftTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.006", (field[CenterRight][RightTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", (field[CenterRight][LeftBottom].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.008", (field[CenterRight][RightBottom].angle_) * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 0.0f,90.0f * AliceMathF::Deg2Rad,0.0f };

		field[CenterRight][LeftTop].isDraw = false;
		field[CenterRight][RightTop].isDraw = false;
		field[CenterRight][LeftBottom].isDraw = false;
		field[CenterRight][RightBottom].isDraw = false;

		break;
#pragma endregion

#pragma region ��ƉE

	case TopToRight:


		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Top][RightBottom].textureData);

		//���UV��]
		surfaceFoldFbxmodel_->rotationUV("Material.004", (-180 + field[Top][LeftTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.003", (-180 + field[Top][RightTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", (-180 + field[Top][LeftBottom].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", (-180 + field[Top][RightBottom].angle_) * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[Right][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Material.005", (field[Right][LeftTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.006", (field[Right][RightTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", (field[Right][LeftBottom].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.008", (field[Right][RightBottom].angle_) * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 0.0f,0.0f,90.0f * AliceMathF::Deg2Rad };

		field[Right][LeftTop].isDraw = false;
		field[Right][RightTop].isDraw = false;
		field[Right][LeftBottom].isDraw = false;
		field[Right][RightBottom].isDraw = false;

#pragma endregion

		break;
	default:
		break;
	}
}

void SurfaceFoldTop2::ShrinkAnimeTopTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, float scale)
{
	field[Top][LeftTop].surfacePartsModelTrans.scale.y = scale;
	field[Top][RightTop].surfacePartsModelTrans.scale.y = scale;
	field[Top][LeftBottom].surfacePartsModelTrans.scale.y = scale;
	field[Top][RightBottom].surfacePartsModelTrans.scale.y = scale;

	switch (fieldIndex)
	{
	case TopToLeft:

		field[Left][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[Left][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[Left][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[Left][RightBottom].surfacePartsModelTrans.scale.y = scale;

		break;

	case TopToCenterLeft:

		field[CenterLeft][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[CenterLeft][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[CenterLeft][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[CenterLeft][RightBottom].surfacePartsModelTrans.scale.y = scale;

		break;

	case TopToCenterRight:

		field[CenterRight][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[CenterRight][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[CenterRight][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[CenterRight][RightBottom].surfacePartsModelTrans.scale.y = scale;

		break;

	case TopToRight:

		field[Right][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[Right][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[Right][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[Right][RightBottom].surfacePartsModelTrans.scale.y = scale;

		break;

	default:
		break;
	}
}

void SurfaceFoldTop2::ReplaceTopTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, AliceModel* surfaceFoldFbxmodel_)
{
	FieldElement element;
	Transform transform1;
	Transform transform2;
	float angle1 = 0.0f;
	float angle2 = 0.0f;

	switch (fieldIndex)
	{
	case TopToLeft:
		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[Top][LeftTop].surfacePartsModelTrans;
		transform2 = field[Left][LeftTop].surfacePartsModelTrans;

		angle1 = field[Top][LeftTop].angle_;
		angle2 = field[Left][LeftTop].angle_;

		element = std::move(field[Top][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[Top][LeftTop] = std::move(field[Left][LeftTop]);
		field[Top][LeftTop].surfacePartsModelTrans = transform1;
		field[Top][LeftTop].angle_ = angle1;

		field[Left][LeftTop] = std::move(element);
		field[Left][LeftTop].surfacePartsModelTrans = transform2;
		field[Left][LeftTop].angle_ = angle2;

		//SetCollider(field, Top, LeftTop, 3);
		//SetCollider(field, Left, LeftTop, 5);

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Top][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Left][RightTop].surfacePartsModelTrans;

		angle1 = field[Top][LeftBottom].angle_;
		angle2 = field[Left][RightTop].angle_;

		element = std::move(field[Top][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[Top][LeftBottom] = std::move(field[Left][RightTop]);
		field[Top][LeftBottom].surfacePartsModelTrans = transform1;
		field[Top][LeftBottom].angle_ = angle1;

		field[Left][RightTop] = std::move(element);
		field[Left][RightTop].surfacePartsModelTrans = transform2;
		field[Left][RightTop].angle_ = angle2;

		//SetCollider(field, Top, LeftBottom, 4);
		//SetCollider(field, Left, RightTop, 6);

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[Top][RightTop].surfacePartsModelTrans;
		transform2 = field[Left][LeftBottom].surfacePartsModelTrans;

		angle1 = field[Top][RightTop].angle_;
		angle2 = field[Left][LeftBottom].angle_;

		element = std::move(field[Top][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[Top][RightTop] = std::move(field[Left][LeftBottom]);
		field[Top][RightTop].surfacePartsModelTrans = transform1;
		field[Top][RightTop].angle_ = angle1;

		field[Left][LeftBottom] = std::move(element);
		field[Left][LeftBottom].surfacePartsModelTrans = transform2;
		field[Left][LeftBottom].angle_ = angle2;

		//SetCollider(field, Top, RightTop, 1);
		//SetCollider(field, Left, LeftBottom, 7);

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[Top][RightBottom].surfacePartsModelTrans;
		transform2 = field[Left][RightBottom].surfacePartsModelTrans;

		angle1 = field[Top][RightBottom].angle_;
		angle2 = field[Left][RightBottom].angle_;

		element = std::move(field[Top][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Left][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[Top][RightBottom] = std::move(field[Left][RightBottom]);
		field[Top][RightBottom].surfacePartsModelTrans = transform1;
		field[Top][RightBottom].angle_ = angle1;

		field[Left][RightBottom] = std::move(element);
		field[Left][RightBottom].surfacePartsModelTrans = transform2;
		field[Left][RightBottom].angle_ = angle2;

		//SetCollider(field, Top, RightBottom, 2);
		//SetCollider(field, Left, RightBottom, 8);

		break;

	case TopToCenterLeft:

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[Top][LeftTop].surfacePartsModelTrans;
		transform2 = field[CenterLeft][LeftBottom].surfacePartsModelTrans;

		angle1 = field[Top][LeftTop].angle_;
		angle2 = field[CenterLeft][LeftBottom].angle_;

		element = std::move(field[Top][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[Top][LeftTop] = std::move(field[CenterLeft][LeftBottom]);
		field[Top][LeftTop].surfacePartsModelTrans = transform1;
		field[Top][LeftTop].angle_ = angle1;

		field[CenterLeft][LeftBottom] = std::move(element);
		field[CenterLeft][LeftBottom].surfacePartsModelTrans = transform2;
		field[CenterLeft][LeftBottom].angle_ = angle2;

		//SetCollider(field, Top, LeftTop, 1);
		//SetCollider(field, CenterLeft, LeftBottom, 7);

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[Top][RightTop].surfacePartsModelTrans;
		transform2 = field[CenterLeft][RightBottom].surfacePartsModelTrans;

		angle1 = field[Top][RightTop].angle_;
		angle2 = field[CenterLeft][RightBottom].angle_;

		element = std::move(field[Top][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[CenterLeft][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[Top][RightTop] = std::move(field[CenterLeft][RightBottom]);
		field[Top][RightTop].surfacePartsModelTrans = transform1;
		field[Top][RightTop].angle_ = angle1;

		field[CenterLeft][RightBottom] = std::move(element);
		field[CenterLeft][RightBottom].surfacePartsModelTrans = transform2;
		field[CenterLeft][RightBottom].angle_ = angle2;

		//SetCollider(field, Top, RightTop, 2);
		//SetCollider(field, CenterLeft, RightBottom, 8);

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[Top][LeftBottom].surfacePartsModelTrans;
		transform2 = field[CenterLeft][LeftTop].surfacePartsModelTrans;

		angle1 = field[Top][LeftBottom].angle_;
		angle2 = field[CenterLeft][LeftTop].angle_;

		element = std::move(field[Top][LeftBottom]);


		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[Top][LeftBottom] = std::move(field[CenterLeft][LeftTop]);
		field[Top][LeftBottom].surfacePartsModelTrans = transform1;
		field[Top][LeftBottom].angle_ = angle1;

		field[CenterLeft][LeftTop] = std::move(element);
		field[CenterLeft][LeftTop].surfacePartsModelTrans = transform2;
		field[CenterLeft][LeftTop].angle_ = angle2;

		//SetCollider(field, Top, LeftBottom, 3);
		//SetCollider(field, CenterLeft, LeftTop, 5);

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Top][RightBottom].surfacePartsModelTrans;
		transform2 = field[CenterLeft][RightTop].surfacePartsModelTrans;

		angle1 = field[Top][RightBottom].angle_;
		angle2 = field[CenterLeft][RightTop].angle_;

		element = std::move(field[Top][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[Top][RightBottom] = std::move(field[CenterLeft][RightTop]);
		field[Top][RightBottom].surfacePartsModelTrans = transform1;
		field[Top][RightBottom].angle_ = angle1;

		field[CenterLeft][RightTop] = std::move(element);
		field[CenterLeft][RightTop].surfacePartsModelTrans = transform2;
		field[CenterLeft][RightTop].angle_ = angle2;

		//SetCollider(field, Top, RightBottom, 4);
		//SetCollider(field, CenterLeft, RightTop, 6);

		break;

	case TopToCenterRight:

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[Top][LeftTop].surfacePartsModelTrans;
		transform2 = field[CenterRight][RightBottom].surfacePartsModelTrans;

		angle1 = field[Top][LeftTop].angle_;
		angle2 = field[CenterRight][RightBottom].angle_;

		element = std::move(field[Top][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[CenterRight][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[Top][LeftTop] = std::move(field[CenterRight][RightBottom]);
		field[Top][LeftTop].surfacePartsModelTrans = transform1;
		field[Top][LeftTop].angle_ = angle1;

		field[CenterRight][RightBottom] = std::move(element);
		field[CenterRight][RightBottom].surfacePartsModelTrans = transform2;
		field[CenterRight][RightBottom].angle_ = angle2;

		//SetCollider(field, Top, LeftTop, 2);
		//SetCollider(field, CenterRight, RightBottom, 8);

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Top][RightTop].surfacePartsModelTrans;
		transform2 = field[CenterRight][RightTop].surfacePartsModelTrans;

		angle1 = field[Top][RightTop].angle_;
		angle2 = field[CenterRight][RightTop].angle_;

		element = std::move(field[Top][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[Top][RightTop] = std::move(field[CenterRight][RightTop]);
		field[Top][RightTop].surfacePartsModelTrans = transform1;
		field[Top][RightTop].angle_ = angle1;

		field[CenterRight][RightTop] = std::move(element);
		field[CenterRight][RightTop].surfacePartsModelTrans = transform2;
		field[CenterRight][RightTop].angle_ = angle2;

		//SetCollider(field, Top, RightTop, 4);
		//SetCollider(field, CenterRight, RightTop, 6);

		//1�Ԃ�5�Ԃ����ւ���
		transform1 = field[Top][LeftBottom].surfacePartsModelTrans;
		transform2 = field[CenterRight][LeftBottom].surfacePartsModelTrans;

		angle1 = field[Top][LeftBottom].angle_;
		angle2 = field[CenterRight][LeftBottom].angle_;

		element = std::move(field[Top][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[Top][LeftBottom] = std::move(field[CenterRight][LeftBottom]);
		field[Top][LeftBottom].surfacePartsModelTrans = transform1;
		field[Top][LeftBottom].angle_ = angle1;

		field[CenterRight][LeftBottom] = std::move(element);
		field[CenterRight][LeftBottom].surfacePartsModelTrans = transform2;
		field[CenterRight][LeftBottom].angle_ = angle2;

		//SetCollider(field, Top, LeftBottom, 1);
		//SetCollider(field, CenterRight, LeftBottom, 7);

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Top][RightBottom].surfacePartsModelTrans;
		transform2 = field[CenterRight][LeftTop].surfacePartsModelTrans;

		angle1 = field[Top][RightBottom].angle_;
		angle2 = field[CenterRight][LeftTop].angle_;

		element = std::move(field[Top][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[Top][RightBottom] = std::move(field[CenterRight][LeftTop]);
		field[Top][RightBottom].surfacePartsModelTrans = transform1;
		field[Top][RightBottom].angle_ = angle1;

		field[CenterRight][LeftTop] = std::move(element);
		field[CenterRight][LeftTop].surfacePartsModelTrans = transform2;
		field[CenterRight][LeftTop].angle_ = angle2;

		//SetCollider(field, Top, RightBottom, 3);
		//SetCollider(field, CenterRight, LeftTop, 5);

		break;

	case TopToRight:

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Top][LeftTop].surfacePartsModelTrans;
		transform2 = field[Right][RightTop].surfacePartsModelTrans;

		angle1 = field[Top][LeftTop].angle_;
		angle2 = field[Right][RightTop].angle_;

		element = std::move(field[Top][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[Top][LeftTop] = std::move(field[Right][RightTop]);
		field[Top][LeftTop].surfacePartsModelTrans = transform1;
		field[Top][LeftTop].angle_ = angle1;

		field[Right][RightTop] = std::move(element);
		field[Right][RightTop].surfacePartsModelTrans = transform2;
		field[Right][RightTop].angle_ = angle2;

		//SetCollider(field, Top, LeftTop, 4);
		//SetCollider(field, Right, RightTop, 6);

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[Top][RightTop].surfacePartsModelTrans;
		transform2 = field[Right][LeftTop].surfacePartsModelTrans;

		angle1 = field[Top][RightTop].angle_;
		angle2 = field[Right][LeftTop].angle_;

		element = std::move(field[Top][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[Top][RightTop] = std::move(field[Right][LeftTop]);
		field[Top][RightTop].surfacePartsModelTrans = transform1;
		field[Top][RightTop].angle_ = angle1;

		field[Right][LeftTop] = std::move(element);
		field[Right][LeftTop].surfacePartsModelTrans = transform2;
		field[Right][LeftTop].angle_ = angle2;

		//SetCollider(field, Top, RightTop, 3);
		//SetCollider(field, Right, LeftTop, 5);

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[Top][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Right][RightBottom].surfacePartsModelTrans;

		angle1 = field[Top][LeftBottom].angle_;
		angle2 = field[Right][RightBottom].angle_;

		element = std::move(field[Top][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Right][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[Top][LeftBottom] = std::move(field[Right][RightBottom]);
		field[Top][LeftBottom].surfacePartsModelTrans = transform1;
		field[Top][LeftBottom].angle_ = angle1;

		field[Right][RightBottom] = std::move(element);
		field[Right][RightBottom].surfacePartsModelTrans = transform2;
		field[Right][RightBottom].angle_ = angle2;

		//SetCollider(field, Top, LeftBottom, 2);
		//SetCollider(field, Right, RightBottom, 8);

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[Top][RightBottom].surfacePartsModelTrans;
		transform2 = field[Right][LeftBottom].surfacePartsModelTrans;

		angle1 = field[Top][RightBottom].angle_;
		angle2 = field[Right][LeftBottom].angle_;

		element = std::move(field[Top][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[Top][RightBottom] = std::move(field[Right][LeftBottom]);
		field[Top][RightBottom].surfacePartsModelTrans = transform1;
		field[Top][RightBottom].angle_ = angle1;

		field[Right][LeftBottom] = std::move(element);
		field[Right][LeftBottom].surfacePartsModelTrans = transform2;
		field[Right][LeftBottom].angle_ = angle2;

		//SetCollider(field, Top, RightBottom, 1);
		//SetCollider(field, Right, LeftBottom, 7);

		break;

	default:
		break;
	}
}

void SurfaceFoldTop2::EndTopTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	field[Top][LeftTop].isDraw = true;
	field[Top][RightTop].isDraw = true;
	field[Top][LeftBottom].isDraw = true;
	field[Top][RightBottom].isDraw = true;

	switch (fieldIndex)
	{
	case TopToLeft:

		field[Left][LeftTop].isDraw = true;
		field[Left][RightTop].isDraw = true;
		field[Left][LeftBottom].isDraw = true;
		field[Left][RightBottom].isDraw = true;

		break;

	case TopToCenterLeft:

		field[CenterLeft][LeftTop].isDraw = true;
		field[CenterLeft][RightTop].isDraw = true;
		field[CenterLeft][LeftBottom].isDraw = true;
		field[CenterLeft][RightBottom].isDraw = true;

		break;

	case TopToCenterRight:

		field[CenterRight][LeftTop].isDraw = true;
		field[CenterRight][RightTop].isDraw = true;
		field[CenterRight][LeftBottom].isDraw = true;
		field[CenterRight][RightBottom].isDraw = true;

		break;

	case TopToRight:

		field[Right][LeftTop].isDraw = true;
		field[Right][RightTop].isDraw = true;
		field[Right][LeftBottom].isDraw = true;
		field[Right][RightBottom].isDraw = true;

		break;

	default:
		break;
	}
}


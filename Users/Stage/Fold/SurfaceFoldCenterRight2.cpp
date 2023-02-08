#include "SurfaceFoldCenterRight2.h"
#include "MeshCollider.h"
#include "CollisionAttribute.h"
#include "CollisionManager.h"

#include "ChangeCollider.h"

void SurfaceFoldCenterRight2::StartCenterRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, AliceModel* surfaceFoldFbxmodel_)
{
	field[CenterRight][LeftTop].isDraw = false;
	field[CenterRight][RightTop].isDraw = false;
	field[CenterRight][LeftBottom].isDraw = false;
	field[CenterRight][RightBottom].isDraw = false;

	switch (fieldIndex)
	{
#pragma region 真ん中右と上
	case CenterRightToTop:

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[CenterRight][RightBottom].textureData);

		//上のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.004", (field[CenterRight][LeftTop].angle_ - 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.003", (field[CenterRight][RightTop].angle_ - 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", (field[CenterRight][LeftBottom].angle_ - 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", (field[CenterRight][RightBottom].angle_ - 180.0f) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[Top][RightBottom].textureData);

		//下のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.006", (field[Top][LeftTop].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.008", (field[Top][RightTop].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.005", (field[Top][LeftBottom].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", (field[Top][RightBottom].angle_ - 90.0f) * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { -90.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[Top][LeftTop].isDraw = false;
		field[Top][RightTop].isDraw = false;
		field[Top][LeftBottom].isDraw = false;
		field[Top][RightBottom].isDraw = false;

		break;
#pragma endregion

#pragma region 真ん中右と真ん中左

	case CenterRightToCenterLeft:

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[CenterRight][RightBottom].textureData);

		//上のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.003", (field[CenterRight][LeftTop].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", (field[CenterRight][RightTop].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", (field[CenterRight][LeftBottom].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", (field[CenterRight][RightBottom].angle_ - 90.0f) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[CenterLeft][RightBottom].textureData);

		//下のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.007", (field[CenterLeft][LeftTop].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.005", (field[CenterLeft][RightTop].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.008", (field[CenterLeft][LeftBottom].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.006", (field[CenterLeft][RightBottom].angle_ - 90.0f) * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 0.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[CenterLeft][LeftTop].isDraw = false;
		field[CenterLeft][RightTop].isDraw = false;
		field[CenterLeft][LeftBottom].isDraw = false;
		field[CenterLeft][RightBottom].isDraw = false;

		break;
#pragma endregion

#pragma region 真ん中右と右

	case CenterRightToRight:

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[CenterRight][RightBottom].textureData);

		//上のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.002", (field[CenterRight][LeftTop].angle_ + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", (field[CenterRight][RightTop].angle_ + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", (field[CenterRight][LeftBottom].angle_ + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.003", (field[CenterRight][RightBottom].angle_ + 90.0f) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[Right][RightBottom].textureData);

		//下のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.006", (field[Right][LeftTop].angle_ + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.008", (field[Right][RightTop].angle_ + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.005", (field[Right][LeftBottom].angle_ + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", (field[Right][RightBottom].angle_ + 90.0f) * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 180.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[Right][LeftTop].isDraw = false;
		field[Right][RightTop].isDraw = false;
		field[Right][LeftBottom].isDraw = false;
		field[Right][RightBottom].isDraw = false;

		break;
#pragma endregion

#pragma region 真ん中右と下
	case CenterRightToBottom:

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[CenterRight][RightBottom].textureData);

		surfaceFoldFbxmodel_->rotationUV("Material.001", (field[CenterRight][LeftTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", (field[CenterRight][RightTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.003", (field[CenterRight][LeftBottom].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", (field[CenterRight][RightBottom].angle_) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[Bottom][RightBottom].textureData);

		//下のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.006", (-90.0f - field[Bottom][LeftTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.008", (-90.0f - field[Bottom][RightTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.005", (-90.0f - field[Bottom][LeftBottom].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", (-90.0f - field[Bottom][RightBottom].angle_) * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 90.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[Bottom][LeftTop].isDraw = false;
		field[Bottom][RightTop].isDraw = false;
		field[Bottom][LeftBottom].isDraw = false;
		field[Bottom][RightBottom].isDraw = false;

		break;
#pragma endregion

	default:
		break;
	}
}

void SurfaceFoldCenterRight2::ShrinkAnimeCenterRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, float scale)
{
	field[CenterRight][LeftTop].surfacePartsModelTrans.scale.y = scale;
	field[CenterRight][RightTop].surfacePartsModelTrans.scale.y = scale;
	field[CenterRight][LeftBottom].surfacePartsModelTrans.scale.y = scale;
	field[CenterRight][RightBottom].surfacePartsModelTrans.scale.y = scale;
	switch (fieldIndex)
	{

	case CenterRightToTop:

		field[Top][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[Top][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[Top][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[Top][RightBottom].surfacePartsModelTrans.scale.y = scale;

		break;

	case CenterRightToCenterLeft:

		field[CenterLeft][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[CenterLeft][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[CenterLeft][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[CenterLeft][RightBottom].surfacePartsModelTrans.scale.y = scale;

		break;

	case CenterRightToRight:

		field[Right][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[Right][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[Right][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[Right][RightBottom].surfacePartsModelTrans.scale.y = scale;

		break;

	case CenterRightToBottom:

		field[Bottom][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[Bottom][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[Bottom][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[Bottom][RightBottom].surfacePartsModelTrans.scale.y = scale;

		break;

	default:
		break;
	}
}

void SurfaceFoldCenterRight2::ReplaceCenterRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, AliceModel* surfaceFoldFbxmodel_)
{
	FieldElement element;
	Transform transform1;
	Transform transform2;
	float angle1 = 0.0f;
	float angle2 = 0.0f;

	switch (fieldIndex)
	{
#pragma region 真ん中右と上
	case CenterRightToTop:

		//4番と6番を入れ替える
		transform1 = field[CenterRight][LeftTop].surfacePartsModelTrans;
		transform2 = field[Top][RightBottom].surfacePartsModelTrans;

		angle1 = field[CenterRight][LeftTop].angle_;
		angle2 = field[Top][RightBottom].angle_;

		element = std::move(field[CenterRight][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Top][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[CenterRight][LeftTop] = std::move(field[Top][RightBottom]);
		field[CenterRight][LeftTop].surfacePartsModelTrans = transform1;
		field[CenterRight][LeftTop].angle_ = angle1;

		field[Top][RightBottom] = std::move(element);
		field[Top][RightBottom].surfacePartsModelTrans = transform2;
		field[Top][RightBottom].angle_ = angle2;

		//SetCollider(field, CenterRight, LeftTop, 4);
		//SetCollider(field, Top, RightBottom, 6);

		//3番と5番を入れ替える
		transform1 = field[CenterRight][RightTop].surfacePartsModelTrans;
		transform2 = field[Top][RightTop].surfacePartsModelTrans;

		angle1 = field[CenterRight][RightTop].angle_;
		angle2 = field[Top][RightTop].angle_;

		element = std::move(field[CenterRight][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[CenterRight][RightTop] = std::move(field[Top][RightTop]);
		field[CenterRight][RightTop].surfacePartsModelTrans = transform1;
		field[CenterRight][RightTop].angle_ = angle1;

		field[Top][RightTop] = std::move(element);
		field[Top][RightTop].surfacePartsModelTrans = transform2;
		field[Top][RightTop].angle_ = angle2;

		//SetCollider(field, CenterRight, RightTop, 3);
		//SetCollider(field, Top, RightTop, 5);

		//2番と8番を入れ替える
		transform1 = field[CenterRight][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Top][LeftBottom].surfacePartsModelTrans;

		angle1 = field[CenterRight][LeftBottom].angle_;
		angle2 = field[Top][LeftBottom].angle_;

		element = std::move(field[CenterRight][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[CenterRight][LeftBottom] = std::move(field[Top][LeftBottom]);
		field[CenterRight][LeftBottom].surfacePartsModelTrans = transform1;
		field[CenterRight][LeftBottom].angle_ = angle1;

		field[Top][LeftBottom] = std::move(element);
		field[Top][LeftBottom].surfacePartsModelTrans = transform2;
		field[Top][LeftBottom].angle_ = angle2;

		//SetCollider(field, CenterRight, LeftBottom, 2);
		//SetCollider(field, Top, LeftBottom, 8);

		//1番と7番を入れ替える
		transform1 = field[CenterRight][RightBottom].surfacePartsModelTrans;
		transform2 = field[Top][LeftTop].surfacePartsModelTrans;

		angle1 = field[CenterRight][RightBottom].angle_;
		angle2 = field[Top][LeftTop].angle_;

		element = std::move(field[CenterRight][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[CenterRight][RightBottom] = std::move(field[Top][LeftTop]);
		field[CenterRight][RightBottom].surfacePartsModelTrans = transform1;
		field[CenterRight][RightBottom].angle_ = angle1;

		field[Top][LeftTop] = std::move(element);
		field[Top][LeftTop].surfacePartsModelTrans = transform2;
		field[Top][LeftTop].angle_ = angle2;

		//SetCollider(field, CenterRight, RightBottom, 1);
		//SetCollider(field, Top, LeftTop, 7);

		break;
#pragma endregion

#pragma region 真ん中右と真ん中左
	case CenterRightToCenterLeft:

		//4番と6番を入れ替える
		transform1 = field[CenterRight][LeftTop].surfacePartsModelTrans;
		transform2 = field[CenterLeft][RightTop].surfacePartsModelTrans;

		angle1 = field[CenterRight][LeftTop].angle_;
		angle2 = field[CenterLeft][RightTop].angle_;

		element = std::move(field[CenterRight][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[CenterRight][LeftTop] = std::move(field[CenterLeft][RightTop]);
		field[CenterRight][LeftTop].surfacePartsModelTrans = transform1;
		field[CenterRight][LeftTop].angle_ = angle1;

		field[CenterLeft][RightTop] = std::move(element);
		field[CenterLeft][RightTop].surfacePartsModelTrans = transform2;
		field[CenterLeft][RightTop].angle_ = angle2;

		//SetCollider(field, CenterRight, LeftTop, 4);
		//SetCollider(field, CenterLeft, RightTop, 6);

		//3番と5番を入れ替える
		transform1 = field[CenterRight][RightTop].surfacePartsModelTrans;
		transform2 = field[CenterLeft][LeftTop].surfacePartsModelTrans;

		angle1 = field[CenterRight][RightTop].angle_;
		angle2 = field[CenterLeft][LeftTop].angle_;

		element = std::move(field[CenterRight][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[CenterRight][RightTop] = std::move(field[CenterLeft][LeftTop]);
		field[CenterRight][RightTop].surfacePartsModelTrans = transform1;
		field[CenterRight][RightTop].angle_ = angle1;

		field[CenterLeft][LeftTop] = std::move(element);
		field[CenterLeft][LeftTop].surfacePartsModelTrans = transform2;
		field[CenterLeft][LeftTop].angle_ = angle2;

		//SetCollider(field, CenterRight, RightTop, 3);
		//SetCollider(field, CenterLeft, LeftTop, 5);

		//2番と8番を入れ替える
		transform1 = field[CenterRight][LeftBottom].surfacePartsModelTrans;
		transform2 = field[CenterLeft][RightBottom].surfacePartsModelTrans;

		angle1 = field[CenterRight][LeftBottom].angle_;
		angle2 = field[CenterLeft][RightBottom].angle_;

		element = std::move(field[CenterRight][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[CenterLeft][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[CenterRight][LeftBottom] = std::move(field[CenterLeft][RightBottom]);
		field[CenterRight][LeftBottom].surfacePartsModelTrans = transform1;
		field[CenterRight][LeftBottom].angle_ = angle1;

		field[CenterLeft][RightBottom] = std::move(element);
		field[CenterLeft][RightBottom].surfacePartsModelTrans = transform2;
		field[CenterLeft][RightBottom].angle_ = angle2;

		//SetCollider(field, CenterRight, LeftBottom, 2);
		//SetCollider(field, CenterLeft, RightBottom, 8);

		//1番と7番を入れ替える
		transform1 = field[CenterRight][RightBottom].surfacePartsModelTrans;
		transform2 = field[CenterLeft][LeftBottom].surfacePartsModelTrans;

		angle1 = field[CenterRight][RightBottom].angle_;
		angle2 = field[CenterLeft][LeftBottom].angle_;

		element = std::move(field[CenterRight][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[CenterRight][RightBottom] = std::move(field[CenterLeft][LeftBottom]);
		field[CenterRight][RightBottom].surfacePartsModelTrans = transform1;
		field[CenterRight][RightBottom].angle_ = angle1;

		field[CenterLeft][LeftBottom] = std::move(element);
		field[CenterLeft][LeftBottom].surfacePartsModelTrans = transform2;
		field[CenterLeft][LeftBottom].angle_ = angle2;

		//SetCollider(field, CenterRight, RightBottom, 1);
		//SetCollider(field, CenterLeft, LeftBottom, 7);

		break;
#pragma endregion

#pragma region 真ん中右と右

	case CenterRightToRight:

		//4番と6番を入れ替える
		transform1 = field[CenterRight][LeftTop].surfacePartsModelTrans;
		transform2 = field[Right][RightTop].surfacePartsModelTrans;

		angle1 = field[CenterRight][LeftTop].angle_;
		angle2 = field[Right][RightTop].angle_;

		element = std::move(field[CenterRight][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[CenterRight][LeftTop] = std::move(field[Right][RightTop]);
		field[CenterRight][LeftTop].surfacePartsModelTrans = transform1;
		field[CenterRight][LeftTop].angle_ = angle1;

		field[Right][RightTop] = std::move(element);
		field[Right][RightTop].surfacePartsModelTrans = transform2;
		field[Right][RightTop].angle_ = angle2;

		//SetCollider(field, CenterRight, LeftTop, 4);
		//SetCollider(field, Right, RightTop, 6);

		//3番と5番を入れ替える
		transform1 = field[CenterRight][RightTop].surfacePartsModelTrans;
		transform2 = field[Right][LeftTop].surfacePartsModelTrans;

		angle1 = field[CenterRight][RightTop].angle_;
		angle2 = field[Right][LeftTop].angle_;

		element = std::move(field[CenterRight][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[CenterRight][RightTop] = std::move(field[Right][LeftTop]);
		field[CenterRight][RightTop].surfacePartsModelTrans = transform1;
		field[CenterRight][RightTop].angle_ = angle1;

		field[Right][LeftTop] = std::move(element);
		field[Right][LeftTop].surfacePartsModelTrans = transform2;
		field[Right][LeftTop].angle_ = angle2;

		//SetCollider(field, CenterRight, RightTop, 3);
		//SetCollider(field, Right, LeftTop, 5);

		//2番と8番を入れ替える
		transform1 = field[CenterRight][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Right][RightBottom].surfacePartsModelTrans;

		angle1 = field[CenterRight][LeftBottom].angle_;
		angle2 = field[Right][RightBottom].angle_;

		element = std::move(field[CenterRight][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Right][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[CenterRight][LeftBottom] = std::move(field[Right][RightBottom]);
		field[CenterRight][LeftBottom].surfacePartsModelTrans = transform1;
		field[CenterRight][LeftBottom].angle_ = angle1;

		field[Right][RightBottom] = std::move(element);
		field[Right][RightBottom].surfacePartsModelTrans = transform2;
		field[Right][RightBottom].angle_ = angle2;

		//SetCollider(field, CenterRight, LeftBottom, 2);
		//SetCollider(field, Right, RightBottom, 8);

		//1番と7番を入れ替える
		transform1 = field[CenterRight][RightBottom].surfacePartsModelTrans;
		transform2 = field[Right][LeftBottom].surfacePartsModelTrans;

		angle1 = field[CenterRight][RightBottom].angle_;
		angle2 = field[Right][LeftBottom].angle_;

		element = std::move(field[CenterRight][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[CenterRight][RightBottom] = std::move(field[Right][LeftBottom]);
		field[CenterRight][RightBottom].surfacePartsModelTrans = transform1;
		field[CenterRight][RightBottom].angle_ = angle1;

		field[Right][LeftBottom] = std::move(element);
		field[Right][LeftBottom].surfacePartsModelTrans = transform2;
		field[Right][LeftBottom].angle_ = angle2;

		//SetCollider(field, CenterRight, RightBottom, 2);
		//SetCollider(field, Right, LeftBottom, 8);

		break;
#pragma endregion

#pragma region 真ん中右と下
	case CenterRightToBottom:

		//4番と6番を入れ替える
		transform1 = field[CenterRight][LeftTop].surfacePartsModelTrans;
		transform2 = field[Bottom][RightBottom].surfacePartsModelTrans;

		angle1 = field[CenterRight][LeftTop].angle_;
		angle2 = field[Bottom][RightBottom].angle_;

		element = std::move(field[CenterRight][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Bottom][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[CenterRight][LeftTop] = std::move(field[Bottom][RightBottom]);
		field[CenterRight][LeftTop].surfacePartsModelTrans = transform1;
		field[CenterRight][LeftTop].angle_ = angle1;

		field[Bottom][RightBottom] = std::move(element);
		field[Bottom][RightBottom].surfacePartsModelTrans = transform2;
		field[Bottom][RightBottom].angle_ = angle2;

		//SetCollider(field, CenterRight, LeftTop, 4);
		//SetCollider(field, Bottom, RightBottom, 6);

		//3番と5番を入れ替える
		transform1 = field[CenterRight][RightTop].surfacePartsModelTrans;
		transform2 = field[Bottom][RightTop].surfacePartsModelTrans;

		angle1 = field[CenterRight][RightTop].angle_;
		angle2 = field[Bottom][RightTop].angle_;

		element = std::move(field[CenterRight][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[CenterRight][RightTop] = std::move(field[Bottom][RightTop]);
		field[CenterRight][RightTop].surfacePartsModelTrans = transform1;
		field[CenterRight][RightTop].angle_ = angle1;

		field[Bottom][RightTop] = std::move(element);
		field[Bottom][RightTop].surfacePartsModelTrans = transform2;
		field[Bottom][RightTop].angle_ = angle2;

		//SetCollider(field, CenterRight, RightTop, 3);
		//SetCollider(field, Bottom, RightTop, 5);

		//2番と8番を入れ替える
		transform1 = field[CenterRight][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Bottom][LeftBottom].surfacePartsModelTrans;

		angle1 = field[CenterRight][LeftBottom].angle_;
		angle2 = field[Bottom][LeftBottom].angle_;

		element = std::move(field[CenterRight][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[CenterRight][LeftBottom] = std::move(field[Bottom][LeftBottom]);
		field[CenterRight][LeftBottom].surfacePartsModelTrans = transform1;
		field[CenterRight][LeftBottom].angle_ = angle1;

		field[Bottom][LeftBottom] = std::move(element);
		field[Bottom][LeftBottom].surfacePartsModelTrans = transform2;
		field[Bottom][LeftBottom].angle_ = angle2;

		//SetCollider(field, CenterRight, LeftBottom, 2);
		//SetCollider(field, Bottom, LeftBottom, 8);

		//1番と7番を入れ替える
		transform1 = field[CenterRight][RightBottom].surfacePartsModelTrans;
		transform2 = field[Bottom][LeftTop].surfacePartsModelTrans;

		angle1 = field[CenterRight][RightBottom].angle_;
		angle2 = field[Bottom][LeftTop].angle_;

		element = std::move(field[CenterRight][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[CenterRight][RightBottom] = std::move(field[Bottom][LeftTop]);
		field[CenterRight][RightBottom].surfacePartsModelTrans = transform1;
		field[CenterRight][RightBottom].angle_ = angle1;

		field[Bottom][LeftTop] = std::move(element);
		field[Bottom][LeftTop].surfacePartsModelTrans = transform2;
		field[Bottom][LeftTop].angle_ = angle2;

		//SetCollider(field, CenterRight, RightBottom, 1);
		//SetCollider(field, Bottom, LeftTop, 7);

		break;
#pragma endregion

	default:
		break;
	}
}

void SurfaceFoldCenterRight2::EndCenterRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	field[CenterRight][LeftTop].isDraw = true;
	field[CenterRight][RightTop].isDraw = true;
	field[CenterRight][LeftBottom].isDraw = true;
	field[CenterRight][RightBottom].isDraw = true;

	switch (fieldIndex)
	{

	case CenterRightToTop:

		field[Top][LeftTop].isDraw = true;
		field[Top][RightTop].isDraw = true;
		field[Top][LeftBottom].isDraw = true;
		field[Top][RightBottom].isDraw = true;

		break;

	case CenterRightToCenterLeft:

		field[CenterLeft][LeftTop].isDraw = true;
		field[CenterLeft][RightTop].isDraw = true;
		field[CenterLeft][LeftBottom].isDraw = true;
		field[CenterLeft][RightBottom].isDraw = true;

		break;

	case CenterRightToRight:

		field[Right][LeftTop].isDraw = true;
		field[Right][RightTop].isDraw = true;
		field[Right][LeftBottom].isDraw = true;
		field[Right][RightBottom].isDraw = true;

		break;

	case CenterRightToBottom:

		field[Bottom][LeftTop].isDraw = true;
		field[Bottom][RightTop].isDraw = true;
		field[Bottom][LeftBottom].isDraw = true;
		field[Bottom][RightBottom].isDraw = true;

		break;

	default:
		break;
	}
}


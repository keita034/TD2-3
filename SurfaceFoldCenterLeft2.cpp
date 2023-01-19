#include "SurfaceFoldCenterLeft2.h"

void SurfaceFoldCenterLeft2::StartCenterLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, fbxModel* surfaceFoldFbxmodel_)
{
	field[CenterLeft][LeftTop].isDraw = false;
	field[CenterLeft][RightTop].isDraw = false;
	field[CenterLeft][LeftBottom].isDraw = false;
	field[CenterLeft][RightBottom].isDraw = false;

	switch (fieldIndex)
	{
#pragma region 真ん中左と上

	case CenterLeftToTop:

		fieldPlaneTrans_.rotation = { -90.0f * AliceMathF::Deg2Rad,-90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[CenterLeft][RightBottom].textureData);

		//上のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.004", (field[CenterLeft][LeftTop].angle_ + 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.003", (field[CenterLeft][RightTop].angle_ + 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", (field[CenterLeft][LeftBottom].angle_ + 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", (field[CenterLeft][RightBottom].angle_ + 180.0f) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[Top][RightBottom].textureData);

		//下のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.008", (field[Top][LeftTop].angle_ - 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", (field[Top][RightTop].angle_ - 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.006", (field[Top][LeftBottom].angle_ - 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.005", (field[Top][RightBottom].angle_ - 180.0f) * AliceMathF::Deg2Rad);

		field[Top][LeftTop].isDraw = false;
		field[Top][RightTop].isDraw = false;
		field[Top][LeftBottom].isDraw = false;
		field[Top][RightBottom].isDraw = false;

		break;
#pragma endregion

#pragma region 真ん中左と左
	case CenterLeftToLeft:

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[CenterLeft][RightBottom].textureData);

		////上のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.003", (field[CenterLeft][LeftTop].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", (field[CenterLeft][RightTop].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", (field[CenterLeft][LeftBottom].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", (field[CenterLeft][RightBottom].angle_ - 90.0f) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[Left][RightBottom].textureData);

		//下のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.008", (180.0f - field[Left][LeftTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", (180.0f - field[Left][RightTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.006", (180.0f - field[Left][LeftBottom].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.005", (180.0f - field[Left][RightBottom].angle_) * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 0.0f,-90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[Left][LeftTop].isDraw = false;
		field[Left][RightTop].isDraw = false;
		field[Left][LeftBottom].isDraw = false;
		field[Left][RightBottom].isDraw = false;

		break;
#pragma endregion

#pragma region 真ん中左と真ん中右

	case CenterLeftToCenterRight:

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[CenterLeft][RightBottom].textureData);

		////上のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.002", (field[CenterLeft][LeftTop].angle_ + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", (field[CenterLeft][RightTop].angle_ + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", (field[CenterLeft][LeftBottom].angle_ + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.003", (field[CenterLeft][RightBottom].angle_ + 90.0f) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[CenterRight][RightBottom].textureData);

		//下のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.006", (90.0f + field[CenterRight][LeftTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.008", (90.0f + field[CenterRight][RightTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.005", (90.0f + field[CenterRight][LeftBottom].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", (90.0f + field[CenterRight][RightBottom].angle_) * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 180.0f * AliceMathF::Deg2Rad,-90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[CenterRight][LeftTop].isDraw = false;
		field[CenterRight][RightTop].isDraw = false;
		field[CenterRight][LeftBottom].isDraw = false;
		field[CenterRight][RightBottom].isDraw = false;

		break;
#pragma endregion

#pragma region 真ん中左と下
	case CenterLeftToBottom:

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[CenterLeft][RightBottom].textureData);

		surfaceFoldFbxmodel_->rotationUV("Material.001", (180.0f - field[CenterLeft][LeftTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", (180.0f - field[CenterLeft][RightTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.003", (180.0f - field[CenterLeft][LeftBottom].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", (180.0f - field[CenterLeft][RightBottom].angle_) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[Bottom][RightBottom].textureData);

		//下のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.008", (field[Bottom][LeftTop].angle_ * -1.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", (field[Bottom][RightTop].angle_ * -1.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.006", (field[Bottom][LeftBottom].angle_ * -1.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.005", (field[Bottom][RightBottom].angle_ * -1.0f) * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 90.0f * AliceMathF::Deg2Rad,-90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

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

void SurfaceFoldCenterLeft2::ShrinkAnimeCenterLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, float scale)
{
	field[CenterLeft][LeftTop].surfacePartsModelTrans.scale.y = scale;
	field[CenterLeft][RightTop].surfacePartsModelTrans.scale.y = scale;
	field[CenterLeft][LeftBottom].surfacePartsModelTrans.scale.y = scale;
	field[CenterLeft][RightBottom].surfacePartsModelTrans.scale.y = scale;

	switch (fieldIndex)
	{
	case CenterLeftToTop:

		field[Top][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[Top][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[Top][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[Top][RightBottom].surfacePartsModelTrans.scale.y = scale;

		break;

	case CenterLeftToLeft:

		field[Left][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[Left][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[Left][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[Left][RightBottom].surfacePartsModelTrans.scale.y = scale;

		break;

	case CenterLeftToCenterRight:

		field[CenterRight][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[CenterRight][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[CenterRight][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[CenterRight][RightBottom].surfacePartsModelTrans.scale.y = scale;

		break;

	case CenterLeftToBottom:

		field[Bottom][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[Bottom][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[Bottom][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[Bottom][RightBottom].surfacePartsModelTrans.scale.y = scale;

		break;

	default:
		break;
	}
}

void SurfaceFoldCenterLeft2::ReplaceCenterLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, fbxModel* surfaceFoldFbxmodel_)
{
	FieldElement element;
	Transform transform1;
	Transform transform2;
	float angle1 = 0.0f;
	float angle2 = 0.0f;

	switch (fieldIndex)
	{

#pragma region 真ん中左と上

	case CenterLeftToTop:

		//4番と6番を入れ替える
		transform1 = field[CenterLeft][LeftTop].surfacePartsModelTrans;
		transform2 = field[Top][LeftBottom].surfacePartsModelTrans;

		angle1 = field[CenterLeft][LeftTop].angle_;
		angle2 = field[Top][LeftBottom].angle_;

		element = std::move(field[CenterLeft][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[CenterLeft][LeftTop] = std::move(field[Top][LeftBottom]);
		field[CenterLeft][LeftTop].surfacePartsModelTrans = transform1;
		field[CenterLeft][LeftTop].angle_ = angle1;

		field[Top][LeftBottom] = std::move(element);
		field[Top][LeftBottom].surfacePartsModelTrans = transform2;
		field[Top][LeftBottom].angle_ = angle2;

		//3番と5番を入れ替える
		transform1 = field[CenterLeft][RightTop].surfacePartsModelTrans;
		transform2 = field[Top][RightBottom].surfacePartsModelTrans;

		angle1 = field[CenterLeft][RightTop].angle_;
		angle2 = field[Top][RightBottom].angle_;

		element = std::move(field[CenterLeft][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Top][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[CenterLeft][RightTop] = std::move(field[Top][RightBottom]);
		field[CenterLeft][RightTop].surfacePartsModelTrans = transform1;
		field[CenterLeft][RightTop].angle_ = angle1;

		field[Top][RightBottom] = std::move(element);
		field[Top][RightBottom].surfacePartsModelTrans = transform2;
		field[Top][RightBottom].angle_ = angle2;

		//2番と8番を入れ替える
		transform1 = field[CenterLeft][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Top][LeftTop].surfacePartsModelTrans;

		angle1 = field[CenterLeft][LeftBottom].angle_;
		angle2 = field[Top][LeftTop].angle_;

		element = std::move(field[CenterLeft][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[CenterLeft][LeftBottom] = std::move(field[Top][LeftTop]);
		field[CenterLeft][LeftBottom].surfacePartsModelTrans = transform1;
		field[CenterLeft][LeftBottom].angle_ = angle1;

		field[Top][LeftTop] = std::move(element);
		field[Top][LeftTop].surfacePartsModelTrans = transform2;
		field[Top][LeftTop].angle_ = angle2;

		//1番と7番を入れ替える
		transform1 = field[CenterLeft][RightBottom].surfacePartsModelTrans;
		transform2 = field[Top][RightTop].surfacePartsModelTrans;
		element = std::move(field[CenterLeft][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[CenterLeft][RightBottom] = std::move(field[Top][RightTop]);
		field[CenterLeft][RightBottom].surfacePartsModelTrans = transform1;
		field[CenterLeft][RightBottom].angle_ = angle1;

		field[Top][RightTop] = std::move(element);
		field[Top][RightTop].surfacePartsModelTrans = transform2;
		field[Top][RightTop].angle_ = angle2;

		break;
#pragma endregion

#pragma region 真ん中左と左

	case CenterLeftToLeft:

		//3番と5番を入れ替える
		transform1 = field[CenterLeft][LeftTop].surfacePartsModelTrans;
		transform2 = field[Left][RightTop].surfacePartsModelTrans;

		angle1 = field[CenterLeft][LeftTop].angle_;
		angle2 = field[Left][RightTop].angle_;

		element = std::move(field[CenterLeft][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[CenterLeft][LeftTop] = std::move(field[Left][RightTop]);
		field[CenterLeft][LeftTop].surfacePartsModelTrans = transform1;
		field[CenterLeft][LeftTop].angle_ = angle1;

		field[Left][RightTop] = std::move(element);
		field[Left][RightTop].surfacePartsModelTrans = transform2;
		field[Left][RightTop].angle_ = angle2;

		//1番と7番を入れ替える
		transform1 = field[CenterLeft][RightTop].surfacePartsModelTrans;
		transform2 = field[Left][LeftTop].surfacePartsModelTrans;

		angle1 = field[CenterLeft][RightTop].angle_;
		angle2 = field[Left][LeftTop].angle_;

		element = std::move(field[CenterLeft][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[CenterLeft][RightTop] = std::move(field[Left][LeftTop]);
		field[CenterLeft][RightTop].surfacePartsModelTrans = transform1;
		field[CenterLeft][RightTop].angle_ = angle1;

		field[Left][LeftTop] = std::move(element);
		field[Left][LeftTop].surfacePartsModelTrans = transform2;
		field[Left][LeftTop].angle_ = angle2;

		//4番と6番を入れ替える
		transform1 = field[CenterLeft][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Left][RightBottom].surfacePartsModelTrans;

		angle1 = field[CenterLeft][LeftBottom].angle_;
		angle2 = field[Left][RightBottom].angle_;

		element = std::move(field[CenterLeft][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Left][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[CenterLeft][LeftBottom] = std::move(field[Left][RightBottom]);
		field[CenterLeft][LeftBottom].surfacePartsModelTrans = transform1;
		field[CenterLeft][LeftBottom].angle_ = angle1;

		field[Left][RightBottom] = std::move(element);
		field[Left][RightBottom].surfacePartsModelTrans = transform2;
		field[Left][RightBottom].angle_ = angle2;

		//2番と8番を入れ替える
		transform1 = field[CenterLeft][RightBottom].surfacePartsModelTrans;
		transform2 = field[Left][LeftBottom].surfacePartsModelTrans;

		angle1 = field[CenterLeft][RightBottom].angle_;
		angle2 = field[Left][LeftBottom].angle_;

		element = std::move(field[CenterLeft][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[CenterLeft][RightBottom] = std::move(field[Left][LeftBottom]);
		field[CenterLeft][RightBottom].surfacePartsModelTrans = transform1;
		field[CenterLeft][RightBottom].angle_ = angle1;

		field[Left][LeftBottom] = std::move(element);
		field[Left][LeftBottom].surfacePartsModelTrans = transform2;
		field[Left][LeftBottom].angle_ = angle2;

		break;
#pragma endregion

#pragma region 真ん中左と真ん中右

	case CenterLeftToCenterRight:
		//3番と5番を入れ替える
		transform1 = field[CenterLeft][LeftTop].surfacePartsModelTrans;
		transform2 = field[CenterRight][RightTop].surfacePartsModelTrans;

		angle1 = field[CenterLeft][LeftTop].angle_;
		angle2 = field[CenterRight][RightTop].angle_;

		element = std::move(field[CenterLeft][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[CenterLeft][LeftTop] = std::move(field[CenterRight][RightTop]);
		field[CenterLeft][LeftTop].surfacePartsModelTrans = transform1;
		field[CenterLeft][LeftTop].angle_ = angle1;

		field[CenterRight][RightTop] = std::move(element);
		field[CenterRight][RightTop].surfacePartsModelTrans = transform2;
		field[CenterRight][RightTop].angle_ = angle2;

		//1番と7番を入れ替える
		transform1 = field[CenterLeft][RightTop].surfacePartsModelTrans;
		transform2 = field[CenterRight][LeftTop].surfacePartsModelTrans;

		angle1 = field[CenterLeft][RightTop].angle_;
		angle2 = field[CenterRight][LeftTop].angle_;

		element = std::move(field[CenterLeft][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[CenterLeft][RightTop] = std::move(field[CenterRight][LeftTop]);
		field[CenterLeft][RightTop].surfacePartsModelTrans = transform1;
		field[CenterLeft][RightTop].angle_ = angle1;

		field[CenterRight][LeftTop] = std::move(element);
		field[CenterRight][LeftTop].surfacePartsModelTrans = transform2;
		field[CenterRight][LeftTop].angle_ = angle2;

		//4番と6番を入れ替える
		transform1 = field[CenterLeft][LeftBottom].surfacePartsModelTrans;
		transform2 = field[CenterRight][RightBottom].surfacePartsModelTrans;

		angle1 = field[CenterLeft][LeftBottom].angle_;
		angle2 = field[CenterRight][RightBottom].angle_;

		element = std::move(field[CenterLeft][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[CenterRight][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[CenterLeft][LeftBottom] = std::move(field[CenterRight][RightBottom]);
		field[CenterLeft][LeftBottom].surfacePartsModelTrans = transform1;
		field[CenterLeft][LeftBottom].angle_ = angle1;

		field[CenterRight][RightBottom] = std::move(element);
		field[CenterRight][RightBottom].surfacePartsModelTrans = transform2;
		field[CenterRight][RightBottom].angle_ = angle2;

		//2番と8番を入れ替える
		transform1 = field[CenterLeft][RightBottom].surfacePartsModelTrans;
		transform2 = field[CenterRight][LeftBottom].surfacePartsModelTrans;

		angle1 = field[CenterLeft][RightBottom].angle_;
		angle2 = field[CenterRight][LeftBottom].angle_;

		element = std::move(field[CenterLeft][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[CenterLeft][RightBottom] = std::move(field[CenterRight][LeftBottom]);
		field[CenterLeft][RightBottom].surfacePartsModelTrans = transform1;
		field[CenterLeft][RightBottom].angle_ = angle1;

		field[CenterRight][LeftBottom] = std::move(element);
		field[CenterRight][LeftBottom].surfacePartsModelTrans = transform2;
		field[CenterRight][LeftBottom].angle_ = angle2;

		break;
#pragma endregion

#pragma region 真ん中左と下
	case CenterLeftToBottom:

		//3番と5番を入れ替える
		transform1 = field[CenterLeft][LeftTop].surfacePartsModelTrans;
		transform2 = field[Bottom][RightTop].surfacePartsModelTrans;

		angle1 = field[CenterLeft][LeftTop].angle_;
		angle2 = field[Bottom][RightTop].angle_;

		element = std::move(field[CenterLeft][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[CenterLeft][LeftTop] = std::move(field[Bottom][RightTop]);
		field[CenterLeft][LeftTop].surfacePartsModelTrans = transform1;
		field[CenterLeft][LeftTop].angle_ = angle1;

		field[Bottom][RightTop] = std::move(element);
		field[Bottom][RightTop].surfacePartsModelTrans = transform2;
		field[Bottom][RightTop].angle_ = angle2;

		//1番と7番を入れ替える
		transform1 = field[CenterLeft][RightTop].surfacePartsModelTrans;
		transform2 = field[Bottom][LeftTop].surfacePartsModelTrans;

		angle1 = field[CenterLeft][RightTop].angle_;
		angle2 = field[Bottom][LeftTop].angle_;

		element = std::move(field[CenterLeft][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[CenterLeft][RightTop] = std::move(field[Bottom][LeftTop]);
		field[CenterLeft][RightTop].surfacePartsModelTrans = transform1;
		field[CenterLeft][RightTop].angle_ = angle1;

		field[Bottom][LeftTop] = std::move(element);
		field[Bottom][LeftTop].surfacePartsModelTrans = transform2;
		field[Bottom][LeftTop].angle_ = angle2;

		//4番と6番を入れ替える
		transform1 = field[CenterLeft][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Bottom][RightBottom].surfacePartsModelTrans;

		angle1 = field[CenterLeft][LeftBottom].angle_;
		angle2 = field[Bottom][RightBottom].angle_;

		element = std::move(field[CenterLeft][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Bottom][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[CenterLeft][LeftBottom] = std::move(field[Bottom][RightBottom]);
		field[CenterLeft][LeftBottom].surfacePartsModelTrans = transform1;
		field[CenterLeft][LeftBottom].angle_ = angle1;

		field[Bottom][RightBottom] = std::move(element);
		field[Bottom][RightBottom].surfacePartsModelTrans = transform2;
		field[Bottom][RightBottom].angle_ = angle2;

		//2番と8番を入れ替える
		transform1 = field[CenterLeft][RightBottom].surfacePartsModelTrans;
		transform2 = field[Bottom][LeftBottom].surfacePartsModelTrans;

		angle1 = field[CenterLeft][RightBottom].angle_;
		angle2 = field[Bottom][LeftBottom].angle_;

		element = std::move(field[CenterLeft][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[CenterLeft][RightBottom] = std::move(field[Bottom][LeftBottom]);
		field[CenterLeft][RightBottom].surfacePartsModelTrans = transform1;
		field[CenterLeft][RightBottom].angle_ = angle1;

		field[Bottom][LeftBottom] = std::move(element);
		field[Bottom][LeftBottom].surfacePartsModelTrans = transform2;
		field[Bottom][LeftBottom].angle_ = angle2;

		break;
#pragma endregion

	default:
		break;
	}
}

void SurfaceFoldCenterLeft2::EndCenterLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	field[CenterLeft][LeftTop].isDraw = true;
	field[CenterLeft][RightTop].isDraw = true;
	field[CenterLeft][LeftBottom].isDraw = true;
	field[CenterLeft][RightBottom].isDraw = true;

	switch (fieldIndex)
	{
	case CenterLeftToTop:

		field[Top][LeftTop].isDraw = true;
		field[Top][RightTop].isDraw = true;
		field[Top][LeftBottom].isDraw = true;
		field[Top][RightBottom].isDraw = true;

		break;

	case CenterLeftToLeft:

		field[Left][LeftTop].isDraw = true;
		field[Left][RightTop].isDraw = true;
		field[Left][LeftBottom].isDraw = true;
		field[Left][RightBottom].isDraw = true;

		break;

	case CenterLeftToCenterRight:

		field[CenterRight][LeftTop].isDraw = true;
		field[CenterRight][RightTop].isDraw = true;
		field[CenterRight][LeftBottom].isDraw = true;
		field[CenterRight][RightBottom].isDraw = true;

		break;

	case CenterLeftToBottom:

		field[Bottom][LeftTop].isDraw = true;
		field[Bottom][RightTop].isDraw = true;
		field[Bottom][LeftBottom].isDraw = true;
		field[Bottom][RightBottom].isDraw = true;

		break;

	default:
		break;
	}
}

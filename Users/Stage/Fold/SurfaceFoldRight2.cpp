#include "SurfaceFoldRight2.h"

void SurfaceFoldRight2::StartRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, AliceModel* surfaceFoldFbxmodel_)
{
	field[Right][LeftTop].isDraw = false;
	field[Right][RightTop].isDraw = false;
	field[Right][LeftBottom].isDraw = false;
	field[Right][RightBottom].isDraw = false;

	switch (fieldIndex)
	{

#pragma region 右と上
	case RightToTop:

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Right][RightBottom].textureData);

		//上のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.002", (field[Right][LeftTop].angle_ + 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", (field[Right][RightTop].angle_ + 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", (field[Right][LeftBottom].angle_ + 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.003", (field[Right][RightBottom].angle_ + 180.0f) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[Top][RightBottom].textureData);

		surfaceFoldFbxmodel_->rotationUV("Material.005", (field[Top][LeftTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.006", (field[Top][RightTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", (field[Top][LeftBottom].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.008", (field[Top][RightBottom].angle_) * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { -90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[Top][LeftTop].isDraw = false;
		field[Top][RightTop].isDraw = false;
		field[Top][LeftBottom].isDraw = false;
		field[Top][RightBottom].isDraw = false;

		break;
#pragma endregion

#pragma region 右と下
	case RightToLeft:

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Right][RightBottom].textureData);

		//上のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.002", (field[Right][LeftTop].angle_ + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", (field[Right][RightTop].angle_ + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", (field[Right][LeftBottom].angle_ + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.003", (field[Right][RightBottom].angle_ + 90.0f) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[Left][RightBottom].textureData);

		//下のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.006", (field[Left][LeftTop].angle_ * -1.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.008", (field[Left][RightTop].angle_ * -1.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.005", (field[Left][LeftBottom].angle_ * -1.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", (field[Left][RightBottom].angle_ * -1.0f) * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 180.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[Left][LeftTop].isDraw = false;
		field[Left][RightTop].isDraw = false;
		field[Left][LeftBottom].isDraw = false;
		field[Left][RightBottom].isDraw = false;

		break;
#pragma endregion

#pragma region 右と真ん中右
	case RightToCenterRight:

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Right][RightBottom].textureData);

		//上のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.003", (field[Right][LeftTop].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", (field[Right][RightTop].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", (field[Right][LeftBottom].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", (field[Right][RightBottom].angle_ - 90.0f) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[CenterRight][RightBottom].textureData);

		//下のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.007", (field[CenterRight][LeftTop].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.005", (field[CenterRight][RightTop].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.008", (field[CenterRight][LeftBottom].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.006", (field[CenterRight][RightBottom].angle_ - 90.0f) * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 0.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[CenterRight][LeftTop].isDraw = false;
		field[CenterRight][RightTop].isDraw = false;
		field[CenterRight][LeftBottom].isDraw = false;
		field[CenterRight][RightBottom].isDraw = false;

		break;
#pragma endregion

#pragma region 右と下

	case RightToBottom:

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Right][RightBottom].textureData);

		surfaceFoldFbxmodel_->rotationUV("Material.001", (field[Right][LeftTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", (field[Right][RightTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.003", (field[Right][LeftBottom].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", (field[Right][RightBottom].angle_) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[Bottom][RightBottom].textureData);

		surfaceFoldFbxmodel_->rotationUV("Material.005", ((field[Bottom][LeftTop].angle_ * -1.0f) - 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.006", ((field[Bottom][RightTop].angle_ * -1.0f) - 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", ((field[Bottom][LeftBottom].angle_ * -1.0f) - 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.008", ((field[Bottom][RightBottom].angle_ * -1.0f) - 180.0f) * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

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

void SurfaceFoldRight2::ShrinkAnimeRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, float scale)
{
	field[Right][LeftTop].surfacePartsModelTrans.scale.y = scale;
	field[Right][RightTop].surfacePartsModelTrans.scale.y = scale;
	field[Right][LeftBottom].surfacePartsModelTrans.scale.y = scale;
	field[Right][RightBottom].surfacePartsModelTrans.scale.y = scale;

	switch (fieldIndex)
	{
	case RightToTop:

		field[Top][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[Top][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[Top][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[Top][RightBottom].surfacePartsModelTrans.scale.y = scale;

		break;

	case RightToLeft:

		field[Left][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[Left][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[Left][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[Left][RightBottom].surfacePartsModelTrans.scale.y = scale;

		break;

	case RightToCenterRight:

		field[CenterRight][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[CenterRight][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[CenterRight][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[CenterRight][RightBottom].surfacePartsModelTrans.scale.y = scale;

		break;

	case RightToBottom:

		field[Bottom][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[Bottom][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[Bottom][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[Bottom][RightBottom].surfacePartsModelTrans.scale.y = scale;

		break;

	default:
		break;
	}
}

void SurfaceFoldRight2::ReplaceRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, AliceModel* surfaceFoldFbxmodel_)
{
	FieldElement element;
	Transform transform1;
	Transform transform2;
	float angle1 = 0.0f;
	float angle2 = 0.0f;

	switch (fieldIndex)
	{
#pragma region 右と上
	case RightToTop:

		//4番と6番を入れ替える
		transform1 = field[Right][LeftTop].surfacePartsModelTrans;
		transform2 = field[Top][RightTop].surfacePartsModelTrans;

		angle1 = field[Right][LeftTop].angle_;
		angle2 = field[Top][RightTop].angle_;

		element = std::move(field[Right][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[Right][LeftTop] = std::move(field[Top][RightTop]);
		field[Right][LeftTop].surfacePartsModelTrans = transform1;
		field[Right][LeftTop].angle_ = angle1;

		field[Top][RightTop] = std::move(element);
		field[Top][RightTop].surfacePartsModelTrans = transform2;
		field[Top][RightTop].angle_ = angle2;

		//3番と5番を入れ替える
		transform1 = field[Right][RightTop].surfacePartsModelTrans;
		transform2 = field[Top][LeftTop].surfacePartsModelTrans;

		angle1 = field[Right][RightTop].angle_;
		angle2 = field[Top][LeftTop].angle_;

		element = std::move(field[Right][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[Right][RightTop] = std::move(field[Top][LeftTop]);
		field[Right][RightTop].surfacePartsModelTrans = transform1;
		field[Right][RightTop].angle_ = angle1;

		field[Top][LeftTop] = std::move(element);
		field[Top][LeftTop].surfacePartsModelTrans = transform2;
		field[Top][LeftTop].angle_ = angle2;

		//2番と8番を入れ替える
		transform1 = field[Right][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Top][RightBottom].surfacePartsModelTrans;

		angle1 = field[Right][LeftBottom].angle_;
		angle2 = field[Top][RightBottom].angle_;

		element = std::move(field[Right][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Top][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[Right][LeftBottom] = std::move(field[Top][RightBottom]);
		field[Right][LeftBottom].surfacePartsModelTrans = transform1;
		field[Right][LeftBottom].angle_ = angle1;

		field[Top][RightBottom] = std::move(element);
		field[Top][RightBottom].surfacePartsModelTrans = transform2;
		field[Top][RightBottom].angle_ = angle2;

		//1番と7番を入れ替える
		transform1 = field[Right][RightBottom].surfacePartsModelTrans;
		transform2 = field[Top][LeftBottom].surfacePartsModelTrans;

		angle1 = field[Right][RightBottom].angle_;
		angle2 = field[Top][LeftBottom].angle_;

		element = std::move(field[Right][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[Right][RightBottom] = std::move(field[Top][LeftBottom]);
		field[Right][RightBottom].surfacePartsModelTrans = transform1;
		field[Right][RightBottom].angle_ = angle1;

		field[Top][LeftBottom] = std::move(element);
		field[Top][LeftBottom].surfacePartsModelTrans = transform2;
		field[Top][LeftBottom].angle_ = angle2;

		break;
#pragma endregion

#pragma region 右と下
	case RightToLeft:

		//4番と6番を入れ替える
		transform1 = field[Right][LeftTop].surfacePartsModelTrans;
		transform2 = field[Left][RightTop].surfacePartsModelTrans;

		angle1 = field[Right][LeftTop].angle_;
		angle2 = field[Left][RightTop].angle_;

		element = std::move(field[Right][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[Right][LeftTop] = std::move(field[Left][RightTop]);
		field[Right][LeftTop].surfacePartsModelTrans = transform1;
		field[Right][LeftTop].angle_ = angle1;

		field[Left][RightTop] = std::move(element);
		field[Left][RightTop].surfacePartsModelTrans = transform2;
		field[Left][RightTop].angle_ = angle2;

		//3番と5番を入れ替える
		transform1 = field[Right][RightTop].surfacePartsModelTrans;
		transform2 = field[Left][LeftTop].surfacePartsModelTrans;

		angle1 = field[Right][RightTop].angle_;
		angle2 = field[Left][LeftTop].angle_;

		element = std::move(field[Right][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[Right][RightTop] = std::move(field[Left][LeftTop]);
		field[Right][RightTop].surfacePartsModelTrans = transform1;
		field[Right][RightTop].angle_ = angle1;

		field[Left][LeftTop] = std::move(element);
		field[Left][LeftTop].surfacePartsModelTrans = transform2;
		field[Left][LeftTop].angle_ = angle2;

		//2番と8番を入れ替える
		transform1 = field[Right][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Left][RightBottom].surfacePartsModelTrans;

		angle1 = field[Right][LeftBottom].angle_;
		angle2 = field[Left][RightBottom].angle_;

		element = std::move(field[Right][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Left][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[Right][LeftBottom] = std::move(field[Left][RightBottom]);
		field[Right][LeftBottom].surfacePartsModelTrans = transform1;
		field[Right][LeftBottom].angle_ = angle1;

		field[Left][RightBottom] = std::move(element);
		field[Left][RightBottom].surfacePartsModelTrans = transform2;
		field[Left][RightBottom].angle_ = angle2;

		//1番と7番を入れ替える
		transform1 = field[Right][RightBottom].surfacePartsModelTrans;
		transform2 = field[Left][LeftBottom].surfacePartsModelTrans;

		angle1 = field[Right][RightBottom].angle_;
		angle2 = field[Left][LeftBottom].angle_;

		element = std::move(field[Right][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[Right][RightBottom] = std::move(field[Left][LeftBottom]);
		field[Right][RightBottom].surfacePartsModelTrans = transform1;
		field[Right][RightBottom].angle_ = angle1;

		field[Left][LeftBottom] = std::move(element);
		field[Left][LeftBottom].surfacePartsModelTrans = transform2;
		field[Left][LeftBottom].angle_ = angle2;

		break;
#pragma endregion

#pragma region 右と真ん中右
	case RightToCenterRight:

		//4番と6番を入れ替える
		transform1 = field[Right][LeftTop].surfacePartsModelTrans;
		transform2 = field[CenterRight][RightTop].surfacePartsModelTrans;

		angle1 = field[Right][LeftTop].angle_;
		angle2 = field[CenterRight][RightTop].angle_;

		element = std::move(field[Right][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[Right][LeftTop] = std::move(field[CenterRight][RightTop]);
		field[Right][LeftTop].surfacePartsModelTrans = transform1;
		field[Right][LeftTop].angle_ = angle1;

		field[CenterRight][RightTop] = std::move(element);
		field[CenterRight][RightTop].surfacePartsModelTrans = transform2;
		field[CenterRight][RightTop].angle_ = angle2;

		//3番と5番を入れ替える
		transform1 = field[Right][RightTop].surfacePartsModelTrans;
		transform2 = field[CenterRight][LeftTop].surfacePartsModelTrans;

		angle1 = field[Right][RightTop].angle_;
		angle2 = field[CenterRight][LeftTop].angle_;

		element = std::move(field[Right][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[Right][RightTop] = std::move(field[CenterRight][LeftTop]);
		field[Right][RightTop].surfacePartsModelTrans = transform1;
		field[Right][RightTop].angle_ = angle1;

		field[CenterRight][LeftTop] = std::move(element);
		field[CenterRight][LeftTop].surfacePartsModelTrans = transform2;
		field[CenterRight][LeftTop].angle_ = angle2;

		//2番と8番を入れ替える
		transform1 = field[Right][LeftBottom].surfacePartsModelTrans;
		transform2 = field[CenterRight][RightBottom].surfacePartsModelTrans;

		angle1 = field[Right][LeftBottom].angle_;
		angle2 = field[CenterRight][RightBottom].angle_;

		element = std::move(field[Right][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[CenterRight][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[Right][LeftBottom] = std::move(field[CenterRight][RightBottom]);
		field[Right][LeftBottom].surfacePartsModelTrans = transform1;
		field[Right][LeftBottom].angle_ = angle1;

		field[CenterRight][RightBottom] = std::move(element);
		field[CenterRight][RightBottom].surfacePartsModelTrans = transform2;
		field[CenterRight][RightBottom].angle_ = angle2;

		//1番と7番を入れ替える
		transform1 = field[Right][RightBottom].surfacePartsModelTrans;
		transform2 = field[CenterRight][LeftBottom].surfacePartsModelTrans;

		angle1 = field[Right][RightBottom].angle_;
		angle2 = field[CenterRight][LeftBottom].angle_;

		element = std::move(field[Right][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[Right][RightBottom] = std::move(field[CenterRight][LeftBottom]);
		field[Right][RightBottom].surfacePartsModelTrans = transform1;
		field[Right][RightBottom].angle_ = angle1;

		field[CenterRight][LeftBottom] = std::move(element);
		field[CenterRight][LeftBottom].surfacePartsModelTrans = transform2;
		field[CenterRight][LeftBottom].angle_ = angle2;

		break;
#pragma endregion

#pragma region 右と下
	case RightToBottom:

		//4番と6番を入れ替える
		transform1 = field[Right][LeftTop].surfacePartsModelTrans;
		transform2 = field[Bottom][LeftBottom].surfacePartsModelTrans;

		angle1 = field[Right][LeftTop].angle_;
		angle2 = field[Bottom][LeftBottom].angle_;

		element = std::move(field[Right][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[Right][LeftTop] = std::move(field[Bottom][LeftBottom]);
		field[Right][LeftTop].surfacePartsModelTrans = transform1;
		field[Right][LeftTop].angle_ = angle1;

		field[Bottom][LeftBottom] = std::move(element);
		field[Bottom][LeftBottom].surfacePartsModelTrans = transform2;
		field[Bottom][LeftBottom].angle_ = angle2;

		//3番と5番を入れ替える
		transform1 = field[Right][RightTop].surfacePartsModelTrans;
		transform2 = field[Bottom][RightBottom].surfacePartsModelTrans;

		angle1 = field[Right][RightTop].angle_;
		angle2 = field[Bottom][RightBottom].angle_;

		element = std::move(field[Right][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Bottom][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[Right][RightTop] = std::move(field[Bottom][RightBottom]);
		field[Right][RightTop].surfacePartsModelTrans = transform1;
		field[Right][RightTop].angle_ = angle1;

		field[Bottom][RightBottom] = std::move(element);
		field[Bottom][RightBottom].surfacePartsModelTrans = transform2;
		field[Bottom][RightBottom].angle_ = angle2;

		//2番と8番を入れ替える
		transform1 = field[Right][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Bottom][LeftTop].surfacePartsModelTrans;

		angle1 = field[Right][LeftBottom].angle_;
		angle2 = field[Bottom][LeftTop].angle_;

		element = std::move(field[Right][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[Right][LeftBottom] = std::move(field[Bottom][LeftTop]);
		field[Right][LeftBottom].surfacePartsModelTrans = transform1;
		field[Right][LeftBottom].angle_ = angle1;

		field[Bottom][LeftTop] = std::move(element);
		field[Bottom][LeftTop].surfacePartsModelTrans = transform2;
		field[Bottom][LeftTop].angle_ = angle2;

		//1番と7番を入れ替える
		transform1 = field[Right][RightBottom].surfacePartsModelTrans;
		transform2 = field[Bottom][RightTop].surfacePartsModelTrans;

		angle1 = field[Right][RightBottom].angle_;
		angle2 = field[Bottom][RightTop].angle_;

		element = std::move(field[Right][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[Right][RightBottom] = std::move(field[Bottom][RightTop]);
		field[Right][RightBottom].surfacePartsModelTrans = transform1;
		field[Right][RightBottom].angle_ = angle1;

		field[Bottom][RightTop] = std::move(element);
		field[Bottom][RightTop].surfacePartsModelTrans = transform2;
		field[Bottom][RightTop].angle_ = angle2;

		break;
#pragma endregion

	default:
		break;
	}
}

void SurfaceFoldRight2::EndRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	field[Right][LeftTop].isDraw = true;
	field[Right][RightTop].isDraw = true;
	field[Right][LeftBottom].isDraw = true;
	field[Right][RightBottom].isDraw = true;

	switch (fieldIndex)
	{
	case RightToTop:

		field[Top][LeftTop].isDraw = true;
		field[Top][RightTop].isDraw = true;
		field[Top][LeftBottom].isDraw = true;
		field[Top][RightBottom].isDraw = true;

		break;

	case RightToLeft:

		field[Left][LeftTop].isDraw = true;
		field[Left][RightTop].isDraw = true;
		field[Left][LeftBottom].isDraw = true;
		field[Left][RightBottom].isDraw = true;

		break;

	case RightToCenterRight:

		field[CenterRight][LeftTop].isDraw = true;
		field[CenterRight][RightTop].isDraw = true;
		field[CenterRight][LeftBottom].isDraw = true;
		field[CenterRight][RightBottom].isDraw = true;

		break;

	case RightToBottom:

		field[Bottom][LeftTop].isDraw = true;
		field[Bottom][RightTop].isDraw = true;
		field[Bottom][LeftBottom].isDraw = true;
		field[Bottom][RightBottom].isDraw = true;

		break;

	default:
		break;
	}
}

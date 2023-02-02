#include "SurfaceFoldLeft2.h"

void SurfaceFoldLeft2::StartLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, fbxModel* surfaceFoldFbxmodel_)
{
	field[Left][LeftTop].isDraw = false;
	field[Left][RightTop].isDraw = false;
	field[Left][LeftBottom].isDraw = false;
	field[Left][RightBottom].isDraw = false;

	switch (fieldIndex)
	{
#pragma region 左と上
	case LeftToTop:

		//回転角
		fieldPlaneTrans_.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Left][RightBottom].textureData);

		//上のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.004", ((field[Left][LeftTop].angle_ * -1.0f) + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.003", ((field[Left][RightTop].angle_ * -1.0f) + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", ((field[Left][LeftBottom].angle_ * -1.0f) + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", ((field[Left][RightBottom].angle_ * -1.0f) + 90.0f) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[Top][RightBottom].textureData);

		//下のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.006", (field[Top][LeftTop].angle_ + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.005", (field[Top][RightTop].angle_ + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.008", (field[Top][LeftBottom].angle_ + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", (field[Top][RightBottom].angle_ + 90.0f) * AliceMathF::Deg2Rad);


		field[Top][LeftTop].isDraw = false;
		field[Top][RightTop].isDraw = false;
		field[Top][LeftBottom].isDraw = false;
		field[Top][RightBottom].isDraw = false;

		break;
#pragma endregion

#pragma region 左と真ん中左

	case LeftToCenterLeft:
		//回転角
		fieldPlaneTrans_.rotation = { 180.0f * AliceMathF::Deg2Rad,0.0f,90.0f * AliceMathF::Deg2Rad };

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Left][RightBottom].textureData);

		//上のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.004", (field[Left][LeftTop].angle_ * -1.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.003", (field[Left][RightTop].angle_ * -1.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", (field[Left][LeftBottom].angle_ * -1.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", (field[Left][RightBottom].angle_ * -1.0f) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[CenterLeft][RightBottom].textureData);

		//下のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.006", (field[CenterLeft][LeftTop].angle_ + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.005", (field[CenterLeft][RightTop].angle_ + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.008", (field[CenterLeft][LeftBottom].angle_ + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", (field[CenterLeft][RightBottom].angle_ + 90.0f) * AliceMathF::Deg2Rad);

		field[CenterLeft][LeftTop].isDraw = false;
		field[CenterLeft][RightTop].isDraw = false;
		field[CenterLeft][LeftBottom].isDraw = false;
		field[CenterLeft][RightBottom].isDraw = false;

		break;
#pragma endregion

#pragma region 左と右
	case LeftToRight:

		//回転角
		fieldPlaneTrans_.rotation = { 0.0f * AliceMathF::Deg2Rad,0.0f,90.0f * AliceMathF::Deg2Rad };

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Left][RightBottom].textureData);

		//上のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.003", ((field[Left][LeftTop].angle_ * -1.0f) - 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", ((field[Left][RightTop].angle_ * -1.0f) - 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", ((field[Left][LeftBottom].angle_ * -1.0f) - 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", ((field[Left][RightBottom].angle_ * -1.0f) - 180.0f) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[Right][RightBottom].textureData);

		//下のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.007", (field[Right][LeftTop].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.005", (field[Right][RightTop].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.008", (field[Right][LeftBottom].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.006", (field[Right][RightBottom].angle_ - 90.0f) * AliceMathF::Deg2Rad);

		field[Right][LeftTop].isDraw = false;
		field[Right][RightTop].isDraw = false;
		field[Right][LeftBottom].isDraw = false;
		field[Right][RightBottom].isDraw = false;

		break;
#pragma endregion

#pragma region 左と下

	case LeftToBottom:

		//回転角
		fieldPlaneTrans_.rotation = { 90.0f * AliceMathF::Deg2Rad,0.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };


		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Left][RightBottom].textureData);

		surfaceFoldFbxmodel_->rotationUV("Material.001", (field[Left][LeftTop].angle_ + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", (field[Left][RightTop].angle_ + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.003", (field[Left][LeftBottom].angle_ + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", (field[Left][RightBottom].angle_ + 90.0f) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[Bottom][RightBottom].textureData);

		//下のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.006", ((field[Bottom][LeftTop].angle_ * -1.0f) + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.005", ((field[Bottom][RightTop].angle_ * -1.0f) + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.008", ((field[Bottom][LeftBottom].angle_ * -1.0f) + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", ((field[Bottom][RightBottom].angle_ * -1.0f) + 90.0f) * AliceMathF::Deg2Rad);

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

void SurfaceFoldLeft2::ShrinkAnimeLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, float scale)
{
	field[Left][LeftTop].surfacePartsModelTrans.scale.y = scale;
	field[Left][RightTop].surfacePartsModelTrans.scale.y = scale;
	field[Left][LeftBottom].surfacePartsModelTrans.scale.y = scale;
	field[Left][RightBottom].surfacePartsModelTrans.scale.y = scale;

	switch (fieldIndex)
	{

	case LeftToTop:

		field[Top][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[Top][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[Top][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[Top][RightBottom].surfacePartsModelTrans.scale.y = scale;
		break;

	case LeftToCenterLeft:

		field[CenterLeft][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[CenterLeft][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[CenterLeft][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[CenterLeft][RightBottom].surfacePartsModelTrans.scale.y = scale;
		break;

	case LeftToRight:

		field[Right][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[Right][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[Right][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[Right][RightBottom].surfacePartsModelTrans.scale.y = scale;
		break;

	case LeftToBottom:

		field[Bottom][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[Bottom][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[Bottom][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[Bottom][RightBottom].surfacePartsModelTrans.scale.y = scale;
		break;

	default:
		break;
	}
}

void SurfaceFoldLeft2::ReplaceLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, fbxModel* surfaceFoldFbxmodel_)
{
	FieldElement element;
	Transform transform1;
	Transform transform2;
	float angle1 = 0.0f;
	float angle2 = 0.0f;

	switch (fieldIndex)
	{
#pragma region 左と上

	case LeftToTop:
		//4番と6番を入れ替える
		transform1 = field[Left][LeftTop].surfacePartsModelTrans;
		transform2 = field[Top][LeftTop].surfacePartsModelTrans;

		angle1 = field[Left][LeftTop].angle_;
		angle2 = field[Top][LeftTop].angle_;

		element = std::move(field[Left][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[Left][LeftTop] = std::move(field[Top][LeftTop]);
		field[Left][LeftTop].surfacePartsModelTrans = transform1;
		field[Left][LeftTop].angle_ = angle1;

		field[Top][LeftTop] = std::move(element);
		field[Top][LeftTop].surfacePartsModelTrans = transform2;
		field[Top][LeftTop].angle_ = angle2;

		//3番と5番を入れ替える
		transform1 = field[Left][RightTop].surfacePartsModelTrans;
		transform2 = field[Top][LeftBottom].surfacePartsModelTrans;

		angle1 = field[Left][RightTop].angle_;
		angle2 = field[Top][LeftBottom].angle_;

		element = std::move(field[Left][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[Left][RightTop] = std::move(field[Top][LeftBottom]);
		field[Left][RightTop].surfacePartsModelTrans = transform1;
		field[Left][RightTop].angle_ = angle1;

		field[Top][LeftBottom] = std::move(element);
		field[Top][LeftBottom].surfacePartsModelTrans = transform2;
		field[Top][LeftBottom].angle_ = angle2;

		//2番と8番を入れ替える
		transform1 = field[Left][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Top][RightTop].surfacePartsModelTrans;

		angle1 = field[Left][LeftBottom].angle_;
		angle2 = field[Top][RightTop].angle_;

		element = std::move(field[Left][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[Left][LeftBottom] = std::move(field[Top][RightTop]);
		field[Left][LeftBottom].surfacePartsModelTrans = transform1;
		field[Left][LeftBottom].angle_ = angle1;

		field[Top][RightTop] = std::move(element);
		field[Top][RightTop].surfacePartsModelTrans = transform2;
		field[Top][RightTop].angle_ = angle2;

		//1番と7番を入れ替える
		transform1 = field[Left][RightBottom].surfacePartsModelTrans;
		transform2 = field[Top][RightBottom].surfacePartsModelTrans;

		angle1 = field[Left][RightBottom].angle_;
		angle2 = field[Top][RightBottom].angle_;

		element = std::move(field[Left][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Top][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[Left][RightBottom] = std::move(field[Top][RightBottom]);
		field[Left][RightBottom].surfacePartsModelTrans = transform1;
		field[Left][RightBottom].angle_ = angle1;

		field[Top][RightBottom] = std::move(element);
		field[Top][RightBottom].surfacePartsModelTrans = transform2;
		field[Top][RightBottom].angle_ = angle2;

		break;
#pragma endregion

#pragma region 左と真ん中左

	case LeftToCenterLeft:

		//2番と8番を入れ替える
		transform1 = field[Left][LeftTop].surfacePartsModelTrans;
		transform2 = field[CenterLeft][RightTop].surfacePartsModelTrans;

		angle1 = field[Left][LeftTop].angle_;
		angle2 = field[CenterLeft][RightTop].angle_;

		element = std::move(field[Left][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[Left][LeftTop] = std::move(field[CenterLeft][RightTop]);
		field[Left][LeftTop].surfacePartsModelTrans = transform1;
		field[Left][LeftTop].angle_ = angle1;

		field[CenterLeft][RightTop] = std::move(element);
		field[CenterLeft][RightTop].surfacePartsModelTrans = transform2;
		field[CenterLeft][RightTop].angle_ = angle2;

		//4番と6番を入れ替える
		transform1 = field[Left][RightTop].surfacePartsModelTrans;
		transform2 = field[CenterLeft][LeftTop].surfacePartsModelTrans;

		angle1 = field[Left][RightTop].angle_;
		angle2 = field[CenterLeft][LeftTop].angle_;

		element = std::move(field[Left][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[Left][RightTop] = std::move(field[CenterLeft][LeftTop]);
		field[Left][RightTop].surfacePartsModelTrans = transform1;
		field[Left][RightTop].angle_ = angle1;

		field[CenterLeft][LeftTop] = std::move(element);
		field[CenterLeft][LeftTop].surfacePartsModelTrans = transform2;
		field[CenterLeft][LeftTop].angle_ = angle2;

		//1番と7番を入れ替える
		transform1 = field[Left][LeftBottom].surfacePartsModelTrans;
		transform2 = field[CenterLeft][RightBottom].surfacePartsModelTrans;

		angle1 = field[Left][LeftBottom].angle_;
		angle2 = field[CenterLeft][RightBottom].angle_;

		element = std::move(field[Left][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[CenterLeft][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[Left][LeftBottom] = std::move(field[CenterLeft][RightBottom]);
		field[Left][LeftBottom].surfacePartsModelTrans = transform1;
		field[Left][LeftBottom].angle_ = angle1;

		field[CenterLeft][RightBottom] = std::move(element);
		field[CenterLeft][RightBottom].surfacePartsModelTrans = transform2;
		field[CenterLeft][RightBottom].angle_ = angle2;

		//1番と7番を入れ替える
		transform1 = field[Left][RightBottom].surfacePartsModelTrans;
		transform2 = field[CenterLeft][LeftBottom].surfacePartsModelTrans;

		angle1 = field[Left][RightBottom].angle_;
		angle2 = field[CenterLeft][LeftBottom].angle_;

		element = std::move(field[Left][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[Left][RightBottom] = std::move(field[CenterLeft][LeftBottom]);
		field[Left][RightBottom].surfacePartsModelTrans = transform1;
		field[Left][RightBottom].angle_ = angle1;

		field[CenterLeft][LeftBottom] = std::move(element);
		field[CenterLeft][LeftBottom].surfacePartsModelTrans = transform2;
		field[CenterLeft][LeftBottom].angle_ = angle2;


		break;
#pragma endregion

#pragma region 真ん中左
	case LeftToRight:

		//3番と5番を入れ替える
		transform1 = field[Left][LeftTop].surfacePartsModelTrans;
		transform2 = field[Right][RightTop].surfacePartsModelTrans;

		angle1 = field[Left][LeftTop].angle_;
		angle2 = field[Right][RightTop].angle_;

		element = std::move(field[Left][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[Left][LeftTop] = std::move(field[Right][RightTop]);
		field[Left][LeftTop].surfacePartsModelTrans = transform1;
		field[Left][LeftTop].angle_ = angle1;

		field[Right][RightTop] = std::move(element);
		field[Right][RightTop].surfacePartsModelTrans = transform2;
		field[Right][RightTop].angle_ = angle2;

		//1番と7番を入れ替える
		transform1 = field[Left][RightTop].surfacePartsModelTrans;
		transform2 = field[Right][LeftTop].surfacePartsModelTrans;

		angle1 = field[Left][RightTop].angle_;
		angle2 = field[Right][LeftTop].angle_;

		element = std::move(field[Left][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[Left][RightTop] = std::move(field[Right][LeftTop]);
		field[Left][RightTop].surfacePartsModelTrans = transform1;
		field[Left][RightTop].angle_ = angle1;

		field[Right][LeftTop] = std::move(element);
		field[Right][LeftTop].surfacePartsModelTrans = transform2;
		field[Right][LeftTop].angle_ = angle2;

		//4番と6番を入れ替える
		transform1 = field[Left][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Right][RightBottom].surfacePartsModelTrans;

		angle1 = field[Left][LeftBottom].angle_;
		angle2 = field[Right][RightBottom].angle_;

		element = std::move(field[Left][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Right][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[Left][LeftBottom] = std::move(field[Right][RightBottom]);
		field[Left][LeftBottom].surfacePartsModelTrans = transform1;
		field[Left][LeftBottom].angle_ = angle1;

		field[Right][RightBottom] = std::move(element);
		field[Right][RightBottom].surfacePartsModelTrans = transform2;
		field[Right][RightBottom].angle_ = angle2;

		//2番と8番を入れ替える
		transform1 = field[Left][RightBottom].surfacePartsModelTrans;
		transform2 = field[Right][LeftBottom].surfacePartsModelTrans;

		angle1 = field[Left][RightBottom].angle_;
		angle2 = field[Right][LeftBottom].angle_;

		element = std::move(field[Left][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[Left][RightBottom] = std::move(field[Right][LeftBottom]);
		field[Left][RightBottom].surfacePartsModelTrans = transform1;
		field[Left][RightBottom].angle_ = angle1;

		field[Right][LeftBottom] = std::move(element);
		field[Right][LeftBottom].surfacePartsModelTrans = transform2;
		field[Right][LeftBottom].angle_ = angle2;

		break;
#pragma endregion

#pragma region 左と下

	case LeftToBottom:

		//1番と7番を入れ替える
		transform1 = field[Left][LeftTop].surfacePartsModelTrans;
		transform2 = field[Bottom][LeftTop].surfacePartsModelTrans;

		angle1 = field[Left][LeftTop].angle_;
		angle2 = field[Bottom][LeftTop].angle_;

		element = std::move(field[Left][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[Left][LeftTop] = std::move(field[Bottom][LeftTop]);
		field[Left][LeftTop].surfacePartsModelTrans = transform1;
		field[Left][LeftTop].angle_ = angle1;

		field[Bottom][LeftTop] = std::move(element);
		field[Bottom][LeftTop].surfacePartsModelTrans = transform2;
		field[Bottom][LeftTop].angle_ = angle2;

		//2番と8番を入れ替える
		transform1 = field[Left][RightTop].surfacePartsModelTrans;
		transform2 = field[Bottom][LeftBottom].surfacePartsModelTrans;

		angle1 = field[Left][RightTop].angle_;
		angle2 = field[Bottom][LeftBottom].angle_;

		element = std::move(field[Left][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[Left][RightTop] = std::move(field[Bottom][LeftBottom]);
		field[Left][RightTop].surfacePartsModelTrans = transform1;
		field[Left][RightTop].angle_ = angle1;

		field[Bottom][LeftBottom] = std::move(element);
		field[Bottom][LeftBottom].surfacePartsModelTrans = transform2;
		field[Bottom][LeftBottom].angle_ = angle2;

		//3番と5番を入れ替える
		transform1 = field[Left][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Bottom][RightTop].surfacePartsModelTrans;

		angle1 = field[Left][LeftBottom].angle_;
		angle2 = field[Bottom][RightTop].angle_;

		element = std::move(field[Left][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[Left][LeftBottom] = std::move(field[Bottom][RightTop]);
		field[Left][LeftBottom].surfacePartsModelTrans = transform1;
		field[Left][LeftBottom].angle_ = angle1;

		field[Bottom][RightTop] = std::move(element);
		field[Bottom][RightTop].surfacePartsModelTrans = transform2;
		field[Bottom][RightTop].angle_ = angle2;

		//4番と6番を入れ替える
		transform1 = field[Left][RightBottom].surfacePartsModelTrans;
		transform2 = field[Bottom][RightBottom].surfacePartsModelTrans;

		angle1 = field[Left][RightBottom].angle_;
		angle2 = field[Bottom][RightBottom].angle_;

		element = std::move(field[Left][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Bottom][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[Left][RightBottom] = std::move(field[Bottom][RightBottom]);
		field[Left][RightBottom].surfacePartsModelTrans = transform1;
		field[Left][RightBottom].angle_ = angle1;

		field[Bottom][RightBottom] = std::move(element);
		field[Bottom][RightBottom].surfacePartsModelTrans = transform2;
		field[Bottom][RightBottom].angle_ = angle2;

		break;
#pragma endregion

	default:
		break;

	}
}

void SurfaceFoldLeft2::EndLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	field[Left][LeftTop].isDraw = true;
	field[Left][RightTop].isDraw = true;
	field[Left][LeftBottom].isDraw = true;
	field[Left][RightBottom].isDraw = true;

	switch (fieldIndex)
	{

	case LeftToTop:

		field[Top][LeftTop].isDraw = true;
		field[Top][RightTop].isDraw = true;
		field[Top][LeftBottom].isDraw = true;
		field[Top][RightBottom].isDraw = true;
		break;

	case LeftToCenterLeft:

		field[CenterLeft][LeftTop].isDraw = true;
		field[CenterLeft][RightTop].isDraw = true;
		field[CenterLeft][LeftBottom].isDraw = true;
		field[CenterLeft][RightBottom].isDraw = true;
		break;

	case LeftToRight:

		field[Right][LeftTop].isDraw = true;
		field[Right][RightTop].isDraw = true;
		field[Right][LeftBottom].isDraw = true;
		field[Right][RightBottom].isDraw = true;
		break;

	case LeftToBottom:

		field[Bottom][LeftTop].isDraw = true;
		field[Bottom][RightTop].isDraw = true;
		field[Bottom][LeftBottom].isDraw = true;
		field[Bottom][RightBottom].isDraw = true;
		break;

	default:
		break;
	}
}

void SurfaceFoldLeft2::SetCollider(int chengeMesh, int chengeMesh2, std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, FieldElementIndex fieldElementIndex)
{

	field[fieldIndex][fieldElementIndex].surfacePartsModelTrans.matWorld;

}

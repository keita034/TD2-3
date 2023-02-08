#include "SurfaceFoldBottom2.h"
#include "MeshCollider.h"
#include "CollisionAttribute.h"
#include "CollisionManager.h"
#include "ChangeCollider.h"

void SurfaceFoldBottom2::StartBottomTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, fbxModel* surfaceFoldFbxmodel_)
{
	field[Bottom][LeftTop].isDraw = false;
	field[Bottom][RightTop].isDraw = false;
	field[Bottom][LeftBottom].isDraw = false;
	field[Bottom][RightBottom].isDraw = false;

	switch (fieldIndex)
	{
#pragma region 下と左
	case BottomToLeft:

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Bottom][RightBottom].textureData);

		////上のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.002", ((field[Bottom][LeftTop].angle_ * -1.0f) - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", ((field[Bottom][RightTop].angle_ * -1.0f) - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", ((field[Bottom][LeftBottom].angle_ * -1.0f) - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.003", ((field[Bottom][RightBottom].angle_ * -1.0f) - 90.0f) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[Left][RightBottom].textureData);

		//下のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.008", ((field[Left][LeftTop].angle_ * -1.0f) + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", ((field[Left][RightTop].angle_ * -1.0f) + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.006", ((field[Left][LeftBottom].angle_ * -1.0f) + 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.005", ((field[Left][RightBottom].angle_ * -1.0f) + 90.0f) * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 180.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad,0.0f * AliceMathF::Deg2Rad };

		field[Left][LeftTop].isDraw = false;
		field[Left][RightTop].isDraw = false;
		field[Left][LeftBottom].isDraw = false;
		field[Left][RightBottom].isDraw = false;

		break;
#pragma endregion

#pragma region 下と真ん中左

	case BottomToCenterLeft:

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Bottom][RightBottom].textureData);

		//下のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.001", ((field[Bottom][LeftTop].angle_ * -1.0f) - 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", ((field[Bottom][RightTop].angle_ * -1.0f) - 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.003", ((field[Bottom][LeftBottom].angle_ * -1.0f) - 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", ((field[Bottom][RightBottom].angle_ * -1.0f) - 180.0f) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[CenterLeft][RightBottom].textureData);

		//下のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.008", ((field[CenterLeft][LeftTop].angle_) - 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", ((field[CenterLeft][RightTop].angle_) - 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.006", ((field[CenterLeft][LeftBottom].angle_) - 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.005", ((field[CenterLeft][RightBottom].angle_) - 180.0f) * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 180.0f * AliceMathF::Deg2Rad,0.0f * AliceMathF::Deg2Rad,0.0f * AliceMathF::Deg2Rad };

		field[CenterLeft][LeftTop].isDraw = false;
		field[CenterLeft][RightTop].isDraw = false;
		field[CenterLeft][LeftBottom].isDraw = false;
		field[CenterLeft][RightBottom].isDraw = false;

		break;
#pragma endregion

#pragma region 下と真ん中右

	case BottomToCenterRight:

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Bottom][RightBottom].textureData);

		//上のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.003", ((field[Bottom][LeftTop].angle_) - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", ((field[Bottom][RightTop].angle_) - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", ((field[Bottom][LeftBottom].angle_) - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", ((field[Bottom][RightBottom].angle_) - 90.0f) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[CenterRight][RightBottom].textureData);

		//下のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.008", ((field[CenterRight][LeftTop].angle_) - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", ((field[CenterRight][RightTop].angle_) - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.006", ((field[CenterRight][LeftBottom].angle_) - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.005", ((field[CenterRight][RightBottom].angle_) - 90.0f) * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 180.0f * AliceMathF::Deg2Rad,-90.0f * AliceMathF::Deg2Rad,0.0f * AliceMathF::Deg2Rad };

		field[CenterRight][LeftTop].isDraw = false;
		field[CenterRight][RightTop].isDraw = false;
		field[CenterRight][LeftBottom].isDraw = false;
		field[CenterRight][RightBottom].isDraw = false;

		break;
#pragma endregion

#pragma region 下と右
	case BottomToRight:

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Bottom][RightBottom].textureData);

		//上のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.003", ((field[Bottom][LeftTop].angle_ * -1.0f)) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", ((field[Bottom][RightTop].angle_ * -1.0f)) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", ((field[Bottom][LeftBottom].angle_ * -1.0f)) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", ((field[Bottom][RightBottom].angle_ * -1.0f)) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[Right][RightBottom].textureData);

		//下のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.007", ((field[Right][LeftTop].angle_) + 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.005", ((field[Right][RightTop].angle_) + 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.008", ((field[Right][LeftBottom].angle_) + 180.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.006", ((field[Right][RightBottom].angle_) + 180.0f) * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 180.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad,0.0f * AliceMathF::Deg2Rad };

		field[Right][LeftTop].isDraw = false;
		field[Right][RightTop].isDraw = false;
		field[Right][LeftBottom].isDraw = false;
		field[Right][RightBottom].isDraw = false;

		break;
#pragma endregion

	default:
		break;
	}
}

void SurfaceFoldBottom2::ShrinkAnimeBottomTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, float scale)
{
	field[Bottom][LeftTop].surfacePartsModelTrans.scale.y = scale;
	field[Bottom][RightTop].surfacePartsModelTrans.scale.y = scale;
	field[Bottom][LeftBottom].surfacePartsModelTrans.scale.y = scale;
	field[Bottom][RightBottom].surfacePartsModelTrans.scale.y = scale;

	switch (fieldIndex)
	{
	case BottomToLeft:

		field[Left][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[Left][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[Left][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[Left][RightBottom].surfacePartsModelTrans.scale.y = scale;

		break;

	case BottomToCenterLeft:

		field[CenterLeft][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[CenterLeft][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[CenterLeft][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[CenterLeft][RightBottom].surfacePartsModelTrans.scale.y = scale;

		break;

	case BottomToCenterRight:

		field[CenterRight][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[CenterRight][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[CenterRight][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[CenterRight][RightBottom].surfacePartsModelTrans.scale.y = scale;

		break;

	case BottomToRight:

		field[Right][LeftTop].surfacePartsModelTrans.scale.y = scale;
		field[Right][RightTop].surfacePartsModelTrans.scale.y = scale;
		field[Right][LeftBottom].surfacePartsModelTrans.scale.y = scale;
		field[Right][RightBottom].surfacePartsModelTrans.scale.y = scale;

		break;

	default:
		break;
	}
}

void SurfaceFoldBottom2::ReplaceBottomTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, fbxModel* surfaceFoldFbxmodel_)
{
	FieldElement element;
	Transform transform1;
	Transform transform2;
	float angle1 = 0.0f;
	float angle2 = 0.0f;

	switch (fieldIndex)
	{
#pragma region 下と左
	case BottomToLeft:

		//4番と6番を入れ替える
		transform1 = field[Bottom][LeftTop].surfacePartsModelTrans;
		transform2 = field[Left][LeftTop].surfacePartsModelTrans;

		angle1 = field[Bottom][LeftTop].angle_;
		angle2 = field[Left][LeftTop].angle_;

		element = std::move(field[Bottom][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[Bottom][LeftTop] = std::move(field[Left][LeftTop]);
		field[Bottom][LeftTop].surfacePartsModelTrans = transform1;
		field[Bottom][LeftTop].angle_ = angle1;

		field[Left][LeftTop] = std::move(element);
		field[Left][LeftTop].surfacePartsModelTrans = transform2;
		field[Left][LeftTop].angle_ = angle2;

		//SetCollider(field, Bottom, LeftTop, 4);
		//SetCollider(field, Left, LeftTop, 6);

		//3番と5番を入れ替える
		transform1 = field[Bottom][RightTop].surfacePartsModelTrans;
		transform2 = field[Left][LeftBottom].surfacePartsModelTrans;

		angle1 = field[Bottom][RightTop].angle_;
		angle2 = field[Left][LeftBottom].angle_;

		element = std::move(field[Bottom][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[Bottom][RightTop] = std::move(field[Left][LeftBottom]);
		field[Bottom][RightTop].surfacePartsModelTrans = transform1;
		field[Bottom][RightTop].angle_ = angle1;

		field[Left][LeftBottom] = std::move(element);
		field[Left][LeftBottom].surfacePartsModelTrans = transform2;
		field[Left][LeftBottom].angle_ = angle2;

		//SetCollider(field, Bottom, RightTop, 3);
		//SetCollider(field, Left, LeftBottom, 5);

		//2番と8番を入れ替える
		transform1 = field[Bottom][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Left][RightTop].surfacePartsModelTrans;

		angle1 = field[Bottom][LeftBottom].angle_;
		angle2 = field[Left][RightTop].angle_;

		element = std::move(field[Bottom][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[Bottom][LeftBottom] = std::move(field[Left][RightTop]);
		field[Bottom][LeftBottom].surfacePartsModelTrans = transform1;
		field[Bottom][LeftBottom].angle_ = angle1;

		field[Left][RightTop] = std::move(element);
		field[Left][RightTop].surfacePartsModelTrans = transform2;
		field[Left][RightTop].angle_ = angle2;

		//SetCollider(field, Bottom, LeftBottom, 2);
		//SetCollider(field, Left, RightTop, 8);

		//1番と7番を入れ替える
		transform1 = field[Bottom][RightBottom].surfacePartsModelTrans;
		transform2 = field[Left][RightBottom].surfacePartsModelTrans;

		angle1 = field[Bottom][RightBottom].angle_;
		angle2 = field[Left][RightBottom].angle_;

		element = std::move(field[Bottom][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Left][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[Bottom][RightBottom] = std::move(field[Left][RightBottom]);
		field[Bottom][RightBottom].surfacePartsModelTrans = transform1;
		field[Bottom][RightBottom].angle_ = angle1;

		field[Left][RightBottom] = std::move(element);
		field[Left][RightBottom].surfacePartsModelTrans = transform2;
		field[Left][RightBottom].angle_ = angle2;

		//SetCollider(field, Bottom, RightBottom, 1);
		//SetCollider(field, Left, RightBottom, 7);

		break;

#pragma endregion

#pragma region 下と真ん中左
	case BottomToCenterLeft:

		//4番と6番を入れ替える
		transform1 = field[Bottom][LeftTop].surfacePartsModelTrans;
		transform2 = field[CenterLeft][RightTop].surfacePartsModelTrans;

		angle1 = field[Bottom][LeftTop].angle_;
		angle2 = field[CenterLeft][RightTop].angle_;

		element = std::move(field[Bottom][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[Bottom][LeftTop] = std::move(field[CenterLeft][RightTop]);
		field[Bottom][LeftTop].surfacePartsModelTrans = transform1;
		field[Bottom][LeftTop].angle_ = angle1;

		field[CenterLeft][RightTop] = std::move(element);
		field[CenterLeft][RightTop].surfacePartsModelTrans = transform2;
		field[CenterLeft][RightTop].angle_ = angle2;

		//SetCollider(field, Bottom, LeftTop, 4);
		//SetCollider(field, CenterLeft, RightTop, 6);

		//3番と5番を入れ替える
		transform1 = field[Bottom][RightTop].surfacePartsModelTrans;
		transform2 = field[CenterLeft][LeftTop].surfacePartsModelTrans;

		angle1 = field[Bottom][RightTop].angle_;
		angle2 = field[CenterLeft][LeftTop].angle_;

		element = std::move(field[Bottom][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[Bottom][RightTop] = std::move(field[CenterLeft][LeftTop]);
		field[Bottom][RightTop].surfacePartsModelTrans = transform1;
		field[Bottom][RightTop].angle_ = angle1;

		field[CenterLeft][LeftTop] = std::move(element);
		field[CenterLeft][LeftTop].surfacePartsModelTrans = transform2;
		field[CenterLeft][LeftTop].angle_ = angle2;

		//SetCollider(field, Bottom, RightTop, 3);
		//SetCollider(field, CenterLeft, LeftTop, 5);


		//2番と8番を入れ替える
		transform1 = field[Bottom][LeftBottom].surfacePartsModelTrans;
		transform2 = field[CenterLeft][RightBottom].surfacePartsModelTrans;

		angle1 = field[Bottom][LeftBottom].angle_;
		angle2 = field[CenterLeft][RightBottom].angle_;

		element = std::move(field[Bottom][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[CenterLeft][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[Bottom][LeftBottom] = std::move(field[CenterLeft][RightBottom]);
		field[Bottom][LeftBottom].surfacePartsModelTrans = transform1;
		field[Bottom][LeftBottom].angle_ = angle1;

		field[CenterLeft][RightBottom] = std::move(element);
		field[CenterLeft][RightBottom].surfacePartsModelTrans = transform2;
		field[CenterLeft][RightBottom].angle_ = angle2;

		//SetCollider(field, Bottom, LeftBottom, 3);
		//SetCollider(field, CenterLeft, RightBottom, 5);

		//1番と7番を入れ替える
		transform1 = field[Bottom][RightBottom].surfacePartsModelTrans;
		transform2 = field[CenterLeft][LeftBottom].surfacePartsModelTrans;

		angle1 = field[Bottom][RightBottom].angle_;
		angle2 = field[CenterLeft][LeftBottom].angle_;

		element = std::move(field[Bottom][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[Bottom][RightBottom] = std::move(field[CenterLeft][LeftBottom]);
		field[Bottom][RightBottom].surfacePartsModelTrans = transform1;
		field[Bottom][RightBottom].angle_ = angle1;

		field[CenterLeft][LeftBottom] = std::move(element);
		field[CenterLeft][LeftBottom].surfacePartsModelTrans = transform2;
		field[CenterLeft][LeftBottom].angle_ = angle2;

		//SetCollider(field, Bottom, RightBottom, 3);
		//SetCollider(field, CenterLeft, LeftBottom, 5);

		break;
#pragma endregion

#pragma region 下と真ん中右
	case BottomToCenterRight:

		//4番と6番を入れ替える
		transform1 = field[Bottom][LeftTop].surfacePartsModelTrans;
		transform2 = field[CenterRight][RightBottom].surfacePartsModelTrans;

		angle1 = field[Bottom][LeftTop].angle_;
		angle2 = field[CenterRight][RightBottom].angle_;

		element = std::move(field[Bottom][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[CenterRight][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[Bottom][LeftTop] = std::move(field[CenterRight][RightBottom]);
		field[Bottom][LeftTop].surfacePartsModelTrans = transform1;
		field[Bottom][LeftTop].angle_ = angle1;

		field[CenterRight][RightBottom] = std::move(element);
		field[CenterRight][RightBottom].surfacePartsModelTrans = transform2;
		field[CenterRight][RightBottom].angle_ = angle2;

		//SetCollider(field, Bottom, LeftTop, 4);
		//SetCollider(field, CenterRight, RightBottom, 6);

		//3番と5番を入れ替える
		transform1 = field[Bottom][RightTop].surfacePartsModelTrans;
		transform2 = field[CenterRight][RightTop].surfacePartsModelTrans;

		angle1 = field[Bottom][RightTop].angle_;
		angle2 = field[CenterRight][RightTop].angle_;

		element = std::move(field[Bottom][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[Bottom][RightTop] = std::move(field[CenterRight][RightTop]);
		field[Bottom][RightTop].surfacePartsModelTrans = transform1;
		field[Bottom][RightTop].angle_ = angle1;

		field[CenterRight][RightTop] = std::move(element);
		field[CenterRight][RightTop].surfacePartsModelTrans = transform2;
		field[CenterRight][RightTop].angle_ = angle2;

		//SetCollider(field, Bottom, RightTop, 3);
		//SetCollider(field, CenterRight, RightTop, 5);

		//2番と8番を入れ替える
		transform1 = field[Bottom][LeftBottom].surfacePartsModelTrans;
		transform2 = field[CenterRight][LeftBottom].surfacePartsModelTrans;

		angle1 = field[Bottom][LeftBottom].angle_;
		angle2 = field[CenterRight][LeftBottom].angle_;

		element = std::move(field[Bottom][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[Bottom][LeftBottom] = std::move(field[CenterRight][LeftBottom]);
		field[Bottom][LeftBottom].surfacePartsModelTrans = transform1;
		field[Bottom][LeftBottom].angle_ = angle1;

		field[CenterRight][LeftBottom] = std::move(element);
		field[CenterRight][LeftBottom].surfacePartsModelTrans = transform2;
		field[CenterRight][LeftBottom].angle_ = angle2;

		//SetCollider(field, Bottom, LeftBottom, 2);
		//SetCollider(field, CenterRight, LeftBottom, 8);

		//1番と7番を入れ替える
		transform1 = field[Bottom][RightBottom].surfacePartsModelTrans;
		transform2 = field[CenterRight][LeftTop].surfacePartsModelTrans;

		angle1 = field[Bottom][RightBottom].angle_;
		angle2 = field[CenterRight][LeftTop].angle_;

		element = std::move(field[Bottom][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[Bottom][RightBottom] = std::move(field[CenterRight][LeftTop]);
		field[Bottom][RightBottom].surfacePartsModelTrans = transform1;
		field[Bottom][RightBottom].angle_ = angle1;

		field[CenterRight][LeftTop] = std::move(element);
		field[CenterRight][LeftTop].surfacePartsModelTrans = transform2;
		field[CenterRight][LeftTop].angle_ = angle2;

		//SetCollider(field, Bottom, RightBottom, 1);
		//SetCollider(field, CenterRight, LeftTop, 7);

		break;
#pragma endregion

#pragma region 下と右
	case BottomToRight:

		//4番と6番を入れ替える
		transform1 = field[Bottom][LeftTop].surfacePartsModelTrans;
		transform2 = field[Right][LeftBottom].surfacePartsModelTrans;

		angle1 = field[Bottom][LeftTop].angle_;
		angle2 = field[Right][LeftBottom].angle_;

		element = std::move(field[Bottom][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, element.textureData);

		field[Bottom][LeftTop] = std::move(field[Right][LeftBottom]);
		field[Bottom][LeftTop].surfacePartsModelTrans = transform1;
		field[Bottom][LeftTop].angle_ = angle1;

		field[Right][LeftBottom] = std::move(element);
		field[Right][LeftBottom].surfacePartsModelTrans = transform2;
		field[Right][LeftBottom].angle_ = angle2;

		//SetCollider(field, Bottom, LeftTop, 4);
		//SetCollider(field, Right, LeftBottom, 6);

		//3番と5番を入れ替える
		transform1 = field[Bottom][RightTop].surfacePartsModelTrans;
		transform2 = field[Right][RightBottom].surfacePartsModelTrans;

		angle1 = field[Bottom][RightTop].angle_;
		angle2 = field[Right][RightBottom].angle_;

		element = std::move(field[Bottom][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Right][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, element.textureData);

		field[Bottom][RightTop] = std::move(field[Right][RightBottom]);
		field[Bottom][RightTop].surfacePartsModelTrans = transform1;
		field[Bottom][RightTop].angle_ = angle1;

		field[Right][RightBottom] = std::move(element);
		field[Right][RightBottom].surfacePartsModelTrans = transform2;
		field[Right][RightBottom].angle_ = angle2;

		//SetCollider(field, Bottom, RightTop, 3);
		//SetCollider(field, Right, RightBottom, 5);

		//2番と8番を入れ替える
		transform1 = field[Bottom][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Right][LeftTop].surfacePartsModelTrans;

		angle1 = field[Bottom][LeftBottom].angle_;
		angle2 = field[Right][LeftTop].angle_;

		element = std::move(field[Bottom][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, element.textureData);

		field[Bottom][LeftBottom] = std::move(field[Right][LeftTop]);
		field[Bottom][LeftBottom].surfacePartsModelTrans = transform1;
		field[Bottom][LeftBottom].angle_ = angle1;

		field[Right][LeftTop] = std::move(element);
		field[Right][LeftTop].surfacePartsModelTrans = transform2;
		field[Right][LeftTop].angle_ = angle2;

		//SetCollider(field, Bottom, LeftBottom, 2);
		//SetCollider(field, Right, LeftTop, 8);

		//1番と7番を入れ替える
		transform1 = field[Bottom][RightBottom].surfacePartsModelTrans;
		transform2 = field[Right][RightTop].surfacePartsModelTrans;

		angle1 = field[Bottom][RightBottom].angle_;
		angle2 = field[Right][RightTop].angle_;

		element = std::move(field[Bottom][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, element.textureData);

		field[Bottom][RightBottom] = std::move(field[Right][RightTop]);
		field[Bottom][RightBottom].surfacePartsModelTrans = transform1;
		field[Bottom][RightBottom].angle_ = angle1;

		field[Right][RightTop] = std::move(element);
		field[Right][RightTop].surfacePartsModelTrans = transform2;
		field[Right][RightTop].angle_ = angle2;

		//SetCollider(field, Bottom, RightBottom, 1);
		//SetCollider(field, Right, RightTop, 7);

		break;
#pragma endregion

	default:
		break;
	}
}

void SurfaceFoldBottom2::EndBottomTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	field[Bottom][LeftTop].isDraw = true;
	field[Bottom][RightTop].isDraw = true;
	field[Bottom][LeftBottom].isDraw = true;
	field[Bottom][RightBottom].isDraw = true;

	switch (fieldIndex)
	{
	case BottomToLeft:

		field[Left][LeftTop].isDraw = true;
		field[Left][RightTop].isDraw = true;
		field[Left][LeftBottom].isDraw = true;
		field[Left][RightBottom].isDraw = true;

		break;

	case BottomToCenterLeft:

		field[CenterLeft][LeftTop].isDraw = true;
		field[CenterLeft][RightTop].isDraw = true;
		field[CenterLeft][LeftBottom].isDraw = true;
		field[CenterLeft][RightBottom].isDraw = true;

		break;

	case BottomToCenterRight:

		field[CenterRight][LeftTop].isDraw = true;
		field[CenterRight][RightTop].isDraw = true;
		field[CenterRight][LeftBottom].isDraw = true;
		field[CenterRight][RightBottom].isDraw = true;

		break;

	case BottomToRight:

		field[Right][LeftTop].isDraw = true;
		field[Right][RightTop].isDraw = true;
		field[Right][LeftBottom].isDraw = true;
		field[Right][RightBottom].isDraw = true;

		break;

	default:
		break;
	}
}

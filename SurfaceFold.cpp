#include "SurfaceFold.h"

void SurfaceFold::Initialize()
{
	//面折りモデル
	surfaceFoldFbxmodel_ = std::make_unique<fbxModel>();
	surfaceFoldFbxmodel_->Initialize();
	surfaceFoldFbxmodel_->Create("Resources/SurfaceFold/FBX 2013", false, false, true, false);
	surfaceFoldFbxmodelAnime_ = std::make_unique<fbxAnimation>();
	FbxLoader::GetInstance()->LoadAnimation(surfaceFoldFbxmodelAnime_.get(), "Resources/SurfaceFold/FBX 2013", "");


	fieldPlaneTrans_.Initialize();
	fieldPlaneTrans_.scale = { 0.4f,0.4f ,0.4f };
	fieldPlaneTrans_.translation = { 0,-10,0 };
}

void SurfaceFold::Start(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, float standardAngle)
{
	surfaceFoldFbxmodel_->InitializeVertex();

	switch (fieldIndex)
	{
	case TopToLeft:
	case TopToCenterLeft:
	case TopToCenterRight:
	case TopToRight:

		StartTopTo(field, fieldIndex, standardAngle);

		break;

	case LeftToTop:
	case LeftToCenterLeft:
	case LeftToRight:
	case LeftToBottom:

		StartLeftTo(field, fieldIndex);

		break;

	case CenterLeftToTop:
	case CenterLeftToLeft:
	case CenterLeftToCenterRight:
	case CenterLeftToBottom:

		StartCenterLeftTo(field, fieldIndex);

		break;

	case CenterRightToTop:
	case CenterRightToCenterLeft:
	case CenterRightToRight:
	case CenterRightToBottom:

		StartCenterRightTo(field, fieldIndex);

		break;

	case RightToTop:
	case RightToLeft:
	case RightToCenterRight:
	case RightToBottom:

		StartRightTo(field, fieldIndex);

		break;

	case BottomToLeft:
	case BottomToCenterLeft:
	case BottomToCenterRight:
	case BottomToRight:

		StartBottomTo(field, fieldIndex);

		break;

	default:
		break;
	}

}

void SurfaceFold::Update(Camera* camera, std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, bool& fieldPlaneDrawFlag)
{
	fieldPlaneAnimeFlam_ += 0.02f;

	fieldPlaneTrans_.TransUpdate(camera);

	if (surfaceFoldFbxmodelAnime_->GetTickTimes(fieldPlaneAnimeFlam_) >= surfaceFoldFbxmodelAnime_->GetAnimeMaxflame() / 2 && !fieldReplaceFlag_)
	{
		Replace(field, fieldIndex);
		fieldReplaceFlag_ = true;
	}

	if (surfaceFoldFbxmodelAnime_->GetTickTimes(fieldPlaneAnimeFlam_) >= surfaceFoldFbxmodelAnime_->GetAnimeMaxflame())
	{
		fieldPlaneDrawFlag = false;
		fieldPlaneAnimeFlam_ = 0.0f;
		fieldReplaceFlag_ = false;

		switch (fieldIndex)
		{
		case TopToLeft:
		case TopToCenterLeft:
		case TopToCenterRight:
		case TopToRight:

			EndTopTo(field, fieldIndex);

			break;

		case LeftToTop:
		case LeftToCenterLeft:
		case LeftToRight:
		case LeftToBottom:

			EndLeftTo(field, fieldIndex);

			break;

		case CenterLeftToTop:
		case CenterLeftToLeft:
		case CenterLeftToCenterRight:
		case CenterLeftToBottom:

			EndCenterLeftTo(field, fieldIndex);

			break;

		case CenterRightToTop:
		case CenterRightToCenterLeft:
		case CenterRightToRight:
		case CenterRightToBottom:

			EndCenterRightTo(field, fieldIndex);

			break;

		case RightToTop:
		case RightToLeft:
		case RightToCenterRight:
		case RightToBottom:

			EndRightTo(field, fieldIndex);

			break;

		case BottomToLeft:
		case BottomToCenterLeft:
		case BottomToCenterRight:
		case BottomToRight:

			EndBottomTo(field, fieldIndex);

			break;

		default:
			break;
		}
	}

	surfaceFoldFbxmodel_->AnimationUpdate(surfaceFoldFbxmodelAnime_.get(), fieldPlaneAnimeFlam_);
}

void SurfaceFold::Replace(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	switch (fieldIndex)
	{
	case TopToLeft:
	case TopToCenterLeft:
	case TopToCenterRight:
	case TopToRight:

		ReplaceTopTo(field, fieldIndex);

		break;

	case LeftToTop:
	case LeftToCenterLeft:
	case LeftToRight:
	case LeftToBottom:

		ReplaceLeftTo(field, fieldIndex);

		break;

	case CenterLeftToTop:
	case CenterLeftToLeft:
	case CenterLeftToCenterRight:
	case CenterLeftToBottom:

		ReplaceCenterLeftTo(field, fieldIndex);

		break;

	case CenterRightToTop:
	case CenterRightToCenterLeft:
	case CenterRightToRight:
	case CenterRightToBottom:

		ReplaceCenterRightTo(field, fieldIndex);

		break;

	case RightToTop:
	case RightToLeft:
	case RightToCenterRight:
	case RightToBottom:

		ReplaceRightTo(field, fieldIndex);

		break;

	case BottomToLeft:
	case BottomToCenterLeft:
	case BottomToCenterRight:
	case BottomToRight:

		ReplaceBottomTo(field, fieldIndex);

		break;

	default:
		break;
	}
}

void SurfaceFold::Draw()
{
	surfaceFoldFbxmodel_->Draw(&fieldPlaneTrans_);
}

void SurfaceFold::StartTopTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, float standardAngle)
{
	field[Top][LeftTop].isDraw = false;
	field[Top][RightTop].isDraw = false;
	field[Top][LeftBottom].isDraw = false;
	field[Top][RightBottom].isDraw = false;

	float angle;

	switch (fieldIndex)
	{

#pragma region 上と左

	case TopToLeft:

		//回転
		fieldPlaneTrans_.rotation = { 0.0f * AliceMathF::Deg2Rad,-90.0f * AliceMathF::Deg2Rad,0.0f * AliceMathF::Deg2Rad };

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Top][RightBottom].textureData);

		//上のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.003", (field[Top][LeftTop].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", (field[Top][RightTop].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", (field[Top][LeftBottom].angle_ - 90.0f) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", (field[Top][RightBottom].angle_ - 90.0f) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[Left][RightBottom].textureData);

		//下のUV回転
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

#pragma region 上と真ん中左
	case TopToCenterLeft:

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Top][RightBottom].textureData);

		//上のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.001", (field[Top][LeftTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", (field[Top][RightTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.003", (field[Top][LeftBottom].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", (field[Top][RightBottom].angle_) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[CenterLeft][RightBottom].textureData);

		//下のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.005", (-field[CenterRight][LeftTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.006", (-field[CenterRight][RightTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", (-field[CenterRight][LeftBottom].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.008", (-field[CenterRight][RightBottom].angle_) * AliceMathF::Deg2Rad);

		//回転
		fieldPlaneTrans_.rotation = { 0.0f,180.0f * AliceMathF::Deg2Rad,0.0f };

		field[CenterLeft][LeftTop].isDraw = false;
		field[CenterLeft][RightTop].isDraw = false;
		field[CenterLeft][LeftBottom].isDraw = false;
		field[CenterLeft][RightBottom].isDraw = false;

		break;
#pragma endregion

#pragma region  上と真ん中右

	case TopToCenterRight:

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Top][RightBottom].textureData);

		//上のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.003", (90.0f + field[Top][LeftTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", (90.0f + field[Top][RightTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", (90.0f + field[Top][LeftBottom].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", (90.0f + field[Top][RightBottom].angle_) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[CenterRight][RightBottom].textureData);

		//下のUV回転
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

#pragma region 上と右

	case TopToRight:

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.004", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.003", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.002", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.001", 0, field[Top][RightBottom].textureData);

		//上のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.004", (-180 + field[Top][LeftTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.003", (-180 + field[Top][RightTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.002", (-180 + field[Top][LeftBottom].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", (-180 + field[Top][RightBottom].angle_) * AliceMathF::Deg2Rad);

		//テクスチャをセット
		surfaceFoldFbxmodel_->TransTexture("Material.005", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.006", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.007", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Material.008", 0, field[Right][RightBottom].textureData);

		//下のUV回転
		surfaceFoldFbxmodel_->rotationUV("Material.005", (field[Right][LeftTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.006", (field[Right][RightTop].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.007", (field[Right][LeftBottom].angle_) * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.008", (field[Right][RightBottom].angle_) * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 0.0f,0.0f,0.0f };

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

void SurfaceFold::ReplaceTopTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	FieldElement element;
	Transform transform1;
	Transform transform2;
	float angle1 = 0.0f;
	float angle2 = 0.0f;

	switch (fieldIndex)
	{
	case TopToLeft:
		//3番と5番を入れ替える
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

		//4番と6番を入れ替える
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

		//1番と7番を入れ替える
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

		//2番と8番を入れ替える
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

		break;

	case TopToCenterLeft:

		//1番と7番を入れ替える
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

		//2番と8番を入れ替える
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

		//3番と5番を入れ替える
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

		//4番と6番を入れ替える
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

		break;

	case TopToCenterRight:

		//2番と8番を入れ替える
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

		//4番と6番を入れ替える
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

		//1番と5番を入れ替える
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

		//4番と6番を入れ替える
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

		break;

	case TopToRight:

		//4番と6番を入れ替える
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

		//3番と5番を入れ替える
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

		//2番と8番を入れ替える
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

		//1番と7番を入れ替える
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

		break;

	default:
		break;
	}
}

void SurfaceFold::EndTopTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
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

void SurfaceFold::StartLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
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

void SurfaceFold::ReplaceLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
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

void SurfaceFold::EndLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
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

void SurfaceFold::StartCenterLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
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

void SurfaceFold::ReplaceCenterLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
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

void SurfaceFold::EndCenterLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
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

void SurfaceFold::StartCenterRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
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

void SurfaceFold::ReplaceCenterRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
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

		break;
#pragma endregion

	default:
		break;
	}
}

void SurfaceFold::EndCenterRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
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

void SurfaceFold::StartRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
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

void SurfaceFold::ReplaceRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
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

void SurfaceFold::EndRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
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

void SurfaceFold::StartBottomTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
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
		surfaceFoldFbxmodel_->rotationUV("Material.003", ((field[Bottom][LeftTop].angle_ * -1.0f))* AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.001", ((field[Bottom][RightTop].angle_ * -1.0f))* AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Material.004", ((field[Bottom][LeftBottom].angle_ * -1.0f))* AliceMathF::Deg2Rad);
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

void SurfaceFold::ReplaceBottomTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
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

		break;
#pragma endregion

	default:
		break;
	}
}

void SurfaceFold::EndBottomTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
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


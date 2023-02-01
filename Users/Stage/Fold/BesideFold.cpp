#include "BesideFold.h"

void BesideFold::Initialize()
{
	//â°ê‹ÇËÉÇÉfÉã
	besideFoldFbxmodel_ = std::make_unique<fbxModel>();
	besideFoldFbxmodel_->Initialize();
	besideFoldFbxmodel_->Create("Resources/BesideFoldPlane", false, false, true, false);
	besideFoldFbxmodelAnime_ = std::make_unique<fbxAnimation>();
	FbxLoader::GetInstance()->LoadAnimation(besideFoldFbxmodelAnime_.get(), "Resources/BesideFoldPlane", "");

	fieldPlaneTrans_.Initialize();
	fieldPlaneTrans_.scale = { 0.1f,0.1f ,0.1f };
	fieldPlaneTrans_.translation = { 0,-10,0 };
}

void BesideFold::Start(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	besideFoldFbxmodel_->TransTexture("Map01.005", 0, field[fieldIndex][LeftTop].textureData);
	besideFoldFbxmodel_->TransTexture("Map02.005", 0, field[fieldIndex][RightTop].textureData);
	besideFoldFbxmodel_->TransTexture("Map03.005", 0, field[fieldIndex][LeftBottom].textureData);
	besideFoldFbxmodel_->TransTexture("Map04.005", 0, field[fieldIndex][RightBottom].textureData);

	field[fieldIndex][LeftTop].isDraw = false;
	field[fieldIndex][RightTop].isDraw = false;
	field[fieldIndex][LeftBottom].isDraw = false;
	field[fieldIndex][RightBottom].isDraw = false;

	switch (fieldIndex)
	{
	case Top:

		fieldPlaneTrans_.rotation = { 0.0f,-90.0f * AliceMathF::Deg2Rad,0.0f };
		fieldPlaneTrans_.translation = { -0.0f,30.0f,0.0f };

		break;

	case Left:

		fieldPlaneTrans_.rotation = { 0.0f,0.0f,90.0f * AliceMathF::Deg2Rad };
		fieldPlaneTrans_.translation = { -40.0f,-10.0f,0.0f };

		break;

	case CenterLeft:

		fieldPlaneTrans_.rotation = { 0.0f * AliceMathF::Deg2Rad,-90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };
		fieldPlaneTrans_.translation = { -0.0f,-10.0f,-40.0f };

		break;

	case CenterRight:

		fieldPlaneTrans_.rotation = { 180.0f * AliceMathF::Deg2Rad,0.0f,-90.0f * AliceMathF::Deg2Rad };
		fieldPlaneTrans_.translation = { 40.0f,-10.0f,0.0f };

		break;

	case Right:

		fieldPlaneTrans_.rotation = { 0.0f,90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };
		fieldPlaneTrans_.translation = { 0.0f,-10.0f,40.0f };

		break;

	case Bottom:
		fieldPlaneTrans_.rotation = { 180.0f * AliceMathF::Deg2Rad,-90.0f * AliceMathF::Deg2Rad,0.0f * AliceMathF::Deg2Rad };
		fieldPlaneTrans_.translation = { -0.0f,-50.0f,0.0f };
		break;
	default:
		break;
	}
}

void BesideFold::Update(Camera* camera, std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, bool& fieldPlaneDrawFlag)
{
	fieldPlaneAnimeFlam_ += 0.02f;

	fieldPlaneTrans_.TransUpdate(camera);

	if (fieldPlaneAnimeFlam_ >= besideFoldFbxmodelAnime_->GetAnimeMaxflame() / 2 && !fieldReplaceFlag_)
	{
		Replace(field, fieldIndex);
		fieldReplaceFlag_ = true;
	}

	if (fieldPlaneAnimeFlam_ >= besideFoldFbxmodelAnime_->GetAnimeMaxflame())
	{
		fieldPlaneDrawFlag = false;
		fieldPlaneAnimeFlam_ = 0.0f;
		fieldReplaceFlag_ = false;

		field[fieldIndex][LeftTop].isDraw = true;
		field[fieldIndex][RightTop].isDraw = true;
		field[fieldIndex][LeftBottom].isDraw = true;
		field[fieldIndex][RightBottom].isDraw = true;
	}

	besideFoldFbxmodel_->AnimationUpdate(besideFoldFbxmodelAnime_.get(), fieldPlaneAnimeFlam_);
}

void BesideFold::Replace(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	FieldElement element;
	Transform transform1;
	Transform transform2;

	//1î‘Ç∆2î‘Çì¸ÇÍë÷Ç¶ÇÈ
	transform1 = field[fieldIndex][RightTop].surfacePartsModelTrans;
	transform2 = field[fieldIndex][LeftTop].surfacePartsModelTrans;
	element = std::move(field[fieldIndex][RightTop]);

	besideFoldFbxmodel_->TransTexture("Map02.005", element.textureData->path.c_str(), field[fieldIndex][LeftTop].textureData);
	besideFoldFbxmodel_->TransTexture("Map01.005", field[fieldIndex][LeftTop].textureData->path.c_str(), element.textureData);

	field[fieldIndex][RightTop] = std::move(field[fieldIndex][LeftTop]);
	field[fieldIndex][RightTop].surfacePartsModelTrans = transform1;

	field[fieldIndex][LeftTop] = std::move(element);
	field[fieldIndex][LeftTop].surfacePartsModelTrans = transform2;

	//3î‘Ç∆4î‘Çì¸ÇÍë÷Ç¶ÇÈ
	transform1 = field[fieldIndex][RightBottom].surfacePartsModelTrans;
	transform2 = field[fieldIndex][LeftBottom].surfacePartsModelTrans;
	element = std::move(field[fieldIndex][RightBottom]);

	besideFoldFbxmodel_->TransTexture("Map04.005", element.textureData->path.c_str(), field[fieldIndex][LeftBottom].textureData);
	besideFoldFbxmodel_->TransTexture("Map03.005", field[fieldIndex][LeftBottom].textureData->path.c_str(), element.textureData);

	field[fieldIndex][RightBottom] = std::move(field[fieldIndex][LeftBottom]);
	field[fieldIndex][RightBottom].surfacePartsModelTrans = transform1;

	field[fieldIndex][LeftBottom] = std::move(element);
	field[fieldIndex][LeftBottom].surfacePartsModelTrans = transform2;
}

void BesideFold::Draw()
{
	besideFoldFbxmodel_->Draw(&fieldPlaneTrans_);
}

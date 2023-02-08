#include "VerticalFold.h"


void VerticalFold::Initialize()
{
	//縦折りモデル
	verticalFoldFbxmodel_ = std::make_unique<fbxModel>();
	verticalFoldFbxmodel_->Initialize();
	verticalFoldFbxmodel_->Create("Resources/VerticalFoldPlane", false, false, true, false);
	verticalFoldFbxmodelAnime_ = std::make_unique<fbxAnimation>();
	FbxLoader::GetInstance()->LoadAnimation(verticalFoldFbxmodelAnime_.get(), "Resources/VerticalFoldPlane", "");

	fieldPlaneTrans_.Initialize();
	fieldPlaneTrans_.scale = { 0.1f,0.1f ,0.1f };
	fieldPlaneTrans_.translation = { 0,-10,0 };
}

void VerticalFold::Start(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	//テクスチャをセット
	verticalFoldFbxmodel_->TransTexture("Map02.005", 0, field[fieldIndex][LeftTop].textureData);
	verticalFoldFbxmodel_->TransTexture("Map04.005", 0, field[fieldIndex][RightTop].textureData);
	verticalFoldFbxmodel_->TransTexture("Map01.005", 0, field[fieldIndex][LeftBottom].textureData);
	verticalFoldFbxmodel_->TransTexture("Map03.005", 0, field[fieldIndex][RightBottom].textureData);

	//OBJ版を描画しない
	field[fieldIndex][LeftTop].isDraw = false;
	field[fieldIndex][RightTop].isDraw = false;
	field[fieldIndex][LeftBottom].isDraw = false;
	field[fieldIndex][RightBottom].isDraw = false;

	//面によって座標と回転角を設定
	switch (fieldIndex)
	{
	case Top:

		fieldPlaneTrans_.rotation = { 0.0f,180.0f * AliceMathF::Deg2Rad,0.0f };
		fieldPlaneTrans_.translation = { -0.6f,30.0f,0.0f };

		break;

	case Left:

		fieldPlaneTrans_.rotation = { 90.0f * AliceMathF::Deg2Rad,-90.0f * AliceMathF::Deg2Rad,0.0f };
		fieldPlaneTrans_.translation = { -40.0f,-10.0f,0.0f };

		break;

	case CenterLeft:
		fieldPlaneTrans_.rotation = { 90.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad,0.0f };
		fieldPlaneTrans_.translation = { -0.0f,-10.0f,-40.0f };

		break;

	case CenterRight:

		fieldPlaneTrans_.rotation = { 90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad,0.0f };
		fieldPlaneTrans_.translation = { 40.0f,-10.0f,0.0f };

		break;

	case Right:

		fieldPlaneTrans_.rotation = { 90.0f * AliceMathF::Deg2Rad,0.0f ,0.0f };
		fieldPlaneTrans_.translation = { 0.0f,-10.0f,40.0f };

		break;

	case Bottom:
		fieldPlaneTrans_.rotation = { 180.0f * AliceMathF::Deg2Rad,0.0f * AliceMathF::Deg2Rad,0.0f * AliceMathF::Deg2Rad };
		fieldPlaneTrans_.translation = { -0.0f,-50.0f,0.0f };
		break;
	default:
		break;
	}
}

void VerticalFold::Update(Camera* camera, std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, bool& fieldPlaneDrawFlag)
{
	fieldPlaneAnimeFlam_ += 0.02f;

	fieldPlaneTrans_.TransUpdate(camera);

	if (fieldPlaneAnimeFlam_ >= verticalFoldFbxmodelAnime_->GetAnimeMaxflame() / 2 && !fieldReplaceFlag_)
	{
		Replace(field, fieldIndex);
		fieldReplaceFlag_ = true;
	}

	if (fieldPlaneAnimeFlam_ >= verticalFoldFbxmodelAnime_->GetAnimeMaxflame())
	{
		fieldPlaneDrawFlag = false;
		fieldPlaneAnimeFlam_ = 0.0f;
		fieldReplaceFlag_ = false;

		field[fieldIndex][LeftTop].isDraw = true;
		field[fieldIndex][RightTop].isDraw = true;
		field[fieldIndex][LeftBottom].isDraw = true;
		field[fieldIndex][RightBottom].isDraw = true;
	}

	verticalFoldFbxmodel_->AnimationUpdate(verticalFoldFbxmodelAnime_.get(), fieldPlaneAnimeFlam_);
}

void VerticalFold::Replace(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	FieldElement element;
	Transform transform1;
	Transform transform2;

	//1番と3番を入れ替える
	transform1 = field[fieldIndex][RightTop].surfacePartsModelTrans;
	transform2 = field[fieldIndex][RightBottom].surfacePartsModelTrans;
	element = std::move(field[fieldIndex][RightTop]);

	verticalFoldFbxmodel_->TransTexture("Map04.005", element.textureData->path.c_str(), field[fieldIndex][RightBottom].textureData);
	verticalFoldFbxmodel_->TransTexture("Map03.005", field[fieldIndex][RightBottom].textureData->path.c_str(), element.textureData);

	field[fieldIndex][RightTop] = std::move(field[fieldIndex][RightBottom]);
	field[fieldIndex][RightTop].surfacePartsModelTrans = transform1;

	field[fieldIndex][RightBottom] = std::move(element);
	field[fieldIndex][RightBottom].surfacePartsModelTrans = transform2;


	//2番と4番を入れ替える
	transform1 = field[fieldIndex][LeftTop].surfacePartsModelTrans;
	transform2 = field[fieldIndex][LeftBottom].surfacePartsModelTrans;
	element = std::move(field[fieldIndex][LeftTop]);

	verticalFoldFbxmodel_->TransTexture("Map02.005", element.textureData->path.c_str(), field[fieldIndex][LeftBottom].textureData);
	verticalFoldFbxmodel_->TransTexture("Map01.005", field[fieldIndex][LeftBottom].textureData->path.c_str(), element.textureData);

	field[fieldIndex][LeftTop] = std::move(field[fieldIndex][LeftBottom]);
	field[fieldIndex][LeftTop].surfacePartsModelTrans = transform1;

	field[fieldIndex][LeftBottom] = std::move(element);
	field[fieldIndex][LeftBottom].surfacePartsModelTrans = transform2;
}

void VerticalFold::Draw()
{
	verticalFoldFbxmodel_->Draw(&fieldPlaneTrans_);
}

//void VerticalFold::SetCollider(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, FieldElementIndex fieldElementIndex, int changeNumber)
//{
//	// コリジョンマネージャに追加
//	MeshCollider* meshCollider = new MeshCollider;
//	CollisionManager::GetInstance()->AddCollider(changeNumber, meshCollider);
//	meshCollider->Update(field[fieldIndex][fieldElementIndex].surfacePartsModelTrans.matWorld);
//	meshCollider->ConstructTriangles(field[fieldIndex][fieldElementIndex].surfacePartsModel, field[fieldIndex][fieldElementIndex].surfacePartsModelTrans.matWorld);
//	meshCollider->SetAttribute(COLLISION_ATTR_LANDSHAPE);
//}
#include "Stage.h"
#include"FbxLoader.h"
#include"Input.h"
#include"TextureManager.h"

void Stage::Initialize()
{
	besideFoldFbxmodel_ = std::make_unique<fbxModel>();
	besideFoldFbxmodel_->Initialize();
	besideFoldFbxmodel_->Create("Resources/BesideFoldPlane", false, false, true, false);

	besideFoldFbxmodelAnime_ = std::make_unique<fbxAnimation>();

	FbxLoader::GetInstance()->LoadAnimation(besideFoldFbxmodelAnime_.get(), "Resources/BesideFoldPlane", "");

	verticalFoldFbxmodel_ = std::make_unique<fbxModel>();
	verticalFoldFbxmodel_->Initialize();
	verticalFoldFbxmodel_->Create("Resources/VerticalFoldPlane", false, false, true, false);

	verticalFoldFbxmodelAnime_ = std::make_unique<fbxAnimation>();

	FbxLoader::GetInstance()->LoadAnimation(verticalFoldFbxmodelAnime_.get(), "Resources/VerticalFoldPlane", "");

	fieldPlaneTrans_.Initialize();
	fieldPlaneTrans_.scale = { 0.1f,0.1f ,0.1f };
	fieldPlaneTrans_.translation = { 0,-10,0 };

	int32_t handl = TextureManager::Load("Resources/BesideFoldPlane\\Map01.png");
	field[Top][LeftTop] = { TextureManager::GetTextureData(handl),Field::a };

	handl = TextureManager::Load("Resources/BesideFoldPlane\\Map02.png");
	field[Top][RightTop] = { TextureManager::GetTextureData(handl),Field::b };

	handl = TextureManager::Load("Resources/BesideFoldPlane\\Map03.png");
	field[Top][LeftBottom] = { TextureManager::GetTextureData(handl),Field::c };

	handl = TextureManager::Load("Resources/BesideFoldPlane\\Map04.png");
	field[Top][RightBottom] = { TextureManager::GetTextureData(handl),Field::d };
}

void Stage::FieldPlaneFoldStart(FieldIndex fieldIndex, FoldIndex foldIndex)
{
	foldDirection = foldIndex;

	FieldSurfaceIndex = fieldIndex;

	switch (foldIndex)
	{
	case FoldIndex::Vertical:
		verticalFoldFbxmodel_->TransTexture("Map02.005", 0, field[FieldSurfaceIndex][LeftTop].textureData);
		verticalFoldFbxmodel_->TransTexture("Map04.005", 0, field[FieldSurfaceIndex][RightTop].textureData);
		verticalFoldFbxmodel_->TransTexture("Map01.005", 0, field[FieldSurfaceIndex][LeftBottom].textureData);
		verticalFoldFbxmodel_->TransTexture("Map03.005", 0, field[FieldSurfaceIndex][RightBottom].textureData);
		fieldPlaneTrans_.rotation = { 0.0f,-90.0f * AliceMathF::Deg2Rad,0.0f };
		break;
	case FoldIndex::Beside:
		besideFoldFbxmodel_->TransTexture("Map01.005", 0, field[FieldSurfaceIndex][LeftTop].textureData);
		besideFoldFbxmodel_->TransTexture("Map02.005", 0, field[FieldSurfaceIndex][RightTop].textureData);
		besideFoldFbxmodel_->TransTexture("Map03.005", 0, field[FieldSurfaceIndex][LeftBottom].textureData);
		besideFoldFbxmodel_->TransTexture("Map04.005", 0, field[FieldSurfaceIndex][RightBottom].textureData);
		fieldPlaneTrans_.rotation = { 0,0,0 };
		break;
	default:
		break;
	}

	fieldPlaneDrawFlag = true;
}

void Stage::FieldPlaneFold()
{

	FieldElement element;

	switch (foldDirection)
	{
	case FoldIndex::Vertical://c
		element = field[FieldSurfaceIndex][RightTop];

		verticalFoldFbxmodel_->TransTexture("Map04.005", element.textureData->path.c_str(), field[FieldSurfaceIndex][RightBottom].textureData);
		verticalFoldFbxmodel_->TransTexture("Map03.005", field[FieldSurfaceIndex][RightBottom].textureData->path.c_str(), element.textureData);

		field[FieldSurfaceIndex][RightTop] = field[FieldSurfaceIndex][RightBottom];
		field[FieldSurfaceIndex][RightBottom] = element;

		element = field[FieldSurfaceIndex][LeftTop];

		verticalFoldFbxmodel_->TransTexture("Map02.005", element.textureData->path.c_str(), field[FieldSurfaceIndex][LeftBottom].textureData);
		verticalFoldFbxmodel_->TransTexture("Map01.005", field[FieldSurfaceIndex][LeftBottom].textureData->path.c_str(), element.textureData);

		field[FieldSurfaceIndex][LeftTop] = field[FieldSurfaceIndex][LeftBottom];
		field[FieldSurfaceIndex][LeftBottom] = element;

		break;
	case FoldIndex::Beside://‰¡
		element = field[FieldSurfaceIndex][RightTop];

		besideFoldFbxmodel_->TransTexture("Map02.005", element.textureData->path.c_str(), field[FieldSurfaceIndex][LeftTop].textureData);
		besideFoldFbxmodel_->TransTexture("Map01.005", field[FieldSurfaceIndex][LeftTop].textureData->path.c_str(), element.textureData);

		field[FieldSurfaceIndex][RightTop] = field[FieldSurfaceIndex][LeftTop];
		field[FieldSurfaceIndex][LeftTop] = element;

		element = field[FieldSurfaceIndex][RightBottom];

		besideFoldFbxmodel_->TransTexture("Map04.005", element.textureData->path.c_str(), field[FieldSurfaceIndex][LeftBottom].textureData);
		besideFoldFbxmodel_->TransTexture("Map03.005", field[FieldSurfaceIndex][LeftBottom].textureData->path.c_str(), element.textureData);

		field[FieldSurfaceIndex][RightBottom] = field[FieldSurfaceIndex][LeftBottom];
		field[FieldSurfaceIndex][LeftBottom] = element;

		break;
	default:
		break;
	}


}

void Stage::Update(Camera* camera)
{

	if (fieldPlaneDrawFlag)
	{
		switch (foldDirection)
		{
		case FoldIndex::Vertical://c

			if (fieldPlaneAnimeFlam >= verticalFoldFbxmodelAnime_->GetAnimeMaxflame() / 2 && fieldFoldFlag)
			{
				FieldPlaneFold();
				fieldFoldFlag = false;
			}

			if (fieldPlaneAnimeFlam >= verticalFoldFbxmodelAnime_->GetAnimeMaxflame())
			{
				fieldPlaneDrawFlag = false;
				fieldPlaneAnimeFlam = 0.0f;
				fieldFoldFlag = true;
			}

			verticalFoldFbxmodel_->AnimationUpdate(verticalFoldFbxmodelAnime_.get(), fieldPlaneAnimeFlam);
			break;

		case FoldIndex::Beside://‰¡

			if (fieldPlaneAnimeFlam >= besideFoldFbxmodelAnime_->GetAnimeMaxflame() / 2 && fieldFoldFlag)
			{
				FieldPlaneFold();
				fieldFoldFlag = false;
			}

			if (fieldPlaneAnimeFlam >= besideFoldFbxmodelAnime_->GetAnimeMaxflame())
			{
				fieldPlaneDrawFlag = false;
				fieldPlaneAnimeFlam = 0.0f;
				fieldFoldFlag = true;
			}

			besideFoldFbxmodel_->AnimationUpdate(besideFoldFbxmodelAnime_.get(), fieldPlaneAnimeFlam);

			break;
		default:
			break;
		}

		fieldPlaneAnimeFlam += 0.02f;
	}

	fieldPlaneTrans_.TransUpdate(camera);
}

void Stage::Draw()
{
	//if (foldPlaneDrawFlag)
	{
		switch (foldDirection)
		{
		case FoldIndex::Vertical://c
			verticalFoldFbxmodel_->Draw(&fieldPlaneTrans_);
			break;
		case FoldIndex::Beside://‰¡
			besideFoldFbxmodel_->Draw(&fieldPlaneTrans_);
			break;
		default:
			break;
		}

	}
}

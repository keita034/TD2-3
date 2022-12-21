#include "Stage.h"
#include"FbxLoader.h"
#include"Input.h"
#include"TextureManager.h"

void Stage::Initialize()
{
	//â°ê‹ÇËÉÇÉfÉã
	besideFoldFbxmodel_ = std::make_unique<fbxModel>();
	besideFoldFbxmodel_->Initialize();
	besideFoldFbxmodel_->Create("Resources/BesideFoldPlane", false, false, true, false);
	besideFoldFbxmodelAnime_ = std::make_unique<fbxAnimation>();
	FbxLoader::GetInstance()->LoadAnimation(besideFoldFbxmodelAnime_.get(), "Resources/BesideFoldPlane", "");

	//ècê‹ÇËÉÇÉfÉã
	verticalFoldFbxmodel_ = std::make_unique<fbxModel>();
	verticalFoldFbxmodel_->Initialize();
	verticalFoldFbxmodel_->Create("Resources/VerticalFoldPlane", false, false, true, false);
	verticalFoldFbxmodelAnime_ = std::make_unique<fbxAnimation>();
	FbxLoader::GetInstance()->LoadAnimation(verticalFoldFbxmodelAnime_.get(), "Resources/VerticalFoldPlane", "");

	surfaceFoldFbxmodel_ = std::make_unique<fbxModel>();
	surfaceFoldFbxmodel_->Initialize();
	surfaceFoldFbxmodel_->Create("Resources/SurfaceFold", false, false, true, false);
	surfaceFoldFbxmodelAnime_ = std::make_unique<fbxAnimation>();
	FbxLoader::GetInstance()->LoadAnimation(surfaceFoldFbxmodelAnime_.get(), "Resources/SurfaceFold", "");


	fieldPlaneTrans_.Initialize();
	fieldPlaneTrans_.scale = { 0.1f,0.1f ,0.1f };
	fieldPlaneTrans_.translation = { 0,-10,0 };

	//è„
	int32_t handl;
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
	field[Top][LeftTop] = { TextureManager::GetTextureData(handl),Field::a };
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map02.png");
	field[Top][RightTop] = { TextureManager::GetTextureData(handl),Field::b };
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map03.png");
	field[Top][LeftBottom] = { TextureManager::GetTextureData(handl),Field::c };
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map04.png");
	field[Top][RightBottom] = { TextureManager::GetTextureData(handl),Field::d };

	//ç∂
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map05.png");
	field[Left][LeftTop] = { TextureManager::GetTextureData(handl),Field::e };
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map06.png");
	field[Left][RightTop] = { TextureManager::GetTextureData(handl),Field::f };
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map07.png");
	field[Left][LeftBottom] = { TextureManager::GetTextureData(handl),Field::g };
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map08.png");
	field[Left][RightBottom] = { TextureManager::GetTextureData(handl),Field::h };

	//ê^ÇÒíÜç∂
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map09.png");
	field[CenterLeft][LeftTop] = { TextureManager::GetTextureData(handl),Field::i };
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map010.png");
	field[CenterLeft][RightTop] = { TextureManager::GetTextureData(handl),Field::j };
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map011.png");
	field[CenterLeft][LeftBottom] = { TextureManager::GetTextureData(handl),Field::k };
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map012.png");
	field[CenterLeft][RightBottom] = { TextureManager::GetTextureData(handl),Field::l };

	//ê^ÇÒíÜâE
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map013.png");
	field[CenterRight][LeftTop] = { TextureManager::GetTextureData(handl),Field::n };
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map014.png");
	field[CenterRight][RightTop] = { TextureManager::GetTextureData(handl),Field::m };
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map015.png");
	field[CenterRight][LeftBottom] = { TextureManager::GetTextureData(handl),Field::o };
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map016.png");
	field[CenterRight][RightBottom] = { TextureManager::GetTextureData(handl),Field::p };

	//âE
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map017.png");
	field[Right][LeftTop] = { TextureManager::GetTextureData(handl),Field::r };
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map018.png");
	field[Right][RightTop] = { TextureManager::GetTextureData(handl),Field::s };
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map019.png");
	field[Right][LeftBottom] = { TextureManager::GetTextureData(handl),Field::t };
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map020.png");
	field[Right][RightBottom] = { TextureManager::GetTextureData(handl),Field::u };

	//â∫
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map021.png");
	field[Bottom][LeftTop] = { TextureManager::GetTextureData(handl),Field::v };
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map022.png");
	field[Bottom][RightTop] = { TextureManager::GetTextureData(handl),Field::w };
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map023.png");
	field[Bottom][LeftBottom] = { TextureManager::GetTextureData(handl),Field::x };
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map024.png");
	field[Bottom][RightBottom] = { TextureManager::GetTextureData(handl),Field::y };
}

void Stage::FieldPlaneFoldStart(FieldIndex fieldIndex, FoldIndex foldIndex)
{
	foldDirection = foldIndex;

	FieldSurfaceIndex = fieldIndex;

	switch (foldIndex)
	{
	case FoldIndex::Vertical:
		switch (fieldIndex)
		{
		case Top:
			verticalFoldFbxmodel_->TransTexture("Map02.005", 0, field[Top][LeftTop].textureData);
			verticalFoldFbxmodel_->TransTexture("Map04.005", 0, field[Top][RightTop].textureData);
			verticalFoldFbxmodel_->TransTexture("Map01.005", 0, field[Top][LeftBottom].textureData);
			verticalFoldFbxmodel_->TransTexture("Map03.005", 0, field[Top][RightBottom].textureData);
			fieldPlaneTrans_.rotation = { 0.0f,-90.0f * AliceMathF::Deg2Rad,0.0f };
			break;
		case Left:
			break;
		case CenterLeft:
			break;
		case CenterRight:
			break;
		case Right:
			break;
		case Bottom:
			break;
		default:
			break;
		}

		break;
	case FoldIndex::Beside:
		switch (fieldIndex)
		{
		case Top:
			besideFoldFbxmodel_->TransTexture("Map01.005", 0, field[Top][LeftTop].textureData);
			besideFoldFbxmodel_->TransTexture("Map02.005", 0, field[Top][RightTop].textureData);
			besideFoldFbxmodel_->TransTexture("Map03.005", 0, field[Top][LeftBottom].textureData);
			besideFoldFbxmodel_->TransTexture("Map04.005", 0, field[Top][RightBottom].textureData);
			fieldPlaneTrans_.rotation = { 0,0,0 };
			break;
		case Left:
			break;
		case CenterLeft:
			break;
		case CenterRight:
			break;
		case Right:
			break;
		case Bottom:
			break;
		default:
			break;
		}

		break;
	case FoldIndex::Surface:

		switch (fieldIndex)
		{
		case TopToLeft:
			break;
		case TopToCenterLeft:
			surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Top][LeftTop].textureData);
			surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Top][RightTop].textureData);
			surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Top][LeftBottom].textureData);
			surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Top][RightBottom].textureData);

			surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[CenterLeft][LeftTop].textureData);
			surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[CenterLeft][RightTop].textureData);
			surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[CenterLeft][LeftBottom].textureData);
			surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[CenterLeft][RightBottom].textureData);

			fieldPlaneTrans_.rotation = { 0.0f,-90.0f * AliceMathF::Deg2Rad,0.0f };
			break;
		case TopToCenterRight:
			break;
		case TopToRight:
			break;
		case LeftToTop:
			break;
		case LeftToTopToCenterLeft:
			break;
		case LeftToRight:
			break;
		case LeftToBottom:
			break;
		case CenterLeftToTop:
			break;
		case CenterLeftToLeft:
			break;
		case CenterLeftToCenterRight:
			break;
		case CenterLeftToBottom:
			break;
		case CenterRightToTop:
			break;
		case CenterRightToCenterLeft:
			break;
		case CenterRightToRight:
			break;
		case CenterRightToBottom:
			break;
		case RightToTop:
			break;
		case RightToLeft:
			break;
		case RightToCenterRight:
			break;
		case RightToBottom:
			break;
		case BottomToLeft:
			break;
		case BottomToCenterLeft:
			break;
		case BottomToCenterRight:
			break;
		case BottomToRight:
			break;
		default:
			break;
		}
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
	case FoldIndex::Vertical://èc

		switch (FieldSurfaceIndex)
		{
		case Top:
			//1î‘Ç∆3î‘Çì¸ÇÍë÷Ç¶ÇÈ
			element = std::move(field[Top][RightTop]);
			verticalFoldFbxmodel_->TransTexture("Map04.005", element.textureData->path.c_str(), field[Top][RightBottom].textureData);
			verticalFoldFbxmodel_->TransTexture("Map03.005", field[Top][RightBottom].textureData->path.c_str(), element.textureData);
			field[Top][RightTop] = std::move(field[Top][RightBottom]);
			field[Top][RightBottom] = std::move(element);

			//2î‘Ç∆4î‘Çì¸ÇÍë÷Ç¶ÇÈ
			element = std::move(field[Top][LeftTop]);
			verticalFoldFbxmodel_->TransTexture("Map02.005", element.textureData->path.c_str(), field[Top][LeftBottom].textureData);
			verticalFoldFbxmodel_->TransTexture("Map01.005", field[Top][LeftBottom].textureData->path.c_str(), element.textureData);
			field[Top][LeftTop] = std::move(field[Top][LeftBottom]);
			field[Top][LeftBottom] = std::move(element);

			break;
		case Left:
			break;
		case CenterLeft:
			break;
		case CenterRight:
			break;
		case Right:
			break;
		case Bottom:
			break;
		default:
			break;
		}

		break;
	case FoldIndex::Beside://â°
		switch (FieldSurfaceIndex)
		{
		case Top:
			//1î‘Ç∆2î‘Çì¸ÇÍë÷Ç¶ÇÈ
			element = std::move(field[Top][RightTop]);
			besideFoldFbxmodel_->TransTexture("Map02.005", element.textureData->path.c_str(), field[Top][LeftTop].textureData);
			besideFoldFbxmodel_->TransTexture("Map01.005", field[Top][LeftTop].textureData->path.c_str(), element.textureData);
			field[Top][RightTop] = std::move(field[Top][LeftTop]);
			field[Top][LeftTop] = std::move(element);

			//3î‘Ç∆4î‘Çì¸ÇÍë÷Ç¶ÇÈ
			element = std::move(field[Top][RightBottom]);
			besideFoldFbxmodel_->TransTexture("Map04.005", element.textureData->path.c_str(), field[Top][LeftBottom].textureData);
			besideFoldFbxmodel_->TransTexture("Map03.005", field[Top][LeftBottom].textureData->path.c_str(), element.textureData);
			field[Top][RightBottom] = std::move(field[Top][LeftBottom]);
			field[Top][LeftBottom] = std::move(element);

			break;
		case Left:
			break;
		case CenterLeft:
			break;
		case CenterRight:
			break;
		case Right:
			break;
		case Bottom:
			break;
		default:
			break;
		}

		break;

	case FoldIndex::Surface:

		switch (FieldSurfaceIndex)
		{
		case TopToLeft:
			break;
		case TopToCenterLeft:

			//1î‘Ç∆7î‘Çì¸ÇÍë÷Ç¶ÇÈ
			element = std::move(field[Top][LeftTop]);
			surfaceFoldFbxmodel_->TransTexture("Map01", element.textureData->path.c_str(), field[CenterLeft][LeftBottom].textureData);
			surfaceFoldFbxmodel_->TransTexture("Map07", field[CenterLeft][LeftBottom].textureData->path.c_str(), element.textureData);
			field[Top][LeftTop] = std::move(field[CenterLeft][LeftBottom]);
			field[CenterLeft][LeftBottom] = std::move(element);

			//2î‘Ç∆8î‘Çì¸ÇÍë÷Ç¶ÇÈ
			element = std::move(field[Top][RightTop]);
			surfaceFoldFbxmodel_->TransTexture("Map02", element.textureData->path.c_str(), field[CenterLeft][RightBottom].textureData);
			surfaceFoldFbxmodel_->TransTexture("Map08", field[CenterLeft][RightBottom].textureData->path.c_str(), element.textureData);
			field[Top][RightTop] = std::move(field[CenterLeft][RightBottom]);
			field[CenterLeft][RightBottom] = std::move(element);

			//3î‘Ç∆5î‘Çì¸ÇÍë÷Ç¶ÇÈ
			element = std::move(field[Top][LeftBottom]);
			surfaceFoldFbxmodel_->TransTexture("Map03", element.textureData->path.c_str(), field[CenterLeft][LeftTop].textureData);
			surfaceFoldFbxmodel_->TransTexture("Map05", field[CenterLeft][LeftTop].textureData->path.c_str(), element.textureData);
			field[Top][LeftBottom] = std::move(field[CenterLeft][LeftTop]);
			field[CenterLeft][LeftTop] = std::move(element);

			//4î‘Ç∆6î‘Çì¸ÇÍë÷Ç¶ÇÈ
			element = std::move(field[Top][RightBottom]);
			surfaceFoldFbxmodel_->TransTexture("Map04", element.textureData->path.c_str(), field[CenterLeft][RightTop].textureData);
			surfaceFoldFbxmodel_->TransTexture("Map06", field[CenterLeft][RightTop].textureData->path.c_str(), element.textureData);
			field[Top][RightBottom] = std::move(field[CenterLeft][RightTop]);
			field[CenterLeft][RightTop] = std::move(element);

			break;
		case TopToCenterRight:
			break;
		case TopToRight:
			break;
		case LeftToTop:
			break;
		case LeftToTopToCenterLeft:
			break;
		case LeftToRight:
			break;
		case LeftToBottom:
			break;
		case CenterLeftToTop:
			break;
		case CenterLeftToLeft:
			break;
		case CenterLeftToCenterRight:
			break;
		case CenterLeftToBottom:
			break;
		case CenterRightToTop:
			break;
		case CenterRightToCenterLeft:
			break;
		case CenterRightToRight:
			break;
		case CenterRightToBottom:
			break;
		case RightToTop:
			break;
		case RightToLeft:
			break;
		case RightToCenterRight:
			break;
		case RightToBottom:
			break;
		case BottomToLeft:
			break;
		case BottomToCenterLeft:
			break;
		case BottomToCenterRight:
			break;
		case BottomToRight:
			break;
		default:
			break;
		}
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
		case FoldIndex::Vertical://èc

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

		case FoldIndex::Beside://â°

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

		case FoldIndex::Surface:
			if (fieldPlaneAnimeFlam >= surfaceFoldFbxmodelAnime_->GetAnimeMaxflame() / 2 && fieldFoldFlag)
			{
				FieldPlaneFold();
				fieldFoldFlag = false;
			}

			if (fieldPlaneAnimeFlam >= surfaceFoldFbxmodelAnime_->GetAnimeMaxflame())
			{
				fieldPlaneDrawFlag = false;
				fieldPlaneAnimeFlam = 0.0f;
				fieldFoldFlag = true;
			}

			surfaceFoldFbxmodel_->AnimationUpdate(surfaceFoldFbxmodelAnime_.get(), fieldPlaneAnimeFlam);
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
		case FoldIndex::Vertical://èc
			verticalFoldFbxmodel_->Draw(&fieldPlaneTrans_);
			break;
		case FoldIndex::Beside://â°
			besideFoldFbxmodel_->Draw(&fieldPlaneTrans_);
			break;
		case FoldIndex::Surface:
			surfaceFoldFbxmodel_->Draw(&fieldPlaneTrans_);
			break;
		default:
			break;
		}

	}
}

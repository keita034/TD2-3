#include "Stage.h"
#include"FbxLoader.h"
#include"Input.h"
#include"TextureManager.h"

void Stage::Initialize()
{
	//横折りモデル
	besideFoldFbxmodel_ = std::make_unique<fbxModel>();
	besideFoldFbxmodel_->Initialize();
	besideFoldFbxmodel_->Create("Resources/BesideFoldPlane", false, false, true, false);
	besideFoldFbxmodelAnime_ = std::make_unique<fbxAnimation>();
	FbxLoader::GetInstance()->LoadAnimation(besideFoldFbxmodelAnime_.get(), "Resources/BesideFoldPlane", "");

	//縦折りモデル
	verticalFoldFbxmodel_ = std::make_unique<fbxModel>();
	verticalFoldFbxmodel_->Initialize();
	verticalFoldFbxmodel_->Create("Resources/VerticalFoldPlane", false, false, true, false);
	verticalFoldFbxmodelAnime_ = std::make_unique<fbxAnimation>();
	FbxLoader::GetInstance()->LoadAnimation(verticalFoldFbxmodelAnime_.get(), "Resources/VerticalFoldPlane", "");

	//面折りモデル
	surfaceFoldFbxmodel_ = std::make_unique<fbxModel>();
	surfaceFoldFbxmodel_->Initialize();
	surfaceFoldFbxmodel_->Create("Resources/SurfaceFold", false, false, true, false);
	surfaceFoldFbxmodelAnime_ = std::make_unique<fbxAnimation>();
	FbxLoader::GetInstance()->LoadAnimation(surfaceFoldFbxmodelAnime_.get(), "Resources/SurfaceFold", "");


	fieldPlaneTrans_.Initialize();
	fieldPlaneTrans_.scale = { 0.1f,0.1f ,0.1f };
	fieldPlaneTrans_.translation = { 0,-10,0 };

	uint32_t handl;

#pragma region 上

	//左上
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
	field[Top][LeftTop] = { TextureManager::GetTextureData(handl),Field::a };

	field[Top][LeftTop].surfacePartsModelTrans.Initialize();
	field[Top][LeftTop].surfacePartsModelTrans.translation = { -20.0f,30.0f,20.0f };
	field[Top][LeftTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };

	field[Top][LeftTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map01");

	field[Top][LeftTop].surfacePartsModel = std::make_unique<Model>();
	field[Top][LeftTop].surfacePartsModel->SetModel(field[Top][LeftTop].surfacePartsModelHandle);
	field[Top][LeftTop].surfacePartsModel->SetTexture(handl);

	//右上
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map02.png");
	field[Top][RightTop] = { TextureManager::GetTextureData(handl),Field::b };

	field[Top][RightTop].surfacePartsModelTrans.Initialize();
	field[Top][RightTop].surfacePartsModelTrans.translation = { 20.0f,30.0f,20.0f };
	field[Top][RightTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };

	field[Top][RightTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map02");

	field[Top][RightTop].surfacePartsModel = std::make_unique<Model>();
	field[Top][RightTop].surfacePartsModel->SetModel(field[Top][RightTop].surfacePartsModelHandle);
	field[Top][RightTop].surfacePartsModel->SetTexture(handl);

	//左下
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map03.png");
	field[Top][LeftBottom] = { TextureManager::GetTextureData(handl),Field::c };

	field[Top][LeftBottom].surfacePartsModelTrans.Initialize();
	field[Top][LeftBottom].surfacePartsModelTrans.translation = { -20.0f,30.0f,-20.0f };
	field[Top][LeftBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };

	field[Top][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map03");

	field[Top][LeftBottom].surfacePartsModel = std::make_unique<Model>();
	field[Top][LeftBottom].surfacePartsModel->SetModel(field[Top][LeftBottom].surfacePartsModelHandle);
	field[Top][LeftBottom].surfacePartsModel->SetTexture(handl);

	//右下　
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map04.png");
	field[Top][RightBottom] = { TextureManager::GetTextureData(handl),Field::d };

	field[Top][RightBottom].surfacePartsModelTrans.Initialize();
	field[Top][RightBottom].surfacePartsModelTrans.translation = { 20.0f,30.0f,-20.0f };
	field[Top][RightBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };

	field[Top][RightBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map04");

	field[Top][RightBottom].surfacePartsModel = std::make_unique<Model>();
	field[Top][RightBottom].surfacePartsModel->SetModel(field[Top][RightBottom].surfacePartsModelHandle);
	field[Top][RightBottom].surfacePartsModel->SetTexture(handl);
#pragma endregion

#pragma region 左

	//左上
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map05.png");
	field[Left][LeftTop] = { TextureManager::GetTextureData(handl),Field::e };

	field[Left][LeftTop].surfacePartsModelTrans.Initialize();
	field[Left][LeftTop].surfacePartsModelTrans.translation = { -40.0f,10.0f,20.0f };
	field[Left][LeftTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[Left][LeftTop].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f,90.0f * AliceMathF::Deg2Rad };

	field[Left][LeftTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map05");

	field[Left][LeftTop].surfacePartsModel = std::make_unique<Model>();
	field[Left][LeftTop].surfacePartsModel->SetModel(field[Left][LeftTop].surfacePartsModelHandle);
	field[Left][LeftTop].surfacePartsModel->SetTexture(handl);

	//右上
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map06.png");
	field[Left][RightTop] = { TextureManager::GetTextureData(handl),Field::f };

	field[Left][RightTop].surfacePartsModelTrans.Initialize();
	field[Left][RightTop].surfacePartsModelTrans.translation = { -40.0f,10.0f,-20.0f };
	field[Left][RightTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[Left][RightTop].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f,90.0f * AliceMathF::Deg2Rad };

	field[Left][RightTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map06");

	field[Left][RightTop].surfacePartsModel = std::make_unique<Model>();
	field[Left][RightTop].surfacePartsModel->SetModel(field[Left][RightTop].surfacePartsModelHandle);
	field[Left][RightTop].surfacePartsModel->SetTexture(handl);

	//左下
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map07.png");
	field[Left][LeftBottom] = { TextureManager::GetTextureData(handl),Field::g };

	field[Left][LeftBottom].surfacePartsModelTrans.Initialize();
	field[Left][LeftBottom].surfacePartsModelTrans.translation = { -40.0f,-30.0f,20.0f };
	field[Left][LeftBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[Left][LeftBottom].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f,90.0f * AliceMathF::Deg2Rad };

	field[Left][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map07");

	field[Left][LeftBottom].surfacePartsModel = std::make_unique<Model>();
	field[Left][LeftBottom].surfacePartsModel->SetModel(field[Left][LeftBottom].surfacePartsModelHandle);
	field[Left][LeftBottom].surfacePartsModel->SetTexture(handl);

	//右下　
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map08.png");
	field[Left][RightBottom] = { TextureManager::GetTextureData(handl),Field::h };

	field[Left][RightBottom].surfacePartsModelTrans.Initialize();
	field[Left][RightBottom].surfacePartsModelTrans.translation = { -40.0f,-30.0f,-20.0f };
	field[Left][RightBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[Left][RightBottom].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f,90.0f * AliceMathF::Deg2Rad };

	field[Left][RightBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map08");

	field[Left][RightBottom].surfacePartsModel = std::make_unique<Model>();
	field[Left][RightBottom].surfacePartsModel->SetModel(field[Left][RightBottom].surfacePartsModelHandle);
	field[Left][RightBottom].surfacePartsModel->SetTexture(handl);
#pragma endregion

#pragma region 真ん中左

	//左上
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map09.png");
	field[CenterLeft][LeftTop] = { TextureManager::GetTextureData(handl),Field::i };

	field[CenterLeft][LeftTop].surfacePartsModelTrans.Initialize();
	field[CenterLeft][LeftTop].surfacePartsModelTrans.translation = { -20.0f,10.0f,-40.0f };
	field[CenterLeft][LeftTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[CenterLeft][LeftTop].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f,0.0f };

	field[CenterLeft][LeftTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map09");

	field[CenterLeft][LeftTop].surfacePartsModel = std::make_unique<Model>();
	field[CenterLeft][LeftTop].surfacePartsModel->SetModel(field[CenterLeft][LeftTop].surfacePartsModelHandle);
	field[CenterLeft][LeftTop].surfacePartsModel->SetTexture(handl);

	//右上
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map010.png");
	field[CenterLeft][RightTop] = { TextureManager::GetTextureData(handl),Field::j };

	field[CenterLeft][RightTop].surfacePartsModelTrans.Initialize();
	field[CenterLeft][RightTop].surfacePartsModelTrans.translation = { 20.0f,10.0f,-40.0f };
	field[CenterLeft][RightTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[CenterLeft][RightTop].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f,0.0f };

	field[CenterLeft][RightTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map010");

	field[CenterLeft][RightTop].surfacePartsModel = std::make_unique<Model>();
	field[CenterLeft][RightTop].surfacePartsModel->SetModel(field[CenterLeft][RightTop].surfacePartsModelHandle);
	field[CenterLeft][RightTop].surfacePartsModel->SetTexture(handl);

	//左下
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map011.png");
	field[CenterLeft][LeftBottom] = { TextureManager::GetTextureData(handl),Field::k };

	field[CenterLeft][LeftBottom].surfacePartsModelTrans.Initialize();
	field[CenterLeft][LeftBottom].surfacePartsModelTrans.translation = { -20.0f,-30.0f,-40.0f };
	field[CenterLeft][LeftBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[CenterLeft][LeftBottom].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f,0.0f };

	field[CenterLeft][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map011");

	field[CenterLeft][LeftBottom].surfacePartsModel = std::make_unique<Model>();
	field[CenterLeft][LeftBottom].surfacePartsModel->SetModel(field[CenterLeft][LeftBottom].surfacePartsModelHandle);
	field[CenterLeft][LeftBottom].surfacePartsModel->SetTexture(handl);

	//右下　
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map012.png");
	field[CenterLeft][RightBottom] = { TextureManager::GetTextureData(handl),Field::l };

	field[CenterLeft][RightBottom].surfacePartsModelTrans.Initialize();
	field[CenterLeft][RightBottom].surfacePartsModelTrans.translation = { 20.0f,-30.0f,-40.0f };
	field[CenterLeft][RightBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[CenterLeft][RightBottom].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f,0.0f };

	field[CenterLeft][RightBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map012");

	field[CenterLeft][RightBottom].surfacePartsModel = std::make_unique<Model>();
	field[CenterLeft][RightBottom].surfacePartsModel->SetModel(field[CenterLeft][RightBottom].surfacePartsModelHandle);
	field[CenterLeft][RightBottom].surfacePartsModel->SetTexture(handl);
#pragma endregion

#pragma region 真ん中右

	//左上
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map013.png");
	field[CenterRight][LeftTop] = { TextureManager::GetTextureData(handl),Field::n };

	field[CenterRight][LeftTop].surfacePartsModelTrans.Initialize();
	field[CenterRight][LeftTop].surfacePartsModelTrans.translation = { 40.0f,10.0f,-20.0f };
	field[CenterRight][LeftTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[CenterRight][LeftTop].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f ,270.0f * AliceMathF::Deg2Rad };

	field[CenterRight][LeftTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map013");

	field[CenterRight][LeftTop].surfacePartsModel = std::make_unique<Model>();
	field[CenterRight][LeftTop].surfacePartsModel->SetModel(field[CenterRight][LeftTop].surfacePartsModelHandle);
	field[CenterRight][LeftTop].surfacePartsModel->SetTexture(handl);

	//右上
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map014.png");
	field[CenterRight][RightTop] = { TextureManager::GetTextureData(handl),Field::m };

	field[CenterRight][RightTop].surfacePartsModelTrans.Initialize();
	field[CenterRight][RightTop].surfacePartsModelTrans.translation = { 40.0f,10.0f,20.0f };
	field[CenterRight][RightTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[CenterRight][RightTop].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f ,270.0f * AliceMathF::Deg2Rad };

	field[CenterRight][RightTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map014");

	field[CenterRight][RightTop].surfacePartsModel = std::make_unique<Model>();
	field[CenterRight][RightTop].surfacePartsModel->SetModel(field[CenterRight][RightTop].surfacePartsModelHandle);
	field[CenterRight][RightTop].surfacePartsModel->SetTexture(handl);

	//左下
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map015.png");
	field[CenterRight][LeftBottom] = { TextureManager::GetTextureData(handl),Field::o };

	field[CenterRight][LeftBottom].surfacePartsModelTrans.Initialize();
	field[CenterRight][LeftBottom].surfacePartsModelTrans.translation = { 40.0f,-30.0f,-20.0f };
	field[CenterRight][LeftBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[CenterRight][LeftBottom].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f ,270.0f * AliceMathF::Deg2Rad };

	field[CenterRight][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map015");

	field[CenterRight][LeftBottom].surfacePartsModel = std::make_unique<Model>();
	field[CenterRight][LeftBottom].surfacePartsModel->SetModel(field[CenterRight][LeftBottom].surfacePartsModelHandle);
	field[CenterRight][LeftBottom].surfacePartsModel->SetTexture(handl);

	//右下
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map016.png");
	field[CenterRight][RightBottom] = { TextureManager::GetTextureData(handl),Field::p };

	field[CenterRight][RightBottom].surfacePartsModelTrans.Initialize();
	field[CenterRight][RightBottom].surfacePartsModelTrans.translation = { 40.0f,-30.0f,20.0f };
	field[CenterRight][RightBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[CenterRight][RightBottom].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f ,270.0f * AliceMathF::Deg2Rad };

	field[CenterRight][RightBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map016");

	field[CenterRight][RightBottom].surfacePartsModel = std::make_unique<Model>();
	field[CenterRight][RightBottom].surfacePartsModel->SetModel(field[CenterRight][RightBottom].surfacePartsModelHandle);
	field[CenterRight][RightBottom].surfacePartsModel->SetTexture(handl);

#pragma endregion

#pragma region 右

	//左上
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map017.png");
	field[Right][LeftTop] = { TextureManager::GetTextureData(handl),Field::r };

	field[Right][LeftTop].surfacePartsModelTrans.Initialize();
	field[Right][LeftTop].surfacePartsModelTrans.translation = { 20.0f,10.0f,40.0f };
	field[Right][LeftTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[Right][LeftTop].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad ,0.0f };

	field[Right][LeftTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map017");

	field[Right][LeftTop].surfacePartsModel = std::make_unique<Model>();
	field[Right][LeftTop].surfacePartsModel->SetModel(field[Right][LeftTop].surfacePartsModelHandle);
	field[Right][LeftTop].surfacePartsModel->SetTexture(handl);

	//右上
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map018.png");
	field[Right][RightTop] = { TextureManager::GetTextureData(handl),Field::s };

	field[Right][RightTop].surfacePartsModelTrans.Initialize();
	field[Right][RightTop].surfacePartsModelTrans.translation = { -20.0f,10.0f,40.0f };
	field[Right][RightTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[Right][RightTop].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad ,0.0f };

	field[Right][RightTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map018");

	field[Right][RightTop].surfacePartsModel = std::make_unique<Model>();
	field[Right][RightTop].surfacePartsModel->SetModel(field[Right][RightTop].surfacePartsModelHandle);
	field[Right][RightTop].surfacePartsModel->SetTexture(handl);

	//左下
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map019.png");
	field[Right][LeftBottom] = { TextureManager::GetTextureData(handl),Field::t };

	field[Right][LeftBottom].surfacePartsModelTrans.Initialize();
	field[Right][LeftBottom].surfacePartsModelTrans.translation = { 20.0f,-30.0f,40.0f };
	field[Right][LeftBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[Right][LeftBottom].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad ,0.0f };

	field[Right][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map019");

	field[Right][LeftBottom].surfacePartsModel = std::make_unique<Model>();
	field[Right][LeftBottom].surfacePartsModel->SetModel(field[Right][LeftBottom].surfacePartsModelHandle);
	field[Right][LeftBottom].surfacePartsModel->SetTexture(handl);

	//右下
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map020.png");
	field[Right][RightBottom] = { TextureManager::GetTextureData(handl),Field::u };

	field[Right][RightBottom].surfacePartsModelTrans.Initialize();
	field[Right][RightBottom].surfacePartsModelTrans.translation = { -20.0f,-30.0f,40.0f };
	field[Right][RightBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[Right][RightBottom].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad ,0.0f };

	field[Right][RightBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map020");

	field[Right][RightBottom].surfacePartsModel = std::make_unique<Model>();
	field[Right][RightBottom].surfacePartsModel->SetModel(field[Right][RightBottom].surfacePartsModelHandle);
	field[Right][RightBottom].surfacePartsModel->SetTexture(handl);

#pragma endregion

#pragma region 下

	//左上
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map021.png");
	field[Bottom][LeftTop] = { TextureManager::GetTextureData(handl),Field::v };

	field[Bottom][LeftTop].surfacePartsModelTrans.Initialize();
	field[Bottom][LeftTop].surfacePartsModelTrans.translation = { 20.0f,-50.0f,20.0f };
	field[Bottom][LeftTop].surfacePartsModelTrans.rotation = { 180.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad ,0.0f };
	field[Bottom][LeftTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };

	field[Bottom][LeftTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map021");

	field[Bottom][LeftTop].surfacePartsModel = std::make_unique<Model>();
	field[Bottom][LeftTop].surfacePartsModel->SetModel(field[Bottom][LeftTop].surfacePartsModelHandle);
	field[Bottom][LeftTop].surfacePartsModel->SetTexture(handl);

	//右上
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map022.png");
	field[Bottom][RightTop] = { TextureManager::GetTextureData(handl),Field::w };

	field[Bottom][RightTop].surfacePartsModelTrans.Initialize();
	field[Bottom][RightTop].surfacePartsModelTrans.translation = { -20.0f,-50.0f,20.0f };
	field[Bottom][RightTop].surfacePartsModelTrans.rotation = { 180.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad ,0.0f};
	field[Bottom][RightTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };

	field[Bottom][RightTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map022");

	field[Bottom][RightTop].surfacePartsModel = std::make_unique<Model>();
	field[Bottom][RightTop].surfacePartsModel->SetModel(field[Bottom][RightTop].surfacePartsModelHandle);
	field[Bottom][RightTop].surfacePartsModel->SetTexture(handl);

	//左下
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map023.png");
	field[Bottom][LeftBottom] = { TextureManager::GetTextureData(handl),Field::x };

	field[Bottom][LeftBottom].surfacePartsModelTrans.Initialize();
	field[Bottom][LeftBottom].surfacePartsModelTrans.translation = { 20.0f,-50.0f,-20.0f };
	field[Bottom][LeftBottom].surfacePartsModelTrans.rotation = { 180.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad ,0.0f };
	field[Bottom][LeftBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };

	field[Bottom][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map023");

	field[Bottom][LeftBottom].surfacePartsModel = std::make_unique<Model>();
	field[Bottom][LeftBottom].surfacePartsModel->SetModel(field[Bottom][LeftBottom].surfacePartsModelHandle);
	field[Bottom][LeftBottom].surfacePartsModel->SetTexture(handl);

	//右下
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map024.png");
	field[Bottom][RightBottom] = { TextureManager::GetTextureData(handl),Field::y };

	field[Bottom][RightBottom].surfacePartsModelTrans.Initialize();
	field[Bottom][RightBottom].surfacePartsModelTrans.translation = { -20.0f,-50.0f,-20.0f };
	field[Bottom][RightBottom].surfacePartsModelTrans.rotation = { 180.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad ,0.0f };
	field[Bottom][RightBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };

	field[Bottom][RightBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map024");

	field[Bottom][RightBottom].surfacePartsModel = std::make_unique<Model>();
	field[Bottom][RightBottom].surfacePartsModel->SetModel(field[Bottom][RightBottom].surfacePartsModelHandle);
	field[Bottom][RightBottom].surfacePartsModel->SetTexture(handl);

#pragma endregion

	//verticalFoldFbxmodel_->TransTexture("Map02.005", 0, field[CenterLeft][LeftTop].textureData);
	//verticalFoldFbxmodel_->TransTexture("Map04.005", 0, field[CenterLeft][RightTop].textureData);
	//verticalFoldFbxmodel_->TransTexture("Map01.005", 0, field[CenterLeft][LeftBottom].textureData);
	//verticalFoldFbxmodel_->TransTexture("Map03.005", 0, field[CenterLeft][RightBottom].textureData);

	/*besideFoldFbxmodel_->TransTexture("Map01.005", 0, field[CenterLeft][LeftTop].textureData);
	besideFoldFbxmodel_->TransTexture("Map02.005", 0, field[CenterLeft][RightTop].textureData);
	besideFoldFbxmodel_->TransTexture("Map03.005", 0, field[CenterLeft][LeftBottom].textureData);
	besideFoldFbxmodel_->TransTexture("Map04.005", 0, field[CenterLeft][RightBottom].textureData);

	fieldPlaneTrans_.rotation = { 180.0f * AliceMathF::Deg2Rad,-90.0f * AliceMathF::Deg2Rad,0.0f * AliceMathF::Deg2Rad };
	fieldPlaneTrans_.translation = { -0.0f,-50.0f,0.0f };*/
}

void Stage::FieldPlaneFoldStart(FieldIndex fieldIndex, FoldIndex foldIndex)
{
	foldDirection = foldIndex;

	FieldSurfaceIndex = fieldIndex;

	switch (foldIndex)
	{
	case FoldIndex::Vertical:

		verticalFoldFbxmodel_->TransTexture("Map02.005", 0, field[fieldIndex][LeftTop].textureData);
		verticalFoldFbxmodel_->TransTexture("Map04.005", 0, field[fieldIndex][RightTop].textureData);
		verticalFoldFbxmodel_->TransTexture("Map01.005", 0, field[fieldIndex][LeftBottom].textureData);
		verticalFoldFbxmodel_->TransTexture("Map03.005", 0, field[fieldIndex][RightBottom].textureData);

		field[fieldIndex][LeftTop].isDraw = false;
		field[fieldIndex][RightTop].isDraw = false;
		field[fieldIndex][LeftBottom].isDraw = false;
		field[fieldIndex][RightBottom].isDraw = false;

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

		break;
	case FoldIndex::Beside:

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
	Transform transform1;
	Transform transform2;

	switch (foldDirection)
	{
	case FoldIndex::Vertical://縦
		//1番と3番を入れ替える
		transform1 = field[FieldSurfaceIndex][RightTop].surfacePartsModelTrans;
		transform2 = field[FieldSurfaceIndex][RightBottom].surfacePartsModelTrans;
		element = std::move(field[FieldSurfaceIndex][RightTop]);

		verticalFoldFbxmodel_->TransTexture("Map04.005", element.textureData->path.c_str(), field[FieldSurfaceIndex][RightBottom].textureData);
		verticalFoldFbxmodel_->TransTexture("Map03.005", field[FieldSurfaceIndex][RightBottom].textureData->path.c_str(), element.textureData);

		field[FieldSurfaceIndex][RightTop] = std::move(field[FieldSurfaceIndex][RightBottom]);
		field[FieldSurfaceIndex][RightTop].surfacePartsModelTrans = transform1;

		field[FieldSurfaceIndex][RightBottom] = std::move(element);
		field[FieldSurfaceIndex][RightBottom].surfacePartsModelTrans = transform2;

		//2番と4番を入れ替える
		transform1 = field[FieldSurfaceIndex][LeftTop].surfacePartsModelTrans;
		transform2 = field[FieldSurfaceIndex][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[FieldSurfaceIndex][LeftTop]);

		verticalFoldFbxmodel_->TransTexture("Map02.005", element.textureData->path.c_str(), field[FieldSurfaceIndex][LeftBottom].textureData);
		verticalFoldFbxmodel_->TransTexture("Map01.005", field[FieldSurfaceIndex][LeftBottom].textureData->path.c_str(), element.textureData);

		field[FieldSurfaceIndex][LeftTop] = std::move(field[FieldSurfaceIndex][LeftBottom]);
		field[FieldSurfaceIndex][LeftTop].surfacePartsModelTrans = transform1;

		field[FieldSurfaceIndex][LeftBottom] = std::move(element);
		field[FieldSurfaceIndex][LeftBottom].surfacePartsModelTrans = transform2;

		break;
	case FoldIndex::Beside://横

		//1番と2番を入れ替える
		transform1 = field[FieldSurfaceIndex][RightTop].surfacePartsModelTrans;
		transform2 = field[FieldSurfaceIndex][LeftTop].surfacePartsModelTrans;
		element = std::move(field[FieldSurfaceIndex][RightTop]);

		besideFoldFbxmodel_->TransTexture("Map02.005", element.textureData->path.c_str(), field[FieldSurfaceIndex][LeftTop].textureData);
		besideFoldFbxmodel_->TransTexture("Map01.005", field[FieldSurfaceIndex][LeftTop].textureData->path.c_str(), element.textureData);

		field[FieldSurfaceIndex][RightTop] = std::move(field[FieldSurfaceIndex][LeftTop]);
		field[FieldSurfaceIndex][RightTop].surfacePartsModelTrans = transform1;

		field[FieldSurfaceIndex][LeftTop] = std::move(element);
		field[FieldSurfaceIndex][LeftTop].surfacePartsModelTrans = transform2;

		//3番と4番を入れ替える
		transform1 = field[FieldSurfaceIndex][RightBottom].surfacePartsModelTrans;
		transform2 = field[FieldSurfaceIndex][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[FieldSurfaceIndex][RightBottom]);

		besideFoldFbxmodel_->TransTexture("Map04.005", element.textureData->path.c_str(), field[FieldSurfaceIndex][LeftBottom].textureData);
		besideFoldFbxmodel_->TransTexture("Map03.005", field[FieldSurfaceIndex][LeftBottom].textureData->path.c_str(), element.textureData);

		field[FieldSurfaceIndex][RightBottom] = std::move(field[FieldSurfaceIndex][LeftBottom]);
		field[FieldSurfaceIndex][RightBottom].surfacePartsModelTrans = transform1;

		field[FieldSurfaceIndex][LeftBottom] = std::move(element);
		field[FieldSurfaceIndex][LeftBottom].surfacePartsModelTrans = transform2;

		break;

	case FoldIndex::Surface:

		switch (FieldSurfaceIndex)
		{
		case TopToLeft:
			break;
		case TopToCenterLeft:

			//1番と7番を入れ替える
			element = std::move(field[Top][LeftTop]);
			surfaceFoldFbxmodel_->TransTexture("Map01", element.textureData->path.c_str(), field[CenterLeft][LeftBottom].textureData);
			surfaceFoldFbxmodel_->TransTexture("Map07", field[CenterLeft][LeftBottom].textureData->path.c_str(), element.textureData);
			field[Top][LeftTop] = std::move(field[CenterLeft][LeftBottom]);
			field[CenterLeft][LeftBottom] = std::move(element);

			//2番と8番を入れ替える
			element = std::move(field[Top][RightTop]);
			surfaceFoldFbxmodel_->TransTexture("Map02", element.textureData->path.c_str(), field[CenterLeft][RightBottom].textureData);
			surfaceFoldFbxmodel_->TransTexture("Map08", field[CenterLeft][RightBottom].textureData->path.c_str(), element.textureData);
			field[Top][RightTop] = std::move(field[CenterLeft][RightBottom]);
			field[CenterLeft][RightBottom] = std::move(element);

			//3番と5番を入れ替える
			element = std::move(field[Top][LeftBottom]);
			surfaceFoldFbxmodel_->TransTexture("Map03", element.textureData->path.c_str(), field[CenterLeft][LeftTop].textureData);
			surfaceFoldFbxmodel_->TransTexture("Map05", field[CenterLeft][LeftTop].textureData->path.c_str(), element.textureData);
			field[Top][LeftBottom] = std::move(field[CenterLeft][LeftTop]);
			field[CenterLeft][LeftTop] = std::move(element);

			//4番と6番を入れ替える
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

	//if (Input::GetInstance()->TriggerPush(DIK_A))
	//{
	//	fieldPlaneTrans_.rotation.x += 90.0f * AliceMathF::Deg2Rad;
	//}
	//if (Input::GetInstance()->TriggerPush(DIK_S))
	//{
	//	fieldPlaneTrans_.rotation.x -= 90.0f * AliceMathF::Deg2Rad;

	//}
	//if (Input::GetInstance()->TriggerPush(DIK_D))
	//{
	//	fieldPlaneTrans_.rotation.y += 90.0f * AliceMathF::Deg2Rad;

	//}
	//if (Input::GetInstance()->TriggerPush(DIK_F))
	//{
	//	fieldPlaneTrans_.rotation.y -= 90.0f * AliceMathF::Deg2Rad;

	//}
	//if (Input::GetInstance()->TriggerPush(DIK_G))
	//{
	//	fieldPlaneTrans_.rotation.z += 90.0f * AliceMathF::Deg2Rad;

	//}
	//if (Input::GetInstance()->TriggerPush(DIK_H))
	//{
	//	fieldPlaneTrans_.rotation.z -= 90.0f * AliceMathF::Deg2Rad;

	//}

	if (fieldPlaneDrawFlag)
	{
		switch (foldDirection)
		{
		case FoldIndex::Vertical://縦

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

				field[FieldSurfaceIndex][LeftTop].isDraw = true;
				field[FieldSurfaceIndex][RightTop].isDraw = true;
				field[FieldSurfaceIndex][LeftBottom].isDraw = true;
				field[FieldSurfaceIndex][RightBottom].isDraw = true;
			}

			verticalFoldFbxmodel_->AnimationUpdate(verticalFoldFbxmodelAnime_.get(), fieldPlaneAnimeFlam);
			break;

		case FoldIndex::Beside://横

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

				field[FieldSurfaceIndex][LeftTop].isDraw = true;
				field[FieldSurfaceIndex][RightTop].isDraw = true;
				field[FieldSurfaceIndex][LeftBottom].isDraw = true;
				field[FieldSurfaceIndex][RightBottom].isDraw = true;
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

	for (size_t i = 0; i < field.size(); i++)
	{
		for (size_t j = 0; j < field[Top].size(); j++)
		{
			field[i][j].surfacePartsModelTrans.TransUpdate(camera);
		}
	}
}

void Stage::Draw()
{

	for (size_t i = 0; i < field.size(); i++)
	{
		for (size_t j = 0; j < field[Top].size(); j++)
		{
			field[i][j].Draw();
		}
	}

	if (!Input::GetInstance()->KeepPush(DIK_E))
	{

	}

	if (fieldPlaneDrawFlag)
	{
		switch (foldDirection)
		{
		case FoldIndex::Vertical://縦
			verticalFoldFbxmodel_->Draw(&fieldPlaneTrans_);
			break;
		case FoldIndex::Beside://横
			besideFoldFbxmodel_->Draw(&fieldPlaneTrans_);
			break;
		case FoldIndex::Surface:
			surfaceFoldFbxmodel_->Draw(&fieldPlaneTrans_);
			break;
		default:
			break;
		}
	}

	//verticalFoldFbxmodel_->Draw(&fieldPlaneTrans_);
	//besideFoldFbxmodel_->Draw(&fieldPlaneTrans_);
}

void FieldElement::Draw()
{
	if (isDraw)
	{
		surfacePartsModel->Draw(surfacePartsModelTrans);
	}
}

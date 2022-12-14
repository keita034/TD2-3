#include "Stage.h"
#include"FbxLoader.h"
#include"Input.h"
#include"TextureManager.h"

void Stage::Initialize()
{
	besideFold_ = std::make_unique<BesideFold>();
	besideFold_->Initialize();

	verticalFold_ = std::make_unique<VerticalFold>();
	verticalFold_->Initialize();

	surfaceFold_ = std::make_unique<SurfaceFold>();
	surfaceFold_->Initialize();

	uint32_t handl;

#pragma region ??

	//????
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
	field[Top][LeftTop].textureData = TextureManager::GetTextureData(handl);
	field[Top][LeftTop].field = Field::a;

	field[Top][LeftTop].surfacePartsModelTrans.Initialize();
	field[Top][LeftTop].surfacePartsModelTrans.translation = { -20.0f,30.0f,20.0f };
	field[Top][LeftTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };

	field[Top][LeftTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map01");

	field[Top][LeftTop].surfacePartsModel = std::make_unique<Model>();
	field[Top][LeftTop].surfacePartsModel->SetModel(field[Top][LeftTop].surfacePartsModelHandle);
	field[Top][LeftTop].surfacePartsModel->SetTexture(handl);

	//?E??
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map02.png");
	field[Top][RightTop].textureData = TextureManager::GetTextureData(handl);
	field[Top][RightTop].field = Field::b;

	field[Top][RightTop].surfacePartsModelTrans.Initialize();
	field[Top][RightTop].surfacePartsModelTrans.translation = { 20.0f,30.0f,20.0f };
	field[Top][RightTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };

	field[Top][RightTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map02");

	field[Top][RightTop].surfacePartsModel = std::make_unique<Model>();
	field[Top][RightTop].surfacePartsModel->SetModel(field[Top][RightTop].surfacePartsModelHandle);
	field[Top][RightTop].surfacePartsModel->SetTexture(handl);

	//????
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map03.png");
	field[Top][LeftBottom].textureData = TextureManager::GetTextureData(handl);
	field[Top][LeftBottom].field =  Field::c;

	field[Top][LeftBottom].surfacePartsModelTrans.Initialize();
	field[Top][LeftBottom].surfacePartsModelTrans.translation = { -20.0f,30.0f,-20.0f };
	field[Top][LeftBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };

	field[Top][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map03");

	field[Top][LeftBottom].surfacePartsModel = std::make_unique<Model>();
	field[Top][LeftBottom].surfacePartsModel->SetModel(field[Top][LeftBottom].surfacePartsModelHandle);
	field[Top][LeftBottom].surfacePartsModel->SetTexture(handl);

	//?E???@
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map04.png");
	field[Top][RightBottom].textureData = TextureManager::GetTextureData(handl);
	field[Top][RightBottom].field = Field::d;

	field[Top][RightBottom].surfacePartsModelTrans.Initialize();
	field[Top][RightBottom].surfacePartsModelTrans.translation = { 20.0f,30.0f,-20.0f };
	field[Top][RightBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };

	field[Top][RightBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map04");

	field[Top][RightBottom].surfacePartsModel = std::make_unique<Model>();
	field[Top][RightBottom].surfacePartsModel->SetModel(field[Top][RightBottom].surfacePartsModelHandle);
	field[Top][RightBottom].surfacePartsModel->SetTexture(handl);
#pragma endregion

#pragma region ??

	//????
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map05.png");
	field[Left][LeftTop].textureData = TextureManager::GetTextureData(handl);
	field[Top][LeftTop].field = Field::e;

	field[Left][LeftTop].surfacePartsModelTrans.Initialize();
	field[Left][LeftTop].surfacePartsModelTrans.translation = { -40.0f,10.0f,20.0f };
	field[Left][LeftTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[Left][LeftTop].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f,90.0f * AliceMathF::Deg2Rad };

	field[Left][LeftTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map05");

	field[Left][LeftTop].surfacePartsModel = std::make_unique<Model>();
	field[Left][LeftTop].surfacePartsModel->SetModel(field[Left][LeftTop].surfacePartsModelHandle);
	field[Left][LeftTop].surfacePartsModel->SetTexture(handl);

	//?E??
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map06.png");
	field[Left][RightTop].textureData = TextureManager::GetTextureData(handl);
	field[Left][RightTop].field = Field::f;

	field[Left][RightTop].surfacePartsModelTrans.Initialize();
	field[Left][RightTop].surfacePartsModelTrans.translation = { -40.0f,10.0f,-20.0f };
	field[Left][RightTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[Left][RightTop].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f,90.0f * AliceMathF::Deg2Rad };

	field[Left][RightTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map06");

	field[Left][RightTop].surfacePartsModel = std::make_unique<Model>();
	field[Left][RightTop].surfacePartsModel->SetModel(field[Left][RightTop].surfacePartsModelHandle);
	field[Left][RightTop].surfacePartsModel->SetTexture(handl);

	//????
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map07.png");
	field[Left][LeftBottom].textureData =  TextureManager::GetTextureData(handl);
	field[Left][LeftBottom].field = Field::g;

	field[Left][LeftBottom].surfacePartsModelTrans.Initialize();
	field[Left][LeftBottom].surfacePartsModelTrans.translation = { -40.0f,-30.0f,20.0f };
	field[Left][LeftBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[Left][LeftBottom].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f,90.0f * AliceMathF::Deg2Rad };

	field[Left][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map07");

	field[Left][LeftBottom].surfacePartsModel = std::make_unique<Model>();
	field[Left][LeftBottom].surfacePartsModel->SetModel(field[Left][LeftBottom].surfacePartsModelHandle);
	field[Left][LeftBottom].surfacePartsModel->SetTexture(handl);

	//?E???@
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map08.png");
	field[Left][RightBottom].textureData = TextureManager::GetTextureData(handl);
	field[Left][RightBottom].field = Field::h;

	field[Left][RightBottom].surfacePartsModelTrans.Initialize();
	field[Left][RightBottom].surfacePartsModelTrans.translation = { -40.0f,-30.0f,-20.0f };
	field[Left][RightBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[Left][RightBottom].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f,90.0f * AliceMathF::Deg2Rad };

	field[Left][RightBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map08");

	field[Left][RightBottom].surfacePartsModel = std::make_unique<Model>();
	field[Left][RightBottom].surfacePartsModel->SetModel(field[Left][RightBottom].surfacePartsModelHandle);
	field[Left][RightBottom].surfacePartsModel->SetTexture(handl);
#pragma endregion

#pragma region ?^?񒆍?

	//????
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map09.png");
	field[CenterLeft][LeftTop].textureData =  TextureManager::GetTextureData(handl);
	field[CenterLeft][LeftTop].field = Field::i;

	field[CenterLeft][LeftTop].surfacePartsModelTrans.Initialize();
	field[CenterLeft][LeftTop].surfacePartsModelTrans.translation = { -20.0f,10.0f,-40.0f };
	field[CenterLeft][LeftTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[CenterLeft][LeftTop].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f,0.0f };

	field[CenterLeft][LeftTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map09");

	field[CenterLeft][LeftTop].surfacePartsModel = std::make_unique<Model>();
	field[CenterLeft][LeftTop].surfacePartsModel->SetModel(field[CenterLeft][LeftTop].surfacePartsModelHandle);
	field[CenterLeft][LeftTop].surfacePartsModel->SetTexture(handl);

	//?E??
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map010.png");
	field[CenterLeft][RightTop].textureData = TextureManager::GetTextureData(handl);
	field[CenterLeft][RightTop].field = Field::j;

	field[CenterLeft][RightTop].surfacePartsModelTrans.Initialize();
	field[CenterLeft][RightTop].surfacePartsModelTrans.translation = { 20.0f,10.0f,-40.0f };
	field[CenterLeft][RightTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[CenterLeft][RightTop].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f,0.0f };

	field[CenterLeft][RightTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map010");

	field[CenterLeft][RightTop].surfacePartsModel = std::make_unique<Model>();
	field[CenterLeft][RightTop].surfacePartsModel->SetModel(field[CenterLeft][RightTop].surfacePartsModelHandle);
	field[CenterLeft][RightTop].surfacePartsModel->SetTexture(handl);

	//????
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map011.png");
	field[CenterLeft][LeftBottom].textureData = TextureManager::GetTextureData(handl);
	field[CenterLeft][LeftBottom].field = Field::k;

	field[CenterLeft][LeftBottom].surfacePartsModelTrans.Initialize();
	field[CenterLeft][LeftBottom].surfacePartsModelTrans.translation = { -20.0f,-30.0f,-40.0f };
	field[CenterLeft][LeftBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[CenterLeft][LeftBottom].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f,0.0f };

	field[CenterLeft][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map011");

	field[CenterLeft][LeftBottom].surfacePartsModel = std::make_unique<Model>();
	field[CenterLeft][LeftBottom].surfacePartsModel->SetModel(field[CenterLeft][LeftBottom].surfacePartsModelHandle);
	field[CenterLeft][LeftBottom].surfacePartsModel->SetTexture(handl);

	//?E???@
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map012.png");
	field[CenterLeft][RightBottom].textureData = TextureManager::GetTextureData(handl);
	field[CenterLeft][RightBottom].field = Field::l;

	field[CenterLeft][RightBottom].surfacePartsModelTrans.Initialize();
	field[CenterLeft][RightBottom].surfacePartsModelTrans.translation = { 20.0f,-30.0f,-40.0f };
	field[CenterLeft][RightBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[CenterLeft][RightBottom].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f,0.0f };

	field[CenterLeft][RightBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map012");

	field[CenterLeft][RightBottom].surfacePartsModel = std::make_unique<Model>();
	field[CenterLeft][RightBottom].surfacePartsModel->SetModel(field[CenterLeft][RightBottom].surfacePartsModelHandle);
	field[CenterLeft][RightBottom].surfacePartsModel->SetTexture(handl);
#pragma endregion

#pragma region ?^?񒆉E

	//????
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map013.png");
	field[CenterRight][LeftTop].textureData = TextureManager::GetTextureData(handl);
	field[CenterRight][LeftTop].field = Field::n;

	field[CenterRight][LeftTop].surfacePartsModelTrans.Initialize();
	field[CenterRight][LeftTop].surfacePartsModelTrans.translation = { 40.0f,10.0f,-20.0f };
	field[CenterRight][LeftTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[CenterRight][LeftTop].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f ,270.0f * AliceMathF::Deg2Rad };

	field[CenterRight][LeftTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map013");

	field[CenterRight][LeftTop].surfacePartsModel = std::make_unique<Model>();
	field[CenterRight][LeftTop].surfacePartsModel->SetModel(field[CenterRight][LeftTop].surfacePartsModelHandle);
	field[CenterRight][LeftTop].surfacePartsModel->SetTexture(handl);

	//?E??
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map014.png");
	field[CenterRight][RightTop].textureData = TextureManager::GetTextureData(handl);
	field[CenterRight][RightTop].field = Field::m;

	field[CenterRight][RightTop].surfacePartsModelTrans.Initialize();
	field[CenterRight][RightTop].surfacePartsModelTrans.translation = { 40.0f,10.0f,20.0f };
	field[CenterRight][RightTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[CenterRight][RightTop].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f ,270.0f * AliceMathF::Deg2Rad };

	field[CenterRight][RightTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map014");

	field[CenterRight][RightTop].surfacePartsModel = std::make_unique<Model>();
	field[CenterRight][RightTop].surfacePartsModel->SetModel(field[CenterRight][RightTop].surfacePartsModelHandle);
	field[CenterRight][RightTop].surfacePartsModel->SetTexture(handl);

	//????
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map015.png");
	field[CenterRight][LeftBottom].textureData = TextureManager::GetTextureData(handl);
	field[CenterRight][LeftBottom].field = Field::o;

	field[CenterRight][LeftBottom].surfacePartsModelTrans.Initialize();
	field[CenterRight][LeftBottom].surfacePartsModelTrans.translation = { 40.0f,-30.0f,-20.0f };
	field[CenterRight][LeftBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[CenterRight][LeftBottom].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f ,270.0f * AliceMathF::Deg2Rad };

	field[CenterRight][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map015");

	field[CenterRight][LeftBottom].surfacePartsModel = std::make_unique<Model>();
	field[CenterRight][LeftBottom].surfacePartsModel->SetModel(field[CenterRight][LeftBottom].surfacePartsModelHandle);
	field[CenterRight][LeftBottom].surfacePartsModel->SetTexture(handl);

	//?E??
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map016.png");
	field[CenterRight][RightBottom].textureData = TextureManager::GetTextureData(handl);
	field[CenterRight][RightBottom].field = Field::p;

	field[CenterRight][RightBottom].surfacePartsModelTrans.Initialize();
	field[CenterRight][RightBottom].surfacePartsModelTrans.translation = { 40.0f,-30.0f,20.0f };
	field[CenterRight][RightBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[CenterRight][RightBottom].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f ,270.0f * AliceMathF::Deg2Rad };

	field[CenterRight][RightBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map016");

	field[CenterRight][RightBottom].surfacePartsModel = std::make_unique<Model>();
	field[CenterRight][RightBottom].surfacePartsModel->SetModel(field[CenterRight][RightBottom].surfacePartsModelHandle);
	field[CenterRight][RightBottom].surfacePartsModel->SetTexture(handl);

#pragma endregion

#pragma region ?E

	//????
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map017.png");
	field[Right][LeftTop].textureData = TextureManager::GetTextureData(handl);
	field[Right][LeftTop].field = Field::r;

	field[Right][LeftTop].surfacePartsModelTrans.Initialize();
	field[Right][LeftTop].surfacePartsModelTrans.translation = { 20.0f,10.0f,40.0f };
	field[Right][LeftTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[Right][LeftTop].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad ,0.0f };

	field[Right][LeftTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map017");

	field[Right][LeftTop].surfacePartsModel = std::make_unique<Model>();
	field[Right][LeftTop].surfacePartsModel->SetModel(field[Right][LeftTop].surfacePartsModelHandle);
	field[Right][LeftTop].surfacePartsModel->SetTexture(handl);

	//?E??
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map018.png");
	field[Right][RightTop].textureData = TextureManager::GetTextureData(handl);
	field[Right][RightTop].field = Field::s;

	field[Right][RightTop].surfacePartsModelTrans.Initialize();
	field[Right][RightTop].surfacePartsModelTrans.translation = { -20.0f,10.0f,40.0f };
	field[Right][RightTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[Right][RightTop].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad ,0.0f };

	field[Right][RightTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map018");

	field[Right][RightTop].surfacePartsModel = std::make_unique<Model>();
	field[Right][RightTop].surfacePartsModel->SetModel(field[Right][RightTop].surfacePartsModelHandle);
	field[Right][RightTop].surfacePartsModel->SetTexture(handl);

	//????
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map019.png");
	field[Right][LeftBottom].textureData = TextureManager::GetTextureData(handl);
	field[Right][LeftBottom].field = Field::t;

	field[Right][LeftBottom].surfacePartsModelTrans.Initialize();
	field[Right][LeftBottom].surfacePartsModelTrans.translation = { 20.0f,-30.0f,40.0f };
	field[Right][LeftBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[Right][LeftBottom].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad ,0.0f };

	field[Right][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map019");

	field[Right][LeftBottom].surfacePartsModel = std::make_unique<Model>();
	field[Right][LeftBottom].surfacePartsModel->SetModel(field[Right][LeftBottom].surfacePartsModelHandle);
	field[Right][LeftBottom].surfacePartsModel->SetTexture(handl);

	//?E??
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map020.png");
	field[Right][RightBottom].textureData = TextureManager::GetTextureData(handl);
	field[Right][RightBottom].field = Field::u;

	field[Right][RightBottom].surfacePartsModelTrans.Initialize();
	field[Right][RightBottom].surfacePartsModelTrans.translation = { -20.0f,-30.0f,40.0f };
	field[Right][RightBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };
	field[Right][RightBottom].surfacePartsModelTrans.rotation = { -90.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad ,0.0f };

	field[Right][RightBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map020");

	field[Right][RightBottom].surfacePartsModel = std::make_unique<Model>();
	field[Right][RightBottom].surfacePartsModel->SetModel(field[Right][RightBottom].surfacePartsModelHandle);
	field[Right][RightBottom].surfacePartsModel->SetTexture(handl);

#pragma endregion

#pragma region ??

	//????
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map021.png");
	field[Bottom][LeftTop].textureData = TextureManager::GetTextureData(handl);
	field[Bottom][LeftTop].field = Field::v;

	field[Bottom][LeftTop].surfacePartsModelTrans.Initialize();
	field[Bottom][LeftTop].surfacePartsModelTrans.translation = { 20.0f,-50.0f,20.0f };
	field[Bottom][LeftTop].surfacePartsModelTrans.rotation = { 180.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad ,0.0f };
	field[Bottom][LeftTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };

	field[Bottom][LeftTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map021");

	field[Bottom][LeftTop].surfacePartsModel = std::make_unique<Model>();
	field[Bottom][LeftTop].surfacePartsModel->SetModel(field[Bottom][LeftTop].surfacePartsModelHandle);
	field[Bottom][LeftTop].surfacePartsModel->SetTexture(handl);

	//?E??
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map022.png");
	field[Bottom][RightTop].textureData = TextureManager::GetTextureData(handl);
	field[Bottom][RightTop].field = Field::w;

	field[Bottom][RightTop].surfacePartsModelTrans.Initialize();
	field[Bottom][RightTop].surfacePartsModelTrans.translation = { -20.0f,-50.0f,20.0f };
	field[Bottom][RightTop].surfacePartsModelTrans.rotation = { 180.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad ,0.0f};
	field[Bottom][RightTop].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };

	field[Bottom][RightTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map022");

	field[Bottom][RightTop].surfacePartsModel = std::make_unique<Model>();
	field[Bottom][RightTop].surfacePartsModel->SetModel(field[Bottom][RightTop].surfacePartsModelHandle);
	field[Bottom][RightTop].surfacePartsModel->SetTexture(handl);

	//????
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map023.png");
	field[Bottom][LeftBottom].textureData = TextureManager::GetTextureData(handl);
	field[Bottom][LeftBottom].field = Field::x;

	field[Bottom][LeftBottom].surfacePartsModelTrans.Initialize();
	field[Bottom][LeftBottom].surfacePartsModelTrans.translation = { 20.0f,-50.0f,-20.0f };
	field[Bottom][LeftBottom].surfacePartsModelTrans.rotation = { 180.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad ,0.0f };
	field[Bottom][LeftBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };

	field[Bottom][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map023");

	field[Bottom][LeftBottom].surfacePartsModel = std::make_unique<Model>();
	field[Bottom][LeftBottom].surfacePartsModel->SetModel(field[Bottom][LeftBottom].surfacePartsModelHandle);
	field[Bottom][LeftBottom].surfacePartsModel->SetTexture(handl);

	//?E??
	handl = TextureManager::Load("Resources/FoldPlaneImg\\Map024.png");
	field[Bottom][RightBottom].textureData = TextureManager::GetTextureData(handl);
	field[Bottom][RightBottom].field = Field::y;

	field[Bottom][RightBottom].surfacePartsModelTrans.Initialize();
	field[Bottom][RightBottom].surfacePartsModelTrans.translation = { -20.0f,-50.0f,-20.0f };
	field[Bottom][RightBottom].surfacePartsModelTrans.rotation = { 180.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad ,0.0f };
	field[Bottom][RightBottom].surfacePartsModelTrans.scale = { 40.0f,1.0f,40.0f };

	field[Bottom][RightBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map024");

	field[Bottom][RightBottom].surfacePartsModel = std::make_unique<Model>();
	field[Bottom][RightBottom].surfacePartsModel->SetModel(field[Bottom][RightBottom].surfacePartsModelHandle);
	field[Bottom][RightBottom].surfacePartsModel->SetTexture(handl);

#pragma endregion

}

void Stage::FieldPlaneFoldStart(FieldIndex fieldIndex, FoldIndex foldIndex)
{
	foldDirection = foldIndex;

	FieldSurfaceIndex = fieldIndex;

	switch (foldIndex)
	{
	case FoldIndex::Vertical:

		verticalFold_->Start(field, FieldSurfaceIndex);

		break;
	case FoldIndex::Beside:

		besideFold_->Start(field, FieldSurfaceIndex);

		break;
	case FoldIndex::Surface:

		surfaceFold_->Start(field, FieldSurfaceIndex);
		break;

	default:
		break;
	}

	fieldPlaneDrawFlag = true;
}

void Stage::Update(Camera* camera)
{
	if (fieldPlaneDrawFlag)
	{
		switch (foldDirection)
		{
		case FoldIndex::Vertical://?c

			verticalFold_->Update(camera, field, FieldSurfaceIndex, fieldPlaneDrawFlag);
			break;

		case FoldIndex::Beside://??

			besideFold_->Update(camera, field, FieldSurfaceIndex, fieldPlaneDrawFlag);

			break;

		case FoldIndex::Surface:

			surfaceFold_->Update(camera, field, FieldSurfaceIndex, fieldPlaneDrawFlag);

			break;

		default:
			break;
		}

	}

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
	if (!Input::GetInstance()->KeepPush(DIK_E))
	{
		for (size_t i = 0; i < field.size(); i++)
		{
			for (size_t j = 0; j < field[Top].size(); j++)
			{
				field[i][j].Draw();
			}
		}
	}

	if (fieldPlaneDrawFlag)
	{
		switch (foldDirection)
		{
		case FoldIndex::Vertical://?c
			verticalFold_->Draw();
			break;

		case FoldIndex::Beside://??
			besideFold_->Draw();
			break;

		case FoldIndex::Surface:

			surfaceFold_->Draw();

			break;

		default:
			break;
		}


	}
}



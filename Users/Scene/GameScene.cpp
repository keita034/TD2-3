#include "GameScene.h"

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

void GameScene::Initialize()
{
	input = Input::GetInstance();
	mesh2D = Mesh::GetInstance();

	//ライト初期化
	light.reset(Light::Create());
	light->SetLightColor(lightColor);
	//モデルにライトをセット
	Model::SetLight(light.get());

	camera = std::make_unique<CinemaCamera>();
	camera->Initialize();

	modelHandl = Model::CreateObjModel("Resources/F-15");

	model = std::make_unique<Model>();
	model->SetModel(modelHandl);

	modelTrans.Initialize();
}

void GameScene::Update()
{
	modelTrans.TransUpdate(camera.get());
}

void GameScene::Draw()
{
	model->Draw(&modelTrans);
}
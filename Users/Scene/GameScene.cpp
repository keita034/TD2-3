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

	//���C�g������
	light.reset(Light::Create());
	light->SetLightColor(lightColor);
	//���f���Ƀ��C�g���Z�b�g
	Model::SetLight(light.get());

	camera = std::make_unique<CinemaCamera>();
	camera->Initialize();

}

void GameScene::Update()
{

}

void GameScene::Draw()
{

}
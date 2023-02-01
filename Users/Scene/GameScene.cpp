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
//	camera->SetEye({ -27.0000000f, 226.199310f, -241.000000f });
//	camera->SetTarget({ 0.0f, 85.1993027f, 0.0f });
	camera->Initialize();

	modelHandle = Model::CreateObjModel("Resources/cube");

	model = std::make_unique<Model>();
	model->SetModel(modelHandle);


	spriteHandle = TextureManager::Load("Resources/col.png");
	sprite.reset(Sprite::Create2DSprite(spriteHandle));
	sprite->SetSize({ (float)WindowsApp::GetWindowsSize().width, (float)WindowsApp::GetWindowsSize().height });
	//trans.translation = { WindowsApp::GetWindowsSize().width / 2.0f,WindowsApp::GetWindowsSize().height / 2.0f ,0 };
	trans.translation = { 0,0,0 };
	//trans.scale = {0.01f,0.01f,0.01f };
	trans.Initialize();

	modelHandle1 = Model::CreateObjModel("Resources/cube2");
	modelHandle2 = Model::CreateObjModel("Resources/cube3");

	model->SetBlendModel({ modelHandle1,modelHandle2 });
	

	player = new Player(modelHandle1);
	player->Initialise();
	userCamera = new UserCamera(1280, 720);

}

void GameScene::Update()
{


	if (cameraType == 1) {
		player->SetCameraRot(userCamera->GetCameraRot());
	}
	player->Update(camera.get());
	

	if (input->TriggerPush(DIK_SPACE)) {
		if (cameraType == 0) {
			cameraType = 1;
		}
		else {
			cameraType = 0;
		}
	}

	userCamera->SetCameraType(cameraType);
	userCamera->SetCameraPosition(player->GetPlayerPos());
	userCamera->Update();
	if (cameraType == 0) {

		camera->SetTarget(AliceMathF::Vector3(0.0f,0.0f,0.0f));
		camera->SetEye(camera->GetTarget() + userCamera->GetEye());
		camera->SetUp(userCamera->GetUp());
	}
	else {
		camera->SetEye(userCamera->GetEye());
		camera->SetTarget(userCamera->GetTarget());
	}
	
	


}

void GameScene::Draw()
{

	player->Draw();

}

GameScene* GameScene::GetInstance()
{
	static GameScene instance;
	return &instance;
}

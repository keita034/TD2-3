#include "GameScene.h"
#include"CollisionManager.h"

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

	collisionManager = CollisionManager::GetInstance();

	camera = std::make_unique<CinemaCamera>();
//	camera->SetEye({ -27.0000000f, 226.199310f, -241.000000f });
//	camera->SetTarget({ 0.0f, 85.1993027f, 0.0f });
	camera->Initialize();

	userCamera = new UserCamera(1280, 720);

	stage = std::make_unique<Stage>();

	stage->Initialize(camera.get());

	modelHandle1 = Model::CreateObjModel("Resources/F-15");

	player = new Player(modelHandle1);
	player->Initialise();


	modelHandle2 = Model::CreateObjModel("Resources/Wall");

	//ground = new Ground();
	//ground->Initialise(modelHandle2);
}

void GameScene::Update()
{
	AliceMathF::Vector3 move = { 0.0f,0.0f,0.0f };

	camera->MovePosition(move);

	userCamera->Update();
	camera->SetEye(camera->GetTarget() + userCamera->GetEye());
	camera->SetUp(userCamera->GetUp());

	if (Input::GetInstance()->TriggerPush(DIK_LSHIFT))
	{
		stage->FieldPlaneFoldStart(TopToLeft, FoldIndex::Surface);
	}

	if (Input::GetInstance()->TriggerPush(DIK_RSHIFT))
	{
		stage->FieldPlaneFoldStart(CenterRightToCenterLeft, FoldIndex::Surface);
	}

	if (Input::GetInstance()->TriggerPush(DIK_Z))
	{
		stage->FieldPlaneFoldStart(BottomToRight, FoldIndex::Surface);
	}

	stage->Update(camera.get());

	player->Update(camera.get());

	//ground->Update(camera.get());

	//全ての衝突をチェック
	collisionManager->CheckAllCollisions();
}

void GameScene::Draw()
{
	stage->Draw();

	player->Draw();

	//ground->Draw();
}

GameScene* GameScene::GetInstance()
{
	static GameScene instance;
	return &instance;
}

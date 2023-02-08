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

	//���C�g������
	light.reset(Light::Create());
	light->SetLightColor(lightColor);
	//���f���Ƀ��C�g���Z�b�g
	Model::SetLight(light.get());
	AliceModel::SetLight(light.get());

	collisionManager = CollisionManager::GetInstance();;

	camera = std::make_unique<CinemaCamera>();
//	camera->SetEye({ -27.0000000f, 226.199310f, -241.000000f });
//	camera->SetTarget({ 0.0f, 85.1993027f, 0.0f });
	camera->Initialize();

	titleScene = std::make_unique<TitleScene>();
	resultScene = std::make_unique<ResultScene>();

	titleScene->Initialize();
	resultScene->Initialize();

	stage = std::make_unique<Stage>();

	stage->Initialize(camera.get());

	modelHandle1 = Model::CreateObjModel("Resources/Player");

	player = std::make_unique<Player>(modelHandle1);
	player->Initialise();

	userCamera = std::make_unique<UserCamera>(1280, 720);
	modelHandle2 = Model::CreateObjModel("Resources/Wall");

	skydome = std::make_unique<Skydome>();
	modelHSky = Model::CreateObjModel("Resources/skydome");
	skydome->Initialize(modelHSky);

	goal = std::make_unique<Goal>(modelHandle1);

	//ground = new Ground();
	//ground->Initialise(modelHandle2);
}

void GameScene::Update()
{
	switch (scene)
	{
	case GameScene::title:
#pragma region TitleScene
		titleScene->Update();

		if (input->TriggerPush(DIK_SPACE))
		{
			scene = game;
		}
		break;
#pragma endregion

	case GameScene::game:
#pragma region GameScene
		if (cameraType == 1) {
			player->SetCameraRot(userCamera->GetCameraRot());
		}

		if (collisionManager->GetIsGoal() == true) {
			int a = 0;
			a++;

			cameraType = 0;
		}

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

			camera->SetTarget(AliceMathF::Vector3(0.0f, 0.0f, 0.0f));

			camera->SetEye(camera->GetTarget() + userCamera->GetEye());
			camera->SetUp(userCamera->GetUp());
		}
		else {
			camera->SetEye(userCamera->GetEye());
			camera->SetTarget(userCamera->GetTarget());
		}

		goal->Update(camera.get());

		skydome->Update(camera.get());

		//ground->Update(camera.get());

		//�S�Ă̏Փ˂��`�F�b�N
		collisionManager->CheckAllCollisions();

		if (input->TriggerPush(DIK_RETURN))
		{
			scene = result;
		}
		break;

#pragma endregion

	case GameScene::result:
#pragma region ResultScene
		resultScene->Update();

		if (input->TriggerPush(DIK_SPACE))
		{
			scene = title;
		}
		break;

#pragma endregion

	default:
		break;
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

	//�S�Ă̏Փ˂��`�F�b�N
	collisionManager->CheckAllCollisions();
}

void GameScene::Draw()
{
	switch (scene)
	{
	case GameScene::title:
#pragma region TitleScene
		titleScene->Draw();
		break;

#pragma endregion

	case GameScene::game:
#pragma region GameScene
		skydome->Draw();
		stage->Draw();
		player->Draw();
		goal->Draw();

		break;

#pragma endregion

	case GameScene::result:
#pragma region ResultScene
		resultScene->Draw();
		break;

#pragma endregion

	default:
		break;
	}
}

void GameScene::Finalize()
{
}

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
	audioManager = AudioManager::GetInstance();

	//ライト初期化
	light.reset(Light::Create());
	light->SetLightColor(lightColor);
	//モデルにライトをセット
	Model::SetLight(light.get());
	AliceModel::SetLight(light.get());

	collisionManager = CollisionManager::GetInstance();;

	camera = std::make_unique<CinemaCamera>();
	camera->Initialize();

	titleScene = std::make_unique<TitleScene>();
	resultScene = std::make_unique<ResultScene>();

	titleScene->Initialize();
	resultScene->Initialize();

	stage = std::make_unique<Stage>();

	stage->Initialize(camera.get(), "Resources/SurfaceParts/",
		//左上    //右上    //左下     //右下
		"Map07" , "Map08" , "Map05" , "Map06" ,	//01
		"Map018", "Map020", "Map017", "Map019",	//05
		"Map022", "Map021", "Map024", "Map023",	//06
		"Map013", "Map014", "Map015", "Map016",	//04
		"Map01" , "Map03" , "Map02" , "Map04" ,	//02
		"Map09" , "Map010", "Map011", "Map012"	//03
	);

	modelHandle1 = Model::CreateObjModel("Resources/Player");

	player = std::make_unique<Player>(modelHandle1);
	player->Initialise();

	userCamera = std::make_unique<UserCamera>(1280, 720);

	skydome = std::make_unique<Skydome>();
	modelHSky = Model::CreateObjModel("Resources/skydome");
	skydome->Initialize(modelHSky);

	goal = std::make_unique<Goal>(modelHandle1);

	tatamiTimer = 150;

	//ground = new Ground();
	//ground->Initialise(modelHandle2);

	titleBgmhandl = audioManager->LoadAudio("Resources/sound/BGM/title.mp3", 0.05f);
	gameBgmhandl = audioManager->LoadAudio("Resources/sound/BGM/game.mp3", 0.05f);
	resultBgmhandl = audioManager->LoadAudio("Resources/sound/BGM/result.mp3", 0.05f);

	audioManager->PlayWave(titleBgmhandl, true);
}

void GameScene::Update()
{

	if (isTatamu == 1) {
		tatamiTimer--;
		if (tatamiTimer < 0) {
			tatamiTimer = 150;
			isTatamu = 0;
		}
	}
	switch (scene)
	{
	case GameScene::title:
#pragma region TitleScene
		titleScene->Update();

		if (input->TriggerPush(DIK_SPACE))
		{
			scene = game;
			audioManager->StopWave(titleBgmhandl);
			audioManager->PlayWave(gameBgmhandl, true);

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

		if (isTatamu == 0) {
			if (player->GetPlayerSurfacePos() != 4 && player->GetPlayerSurfacePos() != 3) {
				if (Input::GetInstance()->TriggerPush(DIK_3))
				{
					isTatamu = 1;
					stage->FieldPlaneFoldStart(TopToRight, FoldIndex::Surface);
				}
			}
		}
		
		if (isTatamu == 0) {
			if (player->GetPlayerSurfacePos() != 2 && player->GetPlayerSurfacePos() != 5) {
				if (Input::GetInstance()->TriggerPush(DIK_2))
				{
					isTatamu = 1;
					stage->FieldPlaneFoldStart(CenterLeftToBottom, FoldIndex::Surface);
				}
			}
		}
		if (isTatamu == 0) {
			if (player->GetPlayerSurfacePos() != 0 && player->GetPlayerSurfacePos() != 3) {
				if (Input::GetInstance()->TriggerPush(DIK_1))
				{
					isTatamu = 1;
					stage->FieldPlaneFoldStart(TopToLeft, FoldIndex::Surface);
				}
			}
		}
		stage->Update(camera.get());

		if (isTatamu == 0) {
			player->SetCameraRot(userCamera->GetCameraRotVec3());
			player->Update(camera.get());
		}

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

		//ここにゴールのワールドトランスフォームをぶち込め
		//goal->SetGoal(AliceMathF::GetWorldPosition(stage->GetStageTransform(static_cast < FieldIndex>3, static_cast < FieldElementIndex>1)));//いったんコメントアウトにしとく
		goal->Update(camera.get());

		skydome->Update(camera.get());

		//ground->Update(camera.get());

		//全ての衝突をチェック
		collisionManager->CheckAllCollisions();

		if (collisionManager->GetIsGoal())
		{
			scene = result;
			audioManager->StopWave(gameBgmhandl);
			audioManager->PlayWave(resultBgmhandl, true);
			collisionManager->SetGoal(false);
		}
		break;

#pragma endregion

	case GameScene::result:
#pragma region ResultScene
		resultScene->Update();
		stage->Initialize(camera.get(), "Resources/SurfaceParts/",
			//左上    //右上    //左下     //右下
			"Map07", "Map08", "Map05", "Map06",	//01
			"Map018", "Map020", "Map017", "Map019",	//05
			"Map022", "Map021", "Map024", "Map023",	//06
			"Map013", "Map014", "Map015", "Map016",	//04
			"Map01", "Map03", "Map02", "Map04",	//02
			"Map09", "Map010", "Map011", "Map012"	//03
		);
		player->Initialise();
		camera->Initialize();
		cameraType = 0;
		if (input->TriggerPush(DIK_SPACE))
		{
			scene = title;
			audioManager->StopWave(resultBgmhandl);
			audioManager->PlayWave(titleBgmhandl, true);
		}
		break;

#pragma endregion

	default:
		break;
	}
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

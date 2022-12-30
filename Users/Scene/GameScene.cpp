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
	FbxModel = std::make_unique<fbxModel>();
	FbxModel->Initialize();
	FbxModel->Create("Resources/FBX",false,false,true,false);

	fbxAnim = std::make_unique<fbxAnimation>();
	FbxLoader::GetInstance()->LoadAnimation(fbxAnim.get(), "Resources/FBX","test");

	player = new Player(modelHandle1);
	player->Initialise();
	userCamera = new UserCamera(1280, 720);

}

void GameScene::Update()
{
	AliceMathF::Vector3 move = { 0.0f,0.0f,0.0f };

	fram += 0.03f;
	FbxModel->AnimationUpdate(fbxAnim.get(), fram);
	if (cameraType == 1) {
		player->SetCameraRot(userCamera->GetCameraRot());
	}
	player->Update(camera.get());
	//model->BlendShapeUpdate(fram);

	/*if (input->KeepPush(DIK_W))
	{
		move += {0.0f, 0.0f, 1.0f};
	}
	if (input->KeepPush(DIK_S))
	{
		move -= {0.0f, 0.0f, 1.0f};
	}

	if (input->KeepPush(DIK_A))
	{
		move += {1.0f, 0.0f, 0.0f};
	}
	if (input->KeepPush(DIK_D))
	{
		move -= {1.0f, 0.0f, 0.0f};
	}

	if (input->KeepPush(DIK_Z))
	{
		move += {0.0f, 1.0f, 0.0f};
		camera->MoveTarget({ 0.0f, 1.0f, 0.0f });
	}
	if (input->KeepPush(DIK_X))
	{
		move -= {0.0f, 1.0f, 0.0f};
		camera->MoveTarget({ 0.0f, -1.0f, 0.0f });
	}

	if (input->KeepPush(DIK_UP))
	{
		move += {0.0f, 1.0f, 0.0f};
	}
	if (input->KeepPush(DIK_DOWN))
	{
		move -= {0.0f, 1.0f, 0.0f};
	}

	if (input->KeepPush(DIK_I))
	{
		lns += 0.1f;
		camera->SetFocalLength(lns);
	}
	if (input->KeepPush(DIK_K))
	{
		lns -= 0.1f;
		camera->SetFocalLength(lns);

	}

	camera->MovePosition(move);*/

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
		p = camera->GetTarget();
		p = userCamera->GetEye();
		camera->SetEye(camera->GetTarget() + userCamera->GetEye());
		camera->SetUp(userCamera->GetUp());
	}
	else {
		camera->SetEye(userCamera->GetEye());
		camera->SetTarget(userCamera->GetTarget());
	}


	p = camera->GetEye();
	
	camera->Update();
	trans.TransUpdate(camera.get());

	//trans.GetWorldViewpojCamera()->matWorld =
	//{
	//	1.50888f,0.0f,0.0f ,0.0f
	//	,0.0f, 2.40228f,-0.099317f,-0.0993071f,
	//	0.0f,0.239748f,0.995156f,0.995057f,
	//0.0f,-24.0707,101.402f,101.492 };
	//trans.Update();

	//fram += 0.01f;


}

void GameScene::Draw()
{
	FbxModel->Draw(&trans);
	//model->Draw(&trans);

	//sprite->Draw(trans);

	player->Draw();

}

GameScene* GameScene::GetInstance()
{
	static GameScene instance;
	return &instance;
}

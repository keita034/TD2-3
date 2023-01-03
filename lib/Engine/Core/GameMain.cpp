#include "GameMain.h"

void GameMain::DebugInitialize()
{
	HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD consoleMode = 0;
	GetConsoleMode(stdOut, &consoleMode);
	consoleMode = consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(stdOut, consoleMode);
}

void GameMain::Initialize()
{
	windowsApp = WindowsApp::GetInstance();//WindowsAppクラス読み込み
	windowsApp->CreatWindow();//ウィンドウ生成

	//DirectX初期化処理ここから

	directX12Core = DirectX12Core::GetInstance();//DirectX12Coreクラス読み込み
	directX12Core->DirectXInitialize();//DirectX12初期化
	directX12Core->SetBackScreenColor(0.1f, 0.25f, 0.5f, 0.0f);	//背景の色変更(R,G,B,A)

	//DirectX初期化処理ここまで

	//描画初期化処理ここから
	mesh = Mesh::GetInstance();
	mesh3D = Mesh3D::GetInstance();

	textureManager = TextureManager::GetInstance();
	textureManager->Initialize();

	DefaultMaterial::GetDefaultMaterial()->Initialize();
	//描画初期化処理ここまで

	//その他初期化ここから

	audioManager = AudioManager::GetInstance();
	audioManager->Initialize();

	input = Input::GetInstance();
	input->Initialize();

	fps = new FPS;

	FbxLoader::GetInstance()->Initialize();

	postEffect = std::make_unique<PostEffect>();
	postEffect->PostInitialize();

	Model::CommonInitialize();
	fbxModel::CommonInitialize();
	//その他初期化ここまで

	//シーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize();
}

int GameMain::Ran()
{
	//ゲームループ
	while (true)
	{
#ifdef _DEBUG
		//printf("\x1B[2J");
#endif
		fps->FpsControlBegin();

		if (!windowsApp->MessageWindow())//メッセージ処理
		{
			break;
		}

		//準備処理
		mesh->DrawReset();
		mesh3D->DrawReset();

		//DirectX毎フレーム処理　ここから

		//更新処理

		input->Update();
		audioManager->Update();

		gameScene->Update();

		if (input->TriggerPush(DIK_P))
		{
			if (post)
			{
				post = false;
			}
			else
			{
				post = true;
			}
		}
		if (post)
		{
			//描画処理
			postEffect->PreDrawScen();

			gameScene->Draw();

			postEffect->PostDrawScen();

			directX12Core->BeginDraw();//描画準備
			postEffect->PostDraw();
			//DirectX毎フレーム処理　ここまで
			directX12Core->EndDraw();//描画後処理
		}
		else
		{
			directX12Core->BeginDraw();//描画準備
			gameScene->Draw();
			directX12Core->EndDraw();//描画後処理
		}

		if (input->TriggerPush(DIK_ESCAPE))
		{
			break;
		}

		fps->FpsControlEnd();
	}

	FbxLoader::GetInstance()->Finalize();
	windowsApp->Break();
	directX12Core->Destroy();
	mesh->Destroy();
	mesh3D->Destroy();
	textureManager->Destroy();
	audioManager->Destroy();
	delete fps;

	return 0;
}

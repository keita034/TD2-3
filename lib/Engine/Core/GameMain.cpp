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
	windowsApp = WindowsApp::GetInstance();//WindowsApp�N���X�ǂݍ���
	windowsApp->CreatWindow();//�E�B���h�E����

	//DirectX������������������

	directX12Core = DirectX12Core::GetInstance();//DirectX12Core�N���X�ǂݍ���
	directX12Core->DirectXInitialize();//DirectX12������
	directX12Core->SetBackScreenColor(0.1f, 0.25f, 0.5f, 0.0f);	//�w�i�̐F�ύX(R,G,B,A)

	//DirectX���������������܂�

	//�`�揉����������������
	mesh = Mesh::GetInstance();
	mesh3D = Mesh3D::GetInstance();

	textureManager = TextureManager::GetInstance();
	textureManager->Initialize();

	DefaultMaterial::GetDefaultMaterial()->Initialize();
	//�`�揉�������������܂�

	//���̑���������������

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
	//���̑������������܂�

	//�V�[���̏�����
	gameScene = new GameScene();
	gameScene->Initialize();
}

int GameMain::Ran()
{
	//�Q�[�����[�v
	while (true)
	{
#ifdef _DEBUG
		//printf("\x1B[2J");
#endif
		fps->FpsControlBegin();

		if (!windowsApp->MessageWindow())//���b�Z�[�W����
		{
			break;
		}

		//��������
		mesh->DrawReset();
		mesh3D->DrawReset();

		//DirectX���t���[�������@��������

		//�X�V����

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
			//�`�揈��
			postEffect->PreDrawScen();

			gameScene->Draw();

			postEffect->PostDrawScen();

			directX12Core->BeginDraw();//�`�揀��
			postEffect->PostDraw();
			//DirectX���t���[�������@�����܂�
			directX12Core->EndDraw();//�`��㏈��
		}
		else
		{
			directX12Core->BeginDraw();//�`�揀��
			gameScene->Draw();
			directX12Core->EndDraw();//�`��㏈��
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

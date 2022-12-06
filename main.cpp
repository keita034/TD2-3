//#DirectX�̂��
#include"ErrorException.h"


//����.h
#include"WindowsApp.h"
#include"Input.h"
#include"Controller.h"
#include"DirectX12Core.h"
#include"Mesh.h"
#include"3DMesh.h"
#include"Camera.h"
#include"GameScene.h"
#include"FPS.h"
#include"TextureManager.h"
#include"DefaultMaterial.h"
#include"AudioManager.h"
#include"FbxLoader.h"
#include"PostEffect.h"

//pragma comment


//using namespace

using namespace AliceMathF;

#ifdef _DEBUG
int main()
{
	HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD consoleMode = 0;
	GetConsoleMode(stdOut, &consoleMode);
	consoleMode = consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(stdOut, consoleMode);
#else
#include<windows.h>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#endif


	WindowsApp* windowsApp = WindowsApp::GetInstance();//WindowsApp�N���X�ǂݍ���
	windowsApp->CreatWindow();//�E�B���h�E����

	//DirectX������������������

	DirectX12Core* DirectX12Core = DirectX12Core::GetInstance();//DirectX12Core�N���X�ǂݍ���
	DirectX12Core->DirectXInitialize();//DirectX12������
	DirectX12Core->SetBackScreenColor(0.1f, 0.25f, 0.5f, 0.0f);	//�w�i�̐F�ύX(R,G,B,A)

	//DirectX���������������܂�

	//�`�揉����������������
	Mesh* mesh = Mesh::GetInstance();
	Mesh3D* mesh3D = Mesh3D::GetInstance();

	TextureManager* textureManager = TextureManager::GetInstance();
	textureManager->Initialize();

	DefaultMaterial::GetDefaultMaterial()->Initialize();
	//�`�揉�������������܂�

	//���̑���������������

	AudioManager* audioManager = AudioManager::GetInstance();
	audioManager->Initialize();

	Input* input = Input::GetInstance();
	input->Initialize();

	FPS* fps = new FPS;

	FbxLoader::GetInstance()->Initialize();

	std::unique_ptr<PostEffect> postEffect = std::make_unique<PostEffect>();
	postEffect->PostInitialize();

	Model::CommonInitialize();

	//���̑������������܂�

	//�V�[���̏�����
	GameScene* gameScene = GameScene::GetInstance();
	gameScene->Initialize();

	bool post = true;

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

			DirectX12Core->BeginDraw();//�`�揀��
			postEffect->PostDraw();
			//DirectX���t���[�������@�����܂�
			DirectX12Core->EndDraw();//�`��㏈��
		}
		else
		{
			DirectX12Core->BeginDraw();//�`�揀��
			gameScene->Draw();
			DirectX12Core->EndDraw();//�`��㏈��
		}


		if (input->TriggerPush(DIK_ESCAPE))
		{
			break;
		}

		fps->FpsControlEnd();
	}

	FbxLoader::GetInstance()->Finalize();
	windowsApp->Break();
	DirectX12Core->Destroy();
	mesh->Destroy();
	mesh3D->Destroy();
	textureManager->Destroy();
	audioManager->Destroy();
	delete fps;
	return 0;
}
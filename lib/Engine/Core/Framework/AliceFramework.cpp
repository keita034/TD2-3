#include "AliceFramework.h"

void AliceFramework::DebugInitialize()
{
	HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD consoleMode = 0;
	GetConsoleMode(stdOut, &consoleMode);
	consoleMode = consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(stdOut, consoleMode);
}

void AliceFramework::Initialize()
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

	Model::CommonInitialize();
	fbxModel::CommonInitialize();

	imGuiManager = std::make_unique<ImGuiManager>();
	imGuiManager->Initialize(windowsApp, directX12Core);
	
	sceneManager = SceneManager::GetInstance();

	postEffectManager = PostEffectManager::GetInstance();

	postEffectManager->Initialize();
	//���̑������������܂�
}

void AliceFramework::Finalize()
{
	imGuiManager->Finalize();
	imGuiManager.release();

	FbxLoader::GetInstance()->Finalize();
	windowsApp->Break();
	directX12Core->Destroy();
	mesh->Destroy();
	mesh3D->Destroy();
	textureManager->Destroy();
	audioManager->Destroy();
	delete fps;
}

void AliceFramework::Update()
{
	fps->FpsControlBegin();
	//��������
	mesh->DrawReset();
	mesh3D->DrawReset();

	input->Update();
	audioManager->Update();

	imGuiManager->Bigin();

	sceneManager->Update();

	imGuiManager->End();
}

void AliceFramework::PostUpdate()
{
	fps->FpsControlEnd();
}

void AliceFramework::Draw()
{
	if (postEffectManager->IsAalid())
	{
		//�`�揈��
		postEffectManager->PreDrawScen();

		sceneManager->Draw();

		postEffectManager->PostDrawScen();

		postEffectManager->Update();

		directX12Core->BeginDraw();//�`�揀��
		postEffectManager->Draw();
		imGuiManager->Draw();
		//DirectX���t���[�������@�����܂�
		directX12Core->EndDraw();//�`��㏈��
	}
	else
	{
		directX12Core->BeginDraw();//�`�揀��

		sceneManager->Draw();

		imGuiManager->Draw();

		directX12Core->EndDraw();//�`��㏈��
	}
}

bool AliceFramework::IsEndRequst()
{
	return !windowsApp->MessageWindow()|| input->TriggerPush(DIK_ESCAPE);
}

void AliceFramework::Run()
{
	//����������
	Initialize();

	// �Q�[�����[�v
	while (true)
	{
		//�X�V����
		Update();



		if (IsEndRequst())
		{
			break;
		}

		//�`�揈��
		Draw();

		PostUpdate();
	}

	//�Q�[���̏I��
	Finalize();
}

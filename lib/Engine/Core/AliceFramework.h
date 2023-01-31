#pragma once
#include"TextureManager.h"
#include"AudioManager.h"
#include"ImGuiManager.h"
#include"DefaultMaterial.h"
#include"FPS.h"
#include"FbxLoader.h"
#include"Mesh.h"
#include"3DMesh.h"
#include"WindowsApp.h"
#include"Input.h"
#include"DirectX12Core.h"
#include"SceneManager.h"
#include"AbstractSceneFactory.h"
#include"PostEffectManager.h"
class AliceFramework
{
protected:

	WindowsApp* windowsApp = nullptr;

	DirectX12Core* directX12Core = nullptr;

	Mesh* mesh = nullptr;

	Mesh3D* mesh3D = nullptr;

	TextureManager* textureManager = nullptr;

	AudioManager* audioManager = nullptr;

	Input* input = nullptr;

	FPS* fps = nullptr;

	std::unique_ptr<ImGuiManager> imGuiManager;

	SceneManager* sceneManager = nullptr;

	//�V�[���t�@�N�g���[
	AbstractSceneFactory* sceneFactory = nullptr;

	PostEffectManager* postEffectManager = nullptr;

	//�I���t���O
	bool endRequst;
	char PADING1[7]{};

public:

	virtual ~AliceFramework() = default;
	AliceFramework() = default;

	static void DebugInitialize();

	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// �I��
	/// </summary>
	virtual void Finalize();

	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	virtual void Update();

	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	virtual void PostUpdate();

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();

	virtual bool IsEndRequst();

	/// <summary>
	/// ���s
	/// </summary>
	void Run();

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	AliceFramework& operator=(const AliceFramework&) = delete;
	AliceFramework(const AliceFramework&) = delete;
};

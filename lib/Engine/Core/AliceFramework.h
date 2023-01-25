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

class AliceFramework
{
protected:

	//�I���t���O
	bool endRequst;

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

public:

	virtual ~AliceFramework() = default;

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
	virtual void Draw() = 0;

	virtual bool IsEndRequst();

	/// <summary>
	/// ���s
	/// </summary>
	void Run();
};


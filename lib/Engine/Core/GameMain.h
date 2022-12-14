#pragma once

//#DirectXのやつ
#include"ErrorException.h"


//自作.h
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

class GameMain
{
private:

	WindowsApp* windowsApp = nullptr;

	DirectX12Core* directX12Core = nullptr;

	Mesh* mesh = nullptr;

	Mesh3D* mesh3D = nullptr;

	TextureManager* textureManager = nullptr;

	AudioManager* audioManager = nullptr;

	Input* input = nullptr;

	FPS* fps = nullptr;

	std::unique_ptr<PostEffect> postEffect;

	GameScene* gameScene = nullptr;

	bool post = true;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	static void DebugInitialize();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	int Ran();

};


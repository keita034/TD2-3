#pragma once

//#DirectX‚Ì‚â‚Â
#include"ErrorException.h"


//©ì.h
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
	/// ‰Šú‰»
	/// </summary>
	static void DebugInitialize();

	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize();

	/// <summary>
	/// XV
	/// </summary>
	int Ran();

};


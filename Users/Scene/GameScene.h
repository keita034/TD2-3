#pragma once

#include"ErrorException.h"
#include"Camera.h"
#include"Sprite2D.h"
#include"Sprite3D.h"
#include"Collision.h"
#include"Input.h"
#include"BasicParticle.h"
#include"RainParticle.h"
#include"ParticleEmitter.h"
#include"Light.h"
#include"Mesh.h"
#include"3DMesh.h"
#include"Transform.h"
#include"DefaultMaterial.h"
#include"AudioManager.h"
#include"Button.h"
#include"Cursor.h"
#include"fbxModel.h"
#include"fbxAnimation.h"
#include"FbxLoader.h"
#include"Model.h"
#include "CinemaCamera.h"
#include"UserCamera.h"

class GameScene
{
private:

	Mesh* mesh2D = nullptr;
	Mesh3D* mesh3D = nullptr;
	Input* input = nullptr;

	std::unique_ptr<Light> light;
	AliceMathF::Vector4 lightColor = { 1, 1, 1, 1 };

	std::unique_ptr<CinemaCamera> camera;

	uint32_t modelHandle = 0u;

	std::unique_ptr<Model> model;

	std::unique_ptr<fbxModel> FbxModel;

	std::unique_ptr<fbxAnimation> fbxAnim;

	Transform trans;

	std::unique_ptr<Sprite2D> sprite;
	uint32_t spriteHandle = 0u;

	uint32_t modelHandle1 = 0u;
	uint32_t modelHandle2 = 0u;

	float lns = 70.0f;

	float fram = 0.0f;

	UserCamera* userCamera = nullptr;

public:

	GameScene();
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//ゲッター
	static GameScene* GetInstance();

private:

	//コピーコンストラクタ・代入演算子削除
	GameScene& operator=(const GameScene&) = delete;
	GameScene(const GameScene&) = delete;
};
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
#include "Stage.h"
#include"Player.h"
#include "TouchableObject.h"
#include "Ground.h"
#include "BaseScene.h"
#include "Skydome.h"

#include "TitleScene.h"
#include "ResultScene.h"

#include "Goal.h"

class CollisionManager;

class GameScene : public BaseScene
{
private:
	enum SCENE
	{
		title,
		game,
		result
	};

	SCENE scene = SCENE::title;

private:

	Mesh* mesh2D = nullptr;
	Mesh3D* mesh3D = nullptr;
	Input* input = nullptr;

	std::unique_ptr<Light> light;
	AliceMathF::Vector4 lightColor = { 1, 1, 1, 1 };

	std::unique_ptr<CinemaCamera> camera;

	std::unique_ptr<UserCamera> userCamera = nullptr;
	int cameraType = 0;

	std::unique_ptr<TitleScene> titleScene;
	std::unique_ptr<ResultScene> resultScene;

	std::unique_ptr<Stage> stage;

	uint32_t modelHandle1 = 0u;
	std::unique_ptr<Player> player;

	TouchableObject* objGround = nullptr;

	CollisionManager* collisionManager = nullptr;

	uint32_t modelHandle2 = 0u;

	std::unique_ptr<Skydome> skydome;
	uint32_t modelHSky = 0u;

	std::unique_ptr<Goal> goal;

	int tatamiTimer = 0;
	int isTatamu = 0;

public:

	GameScene();
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize() override;

private:

	//コピーコンストラクタ・代入演算子削除
	GameScene& operator=(const GameScene&) = delete;
	GameScene(const GameScene&) = delete;
};
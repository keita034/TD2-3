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

#include "Goal.h"

class CollisionManager;

class GameScene : public BaseScene
{
private:

	Mesh* mesh2D = nullptr;
	Mesh3D* mesh3D = nullptr;
	Input* input = nullptr;

	std::unique_ptr<Light> light;
	AliceMathF::Vector4 lightColor = { 1, 1, 1, 1 };

	std::unique_ptr<CinemaCamera> camera;

	std::unique_ptr<UserCamera> userCamera = nullptr;
	int cameraType = 0;

	std::unique_ptr<Stage> stage;

	uint32_t modelHandle1 = 0u;
	std::unique_ptr<Player> player;

	TouchableObject* objGround = nullptr;


	CollisionManager* collisionManager = nullptr;

	uint32_t modelHandle2 = 0u;
	//Ground* ground = nullptr;

	std::unique_ptr<Goal> goal;

public:

	GameScene();
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize() override;

private:

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	GameScene& operator=(const GameScene&) = delete;
	GameScene(const GameScene&) = delete;
};
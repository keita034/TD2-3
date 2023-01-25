#pragma once
#include"BaseScene.h"
#include"AbstractSceneFactory.h"

/// <summary>
/// �V�[���Ǘ�
/// </summary>
class SceneManager
{
private:

	//���̃V�[��(���s���̃V�[��)
	BaseScene* scene = nullptr;

	//���̃V�[��
	BaseScene* nextScene = nullptr;

	AbstractSceneFactory* sceneFactory = nullptr;

public:

	static SceneManager* GetInstance();

	//���̃V�[���\��
	void ChangeScene(const std::string& sceneName);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	void SetSceneFactory(AbstractSceneFactory* factory);

private:

	SceneManager() = default;
	~SceneManager();
};


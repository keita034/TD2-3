#include "SceneManager.h"
#include"PostEffectManager.h"
SceneManager::~SceneManager()
{
	scene->Finalize();
	delete scene;
}

SceneManager* SceneManager::GetInstance()
{
	static SceneManager instance;

	return &instance;
}

void SceneManager::ChangeScene(const std::string& sceneName)
{
	assert(sceneFactory);
	assert(nextScene == nullptr);

	nextScene = sceneFactory->CreateScene(sceneName);

	//���̃V�[���̗\�񂪂���Ȃ�
	if (nextScene)
	{
		//���V�[���̏I��
		if (scene)
		{
			scene->Finalize();
			PostEffectManager::GetInstance()->Finalize();
			delete scene;
		}

		//�V�[���؂�ւ�
		scene = nextScene;
		nextScene = nullptr;

		//�V�[���}�l�[�W���[���Z�b�g
		scene->SetSceneManager(this);

		//���̃V�[��������������
		scene->Initialize();
		PostEffectManager::GetInstance()->PostInitialize();
	}
}

void SceneManager::Update()
{
	scene->Update();
}

void SceneManager::Draw()
{
	scene->Draw();
}

void SceneManager::SetSceneFactory(AbstractSceneFactory* factory)
{
	sceneFactory = factory;
}

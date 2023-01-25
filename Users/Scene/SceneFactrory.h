#pragma once
#include"AbstractSceneFactory.h"

/// <summary>
/// �V�[���H��
/// </summary>
class SceneFactrory:public AbstractSceneFactory
{
public:

	static SceneFactrory* GetInstance();

	/// <summary>
	/// �V�[������
	/// </summary>
	/// <param name="sceneName">�V�[����</param>
	/// <returns>���������V�[��</returns>
	BaseScene* CreateScene(const std::string& sceneName) override;
};


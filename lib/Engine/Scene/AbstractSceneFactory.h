#pragma once
#include"ErrorException.h"
#include"BaseScene.h"

/// <summary>
/// �V�[���H��(�T�O)
/// </summary>
class AbstractSceneFactory
{
public:

	virtual ~AbstractSceneFactory() = default;

	//�V�[������
	virtual BaseScene* CreateScene(const std::string& sceneName) = 0;
};


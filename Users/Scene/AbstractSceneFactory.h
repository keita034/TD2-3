#pragma once
#include"ErrorException.h"
#include"BaseScene.h"

/// <summary>
/// ƒV[ƒ“Hê(ŠT”O)
/// </summary>
class AbstractSceneFactory
{
public:

	virtual ~AbstractSceneFactory() = default;

	//ƒV[ƒ“¶¬
	virtual BaseScene* CreateScene(const std::string& sceneName) = 0;
};


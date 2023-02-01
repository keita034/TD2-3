#pragma once
#include"ErrorException.h"
#include"BasePostEffect.h"

class AbstractPostEffectFactory
{
public:

	virtual ~AbstractPostEffectFactory() = default;

	//�V�[������
	virtual BasePostEffect* CreatePostEffect(const std::string& postEffectName) = 0;
};


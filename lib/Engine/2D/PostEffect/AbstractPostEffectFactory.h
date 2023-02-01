#pragma once
#include"ErrorException.h"
#include"BasePostEffect.h"

class AbstractPostEffectFactory
{
public:

	virtual ~AbstractPostEffectFactory() = default;

	//ÉVÅ[Éìê∂ê¨
	virtual BasePostEffect* CreatePostEffect(const std::string& postEffectName) = 0;
};


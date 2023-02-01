#include "PostEffectFactory.h"
#include "LutPostEffect.h"
#include "VignettePostEffect.h"

PostEffectFactory* PostEffectFactory::GetInstance()
{
	static PostEffectFactory instance;
	return &instance;
}

BasePostEffect* PostEffectFactory::CreatePostEffect(const std::string& postEffectName)
{
	BasePostEffect* postEffect = nullptr;

	if (postEffectName == "LUT")
	{
		postEffect = LutPostEffect::GetInstance();
	}
	else if (postEffectName == "VIGNETTE")
	{
		postEffect = VignettePostEffect::GetInstance();
	}

	return postEffect;
}

#include"fbxAnimation.h"

float fbxAnimation::GetAnimeMaxflame()
{
	return static_cast<float>(mAnimation->mAnimations[0]->mDuration);
}

#pragma once
#include "BasePostEffect.h"
#include"ConstantBuffer.h"

class GaussianYBlurPostEffect final :public BasePostEffect
{
private:

	std::unique_ptr<ConstantBuffer> weightBuff;

	std::array<float, 8> weight;

public:

	void Initialize() override;

	void PostUpdate(RenderTarget* mainRenderTarget) override;

	const std::string& GetType()override;

	void SetWeight(std::array<float, 8>& weightPtr);

	GaussianYBlurPostEffect() = default;
	~GaussianYBlurPostEffect() = default;

private:

	void Draw(RenderTarget* mainRenderTarget)override;

	void MainRenderTargetDraw(RenderTarget* mainRenderTarget)override;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	GaussianYBlurPostEffect& operator=(const GaussianYBlurPostEffect&) = delete;
	GaussianYBlurPostEffect(const GaussianYBlurPostEffect&) = delete;
};

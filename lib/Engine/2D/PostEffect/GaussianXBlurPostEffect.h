#pragma once
#include "BasePostEffect.h"
#include"ConstantBuffer.h"

class GaussianXBlurPostEffect final :public BasePostEffect
{
private:

	std::unique_ptr<ConstantBuffer> weightBuff;

	std::array<float, 8> weight;

public:

	void Initialize() override;

	void PostUpdate(RenderTarget* mainRenderTarget) override;

	const std::string& GetType()override;

	void SetWeight(std::array<float, 8>& weightPtr);

	GaussianXBlurPostEffect() = default;
	~GaussianXBlurPostEffect() = default;

private:

	void Draw(RenderTarget* mainRenderTarget)override;

	void MainRenderTargetDraw(RenderTarget* mainRenderTarget)override;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	GaussianXBlurPostEffect& operator=(const GaussianXBlurPostEffect&) = delete;
	GaussianXBlurPostEffect(const GaussianXBlurPostEffect&) = delete;

};
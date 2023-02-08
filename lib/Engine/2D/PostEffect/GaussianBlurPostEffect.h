#pragma once
#include"BasePostEffect.h"
#include"ConstantBuffer.h"
#include"AliceMathUtility.h"
#include "GaussianYBlurPostEffect.h"
#include "GaussianXBlurPostEffect.h"

class GaussianBlurPostEffect final: public BasePostEffect
{
private:

	const size_t NUM_WEIGHTS = 8;

	std::array<float, 8> weight{};

	std::unique_ptr<GaussianXBlurPostEffect>gaussianXBlurPostEffect;
	std::unique_ptr<GaussianYBlurPostEffect>gaussianYBlurPostEffect;

public:

	static GaussianBlurPostEffect* GetInstance();

	//������
	void Initialize() override;

	//�X�V
	void PostUpdate(RenderTarget* mainRenderTarget) override;

	/// <summary>
	/// �^�C�v���擾
	/// </summary>
	const std::string& GetType()override;

	void UpdateWeightsTable(float blurPower);
private:

	void Draw(RenderTarget* mainRenderTarget)override;

	void MainRenderTargetDraw(RenderTarget* mainRenderTarget)override;
	GaussianBlurPostEffect() = default;
	~GaussianBlurPostEffect() = default;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	GaussianBlurPostEffect& operator=(const GaussianBlurPostEffect&) = delete;
	GaussianBlurPostEffect(const GaussianBlurPostEffect&) = delete;
};


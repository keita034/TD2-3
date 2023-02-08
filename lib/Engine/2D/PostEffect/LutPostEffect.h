#pragma once
#include "BasePostEffect.h"
#include"ConstantBuffer.h"
#include"AliceUtility.h"

class LutPostEffect final :public BasePostEffect
{
private:

	std::unique_ptr<ConstantBuffer> lutSizeBuff;

	struct lutSize
	{
		float width;
		float height;
		float lutRed;
		float lutGreen;
		float lutBlue;
		float lutMul;
	};

	TextureData* lutTexture;

	lutSize size = {};



public:

	static LutPostEffect* GetInstance();

	void Initialize() override;

	void PostUpdate(RenderTarget* mainRenderTarget) override;

	void SetLutTexture(uint32_t handle);

	const std::string& GetType()override;

private:

	void Draw(RenderTarget* mainRenderTarget)override;

	void MainRenderTargetDraw(RenderTarget* mainRenderTarget)override;


	LutPostEffect() = default;
	~LutPostEffect() = default;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	LutPostEffect& operator=(const LutPostEffect&) = delete;
	LutPostEffect(const LutPostEffect&) = delete;
};


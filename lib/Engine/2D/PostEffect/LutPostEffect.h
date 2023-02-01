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

	float width = 0.0f;
	float height = 0.0f;

	TextureData* lutTexture;

	lutSize size = {};



public:

	static LutPostEffect* GetInstance();

	void Initialize() override;

	void PostUpdate(D3D12_GPU_DESCRIPTOR_HANDLE& srv, D3D12_GPU_DESCRIPTOR_HANDLE& uav) override;

	void SetLutTexture(uint32_t handle);

	const std::string& GetType()override;

private:

	LutPostEffect() = default;
	~LutPostEffect() = default;

	//コピーコンストラクタ・代入演算子削除
	LutPostEffect& operator=(const LutPostEffect&) = delete;
	LutPostEffect(const LutPostEffect&) = delete;
};


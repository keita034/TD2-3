#pragma once
#include"ErrorException.h"
#include"ComputePipelineState.h"
#include"Shader.h"

class BasePostEffect 
{
protected:

	//パイプラインステート
	std::unique_ptr<ComputePipelineState> pipelineState;
	//ルートシグネチャ
	std::unique_ptr<RootSignature> rootSignature;
	//シェーダー
	std::unique_ptr<Shader> shader;
	//初期化が必要かどうか
	bool needsInit = true;
	char PADING[7]{};

	ID3D12GraphicsCommandList* cmdList = nullptr;

	std::string type;
public:

	virtual ~BasePostEffect();
	BasePostEffect() = default;

	virtual void Initialize() = 0;

	virtual void PostUpdate(D3D12_GPU_DESCRIPTOR_HANDLE& srv, D3D12_GPU_DESCRIPTOR_HANDLE& uav) = 0;

	virtual const std::string& GetType() = 0;

	//コピーコンストラクタ・代入演算子削除
	BasePostEffect& operator=(const BasePostEffect&) = delete;
	BasePostEffect(const BasePostEffect&) = delete;
};


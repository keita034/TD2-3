#pragma once
#include <memory>
#include "Model.h"
#include "Transform.h"
#include "Camera.h"

class Stage
{
private:
	// ワールド変換データ
	Transform mainStageTrans_;
	Transform foldStageTrans_;
	// モデル
	std::unique_ptr<Model> mainStageModel_;
	std::unique_ptr<Model> foldStageModel_;
	uint32_t mainStageHandle_;
	uint32_t foldStageHandle_;

public:
	Stage() = default;
	~Stage() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(uint32_t& model);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(Camera* camera);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 畳む基本動作
	/// </summary>
	void InitializeFold(uint32_t& model);
};
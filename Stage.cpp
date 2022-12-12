#include "Stage.h"
#include <cassert>

void Stage::Initialize(uint32_t& model)
{
	// NULLポインタチェック
	assert(model);
	//引数として受け取ったデータをメンバ変数に記録する
	mainStageHandle_ = model;

	mainStageModel_ = std::make_unique<Model>();
	mainStageModel_->SetModel(mainStageHandle_);

	// ワールド変換データの初期化
	mainStageTrans_.Initialize();
	// スケール
	mainStageTrans_.scale = { 10.0f,1.0f,10.0f };
}

void Stage::InitializeFold(uint32_t& model)
{
	// NULLポインタチェック
	assert(model);
	//引数として受け取ったデータをメンバ変数に記録する
	foldStageHandle_ = model;

	foldStageModel_ = std::make_unique<Model>();
	foldStageModel_->SetModel(foldStageHandle_);

	// ワールド変換データの初期化
	foldStageTrans_.Initialize();
	// スケール
	mainStageTrans_.scale = { 10.0f,1.0f,10.0f };
	// 座標
	foldStageTrans_.translation = { 10.0f,1.0f,10.0f };
}

void Stage::Update(Camera* camera)
{
	// 行列を転送
	mainStageTrans_.TransUpdate(camera);
	//foldStageTrans_.TransUpdate(camera);
}

void Stage::Draw()
{
	mainStageModel_->Draw(&mainStageTrans_);
	//foldStageModel_->Draw(&foldStageTrans_);
}

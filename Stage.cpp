#include "Stage.h"
#include <cassert>

void Stage::Initialize(uint32_t& model)
{
	// NULL�|�C���^�`�F�b�N
	assert(model);
	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	mainStageHandle_ = model;

	mainStageModel_ = std::make_unique<Model>();
	mainStageModel_->SetModel(mainStageHandle_);

	// ���[���h�ϊ��f�[�^�̏�����
	mainStageTrans_.Initialize();
	// �X�P�[��
	mainStageTrans_.scale = { 10.0f,1.0f,10.0f };
}

void Stage::InitializeFold(uint32_t& model)
{
	// NULL�|�C���^�`�F�b�N
	assert(model);
	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	foldStageHandle_ = model;

	foldStageModel_ = std::make_unique<Model>();
	foldStageModel_->SetModel(foldStageHandle_);

	// ���[���h�ϊ��f�[�^�̏�����
	foldStageTrans_.Initialize();
	// �X�P�[��
	mainStageTrans_.scale = { 10.0f,1.0f,10.0f };
	// ���W
	foldStageTrans_.translation = { 10.0f,1.0f,10.0f };
}

void Stage::Update(Camera* camera)
{
	// �s���]��
	mainStageTrans_.TransUpdate(camera);
	//foldStageTrans_.TransUpdate(camera);
}

void Stage::Draw()
{
	mainStageModel_->Draw(&mainStageTrans_);
	//foldStageModel_->Draw(&foldStageTrans_);
}

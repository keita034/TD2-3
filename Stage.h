#pragma once
#include <memory>
#include "Model.h"
#include "Transform.h"
#include "Camera.h"

class Stage
{
private:
	// ���[���h�ϊ��f�[�^
	Transform mainStageTrans_;
	Transform foldStageTrans_;
	// ���f��
	std::unique_ptr<Model> mainStageModel_;
	std::unique_ptr<Model> foldStageModel_;
	uint32_t mainStageHandle_;
	uint32_t foldStageHandle_;

public:
	Stage() = default;
	~Stage() = default;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(uint32_t& model);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(Camera* camera);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// ��ފ�{����
	/// </summary>
	void InitializeFold(uint32_t& model);
};
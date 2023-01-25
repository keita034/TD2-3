#pragma once
#include"ErrorException.h"
#include"fbxModel.h"
#include"FbxLoader.h"
#include"FieldConstant.h"

class BesideFold
{
private:

	//���܂胂�f��
	std::unique_ptr<fbxModel> besideFoldFbxmodel_;
	//���܂�A�j���[�V����
	std::unique_ptr<fbxAnimation> besideFoldFbxmodelAnime_;

	//�A�j���[�V�����t���[��
	float fieldPlaneAnimeFlam_ = 0.0f;

	//�t�B�[���h������ւ���ꂽ��
	bool fieldReplaceFlag_ = false;

	//���[���h�ϊ�
	Transform fieldPlaneTrans_;

public:

	BesideFold() = default;
	~BesideFold() = default;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	void Start(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(Camera* camera, std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, bool& fieldPlaneDrawFlag);

	void Replace(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:

	// �R�s�[�R���X�g���N�^���֎~
	BesideFold(const BesideFold& p) = delete;
	// �R�s�[������Z�q���֎~
	void operator=(const BesideFold& p) = delete;
};


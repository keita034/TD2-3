#pragma once
#include"ErrorException.h"
#include"fbxModel.h"
#include"FbxLoader.h"
#include"FieldConstant.h"

class VerticalFold
{
private:

	//�c�܂胂�f��
	std::unique_ptr<fbxModel> verticalFoldFbxmodel_;
	//�c�܂�A�j���[�V����
	std::unique_ptr<fbxAnimation> verticalFoldFbxmodelAnime_;

	//�A�j���[�V�����t���[��
	float fieldPlaneAnimeFlam_ = 0.0f;

	//�t�B�[���h������ւ���ꂽ��
	bool fieldReplaceFlag_ = false;

	//���[���h�ϊ�
	Transform fieldPlaneTrans_;

public:

	VerticalFold() = default;
	~VerticalFold() = default;

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

	//void SetCollider(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, FieldElementIndex fieldElementIndex, int changeNumber);

private:

	// �R�s�[�R���X�g���N�^���֎~
	VerticalFold(const VerticalFold& p) = delete;
	// �R�s�[������Z�q���֎~
	void operator=(const VerticalFold& p) = delete;
};


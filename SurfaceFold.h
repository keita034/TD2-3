#pragma once
#include"ErrorException.h"
#include"fbxModel.h"
#include"FbxLoader.h"
#include"FieldConstant.h"

class SurfaceFold
{
private:

	//�ʐ܂胂�f��
	std::unique_ptr<fbxModel> surfaceFoldFbxmodel_;
	//�ʐ܂�A�j���[�V����
	std::unique_ptr<fbxAnimation> surfaceFoldFbxmodelAnime_;

	//�A�j���[�V�����t���[��
	float fieldPlaneAnimeFlam_ = 0.0f;

	//�t�B�[���h������ւ���ꂽ��
	bool fieldReplaceFlag_ = false;

	//���[���h�ϊ�
	Transform fieldPlaneTrans_;

	//�k�ރA�j���[�V����
	bool shrinkAnimeFlag_ = false;

	//����ւ��A�j���[�V����
	bool replaceAnimeFlag_ = false;

	//�L�т�A�j���[�V����
	bool extendAnimeFlag_ = false;

	bool animeEnd = false;

	float scale_;

public:

	SurfaceFold() = default;
	~SurfaceFold() = default;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	void Start(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, float standardAngle);

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

	void ExtendShrinkAnime(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);
	void FoldPreparation(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);
	void FoldEnd(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);

	// �R�s�[�R���X�g���N�^���֎~
	SurfaceFold(const SurfaceFold& p) = delete;
	// �R�s�[������Z�q���֎~
	void operator=(const SurfaceFold& p) = delete;
};


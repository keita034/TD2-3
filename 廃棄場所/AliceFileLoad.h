#pragma once
#include"ErrorException.h"
#include"AliceModel.h"

class AliceFileLoad final
{
private:

public:

	bool ModelLoad(const std::string& filepath, AliceModel* model);

	bool ModelAnimationLoad(const std::string& filepath);

	/// <summary>
	/// �V���O���g���C���X�^���X�̎擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static AliceFileLoad* GetInstance();

private:

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	AliceFileLoad& operator=(const AliceFileLoad&) = delete;
	AliceFileLoad(const AliceFileLoad&) = delete;

	AliceFileLoad();
	~AliceFileLoad();
};


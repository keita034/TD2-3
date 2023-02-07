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
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static AliceFileLoad* GetInstance();

private:

	//コピーコンストラクタ・代入演算子削除
	AliceFileLoad& operator=(const AliceFileLoad&) = delete;
	AliceFileLoad(const AliceFileLoad&) = delete;

	AliceFileLoad();
	~AliceFileLoad();
};


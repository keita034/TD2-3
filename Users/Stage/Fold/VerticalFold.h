#pragma once
#include"ErrorException.h"
#include"fbxModel.h"
#include"FbxLoader.h"
#include"FieldConstant.h"

class VerticalFold
{
private:

	//縦折りモデル
	std::unique_ptr<fbxModel> verticalFoldFbxmodel_;
	//縦折りアニメーション
	std::unique_ptr<fbxAnimation> verticalFoldFbxmodelAnime_;

	//アニメーションフレーム
	float fieldPlaneAnimeFlam_ = 0.0f;

	//フィールドが入れ替えられたか
	bool fieldReplaceFlag_ = false;

	//ワールド変換
	Transform fieldPlaneTrans_;

public:

	VerticalFold() = default;
	~VerticalFold() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	void Start(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(Camera* camera, std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, bool& fieldPlaneDrawFlag);

	void Replace(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//void SetCollider(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, FieldElementIndex fieldElementIndex, int changeNumber);

private:

	// コピーコンストラクタを禁止
	VerticalFold(const VerticalFold& p) = delete;
	// コピー代入演算子を禁止
	void operator=(const VerticalFold& p) = delete;
};


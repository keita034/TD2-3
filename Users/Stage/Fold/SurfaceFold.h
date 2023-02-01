#pragma once
#include"ErrorException.h"
#include"fbxModel.h"
#include"FbxLoader.h"
#include"FieldConstant.h"

class SurfaceFold
{
private:

	//面折りモデル
	std::unique_ptr<fbxModel> surfaceFoldFbxmodel_;
	//面折りアニメーション
	std::unique_ptr<fbxAnimation> surfaceFoldFbxmodelAnime_;

	//アニメーションフレーム
	float fieldPlaneAnimeFlam_ = 0.0f;

	//フィールドが入れ替えられたか
	bool fieldReplaceFlag_ = false;

	//ワールド変換
	Transform fieldPlaneTrans_;

	//縮むアニメーション
	bool shrinkAnimeFlag_ = false;

	//入れ替えアニメーション
	bool replaceAnimeFlag_ = false;

	//伸びるアニメーション
	bool extendAnimeFlag_ = false;

	bool animeEnd = false;

	float scale_;

public:

	SurfaceFold() = default;
	~SurfaceFold() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	void Start(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, float standardAngle);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(Camera* camera, std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, bool& fieldPlaneDrawFlag);

	void Replace(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:

	void ExtendShrinkAnime(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);
	void FoldPreparation(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);
	void FoldEnd(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);

	// コピーコンストラクタを禁止
	SurfaceFold(const SurfaceFold& p) = delete;
	// コピー代入演算子を禁止
	void operator=(const SurfaceFold& p) = delete;
};


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

public:

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

	void StartTopTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);
	void ReplaceTopTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);
	void EndTopTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);

	void StartLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);
	void ReplaceLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);
	void EndLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);

	void StartCenterLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);
	void ReplaceCenterLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);
	void EndCenterLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);

	void StartCenterRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);
	void ReplaceCenterRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);
	void EndCenterRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);

	void StartRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);
	void ReplaceRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);
	void EndRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);

	void StartBottomTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);
	void ReplaceBottomTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);
	void EndBottomTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);

};


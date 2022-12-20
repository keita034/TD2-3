#pragma once
#include"ErrorException.h"
#include "Model.h"
#include "Transform.h"
#include "Camera.h"
#include "fbxModel.h"

enum FieldIndex
{
	Top,//上
	Left,
	CenterLeft,
	CenterRight,
	Right,
	Bottom,//下
};

//仮
enum class Field
{

	a,
	b,
	c,
	d,
	e,
	f,
	g,

};

enum class FoldIndex
{
	Vertical,//縦
	Beside//横
};

enum FieldElementIndex
{
	LeftTop,
	LeftBottom,
	RightTop,
	RightBottom,
};

struct FieldElement
{
	TextureData* textureData;
	Field field;
};

class Stage
{
private:
	// ワールド変換データ
	Transform fieldPlaneTrans_;
	// モデル
	std::unique_ptr<Model> surfaceModel_;

	uint32_t surfaceModelHandle_;
	uint32_t besideFoldFbxmodelHandle_;

	Transform surfaceModelTrans_;

	//横折りモデル
	std::unique_ptr<fbxModel> besideFoldFbxmodel_;
	//横折りアニメーション
	std::unique_ptr<fbxAnimation> besideFoldFbxmodelAnime_;

	//横折りモデル
	std::unique_ptr<fbxModel> verticalFoldFbxmodel_;
	//横折りアニメーション
	std::unique_ptr<fbxAnimation> verticalFoldFbxmodelAnime_;

	//どこの面を畳むか
	FieldIndex FieldSurfaceIndex;

	//どの方向に畳むのか
	FoldIndex foldDirection;

	float fieldPlaneAnimeFlam = 0.0f;
	bool fieldPlaneDrawFlag = false;
	bool fieldFoldFlag = true;

	std::array<std::array<FieldElement, 4>, 6> field;

public:
	Stage() = default;
	~Stage() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update(Camera* camera);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 畳む基本動作
	/// </summary>
	void InitializeFold();

	void FieldPlaneFoldStart(FieldIndex fieldIndex, FoldIndex foldIndex);

private:

	void FieldPlaneFold();
};
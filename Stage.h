#pragma once
#include"ErrorException.h"
#include "Model.h"
#include "Transform.h"
#include "Camera.h"
#include "fbxModel.h"

enum FieldIndex
{
	//□□■□□
	//□■■■■
	//□□■□□

	Top,//上
	Left,//左
	CenterLeft,//真ん中左
	CenterRight,//真ん中右
	Right,//右
	Bottom,//下

	TopToLeft,//上と左
	TopToCenterLeft,//上と真ん中左
	TopToCenterRight,//上と真ん中右
	TopToRight,//上と右

	LeftToTop,//左と上
	LeftToTopToCenterLeft,//左と真ん中左
	LeftToRight,//左と右
	LeftToBottom,//左と下

	CenterLeftToTop,//真ん中左と上
	CenterLeftToLeft,//真ん中左と左
	CenterLeftToCenterRight,//真ん中左と真ん中右
	CenterLeftToBottom,//真ん中左と下

	CenterRightToTop,//真ん中右と上
	CenterRightToCenterLeft,//真ん中右と真ん中左
	CenterRightToRight,//真ん中右と右
	CenterRightToBottom,//真ん中右と下

	RightToTop,//右と上
	RightToLeft,//右と下
	RightToCenterRight,//右と真ん中右
	RightToBottom,//右と下

	BottomToLeft,//下と左
	BottomToCenterLeft,//下と真ん中左
	BottomToCenterRight,//下と真ん中右
	BottomToRight,//下と右

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
	h,
	i,
	j,
	k,
	l,
	n,
	m,
	o,
	p,
	q,
	r,
	s,
	t,
	u,
	v,
	w,
	x,
	y,
	z,
};

enum class FoldIndex
{
	Vertical,//縦
	Beside,//横
	Surface,//面と面
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
	//テクスチャ
	TextureData* textureData;
	//識別用
	Field field;
	//面の一部モデル
	std::unique_ptr<Model> surfacePartsModel;
	//モデルハンドル
	uint32_t surfacePartsModelHandle;
	//ワールド変換
	Transform surfacePartsModelTrans;
	bool isDraw = true;

	void Draw();
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

	//縦折りモデル
	std::unique_ptr<fbxModel> verticalFoldFbxmodel_;
	//縦折りアニメーション
	std::unique_ptr<fbxAnimation> verticalFoldFbxmodelAnime_;

	//面折りモデル
	std::unique_ptr<fbxModel> surfaceFoldFbxmodel_;
	//面折りアニメーション
	std::unique_ptr<fbxAnimation> surfaceFoldFbxmodelAnime_;

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

	void FieldPlaneFoldStart(FieldIndex fieldIndex, FoldIndex foldIndex);

private:

	void FieldPlaneFold();
};
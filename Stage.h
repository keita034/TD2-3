#pragma once
#include"ErrorException.h"
#include "Model.h"
#include "Transform.h"
#include "Camera.h"
#include "fbxModel.h"
#include "VerticalFold.h"
#include"FieldConstant.h"
#include"BesideFold.h"
#include"SurfaceFold.h"
#include"MeshCollider.h"

class Stage
{
private:

	//どこの面を畳むか
	FieldIndex FieldSurfaceIndex;

	//どの方向に畳むのか
	FoldIndex foldDirection;

	bool fieldPlaneDrawFlag = false;

	std::array<std::array<FieldElement, 4>, 6> field;

	std::unique_ptr<VerticalFold> verticalFold_;

	std::unique_ptr<BesideFold> besideFold_;

	std::unique_ptr<SurfaceFold> surfaceFold_;

	//基準の角度
	float standardAngle_;

	// コライダーの追加
	MeshCollider* collider = new MeshCollider;
	MeshCollider* collider2 = new MeshCollider;
	MeshCollider* collider3 = new MeshCollider;
	MeshCollider* collider4 = new MeshCollider;
	MeshCollider* collider5 = new MeshCollider;


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

	// コピーコンストラクタを禁止
	Stage(const Stage& p) = delete;
	// コピー代入演算子を禁止
	void operator=(const Stage& p) = delete;
};
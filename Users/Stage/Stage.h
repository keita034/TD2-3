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

	std::unique_ptr<SurfaceFold> surfaceFold_;

	uint32_t modelHandle = 0u;
	std::unique_ptr<Model> BlockCollider;
	Transform BlockTrans;

	//基準の角度
	float standardAngle_;

	std::unique_ptr<MeshCollider> meshCollider[24];
	std::unique_ptr<MeshCollider> StageBlockCollider;

	std::string DefaultModelName;//モデルの名前

public:
	Stage() = default;
	~Stage() = default;
	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Camera* camera, std::string failPath,
		std::string map1, std::string map2, std::string map3, std::string map4,
		std::string map5, std::string map6, std::string map7, std::string map8,
		std::string map9, std::string map10, std::string map11, std::string map12,
		std::string map13, std::string map14, std::string map15, std::string map16,
		std::string map17, std::string map18, std::string map19, std::string map20,
		std::string map21, std::string map22, std::string map23, std::string map24);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(Camera* camera);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void FieldPlaneFoldStart(FieldIndex fieldIndex, FoldIndex foldIndex);

	void SetCollider(FieldIndex fieldIndex, FieldElementIndex fieldElementIndex,int meshNumber);

	void ChangeCollider(FieldIndex fieldIndex, FieldElementIndex fieldElementIndex, int meshNumber);

	void SetStageObjScale(const AliceMathF::Vector3& scale);

	void GoodbyeStage(int meshNumber);

	void SetStageObjScale(const AliceMathF::Vector3& scale);

	void SetStageFrameScale(const AliceMathF::Vector3& scale);
	void SetStageFrameTrans(const AliceMathF::Vector3& trans);

#pragma region SetStageTrans
	void SetStageTopTrans(const AliceMathF::Vector3& trans);
	void SetStageLeftTrans(const AliceMathF::Vector3& trans);
	void SetStageCenterLeftTrans(const AliceMathF::Vector3& trans);
	void SetStageCenterRightTrans(const AliceMathF::Vector3& trans);
	void SetStageRightTrans(const AliceMathF::Vector3& trans);
	void SetStageBottomTrans(const AliceMathF::Vector3& trans);
#pragma endregion

	Transform GetStageTransform(FieldIndex fieldIndex, FieldElementIndex fieldElementIndex);

private:

	// コピーコンストラクタを禁止
	Stage(const Stage& p) = delete;
	// コピー代入演算子を禁止
	void operator=(const Stage& p) = delete;
};
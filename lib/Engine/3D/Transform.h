#pragma once
#include"ErrorException.h"
#include"AliceMathUtility.h"
#include"Camera.h"
#include"ConstantBuffer.h"
#include"AliceUtility.h"
#include"BaseCollider.h"

class Transform
{
private:
	// 定数バッファ
	std::shared_ptr<ConstantBuffer> constBuff;
	//定数バッファのマッピング用ポインタ
	worldViewpojCamera constBuffMap;
	char PADING1[4];

	//初期化用のビュー行列計算
	static AliceMathF::Matrix4 defaultViewMat;

	//初期化用のプロジェクション行列計算
	static AliceMathF::Matrix4 defaultProjectionMat;

	// コライダー
	BaseCollider* collider = nullptr;

public:
	// ローカル座標
	AliceMathF::Vector3 translation = { 0.0f, 0.0f, 0.0f };
	// X,Y,Z軸回りのローカル回転角
	AliceMathF::Vector3 rotation = { 0.0f, 0.0f, 0.0f };
	// ローカルスケール
	AliceMathF::Vector3 scale = { 1.0f, 1.0f, 1.0f };

	AliceMathF::Matrix4 matWorld;
private:
	char PADING2[4];
public:

	// 親となるワールド変換へのポインタ
	const Transform* parent = nullptr;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 行列を転送する
	/// </summary>
	void TransUpdate(Camera* camera);

	void Update();

	void MakeWorldMatrix();

	ID3D12Resource* GetconstBuff();

	worldViewpojCamera* GetWorldViewpojCamera();

	/// <summary>
	/// コライダーのセット
	/// </summary>
	/// <param name="collider">コライダー</param>
	void SetCollider(BaseCollider* collider);
};

namespace AliceMathF
{
	Matrix4 MakeWorldMatrix4(Transform& transform);

	/// <summary>
	/// ワールド座標取得
	/// </summary>
	Vector3 GetWorldPosition(Transform& transform);
}
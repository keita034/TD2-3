#pragma once

#include"BaseCollider.h"
#include"CollisionPrimitive.h"

#include"Model.h"
#include"fbxModel.h"


/// <summary>
/// メッシュ衝突判定オブジェクト
/// </summary>
class MeshCollider :
	public BaseCollider
{
public:
	MeshCollider()
	{
		// メッシュ形状をセット
		shapeType = COLLISIONSHAPE_MESH;
	}

	/// <summary>
	/// 三角形の配列を構築する
	/// </summary>
	void ConstructTriangles(std::unique_ptr<Model>& model, AliceMathF::Vector3 ModelPos);
	void ConstructTriangles(fbxModel* model);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(const AliceMathF::Matrix4& worldPos) override;

	/// <summary>
	/// 球との当たり判定
	/// </summary>
	/// <param name="sphere">球</param>
	/// <param name="inter">交点（出力用）</param>
	/// <returns>交差しているか否か</returns>
	bool CheckCollisionSphere(const Sphere& sphere, AliceMathF::Vector4* inter = nullptr, AliceMathF::Vector4* reject = nullptr);

	/// <summary>
	/// レイとの当たり判定
	/// </summary>
	/// <param name="sphere">レイ</param>
	/// <param name="distance">距離（出力用）</param>
	/// <param name="inter">交点（出力用）</param>
	/// <returns>交差しているか否か</returns>
	bool CheckCollisionRay(const Ray& ray, float* distance = nullptr, AliceMathF::Vector4* inter = nullptr);

private:
	std::vector<Triangle> triangles;
	// ワールド行列の逆行列
	AliceMathF::Matrix4 invMatWorld;
};
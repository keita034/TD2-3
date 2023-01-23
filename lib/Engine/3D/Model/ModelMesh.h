#pragma once
#include "ErrorException.h"
#include"AliceUtility.h"
#include "Model.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "DefaultMaterial.h"
#include "ConstantBuffer.h"
#include "RootSignature.h"
#include"ComputePipelineState.h"
#include"RWStructuredBuffer.h"
#include"StructuredBuffer.h"
#include"Shader.h"
#include"ComputeVertexBuffer.h"
#include"fbxAnimation.h"

#pragma warning(push)
#pragma warning(disable: 5264)
//ボーンの最大数
constexpr int MAX_BONES = 128;
constexpr int MAX_BONE_INDICES = 4;
#pragma warning(pop)

// 骨
struct Bone
{
	//名前
	std::string name;

	AliceMathF::Matrix4 matrix;
	AliceMathF::Matrix4 animationMatrix;
	AliceMathF::Matrix4 offsetMatirx;

	UINT index;

private:
	char PADING[4] = {};

};

struct PosNormUvTangeColSkin
{
	AliceMathF::Vector4 position = { 0.0f,0.f,0.0f,1.0f }; // 位置座標
	AliceMathF::Vector3 normal; // 法線
	AliceMathF::Vector2 uv; // uv座標
	AliceMathF::Vector3 tangent; // 接空間
	AliceMathF::Vector4 color; // 頂点色

	std::array<UINT, MAX_BONE_INDICES> boneIndex;	// ボーンの番号
	std::array<float, MAX_BONE_INDICES> boneWeight;	// ボーンの重み
};

struct PosNormUvTangeCol
{
	AliceMathF::Vector4 position = { 0.0f,0.f,0.0f,1.0f }; // 位置座標
	AliceMathF::Vector3 normal; // 法線
	AliceMathF::Vector2 uv; // uv座標
	AliceMathF::Vector3 tangent; // 接空間
	AliceMathF::Vector4 color; // 頂点色
};

struct PosNormSkin
{
	AliceMathF::Vector4 position; // 位置座標
	AliceMathF::Vector3 normal; // 法線

	std::array<UINT, MAX_BONE_INDICES> boneIndex;	// ボーンの番号
	std::array<float, MAX_BONE_INDICES> boneWeight;	// ボーンの重み
};

struct PosNorm
{
	AliceMathF::Vector4 position; // 位置座標
	AliceMathF::Vector3 normal; // 法線
};
//定数バッファ用データ構造体(スキニング)
struct SkinData
{
	std::vector<AliceMathF::Matrix4> bones;
};

struct SkinComputeInput
{
	std::vector<PosNormSkin> vertices;
	SkinData bone;
};

struct Node
{
	//名前
	std::string name;
	//ローカル変形行列
	AliceMathF::Matrix4 transform;
	//グローバル変形行列
	AliceMathF::Matrix4 globalTransform;
	//親ノード
	Node* parent = nullptr;
};

struct BoneData
{
	//ボーンデータ
	std::array<AliceMathF::Matrix4, MAX_BONES> boneMat;
};

class ModelMesh
{
private:

public:

	//名前
	std::string name;

	//名前
	std::string nodeName;

	//頂点データの配列
	std::vector<PosNormUvTangeColSkin> vertices;

	//インデックスの配列
	std::vector<uint32_t> indices;

	//テクスチャ
	std::vector <TextureData*> textures;

	//テクスチャ
	std::vector <TextureData*> texturesNormal;

	std::unordered_map<std::string, Bone> bones;

	std::vector<Bone> vecBones;

	std::vector< AliceMathF::Matrix4> deformationMat;

	//有効
	bool enable = false;
	char PADING[3]{};

	// カラー
	float col[4] = { 1.0f,1.0f,1.0f,1.0f };
	char PADING1[4]{};

	// マテリアル
	ModelMaterial material;

	Node* node = nullptr;

	//頂点バッファ
	std::shared_ptr<ComputeVertexBuffer> vertexBuffer;
	//インデックスバッファ
	std::shared_ptr<IndexBuffer> indexBuffer;
	//マテリアルバッファ
	std::shared_ptr<ConstantBuffer> materialBuffer;
	//ボーン
	std::shared_ptr<ConstantBuffer> constBoneBuffer;

	//計算シェーダー用頂点データ
	std::shared_ptr<StructuredBuffer> computeInputBuff;
	std::shared_ptr<ConstantBuffer> boneBuffer;

	//描画頂点データ
	std::vector<PosNormUvTangeCol> vertice;

	SkinComputeInput skinComputeInput;

	SkinData skinData;

	BoneData bonedata;

	bool dirtyFlag;

	ModelMesh() = default;
	~ModelMesh() = default;
public:

	/// <summary>
	/// 各種バッファを生成
	/// </summary>
	void CreateBuffer();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList, Transform* transform, Light* light);

	void DrawBgin();

	void Update(ComputeRelation* computeRelation, ID3D12GraphicsCommandList* cmdList);

	void FillVertex();

	void InitializeVertex();

	void InitializeVertexPos();

	/// <summary>
	/// 頂点座標を取得
	/// </summary>
	/// <returns>頂点座標配列</returns>
	const std::vector<PosNormUvTangeCol>GetVertices();

	/// <summary>
	/// インデックスを取得
	/// </summary>
	/// <returns>インデックス座標配列</returns>
	const std::vector<uint32_t>GetIndices();

private:
};
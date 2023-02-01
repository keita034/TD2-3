#pragma once
#include"ErrorException.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"AliceMathUtility.h"
#include"Material.h"
#include"BasePostEffect.h"
#include"RWStructuredBuffer.h"
#include"PostEffectFactory.h"

class PostEffectManager final
{
private:

	struct PostResource
	{
		RWStructuredBuffer buff;
		D3D12_RESOURCE_STATES states = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;

	private:
		char PADDING[4]{};
	public:

		~PostResource() = default;
		PostResource() = default;

	private:
		//コピーコンストラクタ・代入演算子削除
		PostResource& operator=(const PostResource&) = delete;
		PostResource(const PostResource&) = delete;
	};

	HRESULT result;
	char PADDING1[4]{};
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr <ID3D12GraphicsCommandList> cmdList = nullptr;

	//頂点バッファ
	std::unique_ptr<VertexBuffer> vertexBuffer;

	//インデックスバッファ
	std::unique_ptr<IndexBuffer> indexBuffer;

	Material* postEffectMaterial = nullptr;

	float width = 0.0f;
	float height = 0.0f;

	std::list<BasePostEffect*> postEffects;

	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle{};

	TextureData windowTex{};

	std::array<PostResource, 2> postwinTex;

	//有効か
	bool isAalid = false;

	bool isFlip = false;
	char PADDING2[6]{};

	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapRTV;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapDSV;

	static const float clearColor[4];

	PostEffectFactory* factory = nullptr;

public:
	
	static PostEffectManager* GetInstance();

	void Initialize();

	void PostInitialize();

	void PostDraw();

	void PreDrawScen();

	void PostDrawScen();

	void AddPostEffect(const std::string& postEffectName);

	void SubPostEffect(const std::string& postEffectName);

	void Finalize();

	bool IsAalid();

private:

	~PostEffectManager();
	PostEffectManager() = default;

	void CreateWindowTex();

	void CreateRenderTarget();

	void CreateDepthStencilView();

	void Draw();

	//コピーコンストラクタ・代入演算子削除
	PostEffectManager& operator=(const PostEffectManager&) = delete;
	PostEffectManager(const PostEffectManager&) = delete;
};


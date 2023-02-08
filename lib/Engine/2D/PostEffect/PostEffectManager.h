#pragma once
#include"ErrorException.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"AliceMathUtility.h"
#include"Material.h"
#include"BasePostEffect.h"
#include"RWStructuredBuffer.h"
#include"PostEffectFactory.h"
#include"RenderTarget.h"

class PostEffectManager final
{
private:

	HRESULT result;
	char PADDING1[4]{};
	ID3D12Device* device = nullptr;
	ID3D12GraphicsCommandList* cmdList = nullptr;
	DSVDescriptorHeap* dsvHeap = nullptr;
	RTVDescriptorHeap* rtvHeap = nullptr;
	DescriptorHeap* srvHeap = nullptr;

	//���_�o�b�t�@
	std::unique_ptr<VertexBuffer> vertexBuffer;

	//�C���f�b�N�X�o�b�t�@
	std::unique_ptr<IndexBuffer> indexBuffer;

	Material* postEffectMaterial = nullptr;

	float width = 0.0f;
	float height = 0.0f;

	std::list<BasePostEffect*> postEffects;

	//�L����
	bool isAalid = false;

	bool isFlip = false;
	char PADDING2[6]{};

	static const float clearColor[4];

	PostEffectFactory* factory = nullptr;

	std::unique_ptr<RenderTarget> mainRenderTarget;

public:
	
	static PostEffectManager* GetInstance();

	void Initialize();

	void PostInitialize();

	void Update();

	void PreDrawScen();

	void PostDrawScen();

	void AddPostEffect(const std::string& postEffectName);

	void SubPostEffect(const std::string& postEffectName);

	void Finalize();

	bool IsAalid();

	void Draw();

private:

	~PostEffectManager();
	PostEffectManager() = default;

	void CreateWindowTex();

	void CreateRenderTarget();

	void CreateDepthStencilView();



	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	PostEffectManager& operator=(const PostEffectManager&) = delete;
	PostEffectManager(const PostEffectManager&) = delete;
};


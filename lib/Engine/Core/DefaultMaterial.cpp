#include "DefaultMaterial.h"

void DefaultMaterial::Initialize()
{
	CreateDefaultTexture();

	CreateDefaultTextureMaterial();

	CreateDefaultLambertMaterial();

	CreateDefaultPhongMaterial();

	CreateDefaultSprite2DMaterial();

	CreateDefaultSprite3DMaterial();

	CreateDefaultFbxMaterial();

	CreateDefaultPostEffectMaterial();

	CreateDefaultParticleMaterial();

	CreateDefaultRainParticleMaterial();
}

DefaultMaterial* DefaultMaterial::GetDefaultMaterial()
{
	static DefaultMaterial material;
	return &material;
}

DefaultMaterial::~DefaultMaterial()
{
}

void DefaultMaterial::CreateDefaultTexture()
{
	uint32_t handle = TextureManager::Load("Resources/Default/white1x1.png");
	DEFAULT_TEXTURE = TextureManager::GetTextureData(handle);
}

void DefaultMaterial::CreateDefaultTextureMaterial()
{
	DEFAULT_TEXTURE_MATERIAL = std::make_unique<Material>();

	//�e�N�X�`���f�[�^�ݒ�
	DEFAULT_TEXTURE_MATERIAL->textureData = DEFAULT_TEXTURE;

	//���_�V�F�[�_�̓ǂݍ���
	DEFAULT_TEXTURE_MATERIAL->vertexShader = std::make_unique<Shader>();
	DEFAULT_TEXTURE_MATERIAL->vertexShader->Create("Resources/Shaders/3D/Model/ModelBasicVS.hlsl");

	//�W�I���g���V�F�[�_�̓ǂݍ���
	DEFAULT_TEXTURE_MATERIAL->geometryShader = std::make_unique<Shader>();
	DEFAULT_TEXTURE_MATERIAL->geometryShader->Create("Resources/Shaders/3D/Model/PolygonEffectGS.hlsl", "main", "gs_5_0", Shader::ShaderType::GS);

	//�s�N�Z���V�F�[�_�̓ǂݍ���
	DEFAULT_TEXTURE_MATERIAL->pixelShader = std::make_unique<Shader>();
	DEFAULT_TEXTURE_MATERIAL->pixelShader->Create("Resources/Shaders/3D/Model/ModelBasicPS.hlsl", "main", "ps_5_0", Shader::ShaderType::PS);

	//���_���C�A�E�g�ݒ�
	DEFAULT_TEXTURE_MATERIAL->inputLayouts = {
		// xyz���W
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//�@��
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		// uv���W
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

	//���[�g�V�O�l�`���ݒ�
	DEFAULT_TEXTURE_MATERIAL->rootSignature = std::make_unique<RootSignature>();
	DEFAULT_TEXTURE_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
	DEFAULT_TEXTURE_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 1);//b1
	DEFAULT_TEXTURE_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 2);//b2
	DEFAULT_TEXTURE_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 3);//b3
	DEFAULT_TEXTURE_MATERIAL->rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0
	DEFAULT_TEXTURE_MATERIAL->rootSignature->AddStaticSampler(0);//s0
	DEFAULT_TEXTURE_MATERIAL->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

	//�u�����h�ݒ�
	DEFAULT_TEXTURE_MATERIAL->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
	DEFAULT_TEXTURE_MATERIAL->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̃A���t�@�l
	DEFAULT_TEXTURE_MATERIAL->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;// 1.0f-�\�[�X�̃A���t�@�l

	DEFAULT_TEXTURE_MATERIAL->cullMode = D3D12_CULL_MODE_NONE;

	//����
	DEFAULT_TEXTURE_MATERIAL->Initialize();
}

void DefaultMaterial::CreateDefaultLambertMaterial()
{
	DEFAULT_LAMBERT_MATERIAL = std::make_unique<Material>();

	//�e�N�X�`���f�[�^�ݒ�
	DEFAULT_LAMBERT_MATERIAL->textureData = DEFAULT_TEXTURE;

	//���_�V�F�[�_�̓ǂݍ���
	DEFAULT_LAMBERT_MATERIAL->vertexShader = std::make_unique<Shader>();
	DEFAULT_LAMBERT_MATERIAL->vertexShader->Create("Resources/Shaders/3D/Model/LambertVS.hlsl");

	//�s�N�Z���V�F�[�_�̓ǂݍ���
	DEFAULT_LAMBERT_MATERIAL->pixelShader = std::make_unique<Shader>();
	DEFAULT_LAMBERT_MATERIAL->pixelShader->Create("Resources/Shaders/3D/Model/LambertPS.hlsl", "main", "ps_5_0", Shader::ShaderType::PS);

	//���_���C�A�E�g�ݒ�
	DEFAULT_LAMBERT_MATERIAL->inputLayouts = {
		// xyz���W
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//�@��
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		// uv���W
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

	//���[�g�V�O�l�`���ݒ�
	DEFAULT_LAMBERT_MATERIAL->rootSignature = std::make_unique<RootSignature>();
	DEFAULT_LAMBERT_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
	DEFAULT_LAMBERT_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 1);//b1
	DEFAULT_LAMBERT_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 2);//b2
	DEFAULT_LAMBERT_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 3);//b3
	DEFAULT_LAMBERT_MATERIAL->rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0
	DEFAULT_LAMBERT_MATERIAL->rootSignature->AddStaticSampler(0);//s0
	DEFAULT_LAMBERT_MATERIAL->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

	//�u�����h�ݒ�
	DEFAULT_LAMBERT_MATERIAL->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
	DEFAULT_LAMBERT_MATERIAL->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̃A���t�@�l
	DEFAULT_LAMBERT_MATERIAL->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;// 1.0f-�\�[�X�̃A���t�@�l

	//����
	DEFAULT_LAMBERT_MATERIAL->Initialize();
}

void DefaultMaterial::CreateDefaultPhongMaterial()
{
	DEFAULT_PHONG_MATERIAL = std::make_unique<Material>();

	//�e�N�X�`���f�[�^�ݒ�
	DEFAULT_PHONG_MATERIAL->textureData = DEFAULT_TEXTURE;

	//���_�V�F�[�_�̓ǂݍ���
	DEFAULT_PHONG_MATERIAL->vertexShader = std::make_unique<Shader>();
	DEFAULT_PHONG_MATERIAL->vertexShader->Create("Resources/Shaders/3D/Model/PhongVS.hlsl");

	//�s�N�Z���V�F�[�_�̓ǂݍ���
	DEFAULT_PHONG_MATERIAL->pixelShader = std::make_unique<Shader>();
	DEFAULT_PHONG_MATERIAL->pixelShader->Create("Resources/Shaders/3D/Model/PhongPS.hlsl", "main", "ps_5_0", Shader::ShaderType::PS);

	//���_���C�A�E�g�ݒ�
	DEFAULT_PHONG_MATERIAL->inputLayouts = DEFAULT_TEXTURE_MATERIAL->inputLayouts;

	//���[�g�V�O�l�`���ݒ�
	DEFAULT_PHONG_MATERIAL->rootSignature = std::make_unique<RootSignature>();
	DEFAULT_PHONG_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
	DEFAULT_PHONG_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 1);//b1
	DEFAULT_PHONG_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 2);//b2
	DEFAULT_PHONG_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 3);//b3
	DEFAULT_PHONG_MATERIAL->rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0
	DEFAULT_PHONG_MATERIAL->rootSignature->AddStaticSampler(0);//s0
	DEFAULT_PHONG_MATERIAL->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

	//�u�����h�ݒ�
	DEFAULT_PHONG_MATERIAL->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
	DEFAULT_PHONG_MATERIAL->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̃A���t�@�l
	DEFAULT_PHONG_MATERIAL->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;// 1.0f-�\�[�X�̃A���t�@�l

	//����
	DEFAULT_PHONG_MATERIAL->Initialize();
}

void DefaultMaterial::CreateDefaultSprite2DMaterial()
{
	//���_�V�F�[�_�̓ǂݍ���
	std::unique_ptr<Shader>vertexShader = std::make_unique<Shader>();
	vertexShader->Create("Resources/Shaders/2D/SpriteVS.hlsl");

	//�s�N�Z���V�F�[�_�̓ǂݍ���
	std::unique_ptr<Shader>pixelShader = std::make_unique<Shader>();
	pixelShader->Create("Resources/Shaders/2D/SpritePS.hlsl", "main", "ps_5_0", Shader::ShaderType::PS);

	DEFAULT_SPRITE2D_MATERIAL[0].reset(CreateDefaultSprite2DBlend(BlendMode::AX_BLENDMODE_NOBLEND, vertexShader.get(), pixelShader.get()));
	DEFAULT_SPRITE2D_MATERIAL[1].reset(CreateDefaultSprite2DBlend(BlendMode::AX_BLENDMODE_ALPHA, vertexShader.get(), pixelShader.get()));
	DEFAULT_SPRITE2D_MATERIAL[2].reset(CreateDefaultSprite2DBlend(BlendMode::AX_BLENDMODE_ADD, vertexShader.get(), pixelShader.get()));
	DEFAULT_SPRITE2D_MATERIAL[3].reset(CreateDefaultSprite2DBlend(BlendMode::AX_BLENDMODE_SUB, vertexShader.get(), pixelShader.get()));
	DEFAULT_SPRITE2D_MATERIAL[4].reset(CreateDefaultSprite2DBlend(BlendMode::AX_BLENDMODE_MULA, vertexShader.get(), pixelShader.get()));
	DEFAULT_SPRITE2D_MATERIAL[5].reset(CreateDefaultSprite2DBlend(BlendMode::AX_BLENDMODE_INVSRC, vertexShader.get(), pixelShader.get()));
}

void DefaultMaterial::CreateDefaultSprite3DMaterial()
{
	//���_�V�F�[�_�̓ǂݍ���
	std::unique_ptr<Shader>vertexShader = std::make_unique<Shader>();
	vertexShader->Create("Resources/Shaders/2D/SpriteVS.hlsl");

	//�s�N�Z���V�F�[�_�̓ǂݍ���
	std::unique_ptr<Shader>pixelShader = std::make_unique<Shader>();
	pixelShader->Create("Resources/Shaders/2D/SpritePS.hlsl", "main", "ps_5_0", Shader::ShaderType::PS);

	DEFAULT_SPRITE3D_MATERIAL[0].reset(CreateDefaultSprite3DBlend(BlendMode::AX_BLENDMODE_NOBLEND, vertexShader.get(), pixelShader.get()));
	DEFAULT_SPRITE3D_MATERIAL[1].reset(CreateDefaultSprite3DBlend(BlendMode::AX_BLENDMODE_ALPHA, vertexShader.get(), pixelShader.get()));
	DEFAULT_SPRITE3D_MATERIAL[2].reset(CreateDefaultSprite3DBlend(BlendMode::AX_BLENDMODE_ADD, vertexShader.get(), pixelShader.get()));
	DEFAULT_SPRITE3D_MATERIAL[3].reset(CreateDefaultSprite3DBlend(BlendMode::AX_BLENDMODE_SUB, vertexShader.get(), pixelShader.get()));
	DEFAULT_SPRITE3D_MATERIAL[4].reset(CreateDefaultSprite3DBlend(BlendMode::AX_BLENDMODE_MULA, vertexShader.get(), pixelShader.get()));
	DEFAULT_SPRITE3D_MATERIAL[5].reset(CreateDefaultSprite3DBlend(BlendMode::AX_BLENDMODE_INVSRC, vertexShader.get(), pixelShader.get()));
}

void DefaultMaterial::CreateDefaultFbxMaterial()
{
	DEFAULT_FBX_MATERIAL = std::make_unique<Material>();

	//�e�N�X�`���f�[�^�ݒ�
	DEFAULT_FBX_MATERIAL->textureData = DEFAULT_TEXTURE;

	//���_�V�F�[�_�̓ǂݍ���
	DEFAULT_FBX_MATERIAL->vertexShader = std::make_unique<Shader>();
	DEFAULT_FBX_MATERIAL->vertexShader->Create("Resources/Shaders/3D/Model/ModelSimpleVS.hlsl");

	//�s�N�Z���V�F�[�_�̓ǂݍ���
	DEFAULT_FBX_MATERIAL->pixelShader = std::make_unique<Shader>();
	DEFAULT_FBX_MATERIAL->pixelShader->Create("Resources/Shaders/3D/Model/ModelSimplePS.hlsl", "main", "ps_5_0", Shader::ShaderType::PS);

	//���_���C�A�E�g�ݒ�
	DEFAULT_FBX_MATERIAL->inputLayouts = {
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0  }, // float3��POSITION
	{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0   }, // float3��NORMAL
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0  }, // float2��TEXCOORD
	{ "TANGENT",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }, // float3��TANGENT
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }, // float4��COLOR
	};

	//���[�g�V�O�l�`���ݒ�
	DEFAULT_FBX_MATERIAL->rootSignature = std::make_unique<RootSignature>();
	DEFAULT_FBX_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
	DEFAULT_FBX_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 1);//b1
	DEFAULT_FBX_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 2);//b2
	DEFAULT_FBX_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 3);//b3
	DEFAULT_FBX_MATERIAL->rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0
	DEFAULT_FBX_MATERIAL->rootSignature->AddStaticSampler(0);//s0
	DEFAULT_FBX_MATERIAL->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());


	DEFAULT_FBX_MATERIAL->blenddesc = CreateBlend(BlendMode::AX_BLENDMODE_ALPHA);

	DEFAULT_FBX_MATERIAL->cullMode = D3D12_CULL_MODE_NONE;
	//����
	DEFAULT_FBX_MATERIAL->Initialize();
}

void DefaultMaterial::CreateDefaultParticleMaterial()
{
	DEFAULT_PARTICLE_MATERIAL = std::make_unique<Material>();

	//�e�N�X�`���f�[�^�ݒ�
	DEFAULT_PARTICLE_MATERIAL->textureData = DEFAULT_TEXTURE;

	//���_�V�F�[�_�̓ǂݍ���
	DEFAULT_PARTICLE_MATERIAL->vertexShader = std::make_unique<Shader>();
	DEFAULT_PARTICLE_MATERIAL->vertexShader->Create("Resources/Shaders/2D/ParticleVS.hlsl");

	//�s�N�Z���V�F�[�_�̓ǂݍ���
	DEFAULT_PARTICLE_MATERIAL->pixelShader = std::make_unique<Shader>();
	DEFAULT_PARTICLE_MATERIAL->pixelShader->Create("Resources/Shaders/2D/ParticlePS.hlsl", "main", "ps_5_0", Shader::ShaderType::PS);

	DEFAULT_PARTICLE_MATERIAL->geometryShader = std::make_unique<Shader>();
	DEFAULT_PARTICLE_MATERIAL->geometryShader->Create("Resources/Shaders/2D/ParticleGS.hlsl", "main", "gs_5_0", Shader::ShaderType::GS);

	//���_���C�A�E�g�ݒ�
	DEFAULT_PARTICLE_MATERIAL->inputLayouts = {
		// xyz���W
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//�J���[
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//�X�P�[��
		{ "SCALE", 0, DXGI_FORMAT_R32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//��]�p
		{ "ROTATION", 0, DXGI_FORMAT_R32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},

	};

	//���[�g�V�O�l�`���ݒ�
	DEFAULT_PARTICLE_MATERIAL->rootSignature = std::make_unique<RootSignature>();
	DEFAULT_PARTICLE_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
	DEFAULT_PARTICLE_MATERIAL->rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0
	DEFAULT_PARTICLE_MATERIAL->rootSignature->AddStaticSampler(0);//s0
	DEFAULT_PARTICLE_MATERIAL->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

	//�u�����h�ݒ�
	DEFAULT_PARTICLE_MATERIAL->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
	DEFAULT_PARTICLE_MATERIAL->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̃A���t�@�l
	DEFAULT_PARTICLE_MATERIAL->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;// 1.0f-�\�[�X�̃A���t�@�l

	DEFAULT_PARTICLE_MATERIAL->primitiveType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;

	DEFAULT_PARTICLE_MATERIAL->depthFlag = false;

	//����
	DEFAULT_PARTICLE_MATERIAL->Initialize();
}

void DefaultMaterial::CreateDefaultMeshMaterial()
{
	//���_�V�F�[�_�̓ǂݍ���
	std::unique_ptr<Shader>vertexShader = std::make_unique<Shader>();
	vertexShader->Create("Resources/Shaders/2D/MeshVS.hlsl");

	//�s�N�Z���V�F�[�_�̓ǂݍ���
	std::unique_ptr<Shader>pixelShader = std::make_unique<Shader>();
	pixelShader->Create("Resources/Shaders/2D/MeshPS.hlsl", "main", "ps_5_0", Shader::ShaderType::PS);

	//�O�p�`�`��p�p�C�v���C���Z�b�g
	DEFAULT_MESH_MATERIAL[0].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BlendMode::AX_BLENDMODE_NOBLEND, vertexShader.get(), pixelShader.get()));
	DEFAULT_MESH_MATERIAL[1].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BlendMode::AX_BLENDMODE_ALPHA, vertexShader.get(), pixelShader.get()));
	DEFAULT_MESH_MATERIAL[2].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BlendMode::AX_BLENDMODE_ADD, vertexShader.get(), pixelShader.get()));
	DEFAULT_MESH_MATERIAL[3].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BlendMode::AX_BLENDMODE_SUB, vertexShader.get(), pixelShader.get()));
	DEFAULT_MESH_MATERIAL[4].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BlendMode::AX_BLENDMODE_MULA, vertexShader.get(), pixelShader.get()));
	DEFAULT_MESH_MATERIAL[5].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BlendMode::AX_BLENDMODE_INVSRC, vertexShader.get(), pixelShader.get()));

	//���C���`��p�p�C�v���C���Z�b�g
	DEFAULT_LINE_MATERIAL[0].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, BlendMode::AX_BLENDMODE_NOBLEND, vertexShader.get(), pixelShader.get()));
	DEFAULT_LINE_MATERIAL[1].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, BlendMode::AX_BLENDMODE_ALPHA, vertexShader.get(), pixelShader.get()));
	DEFAULT_LINE_MATERIAL[2].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, BlendMode::AX_BLENDMODE_ADD, vertexShader.get(), pixelShader.get()));
	DEFAULT_LINE_MATERIAL[3].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, BlendMode::AX_BLENDMODE_SUB, vertexShader.get(), pixelShader.get()));
	DEFAULT_LINE_MATERIAL[4].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, BlendMode::AX_BLENDMODE_MULA, vertexShader.get(), pixelShader.get()));
	DEFAULT_LINE_MATERIAL[5].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, BlendMode::AX_BLENDMODE_INVSRC, vertexShader.get(), pixelShader.get()));
}

void DefaultMaterial::CreateDefaultRainParticleMaterial()
{
	DEFAULT_RAIN_PARTICLE_MATERIAL = std::make_unique<Material>();

	//�e�N�X�`���f�[�^�ݒ�
	DEFAULT_RAIN_PARTICLE_MATERIAL->textureData = DEFAULT_TEXTURE;

	//���_�V�F�[�_�̓ǂݍ���
	DEFAULT_RAIN_PARTICLE_MATERIAL->vertexShader = std::make_unique<Shader>();
	DEFAULT_RAIN_PARTICLE_MATERIAL->vertexShader->Create("Resources/Shaders/2D/RainParticleVS.hlsl");

	//�s�N�Z���V�F�[�_�̓ǂݍ���
	DEFAULT_RAIN_PARTICLE_MATERIAL->pixelShader = std::make_unique<Shader>();
	DEFAULT_RAIN_PARTICLE_MATERIAL->pixelShader->Create("Resources/Shaders/2D/RainParticlePS.hlsl", "main", "ps_5_0", Shader::ShaderType::PS);

	DEFAULT_RAIN_PARTICLE_MATERIAL->geometryShader = std::make_unique<Shader>();
	DEFAULT_RAIN_PARTICLE_MATERIAL->geometryShader->Create("Resources/Shaders/2D/RainParticleGS.hlsl", "main", "gs_5_0", Shader::ShaderType::GS);

	//���_���C�A�E�g�ݒ�
	DEFAULT_RAIN_PARTICLE_MATERIAL->inputLayouts = {
		// xyz���W
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//�J���[
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//�X�P�[��
		{ "SCALE", 0, DXGI_FORMAT_R32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//��]�p
		{ "ROTATION", 0, DXGI_FORMAT_R32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},

	};

	//���[�g�V�O�l�`���ݒ�
	DEFAULT_RAIN_PARTICLE_MATERIAL->rootSignature = std::make_unique<RootSignature>();
	DEFAULT_RAIN_PARTICLE_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
	DEFAULT_RAIN_PARTICLE_MATERIAL->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

	//�u�����h�ݒ�
	DEFAULT_RAIN_PARTICLE_MATERIAL->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
	DEFAULT_RAIN_PARTICLE_MATERIAL->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̃A���t�@�l
	DEFAULT_RAIN_PARTICLE_MATERIAL->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;// 1.0f-�\�[�X�̃A���t�@�l

	DEFAULT_RAIN_PARTICLE_MATERIAL->primitiveType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;

	DEFAULT_RAIN_PARTICLE_MATERIAL->depthFlag = false;

	//����
	DEFAULT_RAIN_PARTICLE_MATERIAL->Initialize();
}

void DefaultMaterial::CreateDefaultPostEffectMaterial()
{
	DEFAULT_POST_EFFECT_MATERIAL = std::make_unique<Material>();

	//���_�V�F�[�_�̓ǂݍ���
	DEFAULT_POST_EFFECT_MATERIAL->vertexShader = std::make_unique<Shader>();
	DEFAULT_POST_EFFECT_MATERIAL->vertexShader->Create("Resources/Shaders/2D/PostEffect/PostEffectTestVS.hlsl");

	//�s�N�Z���V�F�[�_�̓ǂݍ���
	DEFAULT_POST_EFFECT_MATERIAL->pixelShader = std::make_unique<Shader>();
	DEFAULT_POST_EFFECT_MATERIAL->pixelShader->Create("Resources/Shaders/2D/PostEffect/PostEffectTestPS.hlsl", "main", "ps_5_0");

	//���_���C�A�E�g�ݒ�
	DEFAULT_POST_EFFECT_MATERIAL->inputLayouts =
	{
		// xyz���W
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		// uv���W
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//�J���[
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

	DEFAULT_POST_EFFECT_MATERIAL->depthFlag = false;

	DEFAULT_POST_EFFECT_MATERIAL->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
	DEFAULT_POST_EFFECT_MATERIAL->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̃A���t�@�l
	DEFAULT_POST_EFFECT_MATERIAL->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;// 1.0f-�\�[�X�̃A���t�@�l

	//���[�g�V�O�l�`���ݒ�
	DEFAULT_POST_EFFECT_MATERIAL->rootSignature = std::make_unique<RootSignature>();
	DEFAULT_POST_EFFECT_MATERIAL->rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0
	DEFAULT_POST_EFFECT_MATERIAL->rootSignature->AddStaticSampler(0);//s0
	DEFAULT_POST_EFFECT_MATERIAL->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

	//����
	DEFAULT_POST_EFFECT_MATERIAL->Initialize();
}

Material* DefaultMaterial::CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE type, BlendMode mode, Shader* vex, Shader* pix)
{
	Material* material = new Material;

	//���_�V�F�[�_�̓ǂݍ���
	material->vertexShader = std::make_unique<Shader>();
	material->vertexShader->Copy(vex);

	//�s�N�Z���V�F�[�_�̓ǂݍ���
	material->pixelShader = std::make_unique<Shader>();
	material->pixelShader->Copy(pix);

	//���_���C�A�E�g�ݒ�
	material->inputLayouts = {
		//���W
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//uv���W 
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

	material->depthFlag = false;

	material->primitiveType = type;

	switch (mode)
	{
	case BlendMode::AX_BLENDMODE_NOBLEND:
		break;
	case BlendMode::AX_BLENDMODE_ALPHA:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̃A���t�@�l
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;// 1.0f-�\�[�X�̃A���t�@�l
		break;
	case BlendMode::AX_BLENDMODE_ADD:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̒l��100% �g��
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_ONE;// �f�X�g�̒l��100% �g��
		break;
	case BlendMode::AX_BLENDMODE_SUB:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
		material->blenddesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;// �f�X�g����\�[�X�����Z
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̒l��100% �g��
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_ONE;// �f�X�g�̒l��100% �g��
		break;
	case BlendMode::AX_BLENDMODE_MULA:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ZERO;
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_SRC_COLOR;
		break;
	case BlendMode::AX_BLENDMODE_INVSRC:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_INV_DEST_COLOR;// 1.0f-�f�X�g�J���[�̒l
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;// �g��Ȃ�
		break;
	case BlendMode::AX_BLENDMODE_MAX:
		break;
	case BlendMode::AX_BLENDMODE_CUSTOM:
		break;
	default:
		break;
	}

	//���[�g�V�O�l�`���ݒ�
	material->rootSignature = std::make_unique<RootSignature>();
	material->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
	material->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());
	//����
	material->Initialize();

	return material;
}

Material* DefaultMaterial::CreateDefaultSprite2DBlend(BlendMode mode, Shader* vex, Shader* pix)
{
	Material* material = new Material;

	//���_�V�F�[�_�̓ǂݍ���
	material->vertexShader = std::make_unique<Shader>();
	material->vertexShader->Copy(vex);

	//�s�N�Z���V�F�[�_�̓ǂݍ���
	material->pixelShader = std::make_unique<Shader>();
	material->pixelShader->Copy(pix);

	//���_���C�A�E�g�ݒ�
	material->inputLayouts =
	{
		// xyz���W
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		// uv���W
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//�J���[
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

	material->depthFlag = false;

	switch (mode)
	{
	case BlendMode::AX_BLENDMODE_NOBLEND:
		break;
	case BlendMode::AX_BLENDMODE_ALPHA:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̃A���t�@�l
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;// 1.0f-�\�[�X�̃A���t�@�l
		break;
	case BlendMode::AX_BLENDMODE_ADD:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̒l��100% �g��
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_ONE;// �f�X�g�̒l��100% �g��
		break;
	case BlendMode::AX_BLENDMODE_SUB:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
		material->blenddesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;// �f�X�g����\�[�X�����Z
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̒l��100% �g��
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_ONE;// �f�X�g�̒l��100% �g��
		break;
	case BlendMode::AX_BLENDMODE_MULA:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ZERO;
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_SRC_COLOR;
		break;
	case BlendMode::AX_BLENDMODE_INVSRC:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_INV_DEST_COLOR;// 1.0f-�f�X�g�J���[�̒l
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;// �g��Ȃ�
		break;
	case BlendMode::AX_BLENDMODE_MAX:
		break;
	case BlendMode::AX_BLENDMODE_CUSTOM:
		break;
	default:
		break;
	}

	//���[�g�V�O�l�`���ݒ�
	material->rootSignature = std::make_unique<RootSignature>();
	material->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
	material->rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0
	material->rootSignature->AddStaticSampler(0);//s0
	material->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

	//����
	material->Initialize();

	return material;
}

Material* DefaultMaterial::CreateDefaultSprite3DBlend(BlendMode mode, Shader* vex, Shader* pix)
{
	Material* material = new Material;

//���_�V�F�[�_�̓ǂݍ���
	material->vertexShader = std::make_unique<Shader>();
	material->vertexShader->Copy(vex);

	//�s�N�Z���V�F�[�_�̓ǂݍ���
	material->pixelShader = std::make_unique<Shader>();
	material->pixelShader->Copy(pix);


	//���_���C�A�E�g�ݒ�
	material->inputLayouts =
	{
		// xyz���W
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		// uv���W
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//�J���[
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

	material->blenddesc.AlphaToCoverageEnable = true;

	switch (mode)
	{
	case BlendMode::AX_BLENDMODE_NOBLEND:

		break;
	case BlendMode::AX_BLENDMODE_ALPHA:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̃A���t�@�l
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;// 1.0f-�\�[�X�̃A���t�@�l
		break;
	case BlendMode::AX_BLENDMODE_ADD:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̒l��100% �g��
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_ONE;// �f�X�g�̒l��100% �g��
		break;
	case BlendMode::AX_BLENDMODE_SUB:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
		material->blenddesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;// �f�X�g����\�[�X�����Z
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̒l��100% �g��
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_ONE;// �f�X�g�̒l��100% �g��
		break;
	case BlendMode::AX_BLENDMODE_MULA:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ZERO;
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_SRC_COLOR;
		break;
	case BlendMode::AX_BLENDMODE_INVSRC:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// �u�����h��L��
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_INV_DEST_COLOR;// 1.0f-�f�X�g�J���[�̒l
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;// �g��Ȃ�
		break;
	case BlendMode::AX_BLENDMODE_MAX:
		break;
	case BlendMode::AX_BLENDMODE_CUSTOM:
		break;
	default:
		break;
	}

	//���[�g�V�O�l�`���ݒ�
	material->rootSignature = std::make_unique<RootSignature>();
	material->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
	material->rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0
	material->rootSignature->AddStaticSampler(0);//s0
	material->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

	//����
	material->Initialize();

	return material;
}

D3D12_BLEND_DESC DefaultMaterial::CreateBlend(BlendMode mode)
{
	D3D12_BLEND_DESC blend = CD3DX12_BLEND_DESC(D3D12_DEFAULT);

	switch (mode)
	{
	case BlendMode::AX_BLENDMODE_NOBLEND:

		break;
	case BlendMode::AX_BLENDMODE_ALPHA:
		blend.AlphaToCoverageEnable = true;
		blend.IndependentBlendEnable = false;
		for (int i = 0; i < _countof(blend.RenderTarget); ++i)
		{
			//���₷�����邽�ߕϐ���
			auto rt = blend.RenderTarget[i];
			rt.BlendEnable = true;
			rt.LogicOpEnable = false;
			rt.SrcBlend = D3D12_BLEND_SRC_ALPHA;
			rt.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
			rt.BlendOp = D3D12_BLEND_OP_ADD;
			rt.SrcBlendAlpha = D3D12_BLEND_SRC_ALPHA;
			rt.DestBlendAlpha = D3D12_BLEND_INV_SRC_ALPHA;
			rt.BlendOpAlpha = D3D12_BLEND_OP_ADD;
			rt.LogicOp = D3D12_LOGIC_OP_NOOP;
			rt.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
		}
		break;
	case BlendMode::AX_BLENDMODE_ADD:
		blend.RenderTarget[0].BlendEnable = true;// �u�����h��L��
		blend.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̒l��100% �g��
		blend.RenderTarget[0].DestBlend = D3D12_BLEND_ONE;// �f�X�g�̒l��100% �g��
		break;
	case BlendMode::AX_BLENDMODE_SUB:
		blend.RenderTarget[0].BlendEnable = true;// �u�����h��L��
		blend.RenderTarget[0].BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;// �f�X�g����\�[�X�����Z
		blend.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̒l��100% �g��
		blend.RenderTarget[0].DestBlend = D3D12_BLEND_ONE;// �f�X�g�̒l��100% �g��
		break;
	case BlendMode::AX_BLENDMODE_MULA:
		blend.RenderTarget[0].BlendEnable = true;// �u�����h��L��
		blend.RenderTarget[0].SrcBlend = D3D12_BLEND_ZERO;
		blend.RenderTarget[0].DestBlend = D3D12_BLEND_SRC_COLOR;
		break;
	case BlendMode::AX_BLENDMODE_INVSRC:
		blend.RenderTarget[0].BlendEnable = true;// �u�����h��L��
		blend.RenderTarget[0].SrcBlend = D3D12_BLEND_INV_DEST_COLOR;// 1.0f-�f�X�g�J���[�̒l
		blend.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;// �g��Ȃ�
		break;
	case BlendMode::AX_BLENDMODE_MAX:
		break;
	case BlendMode::AX_BLENDMODE_CUSTOM:
		break;
	default:
		break;
	}

	return blend;
}

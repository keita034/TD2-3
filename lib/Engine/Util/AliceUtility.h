#pragma once
#include"ErrorException.h"
#include"AliceMathUtility.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"ComputePipelineState.h"
#include"RootSignature.h"
#include"Shader.h"

struct TextureData
{
	//�e�N�X�`���o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;

	//�f�X�N�v���^�q�[�v
	Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> srvHeap;

	//GPU�f�X�N�v���^�n���h��
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle{};

	//����
	size_t width = 0;
	//�c��
	size_t height = 0;

	//�J���[
	AliceMathF::Vector4 color = { 1.0f,1.0f,1.0f,1.0f };

	std::string path;

	uint32_t textureHandle;

	~TextureData();

private:
	char PADING[4]{};
};

//���W�ϊ��s��
struct ConstBufferDataTransform
{
	AliceMathF::Matrix4 mat;//3D�ϊ��s��
};


struct PosColor
{
	AliceMathF::Vector3 pos;//���W
	AliceMathF::Vector4 color;//�J���[
};

struct PosNormalUv
{
	AliceMathF::Vector3 pos;//���W
	AliceMathF::Vector3 normal;//�@���x�N�g��
	AliceMathF::Vector2 uv;//uv���W
};

//���W�EUV�E�J���[
struct PosUvColor
{
	AliceMathF::Vector3 pos;//���W
	AliceMathF::Vector2 uv;//uv���W
	AliceMathF::Vector4 color;//�J���[
};

typedef struct
{
	//�p�C�v���C���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	//���[�g�V�O�l�`��
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	//�f�X�N�v���^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;
	//�f�X�N�v���^�����W
	D3D12_DESCRIPTOR_RANGE descriptorRange;
	//�X�v���C�g��
	UINT nextIndex;
}ModelShareVaria;

//�p�C�v���C���E���[�g�V�O�l�`���Z�b�g
struct PipelineSet
{
	//�p�C�v���C���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	//���[�g�V�O�l�`��
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
};

struct worldViewpojCamera
{
	//���[���h�s��
	AliceMathF::Matrix4 world;
	//���[���h���W
	AliceMathF::Matrix4 matWorld;
	//�J�������W(���[���h���W)
	AliceMathF::Vector3 cameraPos;
};

struct worldViewpojCameraWVP
{
	//���[���h�s��
	AliceMathF::Matrix4 world;
	//���[���h���W
	AliceMathF::Matrix4 matWorld;
	//�J�������W(���[���h���W)
	AliceMathF::Vector3 cameraPos;
	AliceMathF::Matrix4 WVP;

};

//�}�e���A���悤�萔�o�b�t�@�\����
struct ConstBuffDataMaterial
{
	//�A���r�G���g�W��
	AliceMathF::Vector3 ambient;
	//�p�f�B���O
	float pad1;
	//�f�B�t���[�Y�W��
	AliceMathF::Vector3 diffuse;
	//�p�f�B���O
	float pad2;
	//�X�y�L�����[�W��
	AliceMathF::Vector3 specular;
	//�A���t�@
	float alpha;
};

//�}�e���A��
struct ModelMaterial
{
	//�}�e���A����
	std::string name;
	//�A���r�G���g�e���x
	AliceMathF::Vector3 ambient = { 0.06f, 0.06f, 0.06f };
	//�f�B�t���[�Y�e���x
	AliceMathF::Vector3 diffuse = { 0.0f,0.0f,0.0f };
	//�X�y�L�����[�e���x
	AliceMathF::Vector3 specular = { 0.0f,0.0f,0.0f };

	AliceMathF::Vector3 emission = { 0.0f,0.0f,0.0f };

	float shininess = 1.0f;
	//�A���t�@
	float alpha = 1.0f;
	//�e�N�X�`���t�@�C����
	std::string textureFiename;

	ConstBuffDataMaterial GetConstBuffMaterial();
};

//�o�b�t�@�֘A
struct Buff
{
	//���_�o�b�t�@
	std::unique_ptr<VertexBuffer> vertexBuffer;
	//���_�}�b�v
	PosColor* vertMap;
	//�C���f�b�N�X�o�b�t�@
	std::unique_ptr<IndexBuffer> indexBuffer;
	//�C���f�b�N�X�}�b�v
	uint32_t* indexMap;

	Buff() = default;
	~Buff() = default;

private:
	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Buff& operator=(const Buff&) = delete;
	Buff(const Buff&) = delete;

};

//�u�����h���[�h
enum class BlendMode
{
	AX_BLENDMODE_NOBLEND,//�m�[�u�����h�i�f�t�H���g�j
	AX_BLENDMODE_ALPHA,//���u�����h
	AX_BLENDMODE_ADD,//���Z�u�����h
	AX_BLENDMODE_SUB,//���Z�u�����h
	AX_BLENDMODE_MULA,//��Z�u�����h
	AX_BLENDMODE_INVSRC,//���]�u�����h

	AX_BLENDMODE_MAX,//�u�����h��ސ�

	AX_BLENDMODE_CUSTOM = -1,
};

//�R���s���[�g�V�F�[�_�[�֘A(�N���X����)
struct ComputeRelation
{
	ComputeRelation();
	~ComputeRelation();

	//�p�C�v���C���X�e�[�g
	std::shared_ptr<ComputePipelineState> computePipelineState;
	//���[�g�V�O�l�`��
	std::unique_ptr<RootSignature> rootSignature;

	std::unique_ptr<RootSignature> rootSignature1;
	//�V�F�[�_�[
	std::unique_ptr<Shader> computeShader;

private:
	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	ComputeRelation& operator=(const ComputeRelation&) = delete;
	ComputeRelation(const ComputeRelation&) = delete;
};
#pragma once
#include"AliceMath.h"
#include"Camera.h"
#include"DirectX12Core.h"
#include"WindowsApp.h"
#include"ModelInterface.h"

class Model
{

private:

	HRESULT result;
	char PADDING[4];
	ID3D12Device* device = nullptr;
	ID3D12GraphicsCommandList* cmdList = nullptr;
	DirectX::TexMetadata metadata{};
	DirectX::ScratchImage scratchImg{};
	DirectX::ScratchImage mipChain{};

	//�p�C�v���C���X�e�[�g
	static Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	//���[�g�V�O�l�`��
	static Microsoft::WRL::ComPtr <ID3D12RootSignature> rootSignature;
	//SRV�̍ő��
	static const size_t kMaxSRVCount;
	//�f�X�N�v���^�q�[�v
	static ID3D12DescriptorHeap* srvHeap;
	//�f�X�N�v���^�����W
	static D3D12_DESCRIPTOR_RANGE descriptorRange;
	//�X�v���C�g��
	static UINT nextIndex;

	//���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	//���_�}�b�v
	PosUvColor* vertMap;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//�C���f�b�N�X�o�b�t�@�̐���
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuff;
	////�C���f�b�N�X�o�b�t�@���}�b�s���O
	uint16_t* indexMap;
	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};
	//�e�N�X�`���o�b�t�@
	ID3D12Resource* texBuff = nullptr;
	//GPU�f�X�N�v���^�n���h��
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle;
	//CPU�f�X�N�v���^�n���h��
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle;
	//�萔�o�b�t�@��GPU���\�[�X�̃|�C���^
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform = nullptr;
	//�萔�o�b�t�@�̃}�b�s���O�p�|�C���^
	SpriteConstBufferDataTransform* constMapTransform = nullptr;
	char PADDING1[4];
	//�C���f�b�N�X�̐�
	UINT maxIndex;
	char PADDING2[4];
	//���_�̐�
	UINT maxVert;

	//�L���[�u�̃C���f�b�N�X���ƒ��_��
	const UINT cubeMaxIndex = 36;
	const UINT cubeMaxVert = 24;

	//�~���̃C���f�b�N�X���ƒ��_��
	const UINT coneMaxIndex = 189;
	const UINT coneMaxVert = 66;

	//�~���̃C���f�b�N�X���ƒ��_��
	const UINT cylinderMaxIndex = 384;
	const UINT cylinderMaxVert = 132;

	//���̃C���f�b�N�X���ƒ��_��
	const UINT sphereMaxIndex = 3072;
	const UINT sphereMaxVert = 560;

public:
	Model();
	~Model();

	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	/// <param name="shape">��������I�u�W�F�N�g�̎��</param>
	void Create(ModelShape shape);

	/// <summary>
	/// �I�u�W�F�N�g�Ƀe�N�X�`�����Z�b�g����
	/// </summary>
	/// <param name="filePath">�e�N�X�`���܂ł̃t�@�C���p�X</param>
	void SetTexture(const wchar_t* filePath);

	///<summary>
	///�X�V
	///</summary>
	///<param name="pos">���W</param>
	///<param name="rot">��]</param>
	///<param name="scale">�g�嗦</param>
	/// ///<param name="color"> �J���[</param>
	void Update(const AliceMath::Vector3& pos = { 0.0f, 0.0f, 0.0f }, const AliceMath::Vector3& rot = { 0.0f, 0.0f, 0.0f }, const AliceMath::Vector3& scale = { 1.0f,1.0f, 1.0f }, const AliceMath::Vector4& color = { 1.0f,1.0f, 1.0f, 1.0f });

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="camera">�J����</param>
	void Draw(Camera*& camera);

private:
	//�L���[�u����
	void CreateCube();

	//�~������
	void CreateCone();

	//�~������
	void CreateCylinder();

	//������
	void CreateSphere();

	//�p�C�v���C���̐���
	void CreatPipeline();
	//�f�X�N�v���^�q�[�v�̐���
	void CreateDescriptorHeap();
	//�f�X�N�v���^�����W�̐���
	void CreateDescriptorRange();
	//�V�F�[�_�|���\�[�X�r���[����
	void CreateShaderResourceView();
	//���_�o�b�t�@�E�C���f�b�N�X����
	void CreatVertexIndexBuffer();
	//�e�N�X�`���o�b�t�@����
	void CreatTextureBuffer();

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Model& operator=(const Model&) = delete;
	Model(const Model&) = delete;
};


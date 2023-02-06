#include"ModelMesh.h"
#include<atldef.h>
ModelMesh::~ModelMesh()
{
}
void ModelMesh::CreateBuffer()
{
	//���_�o�b�t�@����
	//�S�̂̃T�C�Y�v�Z
	size_t size = vertices.size();
	//����̃T�C�Y�v�Z
	size_t stride = sizeof(PosNormUvTangeCol);
	//����
	vertexBuffer = std::make_shared<ComputeVertexBuffer>();
	vertexBuffer->Create(size, stride);
	if (!vertexBuffer->IsValid())
	{
		printf("���_�o�b�t�@�̐����Ɏ��s\n");
		return;
	}

	//�C���f�b�N�X�o�b�t�@����
	//�S�̂̃T�C�Y�v�Z
	size = indices.size();
	uint32_t* indice = indices.data();
	//����
	indexBuffer = std::make_shared<IndexBuffer>();
	indexBuffer->Create(size, indice);
	if (!indexBuffer->IsValid())
	{
		printf("�C���f�b�N�X�o�b�t�@�̐����Ɏ��s\n");
		return;
	}

	materialBuffer = std::make_shared<ConstantBuffer>();
	materialBuffer->Create(sizeof(ModelMaterial));
	if (!materialBuffer->IsValid())
	{
		printf("�}�e���A���p�萔�o�b�t�@�̐����Ɏ��s\n");
		return;
	}

	constBoneBuffer = std::make_unique<ConstantBuffer>();
	constBoneBuffer->Create(sizeof(BoneData));
	if (!constBoneBuffer->IsValid())
	{
		printf("�{�[���f�[�^�p�萔�o�b�t�@�̐����Ɏ��s\n");
		return;
	}
	constBoneBuffer->Update(bonedata.boneMat.data());

	computeInputBuff = std::make_shared<StructuredBuffer>();
	computeInputBuff->Create(vertices.size(),sizeof(PosNormUvTangeColSkin));
	if (!computeInputBuff->IsValid())
	{
		printf("�R���s���[�g�V�F�[�_�̓��͗p�f�[�^�o�b�t�@�̐����Ɏ��s\n");
		return;
	}

	boneBuffer = std::make_shared<ConstantBuffer>();
	boneBuffer->Create(sizeof(AliceMathF::Matrix4) * MAX_BONES);
	if (!boneBuffer->IsValid())
	{
		printf("�R���s���[�g�V�F�[�_�̒萔�o�b�t�@�̐����Ɏ��s\n");
		return;
	}
	boneBuffer->Update(bonedata.boneMat.data());

	// �ϊ��s��̓o�^
	materialBuffer->Update(&material);

	skinComputeInput.vertices.resize(vertices.size());

	vertice.resize(vertices.size());

	for (size_t i = 0; i < vertices.size(); ++i)
	{

		vertice[i].position = vertices[i].position;
		vertice[i].normal = vertices[i].normal;
		vertice[i].uv = vertices[i].uv;
		vertice[i].tangent = vertices[i].tangent;
		vertice[i].color = vertices[i].color;
	}

	vertexBuffer->Update(vertice.data());
}

void ModelMesh::FillVertex()
{

	computeInputBuff->Update(vertices.data());

	BoneData data;
	
	for (size_t i = 0; i < vecBones.size(); i++)
	{
		data.boneMat[i] = vecBones[i].matrix;
	}

	constBoneBuffer->Update(data.boneMat.data());
}

void ModelMesh::InitializeVertex()
{
	for (size_t i = 0; i < vertices.size(); ++i)
	{

		vertice[i].position = vertices[i].position;
		vertice[i].normal = vertices[i].normal;
		vertice[i].uv = vertices[i].uv;
		vertice[i].tangent = vertices[i].tangent;
		vertice[i].color = vertices[i].color;
	}

	vertexBuffer->Update(vertice.data());
}

void ModelMesh::InitializeVertexPos()
{
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		vertice[i].position = vertices[i].position;
		vertice[i].normal = vertices[i].normal;
	}

	vertexBuffer->Update(vertice.data());
}

const std::vector<PosNormUvTangeCol> ModelMesh::GetVertices()
{
	return vertice;
}

const std::vector<uint32_t> ModelMesh::GetIndices()
{
	return indices;
}

void ModelMesh::Draw(ID3D12GraphicsCommandList* cmdList, Transform* transform, Light* light)
{
	D3D12_VERTEX_BUFFER_VIEW vbView = vertexBuffer->GetView();
	D3D12_INDEX_BUFFER_VIEW ibView = indexBuffer->GetView();

	for (TextureData* texture : textures)
	{
		// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
		cmdList->SetGraphicsRootConstantBufferView(0, transform->GetconstBuff()->GetGPUVirtualAddress());
		cmdList->SetGraphicsRootConstantBufferView(1, materialBuffer->GetAddress());
		light->SetConstBufferView(cmdList, 2);

		// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
		cmdList->IASetVertexBuffers(0, 1, &vbView);

		//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
		cmdList->IASetIndexBuffer(&ibView);

		// SRV�q�[�v�̐ݒ�R�}���h
		cmdList->SetDescriptorHeaps(1, texture->srvHeap.GetAddressOf());

		// SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^2�Ԃɐݒ�
		cmdList->SetGraphicsRootDescriptorTable(4, texture->gpuHandle);

		// �`��R�}���h
		cmdList->DrawIndexedInstanced(static_cast<UINT>(indices.size()), 1, 0, 0, 0);

		vertexBuffer->Transition(D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);

	}
}

void ModelMesh::Update(ComputeRelation* computeRelation, ID3D12GraphicsCommandList* cmdList)
{
	FillVertex();

	//�f�X�N�v���^�q�[�v���Z�b�g
	ID3D12DescriptorHeap* descriptorHeaps[] =
	{
		DirectX12Core::GetInstance()->GetSRVDescriptorHeap()->GetHeap(),
	};
	cmdList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
	//���[�g�V�O�l�`�����Z�b�g
	cmdList->SetComputeRootSignature(computeRelation->rootSignature->GetRootSignature());
	//�p�C�v���C���X�e�[�g���Z�b�g
	cmdList->SetPipelineState(computeRelation->computePipelineState->GetPipelineState());

	cmdList->SetComputeRootDescriptorTable(0, computeInputBuff->GetAddress());
	cmdList->SetComputeRootConstantBufferView(1, constBoneBuffer->GetAddress());

	cmdList->SetComputeRootDescriptorTable(2, vertexBuffer->GetAddress());

	cmdList->Dispatch(static_cast<UINT>(vertices.size() / 256 +1), 1, 1);
}

void  ModelMesh::DrawBgin()
{ 
	vertexBuffer->Transition(D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_GENERIC_READ);
};
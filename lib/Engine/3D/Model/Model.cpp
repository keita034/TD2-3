#include "Model.h"
#include"PrimitiveModel.h"
#include"objModel.h"

Light* Model::light = nullptr;
Microsoft::WRL::ComPtr<ID3D12Device> Model::device;
Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> Model::cmdList;
std::vector<std::string>Model::filePaths;
std::unordered_map<std::string, std::unique_ptr<ModelData>> Model::modelDatas;
uint32_t Model::modelCount;
ComputeRelation Model::computeRelation;

AliceMathF::Matrix4& Model::GetMatWorld()
{
	return modelData->matWorld;
}

const std::vector<PosNormalUv> Model::GetVertices()
{
	return modelData->vertices;
}

const std::vector<uint32_t> Model::GetIndices()
{
	return modelData->indices;
}

void Model::SetLight(Light* light_)
{
	light = light_;
}

void Model::SetModel(uint32_t modelHandle)
{
	modelData = modelDatas[filePaths[modelHandle]].get();
}

void Model::SetBlendModel(const std::vector<uint32_t>& models)
{
	for (size_t i = 0; i < models.size(); i++)
	{
		blendModels.push_back(modelDatas[filePaths[models[i]]].get());
	}
}

void Model::ClearBlendModel()
{
	blendModels.clear();
}

uint32_t Model::CreatePrimitiveModel(ModelShape type)
{
	std::string path;

	switch (type)
	{
	case ModelShape::Cube:
		path = "Cube";
		break;
	case ModelShape::Sphere:
		path = "Sphere";
		break;
	case ModelShape::Capsule:
		path = "Capsule";
		break;
	case ModelShape::Cylinder:
		path = "Cylinder";
		break;
	case ModelShape::Cone:
		path = "Cone";
		break;
	}

	//���ǂݍ��񂾂��Ƃ�����t�@�C���͂��̂܂ܕԂ�
	auto itr = find_if(modelDatas.begin(), modelDatas.end(), [&](std::pair<const std::string, std::unique_ptr<ModelData, std::default_delete<ModelData>>>& p)
		{
			return p.second->filePath == path;
		});
	if (itr == modelDatas.end())
	{
		modelCount++;

		std::unique_ptr<ModelData> data;
		data = std::make_unique<ModelData>();

		PrimitiveModel::Create(type, data.get());

		data->modelHandle = modelCount;

		data->filePath = path;

		modelDatas[path] = std::move(data);

		filePaths[modelCount] = path;

		return modelCount;
	}
	else
	{
		uint32_t modelHandle = modelDatas[path]->modelHandle;

		return modelHandle;
	}
}

uint32_t Model::CreateObjModel(const std::string& filePath, bool smoothing)
{

	std::string path = filePath;

	path += smoothing ? " : true" : " : false";

	//���ǂݍ��񂾂��Ƃ�����t�@�C���͂��̂܂ܕԂ�
	auto itr = find_if(modelDatas.begin(), modelDatas.end(), [&](std::pair<const std::string, std::unique_ptr<ModelData, std::default_delete<ModelData>>>& p)
		{
			return p.second->filePath == path;
		});

	if (itr == modelDatas.end())
	{

		uint32_t modelHandle = modelCount;

		std::unique_ptr<ModelData> data;
		data = std::make_unique<ModelData>();

		objModel::Create(filePath.c_str(), smoothing, data.get());

		data->modelHandle = modelCount;

		data->filePath = path;

		modelDatas[path] = std::move(data);

		filePaths[modelCount] = path;

		modelCount++;

		return modelHandle;
	}
	else
	{

		uint32_t modelHandle = modelDatas[path]->modelHandle;

		return modelHandle;
	}
}

void Model::Draw(Transform& transform, Material* material)
{
	assert(modelData);

	modelData->vertexBuffer->Transition(D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_GENERIC_READ);

	if (!material)
	{
		modelData->modelMaterialData = DefaultMaterial::GetDefaultMaterial()->DEFAULT_TEXTURE_MATERIAL.get();
	}
	else
	{
		modelData->modelMaterialData = material;
	}

	D3D12_VERTEX_BUFFER_VIEW vbView = modelData->vertexBuffer->GetView();
	D3D12_INDEX_BUFFER_VIEW ibView = modelData->indexBuffer->GetView();

	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	cmdList->SetPipelineState(modelData->modelMaterialData->pipelineState->GetPipelineState());
	cmdList->SetGraphicsRootSignature(modelData->modelMaterialData->rootSignature->GetRootSignature());

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g

	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->IASetIndexBuffer(&ibView);

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	cmdList->SetGraphicsRootConstantBufferView(0, transform.GetconstBuff()->GetGPUVirtualAddress());
	cmdList->SetGraphicsRootConstantBufferView(1, modelData->constBuffMaterial->GetAddress());
	light->SetConstBufferView(cmdList.Get(), 2);
	cmdList->SetGraphicsRootConstantBufferView(3, modelData->constBuffVelocity->GetAddress());

	// SRV�q�[�v�̐ݒ�R�}���h
	cmdList->SetDescriptorHeaps(1, modelData->textureData->srvHeap.GetAddressOf());

	// SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^2�Ԃɐݒ�
	cmdList->SetGraphicsRootDescriptorTable(4, modelData->textureData->gpuHandle);

	// �`��R�}���h
	cmdList->DrawIndexedInstanced(modelData->maxIndex, 1, 0, 0, 0);

	modelData->vertexBuffer->Transition(D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);

}

void Model::BlendShapeUpdate(float& t)
{
	if (t > 1.0f)
	{
		t = 0.0000000001f;
	}

	float length = static_cast<float>(blendModels.size());
	float progress = (length) * t;
	float index = std::floor(progress);
	float weight = progress - index;

	modelData->csTime->Update(&weight);

	if (index <= 0.0f)
	{
		modelData->csInputVer->Update(modelData->vertices.data());

	}
	else
	{
		modelData->csInputVer->Update(blendModels[static_cast<size_t>(index - 1.0f)]->vertices.data());

	}

	modelData->csInputBlendVer->Update(blendModels[static_cast<size_t>(index)]->vertices.data());

	//�f�X�N�v���^�q�[�v���Z�b�g
	ID3D12DescriptorHeap* descriptorHeaps[] =
	{
		DirectX12Core::GetInstance()->GetSRVDescriptorHeap()->GetHeap(),
	};
	cmdList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
	//���[�g�V�O�l�`�����Z�b�g
	cmdList->SetComputeRootSignature(computeRelation.rootSignature->GetRootSignature());
	//�p�C�v���C���X�e�[�g���Z�b�g
	cmdList->SetPipelineState(computeRelation.computePipelineState->GetPipelineState());

	cmdList->SetComputeRootDescriptorTable(0, modelData->csInputBlendVer->GetAddress());
	cmdList->SetComputeRootDescriptorTable(1, modelData->csInputVer->GetAddress());

	cmdList->SetComputeRootConstantBufferView(2, modelData->csTime->GetAddress());

	cmdList->SetComputeRootDescriptorTable(3, modelData->vertexBuffer->GetAddress());

	cmdList->Dispatch(static_cast<UINT>(modelData->vertices.size()), 1, 1);
}

void Model::EffectDraw(Transform* transform, float velocity, Material* material)
{
	D3D12_VERTEX_BUFFER_VIEW vbView = modelData->vertexBuffer->GetView();
	D3D12_INDEX_BUFFER_VIEW ibView = modelData->indexBuffer->GetView();

	assert(modelData);


	if (!material)
	{
		modelData->modelMaterialData = DefaultMaterial::GetDefaultMaterial()->DEFAULT_TEXTURE_MATERIAL.get();
	}
	else
	{
		modelData->modelMaterialData = material;
	}

	modelData->constBuffVelocity->Update(&velocity);

	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	cmdList->SetPipelineState(modelData->modelMaterialData->pipelineState->GetPipelineState());
	cmdList->SetGraphicsRootSignature(modelData->modelMaterialData->rootSignature->GetRootSignature());

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g

	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->IASetIndexBuffer(&ibView);

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	cmdList->SetGraphicsRootConstantBufferView(0, transform->GetconstBuff()->GetGPUVirtualAddress());
	cmdList->SetGraphicsRootConstantBufferView(1, modelData->constBuffMaterial->GetAddress());
	light->SetConstBufferView(cmdList.Get(), 2);
	cmdList->SetGraphicsRootConstantBufferView(3, modelData->constBuffVelocity->GetAddress());

	// SRV�q�[�v�̐ݒ�R�}���h
	cmdList->SetDescriptorHeaps(1, modelData->textureData->srvHeap.GetAddressOf());

	// SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^2�Ԃɐݒ�
	cmdList->SetGraphicsRootDescriptorTable(4, modelData->textureData->gpuHandle);

	// �`��R�}���h
	cmdList->DrawIndexedInstanced(modelData->maxIndex, 1, 0, 0, 0);
}

bool Model::RotationUV(float angle)
{
	AliceMathF::Matrix3 mat;
	mat.MakeRotation(angle);

	for (PosNormalUv& vertice : modelData->vertices)
	{
		vertice.uv = AliceMathF::Vec2Mat3Mul(vertice.uv, mat);
	}

	modelData->vertexBuffer->Update(modelData->vertices.data());

	return true;
}

void Model::SetTexture(uint32_t handle)
{
	modelData->textureData = TextureManager::GetTextureData(handle);
}

void Model::FlipUV(bool inverseU, bool inverseV)
{
	for (PosNormalUv& vertice : modelData->vertices)
	{
		if (inverseU)
		{
			vertice.uv.x = 1.0f - vertice.uv.x;
		}

		if (inverseV)
		{
			vertice.uv.y = 1.0f - vertice.uv.y;
		}
	}

	modelData->vertexBuffer->Update(modelData->vertices.data());
}

void Model::CommonInitialize()
{
	device = DirectX12Core::GetInstance()->GetDevice();
	cmdList = DirectX12Core::GetInstance()->GetCommandList();

	//������

	//���[�g�V�O�l�`���̏�����
	computeRelation.rootSignature = std::make_unique<RootSignature>();
	//ComputeShader�p
	computeRelation.rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0

	computeRelation.rootSignature->Add(RootSignature::RangeType::SRV, 1);//t1

	computeRelation.rootSignature->Add(RootSignature::RootType::CBV, 0);//c0
	//�v�Z���ꂽ���_�f�[�^�p
	computeRelation.rootSignature->Add(RootSignature::RangeType::UAV, 0);//u0
	//����
	computeRelation.rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

	//�V�F�[�_�[�̏�����
	computeRelation.computeShader = std::make_unique<Shader>();
	//�V�F�[�_�[�ǂݍ���
	computeRelation.computeShader->Create("Resources/Shaders/3D/Model/BlendShapeCS.hlsl", "main", "cs_5_0", Shader::ShaderType::CS);

	//�p�C�v���C���X�e�[�g������
	computeRelation.computePipelineState = std::make_shared<ComputePipelineState>();
	//�V�F�[�_�[���Z�b�g
	computeRelation.computePipelineState->SetShader(*computeRelation.computeShader->GetShader());
	//���[�g�V�O�l�`���̃Z�b�g
	computeRelation.computePipelineState->SetRootSignature(computeRelation.rootSignature.get());
	//�p�C�v���C���X�e�[�g�̐���
	computeRelation.computePipelineState->Create(DirectX12Core::GetInstance()->GetDevice().Get());

	filePaths.resize(maxModel);
}

ModelData::~ModelData()
{
}

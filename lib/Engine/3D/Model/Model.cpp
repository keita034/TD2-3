#include "Model.h"
#include"PrimitiveModel.h"
#include"objModel.h"

Light* Model::light = nullptr;
Microsoft::WRL::ComPtr<ID3D12Device> Model::device;
Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> Model::cmdList;
std::vector<std::string>Model::filePaths;
std::unordered_map<std::string, std::unique_ptr<ModelData>> Model::modelDatas;
uint32_t Model::modelCount;

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

	//一回読み込んだことがあるファイルはそのまま返す
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

	//一回読み込んだことがあるファイルはそのまま返す
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

void Model::Draw(Transform* transform, Material* material)
{
	assert(modelData);

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

	// パイプラインステートとルートシグネチャの設定コマンド
	cmdList->SetPipelineState(modelData->modelMaterialData->pipelineState->GetPipelineState());
	cmdList->SetGraphicsRootSignature(modelData->modelMaterialData->rootSignature->GetRootSignature());

	// プリミティブ形状の設定コマンド
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト

	// 頂点バッファビューの設定コマンド
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	//インデックスバッファビューの設定コマンド
	cmdList->IASetIndexBuffer(&ibView);

	// 定数バッファビュー(CBV)の設定コマンド
	cmdList->SetGraphicsRootConstantBufferView(0, transform->GetconstBuff()->GetGPUVirtualAddress());
	cmdList->SetGraphicsRootConstantBufferView(1, modelData->constBuffMaterial->GetAddress());
	light->SetConstBufferView(cmdList.Get(), 2);

	// SRVヒープの設定コマンド
	cmdList->SetDescriptorHeaps(1, modelData->textureData->srvHeap.GetAddressOf());

	// SRVヒープの先頭にあるSRVをルートパラメータ2番に設定
	cmdList->SetGraphicsRootDescriptorTable(4, modelData->textureData->gpuHandle);

	// 描画コマンド
	cmdList->DrawIndexedInstanced(modelData->maxIndex, 1, 0, 0, 0);
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

	// パイプラインステートとルートシグネチャの設定コマンド
	cmdList->SetPipelineState(modelData->modelMaterialData->pipelineState->GetPipelineState());
	cmdList->SetGraphicsRootSignature(modelData->modelMaterialData->rootSignature->GetRootSignature());

	// プリミティブ形状の設定コマンド
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト

	// 頂点バッファビューの設定コマンド
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	//インデックスバッファビューの設定コマンド
	cmdList->IASetIndexBuffer(&ibView);

	// 定数バッファビュー(CBV)の設定コマンド
	cmdList->SetGraphicsRootConstantBufferView(0, transform->GetconstBuff()->GetGPUVirtualAddress());
	cmdList->SetGraphicsRootConstantBufferView(1, modelData->constBuffMaterial->GetAddress());
	light->SetConstBufferView(cmdList.Get(), 2);
	cmdList->SetGraphicsRootConstantBufferView(3, modelData->constBuffVelocity->GetAddress());

	// SRVヒープの設定コマンド
	cmdList->SetDescriptorHeaps(1, modelData->textureData->srvHeap.GetAddressOf());

	// SRVヒープの先頭にあるSRVをルートパラメータ2番に設定
	cmdList->SetGraphicsRootDescriptorTable(4, modelData->textureData->gpuHandle);

	// 描画コマンド
	cmdList->DrawIndexedInstanced(modelData->maxIndex, 1, 0, 0, 0);
}

void Model::CommonInitialize()
{
	device = DirectX12Core::GetInstance()->GetDevice();
	cmdList = DirectX12Core::GetInstance()->GetCommandList();


	filePaths.resize(maxModel);
}

#include"ModelMesh.h"
#include<atldef.h>
void ModelMesh::CreateBuffer()
{
	//頂点バッファ生成
	//全体のサイズ計算
	size_t size = vertices.size();
	//一つ分のサイズ計算
	size_t stride = sizeof(PosNormUvTangeCol);
	//生成
	vertexBuffer = std::make_shared<ComputeVertexBuffer>();
	vertexBuffer->Create(size, stride);
	if (!vertexBuffer->IsValid())
	{
		printf("頂点バッファの生成に失敗\n");
		return;
	}

	//インデックスバッファ生成
	//全体のサイズ計算
	size = indices.size();
	uint32_t* indice = indices.data();
	//生成
	indexBuffer = std::make_shared<IndexBuffer>();
	indexBuffer->Create(size, indice);
	if (!indexBuffer->IsValid())
	{
		printf("インデックスバッファの生成に失敗\n");
		return;
	}

	materialBuffer = std::make_shared<ConstantBuffer>();
	materialBuffer->Create(sizeof(ModelMaterial));
	if (!materialBuffer->IsValid())
	{
		printf("マテリアル用定数バッファの生成に失敗\n");
		return;
	}

	constBoneBuffer = std::make_unique<ConstantBuffer>();
	constBoneBuffer->Create(sizeof(BoneData));
	if (!constBoneBuffer->IsValid())
	{
		printf("ボーンデータ用定数バッファの生成に失敗\n");
		return;
	}
	constBoneBuffer->Update(bonedata.boneMat.data());

	computeInputBuff = std::make_shared<StructuredBuffer>();
	computeInputBuff->Create(vertices.size(),sizeof(PosNormUvTangeColSkin));
	if (!computeInputBuff->IsValid())
	{
		printf("コンピュートシェーダの入力用データバッファの生成に失敗\n");
		return;
	}

	boneBuffer = std::make_shared<ConstantBuffer>();
	boneBuffer->Create(sizeof(AliceMathF::Matrix4) * MAX_BONES);
	if (!boneBuffer->IsValid())
	{
		printf("コンピュートシェーダの定数バッファの生成に失敗\n");
		return;
	}
	boneBuffer->Update(bonedata.boneMat.data());

	// 変換行列の登録
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

		for (size_t j = 0; j < vertice[i].boneIndex.size(); j++)
		{
			vertice[i].boneIndex[j] = vertices[i].boneIndex[j];
			vertice[i].boneWeight[j] = vertices[i].boneWeight[j];
		}
	}

	vertexBuffer->Update(vertice.data());
}

void ModelMesh::UpdateBoneMatrix(Node* aiNode, AliceMathF::Matrix4 matrix)
{
	static_cast<void>(aiNode);
	static_cast<void>(matrix);

}

void ModelMesh::FillComputeMatrix()
{

}

void ModelMesh::FillVertex()
{
	//GetSkinData(skinData);
	/*skinComputeInput.bone.bones.resize(vecBones.size());

	for (size_t i = 0; i < vecBones.size(); i++)
	{
		skinComputeInput.bone.bones[i] = vecBones[i].matrix;
	}

	boneBuffer->Update(skinComputeInput.bone.bones.data());

	computeInputBuff->Update(vertices.data());*/

	BoneData data;
	
	for (size_t i = 0; i < vecBones.size(); i++)
	{
		data.boneMat[i] = vecBones[i].matrix;
	}

	constBoneBuffer->Update(data.boneMat.data());
}

void ModelMesh::BoneTransform(float frame, std::vector<AliceMathF::Matrix4>& transforms,const fbxAnimation* animation, const AliceMathF::Matrix4& inverseTransform)
{

}

void ModelMesh::GetSkinData(SkinData& data)
{

	size_t i = 0;

	for (auto itr = bones.begin(); itr != bones.end(); ++itr)
	{

		if (32 <= i)
		{
			return;
		}

		data.bones[i] = itr->second.matrix;

		i++;
	}
}

void ModelMesh::CopyResource()
{
	
}
void ModelMesh::Draw(ID3D12GraphicsCommandList* cmdList, Transform* transform, Light* light)
{
	D3D12_VERTEX_BUFFER_VIEW vbView = vertexBuffer->GetView();
	D3D12_INDEX_BUFFER_VIEW ibView = indexBuffer->GetView();

	for (TextureData* texture : textures)
	{
		// 定数バッファビュー(CBV)の設定コマンド
		cmdList->SetGraphicsRootConstantBufferView(0, transform->GetconstBuff()->GetGPUVirtualAddress());
		cmdList->SetGraphicsRootConstantBufferView(1, materialBuffer->GetAddress());
		cmdList->SetGraphicsRootConstantBufferView(4, constBoneBuffer->GetAddress());
		light->SetConstBufferView(cmdList, 2);

		// 頂点バッファビューの設定コマンド
		cmdList->IASetVertexBuffers(0, 1, &vbView);

		//インデックスバッファビューの設定コマンド
		cmdList->IASetIndexBuffer(&ibView);

		// SRVヒープの設定コマンド
		cmdList->SetDescriptorHeaps(1, texture->srvHeap.GetAddressOf());

		// SRVヒープの先頭にあるSRVをルートパラメータ2番に設定
		cmdList->SetGraphicsRootDescriptorTable(5, texture->gpuHandle);

		// 描画コマンド
		cmdList->DrawIndexedInstanced(static_cast<UINT>(indices.size()), 1, 0, 0, 0);

		vertexBuffer->Transition(D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);

	}
}

void ModelMesh::UpdateBoneMatrix(aiNode* aiNode, AliceMathF::Matrix4 matrix)
{
	Bone* bone = &bones[aiNode->mName.C_Str()];

	AliceMathF::Matrix4 world;
	world = matrix;
	world *= bone->animationMatrix;

	bone->matrix = world;
	bone->matrix *= bone->offsetMatirx;

	for (unsigned int n = 0; n < aiNode->mNumChildren; n++)
	{
		UpdateBoneMatrix(aiNode->mChildren[n], world);
	}
}

void ModelMesh::Update(ComputeRelation* computeRelation)
{
	FillComputeMatrix();

	FillVertex();

	ID3D12GraphicsCommandList* cmdList = DirectX12Core::GetInstance()->GetCommandList().Get();

	//デスクプリタヒープをセット
	ID3D12DescriptorHeap* descriptorHeaps[] = {
		DirectX12Core::GetInstance()->GetDescriptorHeap()->GetHeap(),
	};
	cmdList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
	//ルートシグネチャをセット
	cmdList->SetComputeRootSignature(computeRelation->rootSignature->GetRootSignature());
	//パイプラインステートをセット
	cmdList->SetPipelineState(computeRelation->computePipelineState->GetPipelineState());

	cmdList->SetComputeRootDescriptorTable(0, computeInputBuff->GetAddress());
	cmdList->SetComputeRootConstantBufferView(1, boneBuffer->GetAddress());

	cmdList->SetComputeRootDescriptorTable(2, vertexBuffer->GetAddress());

	cmdList->Dispatch(256, 1, 1);

	CopyResource();
}

void  ModelMesh::DrawBgin()
{ 
	vertexBuffer->Transition(D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_GENERIC_READ);
};
#include "fbxModel.h"
#include"FbxLoader.h"

std::shared_ptr<ComputeRelation> fbxModel::computeRelation;


void fbxModel::Initialize()
{
	device = DirectX12Core::GetInstance()->GetDevice();
	cmdList = DirectX12Core::GetInstance()->GetCommandList();

	postureMatBuff = std::make_unique<ConstantBuffer>();

	postureMatBuff->Create(sizeof(AliceMathF::Matrix4));

	AliceMathF::Matrix4 tmp = AliceMathF::Matrix4();
	postureMatBuff->Update(&tmp);
}

void fbxModel::Draw(Transform* transform, Material* material)
{
	if (!material)
	{
		modelMaterialData = DefaultMaterial::GetDefaultMaterial()->DEFAULT_FBX_MATERIAL.get();
	}
	else
	{
		modelMaterialData = material;
	}

	for (size_t i = 0; i < meshes.size(); i++)
	{
		meshes[i].DrawBgin();

		// �v���~�e�B�u�`��̐ݒ�R�}���h
		cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g

		// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
		cmdList->SetPipelineState(modelMaterialData->pipelineState->GetPipelineState());
		cmdList->SetGraphicsRootSignature(modelMaterialData->rootSignature->GetRootSignature());

		if (meshes[i].node)
		{
			postureMatBuff->Update(&meshes[i].node->globalTransform);
		}

		cmdList->SetGraphicsRootConstantBufferView(3, postureMatBuff->GetAddress());
		meshes[i].Draw(cmdList.Get(), transform, light);
	}
}

void fbxModel::AnimationUpdate(const fbxAnimation* animation, float frame)
{
	if (oldFrame == frame)
	{
		return;
	}

	oldFrame = frame;
	if (!animation)
	{
		return;
	}

	

	for (ModelMesh& m : meshes)
	{
		m.BoneTransform(frame, m.skinData.bones, animation, globalInverseTransform);

		m.Update(computeRelation.get());
	}
}

void fbxModel::Create(const char* filePath, bool smoothing, bool inverseU, bool inverseV, bool animeFlag)
{
	static_cast<void>(smoothing);

	FbxLoader::GetInstance()->LoadModel(this, filePath, inverseU, inverseV, animeFlag);

	//�o�b�t�@����
	for (size_t i = 0; i < meshes.size(); i++)
	{
		meshes[i].CreateBuffer();
	}

	//�v�Z�V�F�[�_�[������
	//�N���X���ʂň�񂵂����������Ȃ�
	if (!computeRelation)
	{
		//������
		computeRelation = std::make_shared<ComputeRelation>();

		//���[�g�V�O�l�`���̏�����
		computeRelation->rootSignature = std::make_unique<RootSignature>();
		//ComputeShader�p
		computeRelation->rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0

		computeRelation->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
		//�v�Z���ꂽ���_�f�[�^�p
		computeRelation->rootSignature->Add(RootSignature::RangeType::UAV, 0);//u0
		//����
		computeRelation->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

		//�V�F�[�_�[�̏�����
		computeRelation->computeShader = std::make_unique<Shader>();
		//�V�F�[�_�[�ǂݍ���
		computeRelation->computeShader->Create("Resources/Shaders/3D/Model/GpuSkinningCS.hlsl", "main", "cs_5_0", Shader::ShaderType::CS);

		//�p�C�v���C���X�e�[�g������
		computeRelation->computePipelineState = std::make_shared<ComputePipelineState>();
		//�V�F�[�_�[���Z�b�g
		computeRelation->computePipelineState->SetShader(*computeRelation->computeShader->GetShader());
		//���[�g�V�O�l�`���̃Z�b�g
		computeRelation->computePipelineState->SetRootSignature(computeRelation->rootSignature.get());
		//�p�C�v���C���X�e�[�g�̐���
		computeRelation->computePipelineState->Create(DirectX12Core::GetInstance()->GetDevice().Get());
	}
}


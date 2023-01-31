#include "BasicParticle.h"
#include"DefaultMaterial.h"
#include"DirectX12Core.h"

BasicParticle::~BasicParticle()
{
}

void BasicParticle::Initialize()
{
	device = DirectX12Core::GetInstance()->GetDevice();
	cmdList = DirectX12Core::GetInstance()->GetCommandList();

	//���_�o�b�t�@����
	vertexBuffer = std::make_unique<VertexBuffer>();
	vertexBuffer->Create(vertexCount, sizeof(VerPosColScaRot));

	//�萔�o�b�t�@����
	constBuffTransform = std::make_unique<ConstantBuffer>();
	constBuffTransform->Create(sizeof(ParticleConstBuffData));
}

void BasicParticle::Update()
{

	//�������s�����p�[�e�B�N����S�폜
	particleDatas.remove_if([](ParticleData& x)
		{
			return x.frame >= x.numFrame;
		});

	//�S�p�[�e�B�N���X�V
	for (std::forward_list<ParticleData>::iterator it = particleDatas.begin();
		it != particleDatas.end();
		it++)
	{
		//�o�߃t���[�������J�E���g
		it->frame++;
		//���x�ɉ����x�����Z
		it->velocity = it->velocity + it->accel;
		//���x�ɂ��ړ�
		it->position = it->position + it->velocity;
		//�i�s�x��0�`1�͈̔͂Ɋ��Z
		float f = static_cast<float>(it->frame) / static_cast<float>(it->numFrame);

		//�X�P�[���̐��`���
		it->scale = AliceMathF::Lerp(it->sScale , it->eScale, f);

		//��]�p�̐��`���
		it->rotation = AliceMathF::Lerp(it->sRotation, it->eRotation, f);

		//�J���[�̐��`���
		it->color = AliceMathF::Lerp(it->sColor, it->eColor, f);
	}

	//���_�o�b�t�@�փf�[�^�]��
	VerPosColScaRot* vertMap = nullptr;
	result = vertexBuffer->GetResource()->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	uint16_t count = 0;
	for (std::forward_list<ParticleData>::iterator it = particleDatas.begin();
		it != particleDatas.end();
		it++)
	{
		if (count == vertexCount)
		{
			break;
		}

		//���W
		vertMap->pos = it->position;
		vertMap->scale = it->scale;
		vertMap->rotation = it->rotation;
		vertMap->color = it->color;
		//���̒��_��
		vertMap++;
		count++;
	}

	vertexBuffer->GetResource()->Unmap(0, nullptr);
}

void BasicParticle::Add(UINT life, const AliceMathF::Vector3& position, const AliceMathF::Vector3& velocity,
	const AliceMathF::Vector3& accel, const AliceMathF::Vector2& scale, const AliceMathF::Vector2& rotation,
	const AliceMathF::Vector4& sColor, const AliceMathF::Vector4& eColor)
{
	if (std::distance(particleDatas.begin(), particleDatas.end()) < vertexCount)
	{
		//���X�g�ɗv�f��ǉ�
		particleDatas.emplace_front();
		//�ǉ������v�f�̎Q��
		ParticleData& p = particleDatas.front();
		//�l�̃Z�b�g
		p.position = position;
		p.velocity = velocity;
		p.accel = accel;
		p.numFrame = life;
		p.sScale = scale.x;
		p.eScale = scale.y;
		p.scale = scale.x;
		p.sRotation = rotation.x;
		p.eRotation = rotation.y;
		p.rotation = rotation.x;
		p.sColor = sColor;
		p.eColor = eColor;
		p.color = sColor;
	}
}

void BasicParticle::Draw(Camera* camera, Material* material)
{
	D3D12_VERTEX_BUFFER_VIEW vbView = vertexBuffer->GetView();

	assert(camera);

	if (!material)
	{
		particleMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_PARTICLE_MATERIAL.get();
	}

	AliceMathF::Matrix4 mat = camera->GetViewMatrix();
	mat.m[3][0] = 0;
	mat.m[3][1] = 0;
	mat.m[3][2] = 0;
	mat.m[3][3] = 1;

	constMapTransform.matBillboard = mat;
	constMapTransform.mat = camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
	constBuffTransform->Update(&constMapTransform);

	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	cmdList->SetPipelineState(particleMaterial->pipelineState->GetPipelineState());
	cmdList->SetGraphicsRootSignature(particleMaterial->rootSignature->GetRootSignature());

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST); // �O�p�`���X�g

	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	cmdList->SetGraphicsRootConstantBufferView(0, constBuffTransform->GetAddress());

	// SRV�q�[�v�̐ݒ�R�}���h
	cmdList->SetDescriptorHeaps(1, textureData->srvHeap.GetAddressOf());

	// SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^1�Ԃɐݒ�
	cmdList->SetGraphicsRootDescriptorTable(1, textureData->gpuHandle);

	// �`��R�}���h
	if (std::distance(particleDatas.begin(), particleDatas.end()) < vertexCount)
	{
		cmdList->DrawInstanced(static_cast<UINT> (std::distance(particleDatas.begin(), particleDatas.end())), 1, 0, 0);
	}
	else
	{
		cmdList->DrawInstanced(vertexCount, 1, 0, 0);

	}

}





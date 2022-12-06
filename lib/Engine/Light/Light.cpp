#include "Light.h"
#include"DirectX12Core.h"
Light* Light::Create()
{
	//3D�I�u�W�F�N�g�̃C���X�^���X����
	Light* instance = new Light();
	//������
	instance->Initialize();
	//���������C���X�^���X��Ԃ�
	return instance;
}

void Light::Initialize()
{
	device = DirectX12Core::GetInstance()->GetDevice();

	//�萔�o�b�t�@
	constBuff = std::make_unique<ConstantBuffer>();
	constBuff->Create(sizeof(LightConstBuffData));

	//�萔�o�b�t�@�փf�[�^�]��
	TransferConstBuffer();
}

void Light::TransferConstBuffer(){
	constMap.lightv = -lightdir;
	constMap.lightcolor = lightcolor;

	constBuff->Update(&constMap);
}

void Light::SetLightDir(AliceMathF::Vector3& lightdir_)
{
	//���K�����ăZ�b�g
	lightdir = lightdir_.Normal();
	dirty = true;
}

void Light::SetLightColor(AliceMathF::Vector4& lightcolor_)
{
	lightcolor = lightcolor_;
	dirty = true;
}

void Light::Update()
{
	//�l�̍X�V���������������萔�o�b�t�@�ɓ]������
	if (dirty)
	{
		TransferConstBuffer();
		dirty = false;
	}
}

void Light::SetConstBufferView(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex)
{
	//�萔�o�b�t�@�r���[���Z�b�g
	cmdList->SetGraphicsRootConstantBufferView(rootParameterIndex, constBuff->GetAddress());
}

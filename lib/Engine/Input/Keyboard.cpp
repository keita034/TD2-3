#include "Keyboard.h"

void Keyboard::Initialize(IDirectInput8* directInput)
{
	HRESULT result;

	WindowsApp* app = WindowsApp::GetInstance();

	//�L�[�{�[�h�f�o�C�X�̐���
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	//���̓f�[�^�`���̃Z�b�g
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);//�W���`��
	assert(SUCCEEDED(result));

	//�r�����䃌�x���̃Z�b�g
	result = keyboard->SetCooperativeLevel(app->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Keyboard::Update()
{
	for (int i = 0; i < _countof(oldkey); i++)
	{
		oldkey[i] = key[i];
	}
	//�L�[�{�[�h���̎擾�J�n
	keyboard->Acquire();
	keyboard->GetDeviceState(sizeof(key), key);
}

bool Keyboard::TriggerPush(int keyName)//�������u��
{
	return key[keyName] && !oldkey[keyName];
}

bool Keyboard::KeepPush(int keyName)//������Ă����
{
	return static_cast<bool>(key[keyName]);
}

bool Keyboard::TriggerRelease(int keyName)//�����ꂽ�u��
{
	return !key[keyName] && oldkey[keyName];
}

bool Keyboard::KeepRelease(int keyName)//�����Ă����
{
	return !key[keyName] && !oldkey[keyName];
}

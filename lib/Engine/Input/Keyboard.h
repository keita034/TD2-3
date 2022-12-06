#pragma once
#include"ErrorException.h"
#include"WindowsApp.h"

class Keyboard
{
private:
	Microsoft::WRL::ComPtr<IDirectInputDevice8> keyboard;
	BYTE oldkey[256] = {};
	BYTE key[256] = {};
public:
	void Initialize(IDirectInput8* directInput);
	void Update();

	/// <summary>
	/// �L�[�{�[�h�̃g���K�[����
	/// </summary>
	/// <param name="button">�`�F�b�N�������{�^��</param>
	/// <returns>��������</returns>
	bool TriggerPush(int keyName);

	/// <summary>
	/// �L�[�{�[�h�̓���
	/// </summary>
	/// <param name="button">�`�F�b�N�������{�^��</param>
	/// <returns>��������</returns>
	bool KeepPush(int keyName);

	/// <summary>
	/// �L�[�{�[�h�̗������u��
	/// </summary>
	/// <param name="button">�`�F�b�N�������{�^��</param>
	/// <returns>��������</returns>
	bool TriggerRelease(int keyName);

	/// <summary>
	/// �L�[�{�[�h�̗����Ă��
	/// </summary>
	/// <param name="button">�`�F�b�N�������{�^��</param>
	/// <returns>�����Ă邩</returns>
	bool KeepRelease(int keyName);
};


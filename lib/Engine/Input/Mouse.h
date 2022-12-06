#pragma once
#include"ErrorException.h"
#include <dinput.h>
#include"AliceMathUtility.h"
#include"WindowsApp.h"

enum MouseButton
{
	LEFT,
	RIGHT,
	CENTER
};

class Mouse
{
private:
	//�}�E�X
	Microsoft::WRL::ComPtr<IDirectInputDevice8> mouseDev;
	DIMOUSESTATE2 mouseState = {};
	DIMOUSESTATE2 oldMouseState = {};
	//�}�E�X�̃Q�[����ԓ��ł̃��C
	AliceMathF::Vector2 mousePos;
	AliceMathF::Vector3 mouseMove;

public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(IDirectInput8* dinput);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �}�E�X�{�^���̃g���K�[����
	/// </summary>
	/// <param name="button">�`�F�b�N�������{�^��</param>
	/// <returns>��������</returns>
	bool MouseButtonTrigger(MouseButton button);

	/// <summary>
	/// �}�E�X�{�^���̓���
	/// </summary>
	/// <param name="button">�`�F�b�N�������{�^��</param>
	/// <returns>��������</returns>
	bool MouseButtonInput(MouseButton button);

	/// <summary>
	/// �}�E�X�{�^���̗������u��
	/// </summary>
	/// <param name="button">�`�F�b�N�������{�^��</param>
	/// <returns>��������</returns>
	bool MouseButtonOffTrigger(MouseButton button);

	/// <summary>
	/// �}�E�X�̈ʒu
	/// </summary>
	/// <returns>�}�E�X�̈ʒu</returns>
	const AliceMathF::Vector2 GetMousePos()const;

	/// <summary>
	/// �}�E�X�̈ʒu
	/// </summary>
	/// <returns>�}�E�X�̈ʒu</returns>
	const AliceMathF::Vector3 GetMouseMove();

	char PADDING[4];
};


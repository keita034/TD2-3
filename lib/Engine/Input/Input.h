#pragma once
#include"ErrorException.h"
#include"Keyboard.h"
#include"Mouse.h"
#include"Controller.h"

class Input
{
private:
	Microsoft::WRL::ComPtr<IDirectInput8> directInput;

	//�L�[�{�[�h�f�o�C�X
	Keyboard* keyboard = nullptr;

	//�}�E�X
	Mouse* mouse = nullptr;

	Controller* controller = nullptr;

public:
	/// <summary>
	/// �C���X�^���X������
	/// </summary>
	static Input* GetInstance();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	//�L�[�{�[�h

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

	//�}�E�X

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

	//�R���g���[��-

	/// <summary>
	/// �R���g���[���[�{�^���̃g���K�[����
	/// </summary>
	/// <param name="button">�`�F�b�N�������{�^��</param>
	/// <returns>��������</returns>
	bool ButtonTrigger(ControllerButton button);

	/// <summary>
	/// �R���g���[���[�X�e�B�b�N�̃g���K�[����
	/// </summary>
	/// <param name="stickInput">�R���g���[���[�X�e�B�b�N����</param>
	/// <param name="deadRange">�f�b�h�]�[���͈̔�</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns>�|�������ǂ���</returns>
	bool StickTrigger(ControllerStick stickInput, const float& deadRange = 0.3f, const AliceMathF::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// �R���g���[���[�{�^���̓���
	/// </summary>
	/// <param name="button">�`�F�b�N�������{�^��</param>
	/// <returns>��������</returns>
	bool ButtonInput(ControllerButton button);

	/// <summary>
	/// �R���g���[���[�X�e�B�b�N�̓���
	/// </summary>
	/// <param name="stickInput">�R���g���[���[�X�e�B�b�N����</param>
	/// <param name="deadRange">�f�b�h�]�[���͈̔͏����l0.3f</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns>�|�������ǂ���</returns>
	bool StickInput(ControllerStick stickInput, const float& deadRange = 0.3f, const AliceMathF::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// �R���g���[���[�{�^���̗������u��
	/// </summary>
	/// <param name="button">�`�F�b�N�������{�^��</param>
	/// <returns>��������</returns>
	bool ButtonOffTrigger(ControllerButton button);

	/// <summary>
	/// �R���g���[���[�X�e�B�b�N�̗������u��
	/// </summary>
	/// <param name="stickInput">�R���g���[���[�X�e�B�b�N����</param>
	/// <param name="deadRange">�f�b�h�]�[���͈̔͏����l0.3f</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns>��������</returns>
	bool StickOffTrigger(ControllerStick stickInput, const float& deadRange = 0.3f, const AliceMathF::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// �R���g���[���[�̍��X�e�B�b�N�̃x�N�g��
	/// </summary>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns>�x�N�g��</returns>
	AliceMathF::Vector2 GetLeftStickVec(const AliceMathF::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// �R���g���[���[�̉E�X�e�B�b�N�̃x�N�g��
	/// </summary>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns>�x�N�g��</returns>
	AliceMathF::Vector2 GetRightStickVec(const AliceMathF::Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// �R���g���[���[��U��������
	/// </summary>
	/// <param name="power">�U���̋���0.0f�`1.0f</param>
	/// <param name="span">�U���̎��ԃt���[��</param>
	void ShakeController(const float& power, const int& span);
};
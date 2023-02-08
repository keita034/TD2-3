#pragma once
#include"ErrorException.h"

/// <summary>
/// �E�B���h�E�N���X
/// </summary>
class WindowsApp
{
private:
	WNDCLASSEX wndclassex{};
	HWND hwnd;
	MSG massege{};//���b�Z�[�W
	UINT windowWidth = 1280;//����
	UINT windowHeight = 720;//�c��

public:
	
	//�T�C�Y�擾�p�\����
	struct WindowsSize
	{
		//����
		UINT width;
		//�c��
		UINT height;
	};

	/// <summary>
	/// �V���O���g���C���X�^���X�̎擾
	/// </summary>
	static WindowsApp* GetInstance();

	static WindowsSize GetWindowsSize();

	/// <summary>
	/// �E�B���h�E����
	/// </summary>
	/// <param name="title">�^�C�g��(���C�h����)</param>
	/// <param name="width">�E�B���h�E����</param>
	/// <param name="height">�E�B���h�E����</param>
	void CreatWindow(const wchar_t* title = L"DirectXGame", UINT width = 1280, UINT height = 720);
	
	/// <summary>
	/// ���b�Z�[�W����
	/// </summary>
	bool MessageWindow();

	/// <summary>
	/// ��n��
	/// </summary>
	void Break();

	/// <summary>
	/// �E�B���h�E�N���X���擾
	/// </summary>
	WNDCLASSEX GetWndclassex();

	/// <summary>
	/// �n���h�����擾
	/// </summary>
	HWND GetHwnd();

	/// <summary>
	/// �E�B���h�T�C�Y���擾
	/// </summary>
	WindowsSize GetWindowSize();

private:
	//�R���X�g���N�^�E�f�X�g���N�^
	WindowsApp() = default;
	~WindowsApp() = default;
};
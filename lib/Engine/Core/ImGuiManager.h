#pragma once
#include"ErrorException.h"
#include"DirectX12Core.h"
#include "WindowsApp.h"

//ImGUI�̊Ǘ�
class ImGuiManager
{

private:

	DirectX12Core* directX12Core;

public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(WindowsApp* windowsApp, DirectX12Core* core);

	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();

	/// <summary>
	/// ImGui��t�J�n
	/// </summary>
	void Bigin();

	/// <summary>
	/// ImGui��t�I��
	/// </summary>
	void End();

	/// <summary>
	/// ��ʂւ̕`��
	/// </summary>
	void Draw();
};


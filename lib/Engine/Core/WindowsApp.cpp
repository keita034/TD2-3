#include "WindowsApp.h"
#include"resource.h"
#include"DirectX12Core.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//ウインドウプロシージャ
LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//ImGui用ウィンドウプロシージャ呼び出し
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
	{
		return true;
	}

	//メッセージに応じてゲーム固有の処理を行う
	switch (msg) {

		//ウインドウが破棄された
	case WM_DESTROY:
		//OSに対して、アプリの終了を伝える
		PostQuitMessage(0);
		return 0;
	}

	//標準のメッセージ処理を行う
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

WindowsApp* WindowsApp::GetInstance()
{
	//シングルトン
	static	WindowsApp windowsApp_;
	return &windowsApp_;
}

WindowsApp::WindowsSize WindowsApp::GetWindowsSize()
{
	return GetInstance()->GetWindowSize();
}

void WindowsApp::CreatWindow(const wchar_t* title, UINT width, UINT height)
{
	windowHeight = height;
	windowWidth = width;

	//ウインドウクラスの設定
	wndclassex.cbSize = sizeof(WNDCLASSEX);
	wndclassex.lpfnWndProc = (WNDPROC)WindowProc;//ウインドウプロシージャを設定
	wndclassex.lpszClassName = title;//ウインドウクラス名
	wndclassex.hInstance = GetModuleHandle(nullptr);//ウインドウハンドル
	wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);//カーソル指定
	wndclassex.hIcon = LoadIcon(GetModuleHandle(nullptr), TEXT("ICO"));
	//ウインドウクラスをOSに登録する
	RegisterClassEx(&wndclassex);

	//ウインドウサイズ{X座標　Y座標 横幅　縦幅}
	RECT wrc = { 0,0,this->windowWidth,this->windowHeight };
	//自動でサイズを補正する
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//ウインドウオブジェクトの生成
	hwnd = CreateWindow(wndclassex.lpszClassName,//クラス名
		title,				//タイトルバーの文字
		WS_OVERLAPPEDWINDOW,		//標準的なウインドウスタイル
		CW_USEDEFAULT,				//表示X座標(OSに任せる)
		CW_USEDEFAULT,				//表示Y座標(OSに任せる)
		wrc.right - wrc.left,		//ウインドウ横幅
		wrc.bottom - wrc.top,		//ウインドウ縦幅
		nullptr,					//親ウインドウハンドル
		nullptr,					//メニューハンドル
		wndclassex.hInstance,				//呼び出しアプリケーションハンドル
		nullptr);					//オプション

	//ウインドウを表示状態にする
	ShowWindow(hwnd, SW_SHOW);

}

bool WindowsApp::MessageWindow()
{
	//メッセージがある？
	if (PeekMessage(&massege, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&massege); //キー入力メッセージの処理
		DispatchMessage(&massege); //プロシージャにメッセージを送る
	}

	//×ボタンで終了メッセージが来たらゲームループを抜ける
	if (massege.message == WM_QUIT)
	{
		return false;
	}
	return true;
}

void WindowsApp::Break()
{
	//ウインドウクラスを登録解除
	UnregisterClass(wndclassex.lpszClassName, wndclassex.hInstance);
}

WNDCLASSEX WindowsApp::GetWndclassex()
{
	return wndclassex;
}

HWND WindowsApp::GetHwnd()
{
	return hwnd;
}

WindowsApp::WindowsSize WindowsApp::GetWindowSize()
{
	return { windowWidth,windowHeight };
}

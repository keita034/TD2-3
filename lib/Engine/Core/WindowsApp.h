#pragma once
#include"ErrorException.h"

/// <summary>
/// ウィンドウクラス
/// </summary>
class WindowsApp
{
private:
	WNDCLASSEX wndclassex{};
	HWND hwnd;
	MSG massege{};//メッセージ
	UINT windowWidth = 1280;//横幅
	UINT windowHeight = 720;//縦幅

public:
	
	//サイズ取得用構造体
	struct WindowsSize
	{
		//横幅
		UINT width;
		//縦幅
		UINT height;
	};

	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	static WindowsApp* GetInstance();

	static WindowsSize GetWindowsSize();

	/// <summary>
	/// ウィンドウ生成
	/// </summary>
	/// <param name="title">タイトル(ワイド文字)</param>
	/// <param name="width">ウィンドウ横幅</param>
	/// <param name="height">ウィンドウ横幅</param>
	void CreatWindow(const wchar_t* title = L"DirectXGame", UINT width = 1280, UINT height = 720);
	
	/// <summary>
	/// メッセージ処理
	/// </summary>
	bool MessageWindow();

	/// <summary>
	/// 後始末
	/// </summary>
	void Break();

	/// <summary>
	/// ウィンドウクラスを取得
	/// </summary>
	WNDCLASSEX GetWndclassex();

	/// <summary>
	/// ハンドルを取得
	/// </summary>
	HWND GetHwnd();

	/// <summary>
	/// ウィンドサイズを取得
	/// </summary>
	WindowsSize GetWindowSize();

private:
	//コンストラクタ・デストラクタ
	WindowsApp() = default;
	~WindowsApp() = default;
};
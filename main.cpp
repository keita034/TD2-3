#include"GameMain.h"

#ifdef _DEBUG
int main()
{
	GameMain::DebugInitialize();

#else
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
#endif

	GameMain* gameMain = nullptr;

	gameMain = new GameMain();

	gameMain->Initialize();

	return gameMain->Ran();
}
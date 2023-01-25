#include "ImGuiManager.h"
#include"DescriptorHeap.h"

void ImGuiManager::Initialize(WindowsApp* windowsApp, DirectX12Core* core)
{
	directX12Core = core;

	//ImGuiのコンテキストを生成
	ImGui::CreateContext();

	//ImGuiのスタイルを設定
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(windowsApp->GetHwnd());

	DescriptorHeap::DescriptorHeapViewHandle handl = directX12Core->GetDescriptorHeap()->AddSRV();

	ImGui_ImplDX12_Init(
		directX12Core->GetDevice().Get(),
		static_cast<int>(directX12Core->GetBackBufferCount()),
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, directX12Core->GetDescriptorHeap()->GetHeap(),
		handl.cpuHandle,
		handl.gpuHandle
	);

	ImGuiIO& io = ImGui::GetIO();
	//標準フォントを追加する
	io.Fonts->AddFontDefault();

}

void ImGuiManager::Finalize()
{
	//後始末
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiManager::Bigin()
{
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager::End()
{
	ImGui::Render();
}

void ImGuiManager::Draw()
{
	ID3D12GraphicsCommandList* commandlist = directX12Core->GetCommandList().Get();

	//デスクリプタヒープの配列をセットするコマンド
	ID3D12DescriptorHeap* ppHeaps[] = { directX12Core->GetDescriptorHeap()->GetHeap()};
	commandlist->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	//描画コマンドを発行
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandlist);
}

#include "ImGuiManager.h"
#include"DescriptorHeap.h"

void ImGuiManager::Initialize(WindowsApp* windowsApp, DirectX12Core* core)
{
	directX12Core = core;

	//ImGui�̃R���e�L�X�g�𐶐�
	ImGui::CreateContext();

	//ImGui�̃X�^�C����ݒ�
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(windowsApp->GetHwnd());

	DescriptorHeap::DescriptorHeapViewHandle handl = directX12Core->GetSRVDescriptorHeap()->AddSRV();

	ImGui_ImplDX12_Init(
		directX12Core->GetDevice().Get(),
		static_cast<int>(directX12Core->GetBackBufferCount()),
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, directX12Core->GetSRVDescriptorHeap()->GetHeap(),
		handl.cpuHandle,
		handl.gpuHandle
	);

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("Resources/Fonts/NotoSansJP-Bold.otf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
}

void ImGuiManager::Finalize()
{
	//��n��
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

	//�f�X�N���v�^�q�[�v�̔z����Z�b�g����R�}���h
	ID3D12DescriptorHeap* ppHeaps[] = { directX12Core->GetSRVDescriptorHeap()->GetHeap()};
	commandlist->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	//�`��R�}���h�𔭍s
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandlist);
}

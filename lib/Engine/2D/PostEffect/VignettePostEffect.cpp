#include"VignettePostEffect.h"
#include"WindowsApp.h"
#include"DirectX12Core.h"

VignettePostEffect* VignettePostEffect::GetInstance()
{
	static VignettePostEffect instance;
	return &instance;
}

void VignettePostEffect::Initialize()
{
	if (needsInit)
	{
		//ルートシグネチャの初期化
		rootSignature = std::make_unique<RootSignature>();

		rootSignature->Add(RootSignature::RootType::CBV, 0);//b0

		rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0

		rootSignature->Add(RootSignature::RangeType::UAV, 0);//u0

		//ルートシグネチャの生成
		rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

		//シェーダーの初期化
		shader = std::make_unique<Shader>();
		//シェーダー読み込み
		shader->Create("Resources/Shaders/2D/PostEffect/VignetteShaderCS.hlsl", "main", "cs_5_0", Shader::ShaderType::CS);

		//パイプラインステート初期化
		pipelineState = std::make_unique<ComputePipelineState>();
		//シェーダーをセット
		pipelineState->SetShader(*shader->GetShader());
		//ルートシグネチャのセット
		pipelineState->SetRootSignature(rootSignature.get());
		//パイプラインステートの生成
		pipelineState->Create(DirectX12Core::GetInstance()->GetDevice().Get());

		needsInit = false;

		vignetteDataBuff = std::make_unique<ConstantBuffer>();
		vignetteDataBuff->Create(sizeof(VignetteData));

		data =
		{
			{1.0f,1.0f,1.0f},
			0,
			{0.5f,0.5f},
			2.0f,
			0,
			{static_cast<float>(WindowsApp::GetWindowsSize().width),static_cast<float>(WindowsApp::GetWindowsSize().height)},
			{1.0f, 1.0f},
		};

		vignetteDataBuff->Update(&data);

		cmdList = DirectX12Core::GetInstance()->GetCommandList().Get();

		type = "VIGNETTE";
	}
}

void VignettePostEffect::PostUpdate(D3D12_GPU_DESCRIPTOR_HANDLE& srv, D3D12_GPU_DESCRIPTOR_HANDLE& uav)
{
	if (!needsInit)
	{
		//デスクプリタヒープをセット
		ID3D12DescriptorHeap* descriptorHeaps[] =
		{
			DirectX12Core::GetInstance()->GetDescriptorHeap()->GetHeap(),
		};
		cmdList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
		//ルートシグネチャをセット
		cmdList->SetComputeRootSignature(rootSignature->GetRootSignature());
		//パイプラインステートをセット
		cmdList->SetPipelineState(pipelineState->GetPipelineState());

		cmdList->SetComputeRootConstantBufferView(0, vignetteDataBuff->GetAddress());
		cmdList->SetComputeRootDescriptorTable(1, srv);
		cmdList->SetComputeRootDescriptorTable(2, uav);

		cmdList->Dispatch(static_cast<UINT>(WindowsApp::GetWindowsSize().width / 10), static_cast<UINT>(WindowsApp::GetWindowsSize().height / 10), 1);
	}
	else
	{
		Initialize();

		//デスクプリタヒープをセット
		ID3D12DescriptorHeap* descriptorHeaps[] =
		{
			DirectX12Core::GetInstance()->GetDescriptorHeap()->GetHeap(),
		};
		cmdList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
		//ルートシグネチャをセット
		cmdList->SetComputeRootSignature(rootSignature->GetRootSignature());
		//パイプラインステートをセット
		cmdList->SetPipelineState(pipelineState->GetPipelineState());

		cmdList->SetComputeRootConstantBufferView(0, vignetteDataBuff->GetAddress());
		cmdList->SetComputeRootDescriptorTable(1, srv);
		cmdList->SetComputeRootDescriptorTable(2, uav);

		cmdList->Dispatch(static_cast<UINT>(WindowsApp::GetWindowsSize().width / 10), static_cast<UINT>(WindowsApp::GetWindowsSize().height / 10), 1);
	}
}

void VignettePostEffect::SetData(const AliceMathF::Vector3& color, const AliceMathF::Vector2& center, float power, const AliceMathF::Vector2& size)
{
	AliceMathF::Vector3 col = { 1.0f,1.0f,1.0f };
	col = col - (color / 255.0f);

	data.color = col;
	data.center = center;
	data.power = power;
	data.winSize = { static_cast<float>(WindowsApp::GetWindowsSize().width),static_cast<float>(WindowsApp::GetWindowsSize().height) };
	data.size = size;
	vignetteDataBuff->Update(&data);
}

void VignettePostEffect::SetCol(const AliceMathF::Vector3& color)
{
	AliceMathF::Vector3 col = { 1.0f,1.0f,1.0f };
	col = col - (color / 255.0f);

	data.color = col;

	vignetteDataBuff->Update(&data);
}

void VignettePostEffect::SetCent(const AliceMathF::Vector2& center)
{
	data.center = center;

	vignetteDataBuff->Update(&data);
}

void VignettePostEffect::SetPow(float power)
{
	data.power = power;

	vignetteDataBuff->Update(&data);
}

void VignettePostEffect::SetSi(const AliceMathF::Vector2& size)
{
	data.size = size;

	vignetteDataBuff->Update(&data);
}

void VignettePostEffect::SetVignetteData(const AliceMathF::Vector3& color, const AliceMathF::Vector2& center, float power, const AliceMathF::Vector2& size)
{
	VignettePostEffect::GetInstance()->SetData(color, center, power, size);
}

void VignettePostEffect::SetColor(const AliceMathF::Vector3& color)
{
	VignettePostEffect::GetInstance()->SetCol(color);
}

void VignettePostEffect::SetCenter(const AliceMathF::Vector2& center)
{
	VignettePostEffect::GetInstance()->SetCent(center);
}

void VignettePostEffect::SetPower(float power)
{
	VignettePostEffect::GetInstance()->SetPow(power);
}

void VignettePostEffect::SetSize(const AliceMathF::Vector2& size)
{
	VignettePostEffect::GetInstance()->SetSi(size);
}

const std::string& VignettePostEffect::GetType()
{
	return type;
}


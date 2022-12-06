#include "PipelineState.h"
#include"DirectX12Core.h"

bool PipelineState::Create()
{
	HRESULT result;
	Microsoft::WRL::ComPtr<ID3D12Device> device = DirectX12Core::GetDeviceSta();

	// �O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	// �V�F�[�_�[�̐ݒ�
	if (vsByte)
	{
		pipelineDesc.VS = *vsByte;
	}
	if (psByte)
	{
		pipelineDesc.PS = *psByte;
	}
	if (dsByte)
	{
		pipelineDesc.DS = *dsByte;
	}
	if (hsByte)
	{
		pipelineDesc.HS = *hsByte;
	}
	if (gsByte)
	{
		pipelineDesc.GS = *gsByte;
	}

	// �T���v���}�X�N�̐ݒ�
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�

	// ���X�^���C�U�̐ݒ�
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // �J�����O���Ȃ�
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // �|���S�����h��Ԃ�
	pipelineDesc.RasterizerState.DepthClipEnable = true; // �[�x�N���b�s���O��L����

	//�u�����h�f�X�N
	pipelineDesc.BlendState = blendDesc;

	// ���_���C�A�E�g�̐ݒ�
	pipelineDesc.InputLayout.NumElements = static_cast<UINT>(inputLayoutLength);
	pipelineDesc.InputLayout.pInputElementDescs = inputLayoutData;

	// �}�`�̌`��ݒ�
	pipelineDesc.PrimitiveTopologyType = primitiveType;
	//�f�v�X�X�e���V���X�e�[�g�̐ݒ�
	pipelineDesc.DepthStencilState.DepthEnable = depthFlag;//�[�x�e�X�g���s��
	pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;//�������݋���
	pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;//��������΍��i
	pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;//�[�x�t�H�[�}�b�g
	// ���̑��̐ݒ�
	pipelineDesc.NumRenderTargets = 1; // �`��Ώۂ�1��
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0�`255�w���RGBA
	pipelineDesc.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

	// �p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
	pipelineDesc.pRootSignature = rootSignature;

	// �p�C�v�����X�e�[�g�̐���
	result = device->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(pipelineState.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));
	if (result != S_OK)
	{
		return false;
	}

	return true;
}

void PipelineState::SetHullShader(D3D12_SHADER_BYTECODE* pHsByte)
{
	hsByte = pHsByte;
}

void PipelineState::SetDomainShader(D3D12_SHADER_BYTECODE* pDsByte)
{
	dsByte = pDsByte;
}

void PipelineState::SetPrimitiveType(D3D12_PRIMITIVE_TOPOLOGY_TYPE type)
{
	primitiveType = type;
}

ID3D12PipelineState* PipelineState::GetPipelineState()
{
	return pipelineState.Get();
}

void PipelineState::SetInputLayout(D3D12_INPUT_ELEMENT_DESC* desc, size_t length)
{
	inputLayoutData = desc;
	inputLayoutLength = length;
}

void PipelineState::SetRootSignature(ID3D12RootSignature* pRootSignature)
{
	rootSignature = pRootSignature;
}

void PipelineState::SetBlend(D3D12_BLEND_DESC& desc)
{
	blendDesc = desc;
}

void PipelineState::SetDepthFlag(bool flag)
{
	depthFlag = flag;
}

void PipelineState::SetVertexShader(D3D12_SHADER_BYTECODE* pVsByte)
{
	vsByte = pVsByte;
}

void PipelineState::SetPixelShader(D3D12_SHADER_BYTECODE* pPsByte)
{
	psByte = pPsByte;
}

void PipelineState::SetGeometryShader(D3D12_SHADER_BYTECODE* pGsByte)
{
	gsByte = pGsByte;
}

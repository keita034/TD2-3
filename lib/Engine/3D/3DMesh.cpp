#include"3DMesh.h"
#include"WindowsApp.h"
#include"DefaultMaterial.h"

Mesh3D* Mesh3D::mesh = nullptr;

#pragma region �p�u���b�N

//����`�悷��
void Mesh3D::DrawLine(AliceMathF::Vector3 start, AliceMathF::Vector3 end, AliceMathF::Vector4 color)
{
	D3D12_VERTEX_BUFFER_VIEW vbView = lineBuff->vertexBuffer->GetView();

	assert(lineCount < lineMaxCount);

	// ���_�f�[�^
	std::vector <PosColor > vertices = {
	  {{start.x, start.y, start.z}, {color.x, color.y, color.z, color.w}},
	  {{end.x, end.y, end.z}, {color.x, color.y, color.z, color.w}},
	};

	UINT indxcount = lineCount * lineVertexCount;

	constMapTransform->mat = camera->GetViewMatrixInv() * camera->GetProjectionMatrix();

	//���_�o�b�t�@�ւ̃f�[�^�]��
	copy(vertices.begin(), vertices.end(), &lineBuff->vertMap[indxcount]);
	lineBuff->vertexBuffer->Update(vertices.data());

	// �p�C�v���C���X�e�[�g�̐ݒ�
	directX12Core->GetCommandList()->SetPipelineState(DefaultMaterial::GetDefaultMaterial()->DEFAULT_LINE_MATERIAL[blendMode]->pipelineState->GetPipelineState());

	// ���[�g�V�O�l�`���̐ݒ�
	directX12Core->GetCommandList()->SetGraphicsRootSignature(DefaultMaterial::GetDefaultMaterial()->DEFAULT_LINE_MATERIAL[blendMode]->rootSignature->GetRootSignature());

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	directX12Core->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST); //�O�p�`���X�g

	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	directX12Core->GetCommandList()->IASetVertexBuffers(0, 1, &vbView);

	//�萔�o�b�t�@�r���[
	directX12Core->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffTransform->GetAddress());

	// �`��R�}���h
	directX12Core->GetCommandList()->DrawInstanced(lineVertexCount, 1, indxcount, 0);

	lineCount++;
}

////�O�p�`��`�悷��
//void Mesh3D::DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, AliceMathF::Vector4 color, int fillFlag)
//{
//	if (fillFlag)
//	{
//		DrawTriangleFill(x1, y1, x2, y2, x3, y3, color);
//	}
//	else
//	{
//		DrawLine(x1, y1, x2, y2, color);
//		DrawLine(x2, y2, x3, y3, color);
//		DrawLine(x3, y3, x1, y1, color);
//
//	}
//}
//
////�l�p�`��`�悷��
//void Mesh3D::DrawBox(float x, float y, float radiusX, float radiusY, float angle, AliceMathF::Vector4 color, int fillFlag)
//{
//	if (fillFlag)
//	{
//		DrawBoxFill(x, y, radiusX, radiusY, angle, color);
//
//	}
//	else
//	{
//
//		DrawLine(x - radiusX, y - radiusY, x + radiusX, y - radiusY, color);//���ォ��E��
//		DrawLine(x - radiusX, y - radiusY, x - radiusX, y + radiusY, color);//���ォ�獶��
//		DrawLine(x + radiusX, y - radiusY, x + radiusX, y + radiusY, color);//�E�ォ��E��
//		DrawLine(x - radiusX, y + radiusY, x + radiusX, y + radiusY, color);//��������E��
//	}
//}
//
////�ȉ~��`�悷��
//void Mesh3D::DrawEllipse(float x, float y, float radiusX, float radiusY, float angle, AliceMathF::Vector4 color, int fillMode)
//{
//	constexpr UINT NumDiv = 64; // ������
//	float RadianPerDivision = AliceMathF::AX_2PIF / float(NumDiv); // ����1�P�ʂ̊p�x
//
//	//�����_���������1�������Ă�����1�����悤�ɂ���
//	std::array<float, NumDiv + 1> pointsX{};
//	std::array<float, NumDiv + 1> pointsY{};
//	float angleCos = cos(angle);
//	float angleSin = sin(angle);
//	for (size_t i = 0; i < NumDiv; ++i)
//	{
//		float baseX = cos(RadianPerDivision * static_cast<float>(i)) * radiusX;
//		float baseY = sin(RadianPerDivision * static_cast<float>(i)) * radiusY;
//		pointsX[i] = float(baseX * angleCos - baseY * angleSin + x);
//		pointsY[i] = float(baseY * angleCos + baseX * angleSin + y);
//	}
//
//	//�Ō�ƍŏ��͈ꏏ
//	(*pointsX.rbegin()) = (*pointsX.begin());
//	(*pointsY.rbegin()) = (*pointsY.begin());
//
//	if (fillMode)
//	{
//		for (size_t index = 0; index < NumDiv; ++index)
//		{
//			DrawTriangleFill(x, y, pointsX[index], pointsY[index], pointsX[index + 1], pointsY[index + 1], color);
//		}
//	}
//	else
//	{
//		for (size_t index = 0; index < NumDiv; ++index)
//		{
//			DrawLine(pointsX[index], pointsY[index], pointsX[index + 1], pointsY[index + 1], color);
//		}
//	}
//}

//�J�E���g������
void Mesh3D::DrawReset()
{
	triangleCount = 0;
	lineCount = 0;
	boxCount = 0;
}

//�u�����h���[�h��ݒ肷��
void Mesh3D::SetBlendMode(BlendMode mode)
{
	blendMode = (UINT)mode;
}

//�F�R�[�h���擾����
AliceMathF::Vector4 Mesh3D::GetColor(int red, int blue, int green, int alpha)
{
	AliceMathF::Vector4 color{};

	color.x = static_cast<float>(red) / 255.0f;
	color.y = static_cast<float>(blue) / 255.0f;
	color.z = static_cast<float>(green) / 255.0f;
	color.w = static_cast<float>(alpha) / 255.0f;

	return color;
}

AliceMathF::Vector4 Mesh3D::GetColor(AliceMathF::Vector4 color)
{
	AliceMathF::Vector4 result{};

	result.x = static_cast<float>(color.x) / 255.0f;
	result.y = static_cast<float>(color.y) / 255.0f;
	result.z = static_cast<float>(color.z) / 255.0f;
	result.w = static_cast<float>(color.w) / 255.0f;

	return result;
}


//�R���X�g���N�^
Mesh3D::Mesh3D()
{
	directX12Core = DirectX12Core::GetInstance();

	//�O�p�`�o�b�t�@
	UINT vertexCount = triangleVertexCount * triangleMaxCount;
	UINT indexCount = triangleIndexCount * triangleMaxCount;
	triangleBuff = CreateBuff(vertexCount, indexCount);

	//���o�b�t�@
	vertexCount = lineVertexCount * lineMaxCount;
	indexCount = lineIndexCount * lineMaxCount;
	lineBuff = CreateBuff(vertexCount, indexCount);

	//�l�p�`�o�b�t�@
	vertexCount = boxVertexCount * boxMaxCount;
	indexCount = boxIndexCount * boxMaxCount;
	boxBuff = CreateBuff(vertexCount, indexCount);

	CreatConstBuff();

}

#pragma endregion

#pragma region �v���C�x�[�g

Mesh3D* Mesh3D::GetInstance()
{
	if (mesh == nullptr)
	{
		mesh = new Mesh3D();
	}

	return mesh;
}

void Mesh3D::Destroy()
{
	delete mesh;
}

void Mesh3D::SetCamera(GameCamera* camera_)
{
	camera = camera_;
}

//�O�p�`��`�悷��(���g�h��Ԃ�)
void Mesh3D::DrawTriangleFill(float x1, float y1, float x2, float y2, float x3, float y3, AliceMathF::Vector4 color)
{
	D3D12_VERTEX_BUFFER_VIEW vbView = triangleBuff->vertexBuffer->GetView();

	assert(triangleCount < triangleMaxCount);

	// ���_�f�[�^
	std::vector <PosColor > vertices = {
	  {{x1, y1, 0.0f}, {color.x, color.y, color.z, color.w}},
	  {{x2, y2, 0.0f}, {color.x, color.y, color.z, color.w}},
	  {{x3, y3, 0.0f}, {color.x, color.y, color.z, color.w}},
	};
	UINT vertexCount = triangleCount * triangleVertexCount;
	constMapTransform->mat = camera->GetViewMatrixInv() * camera->GetProjectionMatrix();

	//���_�o�b�t�@�ւ̃f�[�^�]��
	copy(vertices.begin(), vertices.end(), &triangleBuff->vertMap[vertexCount]);
	triangleBuff->vertexBuffer->Update(triangleBuff->vertMap);

	// �p�C�v���C���X�e�[�g�̐ݒ�
	directX12Core->GetCommandList()->SetPipelineState(DefaultMaterial::GetDefaultMaterial()->DEFAULT_MESH_MATERIAL[blendMode]->pipelineState->GetPipelineState());

	// ���[�g�V�O�l�`���̐ݒ�
	directX12Core->GetCommandList()->SetGraphicsRootSignature(DefaultMaterial::GetDefaultMaterial()->DEFAULT_MESH_MATERIAL[blendMode]->rootSignature->GetRootSignature());

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	directX12Core->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); //�O�p�`���X�g

	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	directX12Core->GetCommandList()->IASetVertexBuffers(0, 1, &vbView);

	//�萔�o�b�t�@�r���[
	directX12Core->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffTransform->GetAddress());

	// �`��R�}���h
	directX12Core->GetCommandList()->DrawInstanced(triangleVertexCount, 1, vertexCount, 0);

	// �g�p�J�E���g�㏸
	triangleCount++;
}

//�l�p�`��`�悷��(���g�h��Ԃ�)
void Mesh3D::DrawBoxFill(float x, float y, float radiusX, float radiusY, float angle, AliceMathF::Vector4 color)
{
	D3D12_VERTEX_BUFFER_VIEW vbView = boxBuff->vertexBuffer->GetView();
	D3D12_INDEX_BUFFER_VIEW ibView = boxBuff->indexBuffer->GetView();

	assert(boxCount < boxMaxCount);

	float left = -radiusX;
	float top = -radiusY;
	float right = radiusX;
	float bottom = radiusY;

	// ���_�f�[�^
	std::vector <PosColor > vertices = {
	  {{left, bottom, 0.0f},{color.x, color.y, color.z, color.w}},//����
	  {{left, top, 0.0f},{color.x, color.y, color.z, color.w}},//����
	  {{right, top, 0.0f},{color.x, color.y, color.z, color.w}},//�E��
	  {{right, bottom, 0.0f},{color.x, color.y, color.z, color.w}},//�E��
	};

	//�C���f�b�N�X
	std::vector<uint16_t> indices = { 0, 1, 2, 2, 3, 0 };

	constMapTransform->mat = camera->GetViewMatrixInv() * camera->GetProjectionMatrix();

	//��]
	for (auto& vertex : vertices)
	{
		//��]
		vertex.pos = {
		  vertex.pos.x * cosf(angle) + vertex.pos.y * -sinf(angle),
		  vertex.pos.x * sinf(angle) + vertex.pos.y * cosf(angle), vertex.pos.z };

		//���s�ړ�
		vertex.pos.x += x;
		vertex.pos.y += y;
	}

	UINT vertexCount = boxCount * boxVertexCount;
	UINT indxCount = boxCount * boxIndexCount;

	//���_�o�b�t�@�ւ̃f�[�^�]��
	std::copy(vertices.begin(), vertices.end(), &boxBuff->vertMap[vertexCount]);
	boxBuff->vertexBuffer->Update(boxBuff->vertMap);

	//�C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	std::copy(indices.begin(), indices.end(), &boxBuff->indexMap[indxCount]);
	boxBuff->indexBuffer->Update(boxBuff->indexMap);

	//�p�C�v���C���X�e�[�g�̐ݒ�
	directX12Core->GetCommandList()->SetPipelineState(DefaultMaterial::GetDefaultMaterial()->DEFAULT_MESH_MATERIAL[blendMode]->pipelineState->GetPipelineState());

	//���[�g�V�O�l�`���̐ݒ�
	directX12Core->GetCommandList()->SetGraphicsRootSignature(DefaultMaterial::GetDefaultMaterial()->DEFAULT_MESH_MATERIAL[blendMode]->rootSignature->GetRootSignature());

	//�v���~�e�B�u�`��̐ݒ�R�}���h
	directX12Core->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); //�O�p�`���X�g

	//���_�o�b�t�@�̐ݒ�
	directX12Core->GetCommandList()->IASetVertexBuffers(0, 1, &vbView);

	//�C���f�b�N�X�o�b�t�@�̐ݒ�
	directX12Core->GetCommandList()->IASetIndexBuffer(&ibView);

	//�萔�o�b�t�@�r���[
	directX12Core->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffTransform->GetAddress());

	//�`��R�}���h
	directX12Core->GetCommandList()->DrawIndexedInstanced(boxIndexCount, 1, static_cast<UINT>(indxCount), static_cast<INT>(vertexCount), 0);

	//�g�p�J�E���g�㏸
	boxCount++;
}



//�萔�o�b�t�@����(2D���W�ϊ��s��)
void Mesh3D::CreatConstBuff()
{
	//�萔�o�b�t�@����
	constBuffTransform = std::make_unique<ConstantBuffer>();
	constBuffTransform->Create(sizeof(ConstBufferDataTransform));

	AliceMathF::MakeOrthogonalL(
		0.0f, static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().width),
		static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().height), 0.0f,
		0.0f, 1.0f, projectionMat);

	constBuffTransform->Update(&projectionMat);

}



///<summary>
///�o�b�t�@�쐬
///</summary>
///<param name="vertexCount">���_��</param>
///<param name="indexCount">�C���f�b�N�X��</param>
///<returns>�o�b�t�@</returns>
std::unique_ptr <Buff> Mesh3D::CreateBuff(UINT vertexCount, UINT indexCount)
{
	std::unique_ptr <Buff> buff = std::make_unique<Buff>();

	if (vertexCount > 0)
	{

		buff->vertexBuffer = std::make_unique<VertexBuffer>();
		buff->vertexBuffer->Create(vertexCount, sizeof(PosColor));

		buff->vertMap = static_cast<PosColor*>(malloc(vertexCount * sizeof(PosColor)));

	}

	if (indexCount > 0)
	{
		buff->indexBuffer = std::make_unique<IndexBuffer>();
		buff->indexBuffer->Create(indexCount);

		buff->indexMap = static_cast<uint32_t*>(malloc(indexCount * sizeof(uint32_t)));
	}

	return buff;
}

#pragma endregion

#pragma once
//#DirectX�̂��
#include"ErrorException.h"

//����.h
#include "DirectX12Core.h"
#include"WindowsApp.h"
#include"AliceMathUtility.h"
#include"ConstantBuffer.h"
#include"AliceUtility.h"

//pragma comment
#pragma comment(lib, "d3dcompiler.lib")


//using namespace

class Mesh
{
private:

	DirectX12Core* directX12Core = nullptr;

	//�萔�o�b�t�@��GPU���\�[�X�̃|�C���^
	std::unique_ptr<ConstantBuffer> constBuffTransform;
	//�萔�o�b�t�@�̃}�b�s���O�p
	ConstBufferDataTransform constMapTransform;

	//�u�����h���[�h
	UINT blendMode;
	char PADDING[4];

	//�O�p�`�o�b�t�@
	std::unique_ptr <Buff> triangleBuff;
	//�O�p�`�`����
	UINT triangleMaxCount = 4096;
	//�O�p�`���_��
	UINT triangleVertexCount = 3;
	//�O�p�`�C���f�b�N�X��
	UINT triangleIndexCount = 0;
	//�O�p�`�g�p��
	UINT triangleCount = 0;

	//���o�b�t�@
	std::unique_ptr <Buff> lineBuff;
	//���`����
	UINT lineMaxCount = 4096;
	//�����_��
	UINT lineVertexCount = 2;
	//���C���f�b�N�X��
	UINT lineIndexCount = 0;
	//���g�p��
	UINT lineCount = 0;

	//�l�p�`�o�b�t�@
	std::unique_ptr <Buff> boxBuff;
	//�l�p�`�`����
	UINT boxMaxCount = 2048;
	//�l�p�`���_��
	UINT boxVertexCount = 4;
	//�l�p�`�C���f�b�N�X��
	UINT boxIndexCount = 6;
	//�l�p�`�g�p��
	UINT boxCount = 0;

	static Mesh* mesh;

public:

	///<summary>
	///�O�p�`��`�悷��
	///</summary>
	///<param name="x1">: �`�悷��O�p�`�̒��_1 X</param>
	///<param name="y1">: �`�悷��O�p�`�̒��_1 Y</param>
	///<param name="x2">: �`�悷��O�p�`�̒��_2 X</param>
	///<param name="y2">: �`�悷��O�p�`�̒��_2 Y</param>
	///<param name="x3">: �`�悷��O�p�`�̒��_3 X</param>
	///<param name="y3">: �`�悷��O�p�`�̒��_3 Y</param>
	///<param name="color">: �`�悷��O�p�`�̐F</param>
	///<param name="fillFlag">: �O�p�`�̒��g��h��Ԃ����t���O</param>
	void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, AliceMathF::Vector4 color, int fillFlag);

	///<summary>
	///����`�悷��
	///</summary>
	///<param name="x1">: �`�悷����̎n�_���W X</param>
	///<param name="y1">: �`�悷����̎n�_���W Y</param>
	///<param name="x2">: �`�悷����̏I�_���W X</param>
	///<param name="y2">: �`�悷����̏I�_���W Y</param>
	///<param name="color">: �`�悷����̐F</param>
	void DrawLine(float x1, float y1, float x2, float y2, AliceMathF::Vector4 color);

	///<summary>
	///�l�p�`��`�悷��
	///</summary>
	///<param name="x">: �`�悷��l�p�`�̒��S���W X</param>
	///<param name="y">: �`�悷��l�p�`�̒��S���W Y</param>
	///<param name="radiusX">: �`�悷��l�p�`�̔��a X</param>
	///<param name="radiusY">: �`�悷��l�p�`�̔��a Y</param>
	///<param name="angle">: �`�悷��l�p�`�̉�]�p(�ʓx�@)</param>
	///<param name="color">: �`�悷��l�p�`�̐F</param>
	///<param name="fillFlag">: �l�p�`�̒��g��h��Ԃ����t���O</param>
	void DrawBox(float x, float y, float radiusX, float radiusY, float angle, AliceMathF::Vector4 color, int fillFlag);

	///<summary>
	///�ȉ~��`�悷��
	///</summary>
	///<param name="x">�ȉ~�̒��S���W X</param>
	///<param name="y">�ȉ~�̒��S���W Y</param>
	///<param name="radiusX">�ȉ~�̔��a X</param>
	///<param name="radiusY">�ȉ~�̔��a Y</param>
	///<param name="angle">�ȉ~�̉�]�p(rad)</param>
	///<param name="color">�ȉ~�̐F</param>
	///<param name="fillFlag">: �l�p�`�̒��g��h��Ԃ����t���O</param>
	void DrawEllipse(float x, float y, float radiusX, float radiusY, float angle, AliceMathF::Vector4 color, int fillMode);

	///<summary>
	///�J�E���g������
	///</summary>
	void DrawReset();

	///<summary>
	///�u�����h���[�h��ݒ肷��
	///</summary>
	///<param name="mode">: �u�����h���[�h</param>
	void SetBlendMode(BlendMode mode);

	///<summary>
	///�F�R�[�h���擾����
	///</summary>
	///<param name="red">: �擾�������F�̋P�x�l : �����l255 (0�`255)</param>
	///<param name="blue">: �擾�������F�̋P�x�l : �����l255 (0�`255)</param>
	///<param name="green">: �擾�������F�̋P�x�l : �����l255 (0�`255)</param>
	///<param name="alpha">: �擾�������F�̓��ߗ� : �����l255 (0�`255)</param>
	///<returns>�F�R�[�h</returns>
	AliceMathF::Vector4 GetColor(int red = 255, int blue = 255, int green = 255, int alpha = 255);

	///<summary>
	///�F�R�[�h���擾����
	///</summary>
	///<param name="color">: �擾�������e�F�̋P�x�l : �����l255 (0�`255)</param>
	///<returns>�F�R�[�h</returns>
	AliceMathF::Vector4 GetColor(AliceMathF::Vector4 color);

	/// <summary>
	/// �C���X�^���X������
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static Mesh* GetInstance();

	/// <summary>
	/// �C���X�^���X�����
	/// </summary>
	void Destroy();

private:

	//�R���X�g���N�^
	Mesh();

	//�O�p�`��`�悷��(���g�h��Ԃ�)
	void DrawTriangleFill(float x1, float y1, float x2, float y2, float x3, float y3, AliceMathF::Vector4 color);

	//�l�p�`��`�悷��(���g�h��Ԃ�)
	void DrawBoxFill(float x, float y, float width, float height, float angle, AliceMathF::Vector4 color);

	///<summary>
	///�o�b�t�@�쐬
	///</summary>
	///<param name="vertexCount">: ���_��</param>
	///<param name="indexCount">: �C���f�b�N�X��</param>
	///<returns>�o�b�t�@</returns>
	std::unique_ptr <Buff> CreateBuff(UINT vertexCount, UINT indexCount);

	//�萔�o�b�t�@����(2D���W�ϊ��s��)
	void CreatConstBuff();

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Mesh& operator=(const Mesh&) = delete;
	Mesh(const Mesh&) = delete;
};




#pragma once
//#DirectX�̂��
#include"ErrorException.h"

//����.h
#include"AliceMathUtility.h"
#include"Transform.h"
#include"Mesh.h"
#include"Input.h"
#include"Sprite2D.h"

//pragma comment

class Button
{
private:
	Input* input = nullptr;
	Mesh* mesh = nullptr;
	std::unique_ptr<Sprite2D> sprite;
	TextureData textureData;

public:
	Button();
	Button(uint32_t handle);
	~Button();

	/// <summary>
	/// �{�^������
	/// </summary>
	///<param name="x">: �`�悷��{�^���̒��S���W X</param>
	///<param name="y">: �`�悷��{�^���̒��S���W Y</param>
	///<param name="radiusX">: �`�悷��{�^���̉��̔��a radiusX</param>
	///<param name="radiusY">: �`�悷��{�^���̏c�̔��a radiusY</param>
	///<param name="color">: �`�悷����̐F</param>
	///<param name="fillFlag">: �{�^���̒��g��h��Ԃ����t���O</param>
	///<param name="posX">: �J�[�\�����W X</param>
	///<param name="posY">: �J�[�\�����W Y</param>
	///<param name="sceneFlag">: �{�^�������������ɍX�V�������ϐ���</param>
	///<param name="sceneNextNum">: �{�^�������������sceneFlag�ɃZ�b�g�������l</param>
	void DrawButton(float x,float y, float radiusX, float radiusY, AliceMathF::Vector4 color,float posX,float posY, bool fillFlag,int& sceneFlag,int sceneNextNum);

	/// <summary>
	/// ���\�[�X�Ń{�^������
	/// </summary>
	///<param name="textureData">: �`�悷��{�^���̃e�N�X�`�� textureData</param>
	///<param name="transform">: �`�悷��{�^���̒��S���W Y</param>
	///<param name="posX">: �J�[�\�����W X</param>
	///<param name="posY">: �J�[�\�����W Y</param>
	///<param name="sceneFlag">: �{�^�������������ɍX�V�������ϐ���</param>
	///<param name="sceneNextNum">: �{�^�������������sceneFlag�ɃZ�b�g�������l</param>
	void DrawGraphButton(Transform& transform, float posX, float posY, int& sceneFlag, int sceneNextNum);

private:
	// �R�s�[�R���X�g���N�^���֎~�i�V���O���g���p�^�[���j
	Button(const Button& obj) = delete;
	// �R�s�[������Z�q���֎~�i�V���O���g���p�^�[���j
	void operator=(const Button& obj) = delete;
};
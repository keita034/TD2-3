#pragma once
//#DirectX�̂��
#include"ErrorException.h"

//����.h
#include"AliceMathUtility.h"
#include"Transform.h"
#include"Mesh.h"
#include"Input.h"
#include"Sprite2D.h"

class Cursor
{
private:
	Input* input = nullptr;
	Mesh* mesh = nullptr;
	std::unique_ptr<Sprite2D> sprite;
	TextureData textureData;
	AliceMathF::Vector2 cursor;
public:

	void Update();
	void DrawCursor(float radiusX, float radiusY, AliceMathF::Vector4 color, bool fillMode);
	void DrawGraphCursor(Transform& transform);

	//�Q�b�^�[
	AliceMathF::Vector2 GetCursor();

	Cursor();
	Cursor(uint32_t handle);
	~Cursor();

private:

	// �R�s�[�R���X�g���N�^���֎~�i�V���O���g���p�^�[���j
	Cursor(const Cursor& obj) = delete;
	// �R�s�[������Z�q���֎~�i�V���O���g���p�^�[���j
	void operator=(const Cursor& obj) = delete;
};
#pragma once
//#DirectX�̂��
#include"ErrorException.h"

//����.h
#include"AliceMathUtility.h"
#include"WindowsApp.h"
#include"DirectX12Core.h"
#include "Camera.h"
#include"Sprite.h"
#include"DefaultMaterial.h"

class Sprite3D : public Sprite
{
private:

public:

	Sprite3D() = default;
	~Sprite3D() = default;

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="handle">�e�N�X�`���n���h��</param>
	virtual void Initialize(uint32_t handle)override;

	/// <summary>
	/// �`��(�r���{�[�h����)
	/// </summary>
	/// <param name="transform">���[���h�ϊ��f�[�^</param>
	/// <param name="camera">�J����</param>
	/// <param name="blend">�u�����h�ݒ�(�����l�̓A���t�@�u�����h)</param>
	/// <param name="flag">�r���{�[�h�̎��(�����l�͖���)</param>
	/// <param name="material">�u�����h��CUSTOM���Ɏg��</param>
	virtual void Draw(Transform& transform, Camera* camera, BlendMode blend = BlendMode::AX_BLENDMODE_ALPHA, BillboardFlag flag = NonBillboard, Material* material = nullptr);

	/// <summary>
	/// �`��(�r���{�[�h�Ȃ�)
	/// </summary>
	/// <param name="transform">���[���h�ϊ��f�[�^</param>
	/// <param name="blend">�u�����h�ݒ�(�����l�̓A���t�@�u�����h)</param>
	//// <param name="material">�u�����h��CUSTOM���Ɏg��</param>
	virtual void Draw(Transform& transform, BlendMode blend = BlendMode::AX_BLENDMODE_NOBLEND, Material* material = nullptr)override;

	/// <summary>
	/// �A�j���[�V�����`��(�r���{�[�h�Ȃ�)
	/// </summary>
	/// <param name="transform">���[���h�ϊ��f�[�^</param>
	/// <param name="radiusX">�A�j���[�V�����摜�̈ꖇ���̉���</param>
	/// <param name="radiusY">�A�j���[�V�����摜�̈ꖇ���̏c��</param>
	/// <param name="frame">�A�j���[�V�����t���[��</param>
	/// <param name="frameDiv">�A�j���[�V�����t���[���̍ő�l</param>
	/// <param name="blend">�u�����h�ݒ�(�����l�̓A���t�@�u�����h)</param>
	/// <param name="material">�u�����h��CUSTOM���Ɏg��</param>
	virtual void AnimationDraw(Transform& transform, uint16_t radiusX, uint16_t radiusY, float& frame, float frameDiv, BlendMode blend = BlendMode::AX_BLENDMODE_ALPHA, Material* material = nullptr)override;

	/// <summary>
	/// �A�j���[�V�����`��(�r���{�[�h����)
	/// </summary>
	/// <param name="transform">���[���h�ϊ��f�[�^</param>
	/// <param name="radiusX">�A�j���[�V�����摜�̈ꖇ���̉���</param>
	/// <param name="radiusY">�A�j���[�V�����摜�̈ꖇ���̏c��</param>
	/// <param name="frame">�A�j���[�V�����t���[��</param>
	/// <param name="frameDiv">�A�j���[�V�����t���[���̍ő�l</param>
	//// <param name="camera">�J����</param>
	/// <param name="blend">�u�����h�ݒ�(�����l�̓A���t�@�u�����h)</param>
	/// <param name="material">�u�����h��CUSTOM���Ɏg��</param>
	virtual void AnimationDraw(Transform& transform, uint16_t radiusX, uint16_t radiusY, float& frame, float frameDiv, Camera* camera, BlendMode blend = BlendMode::AX_BLENDMODE_ALPHA, BillboardFlag flag = NonBillboard, Material* material = nullptr);

private:



	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Sprite3D& operator=(const Sprite3D&) = delete;
	Sprite3D(const Sprite3D&) = delete;
};


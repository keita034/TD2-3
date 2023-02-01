#pragma once
#include"ErrorException.h"

#include"AliceMathUtility.h"
#include"Sprite.h"
#include"DefaultMaterial.h"
#include"AliceUtility.h"

class Sprite2D : public Sprite
{
private:


public:

	Sprite2D();
	~Sprite2D();
	
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="handle">�e�N�X�`���n���h��</param>
	virtual void Initialize(uint32_t handle)override;

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="transform">���[���h�ϊ��f�[�^</param>
	/// <param name="blend">�u�����h�ݒ�(�����l�̓A���t�@�u�����h)</param>
	/// <param name="material">�u�����h��CUSTOM���Ɏg��</param>
	virtual void Draw(Transform& transform,BlendMode blend = BlendMode::AX_BLENDMODE_ALPHA, Material* material = nullptr)override;

	/// <summary>
	/// �A�j���[�V�����`��
	/// </summary>
	/// <param name="transform">���[���h�ϊ��f�[�^</param>
	/// <param name="radiusX">�A�j���[�V�����摜�̈ꖇ���̉���</param>
	/// <param name="radiusY">�A�j���[�V�����摜�̈ꖇ���̏c��</param>
	/// <param name="frame">�A�j���[�V�����t���[��</param>
	/// <param name="frameDiv">�A�j���[�V�����t���[���̍ő�l</param>
	/// <param name="blend">�u�����h�ݒ�(�����l�̓A���t�@�u�����h)</param>
	/// <param name="material">�u�����h��CUSTOM���Ɏg��</param>
	virtual void AnimationDraw(Transform& transform, uint16_t radiusX, uint16_t radiusY, float& frame, float frameDiv, BlendMode blend = BlendMode::AX_BLENDMODE_ALPHA, Material* material = nullptr)override;

private:


	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Sprite2D& operator=(const Sprite2D&) = delete;
	Sprite2D(const Sprite2D&) = delete;

};
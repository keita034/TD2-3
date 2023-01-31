#pragma once
#include"BasePostEffect.h"
#include"ConstantBuffer.h"
#include"AliceMathUtility.h"

class VignettePostEffect : public BasePostEffect
{
private:

	std::unique_ptr<ConstantBuffer> vignetteDataBuff;

	struct VignetteData
	{
		//�F
		AliceMathF::Vector3 color;
		float PADING1;
		//���S���W
		AliceMathF::Vector2 center;
		//����
		float power;
		float PADING2;
		//�E�B���h�E�̃T�C�Y(UV���W�v�Z�p)
		AliceMathF::Vector2 winSize;
		//�~�̏c����
		AliceMathF::Vector2 size;
	};

	VignetteData data = {};

public:

	static VignettePostEffect* GetInstance();

	//������
	void Initialize() override;

	//�X�V
	void PostUpdate(D3D12_GPU_DESCRIPTOR_HANDLE& srv, D3D12_GPU_DESCRIPTOR_HANDLE& uav) override;

	/// <summary>
	/// �r�l�b�g�̐ݒ�
	/// </summary>
	/// <param name="color">�r�l�b�g�̐F(255�`0)</param>
	/// <param name="center">�r�l�b�g�̒��S���W(1.0�`0.0)</param>
	/// <param name="power">�r�l�b�g�̋���</param>
	/// <param name="size">�r�l�b�g�̏c����(�E�B���h�E�̔䗦�Ɉˑ�)</param>
	static void SetVignetteData(const AliceMathF::Vector3& color = { 1.0f,1.0f,1.0f }, const AliceMathF::Vector2& center = { 0.5f,0.5f }, float power = 1.0f, const AliceMathF::Vector2& size = { 1.0,1.0f });

	/// <summary>
	/// �J���[��ݒ�
	/// </summary>
	/// <param name="color">�r�l�b�g�̐F(255�`0)</param>
	static void SetColor(const AliceMathF::Vector3& color = { 1.0f,1.0f,1.0f });

	/// <summary>
	/// ���S���W��ݒ�
	/// </summary>
	/// <param name="center">�r�l�b�g�̒��S���W(1.0�`0.0)</param>
	static void SetCenter(const AliceMathF::Vector2& center = { 0.5f,0.5f });

	/// <summary>
	/// ������ݒ�
	/// </summary>
	/// <param name="power">�r�l�b�g�̋���</param>
	static void SetPower(float power = 1.0f);

	/// <summary>
	/// �c�����ݒ�(�E�B���h�E�̔䗦�Ɉˑ�)
	/// </summary>
	/// <param name="size">�r�l�b�g�̏c����</param>
	static void SetSize(const AliceMathF::Vector2& size = { 1.0,1.0f });

	/// <summary>
	/// �^�C�v���擾
	/// </summary>
	const std::string& GetType()override;

private:

	//�r�l�b�g�f�[�^��ݒ�
	void SetData(const AliceMathF::Vector3& color = { 1.0f,1.0f,1.0f }, const AliceMathF::Vector2& center = { 0.5f,0.5f }, float power = 1.0f, const AliceMathF::Vector2& size = { 1.0,1.0f });

	//�r�l�b�g�J���[��ݒ�
	void SetCol(const AliceMathF::Vector3& color = { 1.0f,1.0f,1.0f });

	//�r�l�b�g�̒��S���W��ݒ�
	void SetCent(const AliceMathF::Vector2& center = { 0.5f,0.5f });

	//�r�l�b�g�̋�����ݒ�
	void SetPow(float power = 1.0f);

	//�r�l�b�g�̏c�����ݒ�
	void SetSi(const AliceMathF::Vector2& size = { 1.0,1.0f });

	VignettePostEffect() = default;
	~VignettePostEffect() = default;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	VignettePostEffect& operator=(const VignettePostEffect&) = delete;
	VignettePostEffect(const VignettePostEffect&) = delete;
};


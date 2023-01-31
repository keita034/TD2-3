#pragma once
#include"AbstractPostEffectFactory.h"

/// <summary>
/// �|�X�g�G�t�F�N�g�H��
/// </summary>
class PostEffectFactory final : public AbstractPostEffectFactory
{
public:

	static PostEffectFactory* GetInstance();

	/// <summary>
	/// �|�X�g�G�t�F�N�g����
	/// </summary>
	/// <param name="sceneName">�|�X�g�G�t�F�N�g��</param>
	/// <returns>���������|�X�g�G�t�F�N�g</returns>
	BasePostEffect* CreatePostEffect(const std::string& postEffectName) override;

private:

	PostEffectFactory() = default;
	~PostEffectFactory() = default;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	PostEffectFactory& operator=(const PostEffectFactory&) = delete;
	PostEffectFactory(const PostEffectFactory&) = delete;
};


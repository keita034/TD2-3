#pragma once
/// <summary>
/// �V�[�����N���X
/// </summary>

class SceneManager;

class BaseScene
{
private:

	//�V�[���}�l�[�W���[
	SceneManager* sceneManager = nullptr;

public:

	virtual ~BaseScene() = default;

	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// ��n��
	/// </summary>
	virtual void Finalize() = 0;

	virtual void SetSceneManager(SceneManager* manager);
};


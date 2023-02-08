#pragma once
#include"Transform.h"
#include"Camera.h"
#include"Model.h"


class Goal {

public:
	/// <summary>
	/// �ŏ��Ɏ����������
	/// </summary>
	/// <param name="modelHandl">���f���n���h��</param>
	Goal(uint32_t modelHandl);

	/// <summary>
	/// ���Z�b�g�������̏���������
	/// </summary>
	void Initialise();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="camera"></param>
	void Update(Camera* camera);

	/// <summary>
	/// ���ۂ̕`��
	/// </summary>
	void Draw();


	/// <summary>
	/// �v���C���[�̓����蔻��
	/// </summary>
	void Collider(Camera* camera);



private:

	Transform worldTransform_;
	std::unique_ptr<Model> model;

	// �R���C�_�[�̒ǉ�
	float radius = 2.0f;
	// �R���C�_�[
	BaseCollider* collider = nullptr;
	
};
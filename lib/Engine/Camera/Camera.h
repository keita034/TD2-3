#pragma once
#include"AliceMathUtility.h"


///<summary>
///�ˉe�s��̍X�V���@�B
///</summary>
enum UpdateProjMatrixFunc
{
	UpdateProjMatrixFunc_Perspective,		//�����ˉe�s��B���ߖ@���������G����肽���Ȃ炱�����B
	UpdateProjMatrixFunc_Ortho,			//���s���e�B�Q�c�I�ȕ\�����������Ȃ炱�����B
};

class Camera
{
public:

	Camera() = default;
	virtual ~Camera() = default;

	/// <summary>
	/// �r���[�s����擾
	/// </summary>
	virtual const AliceMathF::Matrix4& GetViewMatrix() = 0;

	/// <summary>
	/// �r���[�s��̋t�s����擾
	/// </summary>
	virtual const AliceMathF::Matrix4& GetViewMatrixInv() = 0;

	/// <summary>
	/// �v���W�F�N�V�����s����擾
	/// </summary>
	virtual const AliceMathF::Matrix4& GetProjectionMatrix() = 0;

	/// <summary>
	/// �r���[�~�v���W�F�N�V�����s����擾
	/// </summary>
	virtual const AliceMathF::Matrix4& GetViewProjectionMatrix() = 0;

	/// <summary>
	/// �J�����̉�]�s����擾
	/// </summary>
	virtual const AliceMathF::Matrix4& GetCameraRotation() = 0;

	/// <summary>
	/// �����ʂ܂ł̋������擾
	/// </summary>
	virtual float GetFar() const = 0;

	/// <summary>
	/// �ߕ��ʂ܂ł̋������擾
	/// </summary>
	virtual float GetNear() const = 0;

	/// <summary>
	/// �A�X�y�N�g����擾
	/// </summary>
	virtual float GetAspect() const = 0;

	/// <summary>
	/// ��p���擾
	/// </summary>
	/// <returns>��p�B�P�ʃ��W�A��</returns>
	virtual float GetFovAngleY() const = 0;

	/// <summary>
	/// �����_�Ǝ��_�̋������擾
	/// </summary>
	/// <returns></returns>
	virtual float GetTargetToPositionLength() const = 0;

	/// <summary>
	/// �J�����̑O�������擾
	/// </summary>
	virtual const AliceMathF::Vector3& GetForward() const = 0;

	/// <summary>
	/// ���s���e�̉��[���擾
	/// </summary>
	virtual float GetBottom() = 0;

	/// <summary>
	/// ���s���e�̏�[���擾
	/// </summary>
	virtual float GetTop() = 0;

	/// <summary>
	/// ���s���e�̉E�[���擾
	/// </summary>
	virtual float GetRight() = 0;

	/// <summary>
	/// ���s���e�̍��[���擾
	/// </summary>
	virtual float GetLeft() = 0;

	/// <summary>
	/// ���_���W���擾
	/// </summary>
	virtual const AliceMathF::Vector3& GetEye() = 0;

	/// <summary>
	/// �����_���W���擾
	/// </summary>
	virtual const AliceMathF::Vector3& GetUp() = 0;

	/// <summary>
	/// ������x�N�g�����擾
	/// </summary>
	virtual const AliceMathF::Vector3& GetTarget() = 0;
};

class GameCamera :public Camera
{
private:

	//���_���W
	AliceMathF::Vector3 eye = { 0.0f,0.0f,-50.0f };
	//�����_���W
	AliceMathF::Vector3 target = { 0.0f,0.0f,0.0f };
	//������x�N�g��
	AliceMathF::Vector3 up = { 0.0f,1.0f,0.0f };

	//�r���[�s��
	AliceMathF::Matrix4 viewMatrix;
	//�v���W�F�N�V�����s��
	AliceMathF::Matrix4 projectionMatrix;
	//�r���[�v���W�F�N�V�����s��
	AliceMathF::Matrix4 viewProjectionMatrix;
	//�r���[�s��̋t�s��
	AliceMathF::Matrix4 viewMatrixInv;
	//�J�����̉�]�s��
	AliceMathF::Matrix4 cameraRotation;

	//��p(���W�A���x)
	float fovAngleY = 0.0;
	//�A�X�y�N�g��(��ʉ���/��ʏc��)
	float aspect = 0.0f;
	//�j�A�N���b�v(�O�[)
	float near_ = 0.0f;
	//�t�@�[�N���b�v(���[)
	float far_ = 0.0f;
	//��ʍ���
	float left = 0.0f;
	//��ʉE�[
	float right = 0.0f;
	//��ʏ㑤
	float top = 0;
	//��ʉ���
	float bottom = 0.0f;

	//�v���W�F�N�V�����s��̍X�V�t���O
	bool updateProjMatrix = true;
	//�r���[�s��̍X�V�t���O
	bool updateViewMatrix = true;
	char PADDING[2]{};

	//�����_�Ǝ��_�̋���
	float tgtToPosLen = 0.0f;

	//�J�����̐��ʃx�N�g��
	AliceMathF::Vector3 forward = { 0.0f,0.0f,0.0f };

	UpdateProjMatrixFunc matrixFunc = UpdateProjMatrixFunc_Perspective;

	char PADDING2[4]{};


public:

	GameCamera() = default;
	~GameCamera() = default;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(UpdateProjMatrixFunc matFunc);

	/// <summary>
	/// �r���[�s��E�v���W�F�N�V�����s����X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �J�����𓮂���
	/// </summary>
	/// <param name="move">��������</param>
	void Move(const AliceMathF::Vector3& move);

	/// <summary>
	/// �����_�𓮂���
	/// </summary>
	/// <param name="move">�ړ���</param>
	void MoveTarget(const AliceMathF::Vector3& move);

	/// <summary>
	/// ���_�𓮂���
	/// </summary>
	/// <param name="move">�ړ���</param>
	void MovePosition(const AliceMathF::Vector3& move);

#pragma region �Z�b�^�[

	/// <summary>
	/// �A�X�y�N�g���ݒ肷��
	/// </summary>
	void SetAspect(float aspect_);

	/// <summary>
	/// �����ʂ܂ł̋�����ݒ�
	/// </summary>
	void SetFar(float fFar);

	/// <summary>
	/// �ߕ��ʂ܂ł̋�����ݒ�
	/// </summary>
	void SetNear(float fNear);

	/// <summary>
	/// �s��̌v�Z���@��ݒ�
	/// </summary>
	/// <param name="func"></param>
	void SetUpdateProjMatrixFunc(UpdateProjMatrixFunc func);

	/// <summary>
	/// ��p��ݒ�
	/// </summary>
	/// <remarks>
	/// SetUpdateProjMatrixFunc��enUpdateProjMatrixFunc_Perspective���ݒ肳��Ă���Ƃ��Ɏg�p�����B
	/// </remarks>
	/// <param name="viewAngle">��p�A�P�ʃ��W�A��</param>
	void SetFovAngleY(float fovAngle);

	/// <summary>
	/// ���s���e�̍��[��ݒ�
	/// </summary>
	/// <param name="left_">���[</param>
	void SetLeft(float left_);

	/// <summary>
	/// ���s���e�̉E�[��ݒ�
	/// </summary>
	/// <param name="right_">�E�[</param>
	void SetRight(float right_);

	/// <summary>
	/// ���s���e�̏�[��ݒ�
	/// </summary>
	/// <param name="top_">��[</param>
	void SetTop(float top_);

	/// <summary>
	/// ���s���e�̉��[��ݒ�
	/// </summary>
	/// <param name="bottom_">���[</param>
	void SetBottom(float bottom_);

	/// <summary>
	/// �J�����̍��W��ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetEye(const AliceMathF::Vector3& pos);

	/// <summary>
	/// �J�����̃^�[�Q�b�g���W��ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetTarget(const AliceMathF::Vector3& pos);

	/// <summary>
	/// �J�����̏�x�N�g����ݒ�
	/// </summary>
	/// <param name="vec">�x�N�g��</param>
	void SetUp(const AliceMathF::Vector3& vec);

#pragma endregion

#pragma region �Q�b�^�[

	/// <summary>
	/// �r���[�s����擾
	/// </summary>
	const AliceMathF::Matrix4& GetViewMatrix();

	/// <summary>
	/// �r���[�s��̋t�s����擾
	/// </summary>
	const AliceMathF::Matrix4& GetViewMatrixInv();

	/// <summary>
	/// �v���W�F�N�V�����s����擾
	/// </summary>
	const AliceMathF::Matrix4& GetProjectionMatrix();

	/// <summary>
	/// �r���[�~�v���W�F�N�V�����s����擾
	/// </summary>
	const AliceMathF::Matrix4& GetViewProjectionMatrix();

	/// <summary>
	/// �J�����̉�]�s����擾
	/// </summary>
	const AliceMathF::Matrix4& GetCameraRotation();

	/// <summary>
	/// �����ʂ܂ł̋������擾
	/// </summary>
	float GetFar() const;

	/// <summary>
	/// �ߕ��ʂ܂ł̋������擾
	/// </summary>
	float GetNear() const;

	/// <summary>
	/// �A�X�y�N�g����擾
	/// </summary>
	float GetAspect() const;

	/// <summary>
	/// ��p���擾
	/// </summary>
	/// <returns>��p�B�P�ʃ��W�A��</returns>
	float GetFovAngleY() const;

	/// <summary>
	/// �����_�Ǝ��_�̋������擾
	/// </summary>
	/// <returns></returns>
	float GetTargetToPositionLength() const;

	/// <summary>
	/// �J�����̑O�������擾
	/// </summary>
	const AliceMathF::Vector3& GetForward() const;

	/// <summary>
	/// ���s���e�̉��[���擾
	/// </summary>
	float GetBottom();

	/// <summary>
	/// ���s���e�̏�[���擾
	/// </summary>
	float GetTop();

	/// <summary>
	/// ���s���e�̉E�[���擾
	/// </summary>
	float GetRight();

	/// <summary>
	/// ���s���e�̍��[���擾
	/// </summary>
	float GetLeft();

	/// <summary>
	/// ���_���W���擾
	/// </summary>
	const AliceMathF::Vector3& GetEye();

	/// <summary>
	/// �����_���W���擾
	/// </summary>
	const AliceMathF::Vector3& GetUp();

	/// <summary>
	/// ������x�N�g�����擾
	/// </summary>
	const AliceMathF::Vector3& GetTarget();

#pragma endregion
};


#pragma once
#include"ErrorException.h"
#include"AliceMathUtility.h"
#include"Camera.h"

enum class SensorSize
{
	MEDIUM_FORMAT,//����
	FF,//�t���T�C�Y
	APS_C,//APS-C
	M_FOUR_THIRDS,//�}�C�N���t�H�[�T�[�Y
	ONE_INCH,//1�C���`
	ONE_OVER_ONE_POINT_SEVEN_INCH,//1/1.7�C���`
	ONE_THIRD_INCH//1/3�C���`
};

struct CinemaCameraSensorSize
{
	float width;
	float height;
};

class CinemaCamera :public Camera
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

	//�v���W�F�N�V�����s��̍X�V�t���O
	bool updateProjMatrix = true;
	//�r���[�s��̍X�V�t���O
	bool updateViewMatrix = true;
	char PADDING[2]{};

	//�����_�Ǝ��_�̋���
	float tgtToPosLen = 0.0f;

	//�J�����̐��ʃx�N�g��
	AliceMathF::Vector3 forward = { 0.0f,0.0f,0.0f };

	bool simpleFollowWithWorldUp = false;
	char PADDING2[3]{};

	//�œ_����
	float focalLength = 70.0f;
	//�Z���T�[�T�C�Y
	SensorSize sensorSize = SensorSize::MEDIUM_FORMAT;
	//��p�v�Z�t���O
	bool updatefovAngleY;
	//�Z���T�[�T�C�Y
	CinemaCameraSensorSize cameraSensorSize = { 43.8f,32.8f };
	//F�l
	float aperture;
	//�B�e����
	float shootingDistance;
public:

	CinemaCamera() = default;
	~CinemaCamera() = default;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

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
	/// �œ_������ݒ�
	/// </summary>
	/// <param name="length">�œ_����</param>
	void SetFocalLength(float length);

	/// <summary>
	/// F�l��ݒ�
	/// </summary>
	void SetAperture(float value);

	/// <summary>
	/// �Z���T�[�̎�ނ�ݒ�
	/// </summary>
	/// <param name="size">���</param>
	void SetSensorSize(SensorSize size);

	/// <summary>
	/// �B�e������ݒ�
	/// </summary>
	void SetShootingDistance(float distance);

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
	float GetTargetToPositionLength() const;

	/// <summary>
	/// �œ_�������擾
	/// </summary>
	float GetFocalLength() const;

	/// <summary>
	/// F�l��ݒ�
	/// </summary>
	float GetAperture() const;

	/// <summary>
	/// �B�e�������擾
	/// </summary>
	float GetDistance() const;

	/// <summary>
	/// �J�����̑O�������擾
	/// </summary>
	const AliceMathF::Vector3& GetForward() const;

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

private:
	/// <summary>
	/// ���s���e�̉��[���擾
	/// </summary>
	float GetBottom()
	{
		return float();
	};

	/// <summary>
	/// ���s���e�̏�[���擾
	/// </summary>
	float GetTop()
	{
		return float();
	};

	/// <summary>
	/// ���s���e�̉E�[���擾
	/// </summary>
	float GetRight()
	{
		return float();
	};

	/// <summary>
	/// ���s���e�̍��[���擾
	/// </summary>
	float GetLeft()
	{
		return float();
	};
};
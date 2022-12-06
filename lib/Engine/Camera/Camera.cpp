#include "Camera.h"
#include"WindowsApp.h"

void GameCamera::Initialize(UpdateProjMatrixFunc matFunc)
{
	//�A�X�y�N�g����v�Z����
	aspect =
		static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().width) /
		static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().height);

	matrixFunc = matFunc;

	if (matFunc == UpdateProjMatrixFunc_Ortho)//���s���e
	{
		if (far_ == 0.0f)
		{
			far_ = 1.0f;
		}
		right = static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().width);
		bottom = static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().height);

		//���s���e�̌v�Z
		AliceMathF::MakeOrthogonalL(left, right, bottom, top, near_, far_, projectionMatrix);

	}
	else//�������e
	{
		if (near_ == 0.0f)
		{
			near_ = 0.1f;
		}
		if (far_ == 0.0f)
		{
			far_ = 1000.0f;
		}
		if (fovAngleY == 0.0f)
		{
			fovAngleY = AliceMathF::AX_PI / 4;
		}

		//�������e�s��̌v�Z
		AliceMathF::MakePerspectiveL(fovAngleY, aspect, near_, far_, projectionMatrix);

	}

	updateProjMatrix = false;

	//�r���[�s��̎Z�o
	AliceMathF::MakeLookL(eye, target, up, viewMatrix);
	//�r���[�s��̋t�s����v�Z
	viewMatrixInv = AliceMathF::MakeInverse(&viewMatrix);
	//�r���[�v���W�F�N�V�����s��̍쐬
	viewProjectionMatrix = viewMatrix * projectionMatrix;

	//�J�����̑O�x�N�g���擾
	forward = { viewMatrixInv.m[2][0], viewMatrixInv.m[2][1], viewMatrixInv.m[2][2] };
	forward.Normal();

	//�����_�Ǝ��_�̋����擾
	AliceMathF::Vector3 toPos;
	toPos = eye - target;
	tgtToPosLen = toPos.Length();

	updateViewMatrix = false;
}

void GameCamera::Update()
{
	if (updateProjMatrix)
	{
		if (matrixFunc == UpdateProjMatrixFunc_Ortho)
		{
			if (far_ == 0.0f)
			{
				far_ = 1.0f;
			}

			right = static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().width);
			bottom = static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().height);
			AliceMathF::MakeOrthogonalL(left, right, bottom, top, near_, far_, projectionMatrix);

		}
		else
		{
			if (near_ == 0.0f)
			{
				near_ = 0.1f;
			}
			if (far_ == 0.0f)
			{
				far_ = 1000.0f;
			}
			if (fovAngleY == 0.0f)
			{
				fovAngleY = AliceMathF::AX_PI / 4;
			}

			AliceMathF::MakePerspectiveL(fovAngleY, aspect, near_, far_, projectionMatrix);
		}
		updateProjMatrix = false;
	}

	if (updateViewMatrix)
	{
		//�r���[�s��̎Z�o
		AliceMathF::MakeLookL(eye, target, up, viewMatrix);
		//�r���[�v���W�F�N�V�����s��̍쐬
		viewProjectionMatrix = viewMatrix * projectionMatrix;
		//�r���[�s��̋t�s����v�Z
		viewMatrixInv = AliceMathF::MakeInverse(&viewMatrix);

		forward = { viewMatrixInv.m[2][0], viewMatrixInv.m[2][1], viewMatrixInv.m[2][2] };

		AliceMathF::Vector3 toPos;
		toPos = eye - target;
		tgtToPosLen = toPos.Length();

		updateViewMatrix = false;
	}
}

void GameCamera::Move(const AliceMathF::Vector3& move)
{
	eye += move;
	target += move;
	updateViewMatrix = true;
}

void GameCamera::MoveTarget(const AliceMathF::Vector3& move)
{
	target += move;
	updateViewMatrix = true;
}

void GameCamera::MovePosition(const AliceMathF::Vector3& move)
{
	eye += move;
	updateViewMatrix = true;
}

#pragma region �Z�b�^�[

void GameCamera::SetAspect(float aspect_)
{
	aspect = aspect_;
	updateViewMatrix = true;
}

void GameCamera::SetFar(float fFar)
{
	far_ = fFar;
	updateProjMatrix = true;
}

void GameCamera::SetNear(float fNear)
{
	near_ = fNear;
	updateProjMatrix = true;
}

void GameCamera::SetFovAngleY(float fovAngle)
{
	this->fovAngleY = fovAngle;
	updateProjMatrix = true;
}

void GameCamera::SetUpdateProjMatrixFunc(UpdateProjMatrixFunc func)
{
	matrixFunc = func;
	updateProjMatrix = true;
}

void GameCamera::SetLeft(float left_)
{
	left = left_;
	updateProjMatrix = true;
}
void GameCamera::SetRight(float right_)
{
	right = right_;
	updateProjMatrix = true;
}

void GameCamera::SetTop(float top_)
{
	top = top_;
	updateProjMatrix = true;
}

void GameCamera::SetBottom(float bottom_)
{
	bottom = bottom_;
	updateProjMatrix = true;
}

void GameCamera::SetEye(const AliceMathF::Vector3& pos)
{
	updateViewMatrix = true;
	eye = pos;
}

void GameCamera::SetTarget(const AliceMathF::Vector3& pos)
{
	updateViewMatrix = true;
	target = pos;
}

void GameCamera::SetUp(const AliceMathF::Vector3& vec)
{
	updateViewMatrix = true;
	up = vec;
}

#pragma endregion

#pragma region �Q�b�^�[

const AliceMathF::Matrix4& GameCamera::GetViewMatrix()
{
	//�X�V
	Update();
	return viewMatrix;
}

const AliceMathF::Matrix4& GameCamera::GetViewMatrixInv()
{
	//�X�V
	Update();
	return viewMatrixInv;
}

const AliceMathF::Matrix4& GameCamera::GetProjectionMatrix()
{
	//�X�V
	Update();
	return projectionMatrix;
}

const AliceMathF::Matrix4& GameCamera::GetViewProjectionMatrix()
{
	//�X�V
	Update();
	return viewProjectionMatrix;
}

const AliceMathF::Matrix4& GameCamera::GetCameraRotation()
{
	//�X�V
	Update();
	return cameraRotation;
}

float GameCamera::GetFar() const
{
	return far_;
}

float GameCamera::GetNear() const
{
	return near_;
}

float GameCamera::GetFovAngleY() const
{
	return fovAngleY;
}

float GameCamera::GetTargetToPositionLength() const
{
	return tgtToPosLen;
}

const AliceMathF::Vector3& GameCamera::GetForward() const
{
	return forward;
}

float GameCamera::GetAspect() const
{
	return aspect;
}

float GameCamera::GetLeft()
{
	return left;
}

const AliceMathF::Vector3& GameCamera::GetEye()
{
	return eye;
}

const AliceMathF::Vector3& GameCamera::GetUp()
{
	return up;
}

const AliceMathF::Vector3& GameCamera::GetTarget()
{
	return target;
}

float GameCamera::GetRight()
{
	return right;
}

float GameCamera::GetTop()
{
	return top;
}

float GameCamera::GetBottom()
{
	return bottom;
}

#pragma endregion
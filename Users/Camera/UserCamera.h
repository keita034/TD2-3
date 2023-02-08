#pragma once

#include "Matrix4.h"
#include"Vector2.h"
#include"Input.h"
#include "Transform.h"

class UserCamera {

public:

	UserCamera(int window_width, int window_height);

	void Initialize(AliceMathF::Matrix4 playerPos);

	void Update();

	void MouseRotation();

	void LabyrinthCamera();

	void MultiplyMatrix(const AliceMathF::Matrix4& matrix);

	AliceMathF::Vector3 Vector3Transform(const AliceMathF::Vector3& v, const AliceMathF::Matrix4& m);

	AliceMathF::Vector3 GetEye() { return vTargetEye; }
	AliceMathF::Vector3 GetUp() { return vUp; }
	AliceMathF::Vector3 GetTarget() { return target; }
	AliceMathF::Matrix4 GetCameraRot() { return this->CameraRot; }
	AliceMathF::Vector3 GetCameraRotVec3() { return this->Rot; }


	void SetCameraType(int x) { cameraType = x; }
	void SetCameraPosition(AliceMathF::Vector3 pos) { playerPos = pos; }

private:
	// �J���������_�܂ł̋���
	float distance_ = 200;
	AliceMathF::Vector2 mousePos = { 0.0f,0.0f };
	AliceMathF::Vector2 oldMousePos = { 0.0f,0.0f };
	Input* input_ = nullptr;

	// ��]�s��
	AliceMathF::Matrix4 matRot;

	AliceMathF::Vector3 Rot;

	float fTheta = 4.57f;//�J�����������p�x
	float fDelta = 0.43f;//�J�����c�����p�x

	float mousepoint_a;//�}�E�X�ʒu
	float mousepoint_b;//�}�E�X�ʒu
	bool dirty = false;

	// �X�P�[�����O
	float scaleX_ = 1.0f;
	float scaleY_ = 1.0f;

	AliceMathF::Vector3 vTargetEye;
	AliceMathF::Vector3 vUp;
	AliceMathF::Vector3 playerPos;
	AliceMathF::Vector3 target;

	int cameraType = 0;

	int winWidth = 0;
	int winHeight = 0;
	AliceMathF::Vector2 MouseMove;
	AliceMathF::Vector2 mouseMoved;
	Transform worldTransform_;

	AliceMathF::Matrix4 CameraRot;
	float playerCameraDistance = 10.0f;

};
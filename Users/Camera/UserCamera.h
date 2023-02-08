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
	// カメラ注視点までの距離
	float distance_ = 200;
	AliceMathF::Vector2 mousePos = { 0.0f,0.0f };
	AliceMathF::Vector2 oldMousePos = { 0.0f,0.0f };
	Input* input_ = nullptr;

	// 回転行列
	AliceMathF::Matrix4 matRot;

	AliceMathF::Vector3 Rot;

	float fTheta = 4.57f;//カメラ横方向角度
	float fDelta = 0.43f;//カメラ縦方向角度

	float mousepoint_a;//マウス位置
	float mousepoint_b;//マウス位置
	bool dirty = false;

	// スケーリング
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
#pragma once

#include "Matrix4.h"
#include"Vector2.h"
#include"Input.h"

class UserCamera {

public:
	
	UserCamera(int window_width, int window_height);

	void Initialize();

	void Update();

	void MultiplyMatrix(const AliceMathF::Matrix4& matrix);

	AliceMathF::Vector3 Vector3Transform(const AliceMathF::Vector3& v, const AliceMathF::Matrix4& m);

	AliceMathF::Vector3 GetEye() { return vTargetEye; }
	AliceMathF::Vector3 GetUp() { return vUp; }

private:
	// カメラ注視点までの距離
	float distance_ = 100;
	AliceMathF::Vector2 mousePos = { 0.0f,0.0f };
	AliceMathF::Vector2 oldMousePos = { 0.0f,0.0f };
	Input* input_ = nullptr;

	// 回転行列
	AliceMathF::Matrix4 matRot;

	// スケーリング
	float scaleX_ = 1.0f;
	float scaleY_ = 1.0f;

	AliceMathF::Vector3 vTargetEye;
	AliceMathF::Vector3 vUp;



};
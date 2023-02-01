#include "UserCamera.h"


UserCamera::UserCamera(int window_width, int window_height) {
	input_ = Input::GetInstance();

	// 画面サイズに対する相対的なスケールに調整
	scaleX_ = 1.0f / (float)window_width;
	scaleY_ = 1.0f / (float)window_height;
}

void UserCamera::Initialize(){

	

}

void UserCamera::Update(){
	bool dirty = false;
	float angleX = 0;
	float angleY = 0;

	oldMousePos = mousePos;
	mousePos = input_->GetMousePos();

	AliceMathF::Vector2 mouseMovement = mousePos - oldMousePos;

	// マウスの左ボタンが押されていたらカメラを回転させる
	if (input_->MouseButtonInput(MouseButton::LEFT))
	{
		float dy = mouseMovement.x * scaleY_;
		float dx = mouseMovement.y * scaleX_;

		angleX = -dx * AliceMathF::AX_PI;
		angleY = -dy * AliceMathF::AX_PI;
		dirty = true;
	}

	if (dirty) {
		// 追加回転分の回転行列を生成
		AliceMathF::Matrix4 matRotNew;
		matRotNew.MakeRotationX(-angleX);
		matRotNew.MakeRotationY(-angleY);

		MultiplyMatrix(matRotNew);
	}

}

void UserCamera::MultiplyMatrix(const AliceMathF::Matrix4& matrix) {
	// 累積の回転行列を合成
	matRot = matrix * matRot;

	// 注視点から視点へのベクトルと、上方向ベクトル
	vTargetEye = { 0.0f, 0.0f, -distance_ };
	vUp = { 0.0f, 1.0f, 0.0f };

	// ベクトルを回転
	vTargetEye = Vector3Transform(vTargetEye, matRot);
	vUp = Vector3Transform(vUp, matRot);

}

AliceMathF::Vector3 UserCamera::Vector3Transform(const AliceMathF::Vector3& v, const AliceMathF::Matrix4& m){

	AliceMathF::Vector3 result{
		  v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0],
		  v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1],
		  v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2] 
	};

	return result;
}

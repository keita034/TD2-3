#include "UserCamera.h"

const float pi = 3.1415926535;

UserCamera::UserCamera() {
	input_ = Input::GetInstance();
}

void UserCamera::Initialize(){

	

}

void UserCamera::Update(){

	float angleX = 0;
	float angleY = 0;

	mouseMovement = input_->GetMousePos();

	// マウスの左ボタンが押されていたらカメラを回転させる
	/*if (input_->MouseButtonInput())
	{
		float dy = mouseMove.lX * scaleY;
		float dx = mouseMove.lY * scaleX;

		angleX = -dx * pi;
		angleY = -dy * pi;
		
	}*/

}

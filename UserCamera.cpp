#include "UserCamera.h"
#include "WindowsApp.h"


UserCamera::UserCamera(int window_width, int window_height) {
	input_ = Input::GetInstance();

	winWidth = window_width;
	winHeight = window_height;

	// 画面サイズに対する相対的なスケールに調整
	scaleX_ = 1.0f / (float)window_width;
	scaleY_ = 1.0f / (float)window_height;

	bool dirty = false;
	float angleX = 0;
	float angleY = 0;

	oldMousePos = mousePos;
	mousePos = input_->GetMousePos();

	// 追加回転分の回転行列を生成
	AliceMathF::Matrix4 matRotNew;
	matRotNew.MakeRotationX(-angleX);
	matRotNew.MakeRotationY(-angleY);

	MultiplyMatrix(matRotNew);

	worldTransform_.Initialize();

}

void UserCamera::Initialize() {



}

void UserCamera::Update() {

	oldMousePos = mousePos;
	mousePos = input_->GetMousePos();

	switch (cameraType){
	case 0:
		// マウスカーソルの表示
		ShowCursor(TRUE);
		MouseRotation();

		break;
	case 1:
		// マウスカーソルの表示
		ShowCursor(FALSE);
		vUp = { 0.0f,1.0f,0.0f };
		LabyrinthCamera();

		break;
	default:
		break;
	}

	

}

void UserCamera::MouseRotation(){

	bool dirty = false;
	float angleX = 0;
	float angleY = 0;

	AliceMathF::Vector2 mouseMovement = mousePos - oldMousePos;


	// マウスの左ボタンが押されていたらカメラを回転させる
	if (input_->MouseButtonInput(MouseButton::LEFT)){

		dirty = true;
	}

	if (dirty) {

		fTheta -= (mousePos.x - oldMousePos.x) * 0.003f;//カメラ横方向角度変更

		if (fDelta + (mousePos.y - oldMousePos.y) * 0.003f >= AliceMathF::AX_PI / 2.0f - 0.0001f)
		{
			fDelta = AliceMathF::AX_PI / 2.0f - 0.0001f;//カメラ縦方向角度変更
		}
		else if (fDelta + (mousePos.y - oldMousePos.y) * 0.003f <= -AliceMathF::AX_PI / 2.0f + 0.0001f)
		{
			fDelta = -AliceMathF::AX_PI / 2.0f + 0.0001f;//カメラ縦方向角度変更
		}
		else
		{
			fDelta += (mousePos.y - oldMousePos.y) * 0.003f;//カメラ縦方向角度変更
		}

	}

	//カメラ位置決定
	vTargetEye.x = distance_ * cos(fDelta) * cos(fTheta);
	vTargetEye.y = distance_ * sin(fDelta);
	vTargetEye.z = distance_ * cos(fDelta) * sin(fTheta);
}

void UserCamera::LabyrinthCamera(){

	//カメラの回転ベクトル
	AliceMathF::Vector3 rotat = { 0, 0, 0 };
	//カメラの移動の速さ
	const float cameraSpeed = 0.0005f;

	AliceMathF::Vector2 windowWH = AliceMathF::Vector2(winWidth / 2, winHeight / 2);
	POINT mousePosition;
	//マウス座標(スクリーン座標)を取得する
	GetCursorPos(&mousePosition);

	//クライアントエリア座標に変換する
	HWND hwnd = WindowsApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);

	int xPos_absolute, yPos_absolute;

	int xPos = windowWH.x;  //移動させたいｘ座標（ウィンドウ内の相対座標）
	int yPos = windowWH.y; //移動させたいｙ座標（ウィンドウ内の相対座標）

	WINDOWINFO windowInfo;
	//ウィンドウの位置を取得
	windowInfo.cbSize = sizeof(WINDOWINFO);
	GetWindowInfo(hwnd, &windowInfo);

	//マウスの移動先の絶対座標（モニター左上からの座標）
	xPos_absolute = xPos + windowInfo.rcWindow.left + 8;//なんかずれてるから直す
	yPos_absolute = yPos + windowInfo.rcWindow.top + 31; //ウィンドウのタイトルバーの分（31px）をプラス

	//マウスの移動量を取得
	MouseMove = AliceMathF::Vector2(0, 0);
	MouseMove = (AliceMathF::Vector2(mousePosition.y, mousePosition.x) - AliceMathF::Vector2(windowWH.y, windowWH.x));//座標軸で回転している関係でこうなる(XとYが入れ替え)
	mouseMoved += AliceMathF::Vector2(MouseMove.x, MouseMove.y) / 500;
	SetCursorPos(xPos_absolute, yPos_absolute);

	AliceMathF::Vector3 rotation = AliceMathF::Vector3(mouseMoved.x, mouseMoved.y, 0);
	
	AliceMathF::Matrix4 cameraRot;

	cameraRot.MakeRotation(rotation);

	CameraRot = cameraRot;

	//ワールド前方ベクトル
	AliceMathF::Vector3 forward(0, 0, playerCameraDistance);
	//レールカメラの回転を反映
	forward = Vector3Transform(forward, cameraRot);

	target = playerPos;
	vTargetEye = playerPos + (forward * playerCameraDistance);
	vTargetEye.y = -vTargetEye.y;
}

void UserCamera::MultiplyMatrix(const AliceMathF::Matrix4& matrix) {
	// 累積の回転行列を合成
	matRot = matrix * matRot;
	
	// 注視点から視点へのベクトルと、上方向ベクトル
	vTargetEye = { 0.0f, 0.0f, -distance_ };
	vUp = { 0.0f, 1.0f, 0.0f };

	// ベクトルを回転
	vTargetEye = Vector3Transform(vTargetEye, matRot);

}

AliceMathF::Vector3 UserCamera::Vector3Transform(const AliceMathF::Vector3& v, const AliceMathF::Matrix4& m) {

	AliceMathF::Vector3 result{
		  v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0],
		  v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1],
		  v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2]
	};

	return result;
}

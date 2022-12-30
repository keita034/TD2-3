#include "UserCamera.h"
#include "WindowsApp.h"


UserCamera::UserCamera(int window_width, int window_height) {
	input_ = Input::GetInstance();

	winWidth = window_width;
	winHeight = window_height;

	// ��ʃT�C�Y�ɑ΂��鑊�ΓI�ȃX�P�[���ɒ���
	scaleX_ = 1.0f / (float)window_width;
	scaleY_ = 1.0f / (float)window_height;

	bool dirty = false;
	float angleX = 0;
	float angleY = 0;

	oldMousePos = mousePos;
	mousePos = input_->GetMousePos();

	// �ǉ���]���̉�]�s��𐶐�
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
		// �}�E�X�J�[�\���̕\��
		ShowCursor(TRUE);
		MouseRotation();

		break;
	case 1:
		// �}�E�X�J�[�\���̕\��
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


	// �}�E�X�̍��{�^����������Ă�����J��������]������
	if (input_->MouseButtonInput(MouseButton::LEFT)){

		dirty = true;
	}

	if (dirty) {

		fTheta -= (mousePos.x - oldMousePos.x) * 0.003f;//�J�����������p�x�ύX

		if (fDelta + (mousePos.y - oldMousePos.y) * 0.003f >= AliceMathF::AX_PI / 2.0f - 0.0001f)
		{
			fDelta = AliceMathF::AX_PI / 2.0f - 0.0001f;//�J�����c�����p�x�ύX
		}
		else if (fDelta + (mousePos.y - oldMousePos.y) * 0.003f <= -AliceMathF::AX_PI / 2.0f + 0.0001f)
		{
			fDelta = -AliceMathF::AX_PI / 2.0f + 0.0001f;//�J�����c�����p�x�ύX
		}
		else
		{
			fDelta += (mousePos.y - oldMousePos.y) * 0.003f;//�J�����c�����p�x�ύX
		}

	}

	//�J�����ʒu����
	vTargetEye.x = distance_ * cos(fDelta) * cos(fTheta);
	vTargetEye.y = distance_ * sin(fDelta);
	vTargetEye.z = distance_ * cos(fDelta) * sin(fTheta);
}

void UserCamera::LabyrinthCamera(){

	//�J�����̉�]�x�N�g��
	AliceMathF::Vector3 rotat = { 0, 0, 0 };
	//�J�����̈ړ��̑���
	const float cameraSpeed = 0.0005f;

	AliceMathF::Vector2 windowWH = AliceMathF::Vector2(winWidth / 2, winHeight / 2);
	POINT mousePosition;
	//�}�E�X���W(�X�N���[�����W)���擾����
	GetCursorPos(&mousePosition);

	//�N���C�A���g�G���A���W�ɕϊ�����
	HWND hwnd = WindowsApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);

	int xPos_absolute, yPos_absolute;

	int xPos = windowWH.x;  //�ړ��������������W�i�E�B���h�E���̑��΍��W�j
	int yPos = windowWH.y; //�ړ��������������W�i�E�B���h�E���̑��΍��W�j

	WINDOWINFO windowInfo;
	//�E�B���h�E�̈ʒu���擾
	windowInfo.cbSize = sizeof(WINDOWINFO);
	GetWindowInfo(hwnd, &windowInfo);

	//�}�E�X�̈ړ���̐�΍��W�i���j�^�[���ォ��̍��W�j
	xPos_absolute = xPos + windowInfo.rcWindow.left + 8;//�Ȃ񂩂���Ă邩�璼��
	yPos_absolute = yPos + windowInfo.rcWindow.top + 31; //�E�B���h�E�̃^�C�g���o�[�̕��i31px�j���v���X

	//�}�E�X�̈ړ��ʂ��擾
	MouseMove = AliceMathF::Vector2(0, 0);
	MouseMove = (AliceMathF::Vector2(mousePosition.y, mousePosition.x) - AliceMathF::Vector2(windowWH.y, windowWH.x));//���W���ŉ�]���Ă���֌W�ł����Ȃ�(X��Y������ւ�)
	mouseMoved += AliceMathF::Vector2(MouseMove.x, MouseMove.y) / 500;
	SetCursorPos(xPos_absolute, yPos_absolute);

	AliceMathF::Vector3 rotation = AliceMathF::Vector3(mouseMoved.x, mouseMoved.y, 0);
	
	AliceMathF::Matrix4 cameraRot;

	cameraRot.MakeRotation(rotation);

	CameraRot = cameraRot;

	//���[���h�O���x�N�g��
	AliceMathF::Vector3 forward(0, 0, playerCameraDistance);
	//���[���J�����̉�]�𔽉f
	forward = Vector3Transform(forward, cameraRot);

	target = playerPos;
	vTargetEye = playerPos + (forward * playerCameraDistance);
	vTargetEye.y = -vTargetEye.y;
}

void UserCamera::MultiplyMatrix(const AliceMathF::Matrix4& matrix) {
	// �ݐς̉�]�s�������
	matRot = matrix * matRot;
	
	// �����_���王�_�ւ̃x�N�g���ƁA������x�N�g��
	vTargetEye = { 0.0f, 0.0f, -distance_ };
	vUp = { 0.0f, 1.0f, 0.0f };

	// �x�N�g������]
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

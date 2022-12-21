#include"Player.h"

Player::Player(uint32_t modelHandl) {

	model = std::make_unique<Model>();
	model->SetModel(modelHandl);

	input_ = Input::GetInstance();

	worldTransform_.Initialize();
}

void Player::Initialise(){

	

}

void Player::Update(Camera* camera) {

	PlayerJump();
	PlayerMove();
	worldTransform_.TransUpdate(camera);
}

void Player::PlayerJump() {

	//�X�y�[�X�����ꂽ��W�����v
	if (input_->TriggerPush(DIK_SPACE)) {
		jumpFlag = 1;
	}
	//�W�����v���Ă鎞�̏���
	if (jumpFlag == 1) {
		//�W�����v�t���[��
		jumpFrame++;
		playerJumpSpeed = 1.3f - gravity * (static_cast<float>(jumpFrame) / 100.0f);
		worldTransform_.translation.y += playerJumpSpeed;
	}

	//0���牺�ɂ����Ȃ��悤��
	if (worldTransform_.translation.y < 0) {
		playerJumpSpeed = 0;
		jumpFrame = 0;
		worldTransform_.translation.y = 0;
		jumpFlag = 0;
	}

}

void Player::PlayerMove() {

	AliceMathF::Vector3 playerMovement = { 0,0,0 };

	if (input_->KeepPush(DIK_W)) {
		playerMovement.z = playerSpeed;
	}
	if (input_->KeepPush(DIK_A)) {
		playerMovement.x = -playerSpeed;
	}
	if (input_->KeepPush(DIK_S)) {
		playerMovement.z = -playerSpeed;
	}
	if (input_->KeepPush(DIK_D)) {
		playerMovement.x = playerSpeed;
	}
	worldTransform_.translation += playerMovement;
}

void Player::Draw() {

	model->Draw(worldTransform_);
}
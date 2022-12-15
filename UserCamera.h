#pragma once
#include"Vector2.h"
#include"Input.h"

class UserCamera {

private:

	UserCamera();

	void Initialize();


	void Update();

public:

	AliceMathF::Vector2 mouseMovement = { 0.0f,0.0f };
	Input* input_ = nullptr;

};
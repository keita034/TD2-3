#pragma once
#include "ErrorException.h"
#include "objModel.h"
#include "Model.h"
#include "Transform.h"
#include "Camera.h"

class Skydome
{
public:
	void Initialize(uint32_t modelHandle);

	void Update(Camera* camera);

	void Draw();

private:
	Transform transform_;

	std::unique_ptr<Model> model_;
	uint32_t modelHandle_;
};


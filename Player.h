#pragma once

#include "Object3d.h"
class Player : public Object3d {
public:
	static Player* Create(Model* model = nullptr);

public:
	bool Initialize()override;

	void Update() override;

	void OnCollision(const CollisionInfo& info)override;

private:
	//�ڒn�t���O
	bool onGround = true;
	//�����x�N�g��
	DirectX::XMVECTOR fallV;

};
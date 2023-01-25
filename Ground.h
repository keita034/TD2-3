#pragma once
#include"Model.h"
#include"Transform.h"
#include "CollisionManager.h"

class Ground {
public:

	/// <summary>
	/// ƒŠƒZƒbƒg‚µ‚½‚Ì‰Šú‰»ˆ—
	/// </summary>
	void Initialise(uint32_t modelHandl);

	void Update(Camera* camera);

	/// <summary>
	/// ÀÛ‚Ì•`‰æ
	/// </summary>
	void Draw();

	void SetCollider(BaseCollider* collider);

private:

	Transform groundPos;

	std::unique_ptr<Model> model;

	BaseCollider* collider = nullptr;
};
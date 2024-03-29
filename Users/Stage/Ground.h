//#pragma once
//#include"Model.h"
//#include"Transform.h"
//#include "CollisionManager.h"
//
//class Ground {
//public:
//
//	/// <summary>
//	/// リセットした時の初期化処理
//	/// </summary>
//	void Initialise(uint32_t modelHandl);
//
//	void Update(Camera* camera);
//
//	/// <summary>
//	/// 実際の描画
//	/// </summary>
//	void Draw();
//
//	void SetCollider(BaseCollider* collider);
//
//private:
//
//	Transform groundPos;
//
//	std::unique_ptr<Model> model;
//
//	BaseCollider* collider = nullptr;
//};
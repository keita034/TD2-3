//#include "Ground.h"
//#include "MeshCollider.h"
//#include "CollisionAttribute.h"
//
//
//void Ground::Initialise(uint32_t modelHandl)
//{
//
//	model = std::make_unique<Model>();
//	model->SetModel(modelHandl);
//	groundPos.Initialize();
//
//	groundPos.scale = AliceMathF::Vector3(4, 4, 4);
//
//
//	// コライダーの追加
//	MeshCollider* collider = new MeshCollider;
//	SetCollider(collider);
//	collider->ConstructTriangles(model);
//	collider->SetAttribute(COLLISION_ATTR_LANDSHAPE);
//
//}
//
//void Ground::Update(Camera* camera)
//{
//	// 当たり判定更新
//	if (collider) {
//		collider->Update(groundPos.matWorld);
//	}
//	groundPos.TransUpdate(camera);
//
//}
//
//void Ground::Draw()
//{
//
//	model->Draw(groundPos);
//
//}
//
//void Ground::SetCollider(BaseCollider* collider)
//{
//	this->collider = collider;
//	// コリジョンマネージャに追加
//	CollisionManager::GetInstance()->AddCollider(collider);
//
//	collider->Update(groundPos.matWorld);
//}

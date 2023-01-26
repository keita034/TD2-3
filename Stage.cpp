#include "Stage.h"
#include"FbxLoader.h"
#include"Input.h"
#include"TextureManager.h"
#include "MeshCollider.h"
#include "CollisionAttribute.h"
#include "CollisionManager.h"

void Stage::Initialize(Camera* camera)
{
	besideFold_ = std::make_unique<BesideFold>();
	besideFold_->Initialize();

	verticalFold_ = std::make_unique<VerticalFold>();
	verticalFold_->Initialize();

	surfaceFold_ = std::make_unique<SurfaceFold>();
	surfaceFold_->Initialize();

	uint32_t handl;

#pragma region 上

	{
		standardAngle_ = 90.0f;


		{
			//左上
			handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
			field[Top][RightTop].textureData = TextureManager::GetTextureData(handl);
			field[Top][RightTop].field = Field::b;

			field[Top][RightTop].surfacePartsModelTrans.Initialize();
			field[Top][RightTop].surfacePartsModelTrans.translation = { 20.0f,30.0f,20.0f };
			field[Top][RightTop].surfacePartsModelTrans.scale = { 1.0f,1.0f,1.0f };
			field[Top][RightTop].surfacePartsModelTrans.rotation = { 0.0f ,standardAngle_ * AliceMathF::Deg2Rad,0.0f };
			field[Top][RightTop].angle_ = standardAngle_;

			field[Top][RightTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map01");

			field[Top][RightTop].surfacePartsModel = std::make_unique<Model>();
			field[Top][RightTop].surfacePartsModel->SetModel(field[Top][RightTop].surfacePartsModelHandle);
			field[Top][RightTop].surfacePartsModel->SetTexture(handl);

			field[Top][RightTop].surfacePartsModelTrans.TransUpdate(camera);

			// コライダーの追加
			MeshCollider* collider = new MeshCollider;
			SetCollider(collider,0, Top, RightTop);
			collider->ConstructTriangles(field[Top][RightTop].surfacePartsModel, field[Top][RightTop].surfacePartsModelTrans.matWorld);
			collider->SetAttribute(COLLISION_ATTR_LANDSHAPE);
		}

		{

			//右上
			handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
			field[Top][RightBottom].textureData = TextureManager::GetTextureData(handl);
			field[Top][RightBottom].field = Field::d;

			field[Top][RightBottom].surfacePartsModelTrans.Initialize();
			field[Top][RightBottom].surfacePartsModelTrans.translation = { 20.0f,30.0f,-20.0f };
			field[Top][RightBottom].surfacePartsModelTrans.scale = { 1.0f,1.0f,1.0f };
			field[Top][RightBottom].surfacePartsModelTrans.rotation = { 0.0f ,standardAngle_ * AliceMathF::Deg2Rad,0.0f };
			field[Top][RightBottom].angle_ = standardAngle_;

			field[Top][RightBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map02");

			field[Top][RightBottom].surfacePartsModel = std::make_unique<Model>();
			field[Top][RightBottom].surfacePartsModel->SetModel(field[Top][RightBottom].surfacePartsModelHandle);
			field[Top][RightBottom].surfacePartsModel->SetTexture(handl);

			

			field[Top][RightBottom].surfacePartsModelTrans.TransUpdate(camera);
			// コライダーの追加
			MeshCollider* collider = new MeshCollider;
			SetCollider(collider,1,Top, RightBottom);
			collider->ConstructTriangles(field[Top][RightBottom].surfacePartsModel, field[Top][RightBottom].surfacePartsModelTrans.matWorld);
			collider->SetAttribute(COLLISION_ATTR_LANDSHAPE);

		}


		{

			//左下
			handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
			field[Top][LeftTop].textureData = TextureManager::GetTextureData(handl);
			field[Top][LeftTop].field = Field::a;

			field[Top][LeftTop].surfacePartsModelTrans.Initialize();
			field[Top][LeftTop].surfacePartsModelTrans.translation = { -20.0f,30.0f,20.0f };
			field[Top][LeftTop].surfacePartsModelTrans.scale = { 1.0f,1.0f,1.0f };
			field[Top][LeftTop].surfacePartsModelTrans.rotation = { 0.0f ,standardAngle_ * AliceMathF::Deg2Rad,0.0f };
			field[Top][LeftTop].angle_ = standardAngle_;

			field[Top][LeftTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map03");

			field[Top][LeftTop].surfacePartsModel = std::make_unique<Model>();
			field[Top][LeftTop].surfacePartsModel->SetModel(field[Top][LeftTop].surfacePartsModelHandle);
			field[Top][LeftTop].surfacePartsModel->SetTexture(handl);


			field[Top][LeftTop].surfacePartsModelTrans.TransUpdate(camera);
			// コライダーの追加
			MeshCollider* collider = new MeshCollider;
			SetCollider(collider,2, Top, LeftTop);
			collider->ConstructTriangles(field[Top][LeftTop].surfacePartsModel, field[Top][LeftTop].surfacePartsModelTrans.matWorld);
			collider->SetAttribute(COLLISION_ATTR_LANDSHAPE);
		}

		{

			//右下　
			handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
			field[Top][LeftBottom].textureData = TextureManager::GetTextureData(handl);
			field[Top][LeftBottom].field = Field::c;

			field[Top][LeftBottom].surfacePartsModelTrans.Initialize();
			field[Top][LeftBottom].surfacePartsModelTrans.translation = { -20.0f,30.0f,-20.0f };
			field[Top][LeftBottom].surfacePartsModelTrans.scale = { 1.0f,1.0f,1.0f };
			field[Top][LeftBottom].surfacePartsModelTrans.rotation = { 0.0f ,standardAngle_ * AliceMathF::Deg2Rad,0.0f };
			field[Top][LeftBottom].angle_ = standardAngle_;

			field[Top][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map04");

			field[Top][LeftBottom].surfacePartsModel = std::make_unique<Model>();
			field[Top][LeftBottom].surfacePartsModel->SetModel(field[Top][LeftBottom].surfacePartsModelHandle);
			field[Top][LeftBottom].surfacePartsModel->SetTexture(handl);


			field[Top][LeftBottom].surfacePartsModelTrans.TransUpdate(camera);
			// コライダーの追加
			MeshCollider* collider = new MeshCollider;
			SetCollider(collider, 3, Top, LeftBottom);
			collider->ConstructTriangles(field[Top][LeftBottom].surfacePartsModel, field[Top][LeftBottom].surfacePartsModelTrans.matWorld);
			collider->SetAttribute(COLLISION_ATTR_LANDSHAPE);
		}
	}

#pragma endregion

#pragma region 左
	{
		float angle = -90.0f;

		//左上
		handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
		field[Left][LeftTop].textureData = TextureManager::GetTextureData(handl);
		field[Left][LeftTop].field = Field::e;

		field[Left][LeftTop].surfacePartsModelTrans.Initialize();
		field[Left][LeftTop].surfacePartsModelTrans.translation = { -40.0f,10.0f,20.0f };
		field[Left][LeftTop].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
		field[Left][LeftTop].surfacePartsModelTrans.rotation = { angle * AliceMathF::Deg2Rad,0.0f,90.0f * AliceMathF::Deg2Rad };
		field[Left][LeftTop].angle_ = (angle);

		field[Left][LeftTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map05");

		field[Left][LeftTop].surfacePartsModel = std::make_unique<Model>();
		field[Left][LeftTop].surfacePartsModel->SetModel(field[Left][LeftTop].surfacePartsModelHandle);
		field[Left][LeftTop].surfacePartsModel->SetTexture(handl);

		//右上
		handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
		field[Left][RightTop].textureData = TextureManager::GetTextureData(handl);
		field[Left][RightTop].field = Field::f;

		field[Left][RightTop].surfacePartsModelTrans.Initialize();
		field[Left][RightTop].surfacePartsModelTrans.translation = { -40.0f,10.0f,-20.0f };
		field[Left][RightTop].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
		field[Left][RightTop].surfacePartsModelTrans.rotation = { angle * AliceMathF::Deg2Rad,0.0f,90.0f * AliceMathF::Deg2Rad };
		field[Left][RightTop].angle_ = (angle);

		field[Left][RightTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map06");

		field[Left][RightTop].surfacePartsModel = std::make_unique<Model>();
		field[Left][RightTop].surfacePartsModel->SetModel(field[Left][RightTop].surfacePartsModelHandle);
		field[Left][RightTop].surfacePartsModel->SetTexture(handl);

		//左下
		handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
		field[Left][LeftBottom].textureData = TextureManager::GetTextureData(handl);
		field[Left][LeftBottom].field = Field::g;

		field[Left][LeftBottom].surfacePartsModelTrans.Initialize();
		field[Left][LeftBottom].surfacePartsModelTrans.translation = { -40.0f,-30.0f,20.0f };
		field[Left][LeftBottom].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
		field[Left][LeftBottom].surfacePartsModelTrans.rotation = { angle * AliceMathF::Deg2Rad,0.0f,90.0f * AliceMathF::Deg2Rad };
		field[Left][LeftBottom].angle_ = (angle);

		field[Left][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map07");

		field[Left][LeftBottom].surfacePartsModel = std::make_unique<Model>();
		field[Left][LeftBottom].surfacePartsModel->SetModel(field[Left][LeftBottom].surfacePartsModelHandle);
		field[Left][LeftBottom].surfacePartsModel->SetTexture(handl);

		//右下　
		handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
		field[Left][RightBottom].textureData = TextureManager::GetTextureData(handl);
		field[Left][RightBottom].field = Field::h;

		field[Left][RightBottom].surfacePartsModelTrans.Initialize();
		field[Left][RightBottom].surfacePartsModelTrans.translation = { -40.0f,-30.0f,-20.0f };
		field[Left][RightBottom].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
		field[Left][RightBottom].surfacePartsModelTrans.rotation = { angle * AliceMathF::Deg2Rad,0.0f,90.0f * AliceMathF::Deg2Rad };
		field[Left][RightBottom].angle_ = (angle);

		field[Left][RightBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map08");

		field[Left][RightBottom].surfacePartsModel = std::make_unique<Model>();
		field[Left][RightBottom].surfacePartsModel->SetModel(field[Left][RightBottom].surfacePartsModelHandle);
		field[Left][RightBottom].surfacePartsModel->SetTexture(handl);

	}
#pragma endregion

#pragma region 真ん中左

	{
		float angle = 0.0f;

		//左上
		handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
		field[CenterLeft][LeftTop].textureData = TextureManager::GetTextureData(handl);
		field[CenterLeft][LeftTop].field = Field::i;

		field[CenterLeft][LeftTop].surfacePartsModelTrans.Initialize();
		field[CenterLeft][LeftTop].surfacePartsModelTrans.translation = { -20.0f,10.0f,-40.0f };
		field[CenterLeft][LeftTop].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
		field[CenterLeft][LeftTop].surfacePartsModelTrans.rotation =
		{
			(AliceMathF::Abs(angle) - 90.0f) * AliceMathF::Deg2Rad,
			-((int)angle / 180 * 180 + angle / 180.0f * -180.0f) * AliceMathF::Deg2Rad,
			-angle * AliceMathF::Deg2Rad
		};
		field[CenterLeft][LeftTop].angle_ = angle;

		field[CenterLeft][LeftTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map09");

		field[CenterLeft][LeftTop].surfacePartsModel = std::make_unique<Model>();
		field[CenterLeft][LeftTop].surfacePartsModel->SetModel(field[CenterLeft][LeftTop].surfacePartsModelHandle);
		field[CenterLeft][LeftTop].surfacePartsModel->SetTexture(handl);

		//右上
		handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
		field[CenterLeft][RightTop].textureData = TextureManager::GetTextureData(handl);
		field[CenterLeft][RightTop].field = Field::j;

		field[CenterLeft][RightTop].surfacePartsModelTrans.Initialize();
		field[CenterLeft][RightTop].surfacePartsModelTrans.translation = { 20.0f,10.0f,-40.0f };
		field[CenterLeft][RightTop].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
		field[CenterLeft][RightTop].surfacePartsModelTrans.rotation =
		{
			(AliceMathF::Abs(angle) - 90.0f) * AliceMathF::Deg2Rad,
			-((int)angle / 180 * 180 + angle / 180.0f * -180.0f) * AliceMathF::Deg2Rad,
			-angle * AliceMathF::Deg2Rad
		};
		field[CenterLeft][RightTop].angle_ = angle;

		field[CenterLeft][RightTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map010");

		field[CenterLeft][RightTop].surfacePartsModel = std::make_unique<Model>();
		field[CenterLeft][RightTop].surfacePartsModel->SetModel(field[CenterLeft][RightTop].surfacePartsModelHandle);
		field[CenterLeft][RightTop].surfacePartsModel->SetTexture(handl);

		//左下
		handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
		field[CenterLeft][LeftBottom].textureData = TextureManager::GetTextureData(handl);
		field[CenterLeft][LeftBottom].field = Field::k;

		field[CenterLeft][LeftBottom].surfacePartsModelTrans.Initialize();
		field[CenterLeft][LeftBottom].surfacePartsModelTrans.translation = { -20.0f,-30.0f,-40.0f };
		field[CenterLeft][LeftBottom].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
		field[CenterLeft][LeftBottom].surfacePartsModelTrans.rotation =
		{
			(AliceMathF::Abs(angle) - 90.0f) * AliceMathF::Deg2Rad,
			-((int)angle / 180 * 180 + angle / 180.0f * -180.0f) * AliceMathF::Deg2Rad,
			-angle * AliceMathF::Deg2Rad
		};
		field[CenterLeft][LeftBottom].angle_ = angle;

		field[CenterLeft][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map011");

		field[CenterLeft][LeftBottom].surfacePartsModel = std::make_unique<Model>();
		field[CenterLeft][LeftBottom].surfacePartsModel->SetModel(field[CenterLeft][LeftBottom].surfacePartsModelHandle);
		field[CenterLeft][LeftBottom].surfacePartsModel->SetTexture(handl);

		//右下　
		handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
		field[CenterLeft][RightBottom].textureData = TextureManager::GetTextureData(handl);
		field[CenterLeft][RightBottom].field = Field::l;

		field[CenterLeft][RightBottom].surfacePartsModelTrans.Initialize();
		field[CenterLeft][RightBottom].surfacePartsModelTrans.translation = { 20.0f,-30.0f,-40.0f };
		field[CenterLeft][RightBottom].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
		field[CenterLeft][RightBottom].surfacePartsModelTrans.rotation =
		{
			(AliceMathF::Abs(angle) - 90.0f) * AliceMathF::Deg2Rad,
			-((int)angle / 180 * 180 + angle / 180.0f * -180.0f) * AliceMathF::Deg2Rad,
			-angle * AliceMathF::Deg2Rad
		};
		field[CenterLeft][RightBottom].angle_ = angle;

		field[CenterLeft][RightBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map012");

		field[CenterLeft][RightBottom].surfacePartsModel = std::make_unique<Model>();
		field[CenterLeft][RightBottom].surfacePartsModel->SetModel(field[CenterLeft][RightBottom].surfacePartsModelHandle);
		field[CenterLeft][RightBottom].surfacePartsModel->SetTexture(handl);
	}

#pragma endregion

#pragma region 真ん中右

	{
		float angle = 0.0f;

		//左上
		handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
		field[CenterRight][LeftTop].textureData = TextureManager::GetTextureData(handl);
		field[CenterRight][LeftTop].field = Field::n;

		field[CenterRight][LeftTop].surfacePartsModelTrans.Initialize();
		field[CenterRight][LeftTop].surfacePartsModelTrans.translation = { 40.0f,10.0f,-20.0f };
		field[CenterRight][LeftTop].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
		field[CenterRight][LeftTop].surfacePartsModelTrans.rotation = { (angle + -90.0f) * AliceMathF::Deg2Rad,0.0f ,-90.0f * AliceMathF::Deg2Rad };
		field[CenterRight][LeftTop].angle_ = angle;

		field[CenterRight][LeftTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map013");

		field[CenterRight][LeftTop].surfacePartsModel = std::make_unique<Model>();
		field[CenterRight][LeftTop].surfacePartsModel->SetModel(field[CenterRight][LeftTop].surfacePartsModelHandle);
		field[CenterRight][LeftTop].surfacePartsModel->SetTexture(handl);

		//右上
		handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
		field[CenterRight][RightTop].textureData = TextureManager::GetTextureData(handl);
		field[CenterRight][RightTop].field = Field::m;

		field[CenterRight][RightTop].surfacePartsModelTrans.Initialize();
		field[CenterRight][RightTop].surfacePartsModelTrans.translation = { 40.0f,10.0f,20.0f };
		field[CenterRight][RightTop].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
		field[CenterRight][RightTop].surfacePartsModelTrans.rotation = { (angle + -90.0f) * AliceMathF::Deg2Rad,0.0f ,-90.0f * AliceMathF::Deg2Rad };
		field[CenterRight][RightTop].angle_ = angle;

		field[CenterRight][RightTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map014");

		field[CenterRight][RightTop].surfacePartsModel = std::make_unique<Model>();
		field[CenterRight][RightTop].surfacePartsModel->SetModel(field[CenterRight][RightTop].surfacePartsModelHandle);
		field[CenterRight][RightTop].surfacePartsModel->SetTexture(handl);

		//左下
		handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
		field[CenterRight][LeftBottom].textureData = TextureManager::GetTextureData(handl);
		field[CenterRight][LeftBottom].field = Field::o;

		field[CenterRight][LeftBottom].surfacePartsModelTrans.Initialize();
		field[CenterRight][LeftBottom].surfacePartsModelTrans.translation = { 40.0f,-30.0f,-20.0f };
		field[CenterRight][LeftBottom].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
		field[CenterRight][LeftBottom].surfacePartsModelTrans.rotation = { (angle + -90.0f) * AliceMathF::Deg2Rad,0.0f ,-90.0f * AliceMathF::Deg2Rad };
		field[CenterRight][LeftBottom].angle_ = angle;

		field[CenterRight][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map015");

		field[CenterRight][LeftBottom].surfacePartsModel = std::make_unique<Model>();
		field[CenterRight][LeftBottom].surfacePartsModel->SetModel(field[CenterRight][LeftBottom].surfacePartsModelHandle);
		field[CenterRight][LeftBottom].surfacePartsModel->SetTexture(handl);

		//右下
		handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
		field[CenterRight][RightBottom].textureData = TextureManager::GetTextureData(handl);
		field[CenterRight][RightBottom].field = Field::p;

		field[CenterRight][RightBottom].surfacePartsModelTrans.Initialize();
		field[CenterRight][RightBottom].surfacePartsModelTrans.translation = { 40.0f,-30.0f,20.0f };
		field[CenterRight][RightBottom].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
		field[CenterRight][RightBottom].surfacePartsModelTrans.rotation = { (angle + -90.0f) * AliceMathF::Deg2Rad,0.0f ,-90.0f * AliceMathF::Deg2Rad };
		field[CenterRight][RightBottom].angle_ = angle;

		field[CenterRight][RightBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map016");

		field[CenterRight][RightBottom].surfacePartsModel = std::make_unique<Model>();
		field[CenterRight][RightBottom].surfacePartsModel->SetModel(field[CenterRight][RightBottom].surfacePartsModelHandle);
		field[CenterRight][RightBottom].surfacePartsModel->SetTexture(handl);
	}

#pragma endregion

#pragma region 右
	{
		float angle = 0.0f;

		//左上
		handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
		field[Right][LeftTop].textureData = TextureManager::GetTextureData(handl);
		field[Right][LeftTop].field = Field::r;

		field[Right][LeftTop].surfacePartsModelTrans.Initialize();
		field[Right][LeftTop].surfacePartsModelTrans.translation = { 20.0f,10.0f,40.0f };
		field[Right][LeftTop].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
		field[Right][LeftTop].surfacePartsModelTrans.rotation =
		{
			(AliceMathF::Abs(angle) - 90.0f) * AliceMathF::Deg2Rad,
			(angle - 180.0f) * AliceMathF::Deg2Rad,
			((int)angle / 180 * 180 + angle / 180.0f * -180.0f) * AliceMathF::Deg2Rad
		};
		field[Right][LeftTop].angle_ = angle;

		field[Right][LeftTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map017");

		field[Right][LeftTop].surfacePartsModel = std::make_unique<Model>();
		field[Right][LeftTop].surfacePartsModel->SetModel(field[Right][LeftTop].surfacePartsModelHandle);
		field[Right][LeftTop].surfacePartsModel->SetTexture(handl);

		//右上
		handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
		field[Right][RightTop].textureData = TextureManager::GetTextureData(handl);
		field[Right][RightTop].field = Field::s;

		field[Right][RightTop].surfacePartsModelTrans.Initialize();
		field[Right][RightTop].surfacePartsModelTrans.translation = { -20.0f,10.0f,40.0f };
		field[Right][RightTop].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
		field[Right][RightTop].surfacePartsModelTrans.rotation =
		{
			(AliceMathF::Abs(angle) - 90.0f) * AliceMathF::Deg2Rad,
			(angle - 180.0f) * AliceMathF::Deg2Rad,
			((int)angle / 180 * 180 + angle / 180.0f * -180.0f) * AliceMathF::Deg2Rad
		};
		field[Right][RightTop].angle_ = angle;

		field[Right][RightTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map018");

		field[Right][RightTop].surfacePartsModel = std::make_unique<Model>();
		field[Right][RightTop].surfacePartsModel->SetModel(field[Right][RightTop].surfacePartsModelHandle);
		field[Right][RightTop].surfacePartsModel->SetTexture(handl);

		//左下
		handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
		field[Right][LeftBottom].textureData = TextureManager::GetTextureData(handl);
		field[Right][LeftBottom].field = Field::t;

		field[Right][LeftBottom].surfacePartsModelTrans.Initialize();
		field[Right][LeftBottom].surfacePartsModelTrans.translation = { 20.0f,-30.0f,40.0f };
		field[Right][LeftBottom].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
		field[Right][LeftBottom].surfacePartsModelTrans.rotation =
		{
			(AliceMathF::Abs(angle) - 90.0f) * AliceMathF::Deg2Rad,
			(angle - 180.0f) * AliceMathF::Deg2Rad,
			((int)angle / 180 * 180 + angle / 180.0f * -180.0f) * AliceMathF::Deg2Rad
		};
		field[Right][LeftBottom].angle_ = angle;

		field[Right][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map019");

		field[Right][LeftBottom].surfacePartsModel = std::make_unique<Model>();
		field[Right][LeftBottom].surfacePartsModel->SetModel(field[Right][LeftBottom].surfacePartsModelHandle);
		field[Right][LeftBottom].surfacePartsModel->SetTexture(handl);

		//右下
		handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
		field[Right][RightBottom].textureData = TextureManager::GetTextureData(handl);
		field[Right][RightBottom].field = Field::u;

		field[Right][RightBottom].surfacePartsModelTrans.Initialize();
		field[Right][RightBottom].surfacePartsModelTrans.translation = { -20.0f,-30.0f,40.0f };
		field[Right][RightBottom].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
		field[Right][RightBottom].surfacePartsModelTrans.rotation =
		{
			(AliceMathF::Abs(angle) - 90.0f) * AliceMathF::Deg2Rad,
			(angle - 180.0f) * AliceMathF::Deg2Rad,
			((int)angle / 180 * 180 + angle / 180.0f * -180.0f) * AliceMathF::Deg2Rad
		};
		field[Right][RightBottom].angle_ = angle;

		field[Right][RightBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map020");

		field[Right][RightBottom].surfacePartsModel = std::make_unique<Model>();
		field[Right][RightBottom].surfacePartsModel->SetModel(field[Right][RightBottom].surfacePartsModelHandle);
		field[Right][RightBottom].surfacePartsModel->SetTexture(handl);
	}
#pragma endregion

#pragma region 下
	{
		float angle = 180.0f;
		//左上
		handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
		field[Bottom][LeftTop].textureData = TextureManager::GetTextureData(handl);
		field[Bottom][LeftTop].field = Field::v;

		field[Bottom][LeftTop].surfacePartsModelTrans.Initialize();
		field[Bottom][LeftTop].surfacePartsModelTrans.translation = { 20.0f,-50.0f,20.0f };
		field[Bottom][LeftTop].surfacePartsModelTrans.rotation = { 180.0f * AliceMathF::Deg2Rad,angle * AliceMathF::Deg2Rad ,0.0f };
		field[Bottom][LeftTop].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
		field[Bottom][LeftTop].angle_ = angle;

		field[Bottom][LeftTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map021");

		field[Bottom][LeftTop].surfacePartsModel = std::make_unique<Model>();
		field[Bottom][LeftTop].surfacePartsModel->SetModel(field[Bottom][LeftTop].surfacePartsModelHandle);
		field[Bottom][LeftTop].surfacePartsModel->SetTexture(handl);

		//右上
		handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
		field[Bottom][RightTop].textureData = TextureManager::GetTextureData(handl);
		field[Bottom][RightTop].field = Field::w;

		field[Bottom][RightTop].surfacePartsModelTrans.Initialize();
		field[Bottom][RightTop].surfacePartsModelTrans.translation = { -20.0f,-50.0f,20.0f };
		field[Bottom][RightTop].surfacePartsModelTrans.rotation = { 180.0f * AliceMathF::Deg2Rad,angle * AliceMathF::Deg2Rad ,0.0f };
		field[Bottom][RightTop].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
		field[Bottom][RightTop].angle_ = angle;

		field[Bottom][RightTop].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map022");

		field[Bottom][RightTop].surfacePartsModel = std::make_unique<Model>();
		field[Bottom][RightTop].surfacePartsModel->SetModel(field[Bottom][RightTop].surfacePartsModelHandle);
		field[Bottom][RightTop].surfacePartsModel->SetTexture(handl);

		//左下
		handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
		field[Bottom][LeftBottom].textureData = TextureManager::GetTextureData(handl);
		field[Bottom][LeftBottom].field = Field::x;

		field[Bottom][LeftBottom].surfacePartsModelTrans.Initialize();
		field[Bottom][LeftBottom].surfacePartsModelTrans.translation = { 20.0f,-50.0f,-20.0f };
		field[Bottom][LeftBottom].surfacePartsModelTrans.rotation = { 180.0f * AliceMathF::Deg2Rad,angle * AliceMathF::Deg2Rad ,0.0f };
		field[Bottom][LeftBottom].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
		field[Bottom][LeftBottom].angle_ = angle;

		field[Bottom][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map023");

		field[Bottom][LeftBottom].surfacePartsModel = std::make_unique<Model>();
		field[Bottom][LeftBottom].surfacePartsModel->SetModel(field[Bottom][LeftBottom].surfacePartsModelHandle);
		field[Bottom][LeftBottom].surfacePartsModel->SetTexture(handl);

		//右下
		handl = TextureManager::Load("Resources/FoldPlaneImg\\Map01.png");
		field[Bottom][RightBottom].textureData = TextureManager::GetTextureData(handl);
		field[Bottom][RightBottom].field = Field::y;

		field[Bottom][RightBottom].surfacePartsModelTrans.Initialize();
		field[Bottom][RightBottom].surfacePartsModelTrans.translation = { -20.0f,-50.0f,-20.0f };
		field[Bottom][RightBottom].surfacePartsModelTrans.rotation = { 180.0f * AliceMathF::Deg2Rad,angle * AliceMathF::Deg2Rad ,0.0f };
		field[Bottom][RightBottom].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
		field[Bottom][RightBottom].angle_ = angle;

		field[Bottom][RightBottom].surfacePartsModelHandle = Model::CreateObjModel("Resources/SurfaceParts/Map024");

		field[Bottom][RightBottom].surfacePartsModel = std::make_unique<Model>();
		field[Bottom][RightBottom].surfacePartsModel->SetModel(field[Bottom][RightBottom].surfacePartsModelHandle);
		field[Bottom][RightBottom].surfacePartsModel->SetTexture(handl);
	}
#pragma endregion

}

void Stage::FieldPlaneFoldStart(FieldIndex fieldIndex, FoldIndex foldIndex)
{
	foldDirection = foldIndex;

	FieldSurfaceIndex = fieldIndex;

	switch (foldIndex)
	{
	case FoldIndex::Vertical:

		verticalFold_->Start(field, FieldSurfaceIndex);

		break;
	case FoldIndex::Beside:

		besideFold_->Start(field, FieldSurfaceIndex);

		break;
	case FoldIndex::Surface:

		surfaceFold_->Start(field, FieldSurfaceIndex, standardAngle_);
		break;

	default:
		break;
	}

	//fieldPlaneDrawFlag = true;
}

void Stage::Update(Camera* camera)
{
	//if (fieldPlaneDrawFlag)
	{
		//switch (foldDirection)
		//{
		//case FoldIndex::Vertical://縦

		//	verticalFold_->Update(camera, field, FieldSurfaceIndex, fieldPlaneDrawFlag);
		//	break;

		//case FoldIndex::Beside://横

		//	besideFold_->Update(camera, field, FieldSurfaceIndex, fieldPlaneDrawFlag);

		//	break;

		//case FoldIndex::Surface:

		surfaceFold_->Update(camera, field, FieldSurfaceIndex, fieldPlaneDrawFlag);

		///break;

	//default:
		//break;
	//}

	}

	for (size_t i = 0; i < field.size(); i++)
	{
		for (size_t j = 0; j < field[Top].size(); j++)
		{
			field[i][j].surfacePartsModelTrans.TransUpdate(camera);

		}
	}

	// 当たり判定更新
	for (int i = 0; i < 26; i++) {
		if (collider[i]) {
			collider[i]->Update(field[Top][RightTop].surfacePartsModelTrans.matWorld);
		}
	}
	


}

void Stage::Draw()
{
	if (!Input::GetInstance()->KeepPush(DIK_E))
	{
		for (size_t i = 0; i < field.size(); i++)
		{
			for (size_t j = 0; j < field[Top].size(); j++)
			{
				field[i][j].Draw();
			}
		}
	}

	if (fieldPlaneDrawFlag)
	{
		switch (foldDirection)
		{
		case FoldIndex::Vertical://縦
			verticalFold_->Draw();
			break;

		case FoldIndex::Beside://横
			besideFold_->Draw();
			break;

		case FoldIndex::Surface:

			surfaceFold_->Draw();

			break;

		default:
			break;
		}


	}
}


void Stage::SetCollider(BaseCollider* collider,int x, FieldIndex fieldIndex, FieldElementIndex fieldElementIndex)
{
	this->collider[x] = collider;
	// コリジョンマネージャに追加
	CollisionManager::GetInstance()->AddCollider(collider);

	collider->Update(field[fieldIndex][fieldElementIndex].surfacePartsModelTrans.matWorld);
}

#include "Stage.h"
#include"FbxLoader.h"
#include"Input.h"
#include"TextureManager.h"
#include "MeshCollider.h"
#include "CollisionAttribute.h"
#include "CollisionManager.h"


void Stage::Initialize(Camera* camera, std::string failPath,
	std::string map1, std::string map2, std::string map3, std::string map4,
	std::string map5, std::string map6, std::string map7, std::string map8,
	std::string map9, std::string map10, std::string map11, std::string map12,
	std::string map13, std::string map14, std::string map15, std::string map16,
	std::string map17, std::string map18, std::string map19, std::string map20,
	std::string map21, std::string map22, std::string map23, std::string map24)
{

	DefaultModelName = failPath;

	surfaceFold_ = std::make_unique<SurfaceFold>();
	surfaceFold_->Initialize();

	uint32_t handl;
	{
		int meshColliderCount = 0;
		for (size_t i = 0; i < field.size(); i++)
		{
			for (size_t j = 0; j < field[Top].size(); j++)
			{
				GoodbyeStage(meshColliderCount);
				meshColliderCount++;
			}
		}
		//CollisionManager::GetInstance()->RemoveCollider(StageBlockCollider.get());
	}


	//ステージブロック
	BlockCollider = std::make_unique<Model>();

	modelHandle = Model::CreateObjModel("Resources/SurfaceParts/stageFlame/flameAll");
	
	BlockCollider->SetModel(modelHandle);
	BlockTrans.Initialize();
	BlockTrans.translation = { 0.0f,-12.0f,0.0f };
	BlockTrans.scale = { 40.0f,40.0f,40.0f };
	BlockTrans.TransUpdate(camera);

	// コリジョンマネージャに追加
	StageBlockCollider = std::make_unique<MeshCollider>();
	CollisionManager::GetInstance()->AddCollider(StageBlockCollider.get());
	StageBlockCollider->Update(BlockTrans.matWorld);
	StageBlockCollider->ConstructTriangles(BlockCollider, BlockTrans.matWorld);
	StageBlockCollider->SetAttribute(COLLISION_ATTR_LANDSHAPE);

#pragma region 上


	{
		standardAngle_ = -90.0f;


		{
			std::string Map = DefaultModelName + map1;

			//左上
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map04.png");
			field[Top][RightTop].textureData = TextureManager::GetTextureData(handl);
			field[Top][RightTop].field = Field::b;

			field[Top][RightTop].surfacePartsModelTrans.Initialize();
			field[Top][RightTop].surfacePartsModelTrans.translation = { -40.0f,-30.0f,20.0f };
			field[Top][RightTop].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
			field[Top][RightTop].surfacePartsModelTrans.rotation = { standardAngle_ * AliceMathF::Deg2Rad,0.0f,90.0f * AliceMathF::Deg2Rad };
			field[Top][RightTop].angle_ = standardAngle_;

			field[Top][RightTop].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[Top][RightTop].surfacePartsModel = std::make_unique<Model>();
			field[Top][RightTop].surfacePartsModel->SetModel(field[Top][RightTop].surfacePartsModelHandle);


			field[Top][RightTop].surfacePartsModelTrans.TransUpdate(camera);


		}

		{
			std::string Map = DefaultModelName + map2;

			//右上
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map04.png");
			field[Top][RightBottom].textureData = TextureManager::GetTextureData(handl);
			field[Top][RightBottom].field = Field::d;

			field[Top][RightBottom].surfacePartsModelTrans.Initialize();
			field[Top][RightBottom].surfacePartsModelTrans.translation = { -40.0f,-30.0f,-20.0f };
			field[Top][RightBottom].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
			field[Top][RightBottom].surfacePartsModelTrans.rotation = { standardAngle_ * AliceMathF::Deg2Rad,0.0f,90.0f * AliceMathF::Deg2Rad };
			field[Top][RightBottom].angle_ = standardAngle_;

			field[Top][RightBottom].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[Top][RightBottom].surfacePartsModel = std::make_unique<Model>();
			field[Top][RightBottom].surfacePartsModel->SetModel(field[Top][RightBottom].surfacePartsModelHandle);




			field[Top][RightBottom].surfacePartsModelTrans.TransUpdate(camera);



		}


		{
			std::string Map = DefaultModelName + map3;

			//左下
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map04.png");
			field[Top][LeftTop].textureData = TextureManager::GetTextureData(handl);
			field[Top][LeftTop].field = Field::a;

			field[Top][LeftTop].surfacePartsModelTrans.Initialize();
			field[Top][LeftTop].surfacePartsModelTrans.translation = { -40.0f,10.0f,20.0f };
			field[Top][LeftTop].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
			field[Top][LeftTop].surfacePartsModelTrans.rotation = { standardAngle_ * AliceMathF::Deg2Rad,0.0f,90.0f * AliceMathF::Deg2Rad };
			field[Top][LeftTop].angle_ = standardAngle_;

			field[Top][LeftTop].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[Top][LeftTop].surfacePartsModel = std::make_unique<Model>();
			field[Top][LeftTop].surfacePartsModel->SetModel(field[Top][LeftTop].surfacePartsModelHandle);


			field[Top][LeftTop].surfacePartsModelTrans.TransUpdate(camera);


		}

		{
			std::string Map = DefaultModelName + map4;

			//右下　
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map04.png");
			field[Top][LeftBottom].textureData = TextureManager::GetTextureData(handl);
			field[Top][LeftBottom].field = Field::c;

			field[Top][LeftBottom].surfacePartsModelTrans.Initialize();
			field[Top][LeftBottom].surfacePartsModelTrans.translation = { -40.0f,10.0f,-20.0f };
			field[Top][LeftBottom].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
			field[Top][LeftBottom].surfacePartsModelTrans.rotation = { standardAngle_ * AliceMathF::Deg2Rad,0.0f,90.0f * AliceMathF::Deg2Rad };
			field[Top][LeftBottom].angle_ = standardAngle_;

			field[Top][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[Top][LeftBottom].surfacePartsModel = std::make_unique<Model>();
			field[Top][LeftBottom].surfacePartsModel->SetModel(field[Top][LeftBottom].surfacePartsModelHandle);



			field[Top][LeftBottom].surfacePartsModelTrans.TransUpdate(camera);


		}
	}

#pragma endregion

#pragma region 左
	{
		float angle = 90.0f;

		{

			std::string Map = DefaultModelName + map5;
			//左上
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map06.png");
			field[Left][LeftTop].textureData = TextureManager::GetTextureData(handl);
			field[Left][LeftTop].field = Field::e;

			field[Left][LeftTop].surfacePartsModelTrans.Initialize();
			field[Left][LeftTop].surfacePartsModelTrans.translation = { -20.0f,30.0f,20.0f };
			field[Left][LeftTop].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
			field[Left][LeftTop].surfacePartsModelTrans.rotation = { 0.0f ,angle * AliceMathF::Deg2Rad,0.0f };
			field[Left][LeftTop].angle_ = (angle);

			field[Left][LeftTop].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[Left][LeftTop].surfacePartsModel = std::make_unique<Model>();
			field[Left][LeftTop].surfacePartsModel->SetModel(field[Left][LeftTop].surfacePartsModelHandle);
			

			field[Left][LeftTop].surfacePartsModelTrans.TransUpdate(camera);


		}

		{

			std::string Map = DefaultModelName + map6;
			//右上
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map05.png");
			field[Left][RightTop].textureData = TextureManager::GetTextureData(handl);
			field[Left][RightTop].field = Field::f;

			field[Left][RightTop].surfacePartsModelTrans.Initialize();
			field[Left][RightTop].surfacePartsModelTrans.translation = { -20.0f,30.0f,-20.0f };
			field[Left][RightTop].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
			field[Left][RightTop].surfacePartsModelTrans.rotation = { 0.0f ,angle * AliceMathF::Deg2Rad,0.0f };
			field[Left][RightTop].angle_ = (angle);

			field[Left][RightTop].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[Left][RightTop].surfacePartsModel = std::make_unique<Model>();
			field[Left][RightTop].surfacePartsModel->SetModel(field[Left][RightTop].surfacePartsModelHandle);


			field[Left][RightTop].surfacePartsModelTrans.TransUpdate(camera);


		}

		{
			std::string Map = DefaultModelName + map7;
			//左下
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map04.png");
			field[Left][LeftBottom].textureData = TextureManager::GetTextureData(handl);
			field[Left][LeftBottom].field = Field::g;

			field[Left][LeftBottom].surfacePartsModelTrans.Initialize();
			field[Left][LeftBottom].surfacePartsModelTrans.translation = { 20.0f,30.0f,20.0f };
			field[Left][LeftBottom].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
			field[Left][LeftBottom].surfacePartsModelTrans.rotation = { 0.0f ,angle * AliceMathF::Deg2Rad,0.0f };
			field[Left][LeftBottom].angle_ = (angle);

			field[Left][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[Left][LeftBottom].surfacePartsModel = std::make_unique<Model>();
			field[Left][LeftBottom].surfacePartsModel->SetModel(field[Left][LeftBottom].surfacePartsModelHandle);


			field[Left][LeftBottom].surfacePartsModelTrans.TransUpdate(camera);


		}

		{
			std::string Map = DefaultModelName + map8;
			//右下　
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map04.png");
			field[Left][RightBottom].textureData = TextureManager::GetTextureData(handl);
			field[Left][RightBottom].field = Field::h;

			field[Left][RightBottom].surfacePartsModelTrans.Initialize();
			field[Left][RightBottom].surfacePartsModelTrans.translation = { 20.0f,30.0f,-20.0f };
			field[Left][RightBottom].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
			field[Left][RightBottom].surfacePartsModelTrans.rotation = { 0.0f ,angle * AliceMathF::Deg2Rad,0.0f };
			field[Left][RightBottom].angle_ = (angle);

			field[Left][RightBottom].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[Left][RightBottom].surfacePartsModel = std::make_unique<Model>();
			field[Left][RightBottom].surfacePartsModel->SetModel(field[Left][RightBottom].surfacePartsModelHandle);


			field[Left][RightBottom].surfacePartsModelTrans.TransUpdate(camera);


		}
	}
#pragma endregion

#pragma region 真ん中左

	{
		float angle = 0.0f;

		{
			std::string Map = DefaultModelName + map9;
			//左上
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map04.png");
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

			field[CenterLeft][LeftTop].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[CenterLeft][LeftTop].surfacePartsModel = std::make_unique<Model>();
			field[CenterLeft][LeftTop].surfacePartsModel->SetModel(field[CenterLeft][LeftTop].surfacePartsModelHandle);


			field[CenterLeft][LeftTop].surfacePartsModelTrans.TransUpdate(camera);



		}


		{
			std::string Map = DefaultModelName + map10;
			//右上
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map04.png");
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

			field[CenterLeft][RightTop].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[CenterLeft][RightTop].surfacePartsModel = std::make_unique<Model>();
			field[CenterLeft][RightTop].surfacePartsModel->SetModel(field[CenterLeft][RightTop].surfacePartsModelHandle);



			field[CenterLeft][RightTop].surfacePartsModelTrans.TransUpdate(camera);


		}

		{
			std::string Map = DefaultModelName + map11;
			//左下
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map02.png");
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

			field[CenterLeft][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[CenterLeft][LeftBottom].surfacePartsModel = std::make_unique<Model>();
			field[CenterLeft][LeftBottom].surfacePartsModel->SetModel(field[CenterLeft][LeftBottom].surfacePartsModelHandle);


			field[CenterLeft][LeftBottom].surfacePartsModelTrans.TransUpdate(camera);


		}

		{
			std::string Map = DefaultModelName + map12;
			//右下　
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map02.png");
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

			field[CenterLeft][RightBottom].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[CenterLeft][RightBottom].surfacePartsModel = std::make_unique<Model>();
			field[CenterLeft][RightBottom].surfacePartsModel->SetModel(field[CenterLeft][RightBottom].surfacePartsModelHandle);


			field[CenterLeft][RightBottom].surfacePartsModelTrans.TransUpdate(camera);


		}
	}

#pragma endregion

#pragma region 真ん中右

	{
		float angle = 0.0f;

		{
			std::string Map = DefaultModelName + map13;
			//左上
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map04.png");
			field[CenterRight][LeftTop].textureData = TextureManager::GetTextureData(handl);
			field[CenterRight][LeftTop].field = Field::n;

			field[CenterRight][LeftTop].surfacePartsModelTrans.Initialize();
			field[CenterRight][LeftTop].surfacePartsModelTrans.translation = { 40.0f,10.0f,-20.0f };
			field[CenterRight][LeftTop].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
			field[CenterRight][LeftTop].surfacePartsModelTrans.rotation = { (angle + -90.0f) * AliceMathF::Deg2Rad,0.0f ,-90.0f * AliceMathF::Deg2Rad };
			field[CenterRight][LeftTop].angle_ = angle;

			field[CenterRight][LeftTop].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[CenterRight][LeftTop].surfacePartsModel = std::make_unique<Model>();
			field[CenterRight][LeftTop].surfacePartsModel->SetModel(field[CenterRight][LeftTop].surfacePartsModelHandle);


			field[CenterRight][LeftTop].surfacePartsModelTrans.TransUpdate(camera);


		}

		{
			std::string Map = DefaultModelName + map14;
			//右上
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map05.png");
			field[CenterRight][RightTop].textureData = TextureManager::GetTextureData(handl);
			field[CenterRight][RightTop].field = Field::m;

			field[CenterRight][RightTop].surfacePartsModelTrans.Initialize();
			field[CenterRight][RightTop].surfacePartsModelTrans.translation = { 40.0f,10.0f,20.0f };
			field[CenterRight][RightTop].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
			field[CenterRight][RightTop].surfacePartsModelTrans.rotation = { (angle + -90.0f) * AliceMathF::Deg2Rad,0.0f ,-90.0f * AliceMathF::Deg2Rad };
			field[CenterRight][RightTop].angle_ = angle;

			field[CenterRight][RightTop].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[CenterRight][RightTop].surfacePartsModel = std::make_unique<Model>();
			field[CenterRight][RightTop].surfacePartsModel->SetModel(field[CenterRight][RightTop].surfacePartsModelHandle);


			field[CenterRight][RightTop].surfacePartsModelTrans.TransUpdate(camera);


		}

		{
			std::string Map = DefaultModelName + map15;
			//左下
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map02.png");
			field[CenterRight][LeftBottom].textureData = TextureManager::GetTextureData(handl);
			field[CenterRight][LeftBottom].field = Field::o;

			field[CenterRight][LeftBottom].surfacePartsModelTrans.Initialize();
			field[CenterRight][LeftBottom].surfacePartsModelTrans.translation = { 40.0f,-30.0f,-20.0f };
			field[CenterRight][LeftBottom].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
			field[CenterRight][LeftBottom].surfacePartsModelTrans.rotation = { (angle + -90.0f) * AliceMathF::Deg2Rad,0.0f ,-90.0f * AliceMathF::Deg2Rad };
			field[CenterRight][LeftBottom].angle_ = angle;

			field[CenterRight][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[CenterRight][LeftBottom].surfacePartsModel = std::make_unique<Model>();
			field[CenterRight][LeftBottom].surfacePartsModel->SetModel(field[CenterRight][LeftBottom].surfacePartsModelHandle);


			field[CenterRight][LeftBottom].surfacePartsModelTrans.TransUpdate(camera);


		}

		{
			std::string Map = DefaultModelName + map16;
			//右下
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map06.png");
			field[CenterRight][RightBottom].textureData = TextureManager::GetTextureData(handl);
			field[CenterRight][RightBottom].field = Field::p;

			field[CenterRight][RightBottom].surfacePartsModelTrans.Initialize();
			field[CenterRight][RightBottom].surfacePartsModelTrans.translation = { 40.0f,-30.0f,20.0f };
			field[CenterRight][RightBottom].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
			field[CenterRight][RightBottom].surfacePartsModelTrans.rotation = { (angle + -90.0f) * AliceMathF::Deg2Rad,0.0f ,-90.0f * AliceMathF::Deg2Rad };
			field[CenterRight][RightBottom].angle_ = angle;

			field[CenterRight][RightBottom].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[CenterRight][RightBottom].surfacePartsModel = std::make_unique<Model>();
			field[CenterRight][RightBottom].surfacePartsModel->SetModel(field[CenterRight][RightBottom].surfacePartsModelHandle);


			field[CenterRight][RightBottom].surfacePartsModelTrans.TransUpdate(camera);


		}
	}

#pragma endregion

#pragma region 右
	{
		float angle = 0.0f;

		{
			std::string Map = DefaultModelName + map17;
			//左上
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map02.png");
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

			field[Right][LeftTop].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[Right][LeftTop].surfacePartsModel = std::make_unique<Model>();
			field[Right][LeftTop].surfacePartsModel->SetModel(field[Right][LeftTop].surfacePartsModelHandle);


			field[Right][LeftTop].surfacePartsModelTrans.TransUpdate(camera);


		}

		{
			std::string Map = DefaultModelName + map18;
			//右上
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map09.png");
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

			field[Right][RightTop].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[Right][RightTop].surfacePartsModel = std::make_unique<Model>();
			field[Right][RightTop].surfacePartsModel->SetModel(field[Right][RightTop].surfacePartsModelHandle);


			field[Right][RightTop].surfacePartsModelTrans.TransUpdate(camera);


		}

		{
			std::string Map = DefaultModelName + map19;
			//左下
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map04.png");
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

			field[Right][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[Right][LeftBottom].surfacePartsModel = std::make_unique<Model>();
			field[Right][LeftBottom].surfacePartsModel->SetModel(field[Right][LeftBottom].surfacePartsModelHandle);


			field[Right][LeftBottom].surfacePartsModelTrans.TransUpdate(camera);


		}

		{
			std::string Map = DefaultModelName + map20;
			//右下
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map03.png");
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

			field[Right][RightBottom].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[Right][RightBottom].surfacePartsModel = std::make_unique<Model>();
			field[Right][RightBottom].surfacePartsModel->SetModel(field[Right][RightBottom].surfacePartsModelHandle);


			field[Right][RightBottom].surfacePartsModelTrans.TransUpdate(camera);


		}
	}
#pragma endregion

#pragma region 下
	{
		float angle = 180.0f;
		{
			std::string Map = DefaultModelName + map21;
			//左上
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map04.png");
			field[Bottom][LeftTop].textureData = TextureManager::GetTextureData(handl);
			field[Bottom][LeftTop].field = Field::v;

			field[Bottom][LeftTop].surfacePartsModelTrans.Initialize();
			field[Bottom][LeftTop].surfacePartsModelTrans.translation = { 20.0f,-50.0f,20.0f };
			field[Bottom][LeftTop].surfacePartsModelTrans.rotation = { 180.0f * AliceMathF::Deg2Rad,angle * AliceMathF::Deg2Rad ,0.0f };
			field[Bottom][LeftTop].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
			field[Bottom][LeftTop].angle_ = angle;

			field[Bottom][LeftTop].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[Bottom][LeftTop].surfacePartsModel = std::make_unique<Model>();
			field[Bottom][LeftTop].surfacePartsModel->SetModel(field[Bottom][LeftTop].surfacePartsModelHandle);


			field[Bottom][LeftTop].surfacePartsModelTrans.TransUpdate(camera);


		}

		{
			std::string Map = DefaultModelName + map22;
			//右上
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map03.png");
			field[Bottom][RightTop].textureData = TextureManager::GetTextureData(handl);
			field[Bottom][RightTop].field = Field::w;

			field[Bottom][RightTop].surfacePartsModelTrans.Initialize();
			field[Bottom][RightTop].surfacePartsModelTrans.translation = { -20.0f,-50.0f,20.0f };
			field[Bottom][RightTop].surfacePartsModelTrans.rotation = { 180.0f * AliceMathF::Deg2Rad,angle * AliceMathF::Deg2Rad ,0.0f };
			field[Bottom][RightTop].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
			field[Bottom][RightTop].angle_ = angle;

			field[Bottom][RightTop].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[Bottom][RightTop].surfacePartsModel = std::make_unique<Model>();
			field[Bottom][RightTop].surfacePartsModel->SetModel(field[Bottom][RightTop].surfacePartsModelHandle);


			field[Bottom][RightTop].surfacePartsModelTrans.TransUpdate(camera);


		}

		{
			std::string Map = DefaultModelName + map23;
			//左下
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map04.png");
			field[Bottom][LeftBottom].textureData = TextureManager::GetTextureData(handl);
			field[Bottom][LeftBottom].field = Field::x;

			field[Bottom][LeftBottom].surfacePartsModelTrans.Initialize();
			field[Bottom][LeftBottom].surfacePartsModelTrans.translation = { 20.0f,-50.0f,-20.0f };
			field[Bottom][LeftBottom].surfacePartsModelTrans.rotation = { 180.0f * AliceMathF::Deg2Rad,angle * AliceMathF::Deg2Rad ,0.0f };
			field[Bottom][LeftBottom].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
			field[Bottom][LeftBottom].angle_ = angle;

			field[Bottom][LeftBottom].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[Bottom][LeftBottom].surfacePartsModel = std::make_unique<Model>();
			field[Bottom][LeftBottom].surfacePartsModel->SetModel(field[Bottom][LeftBottom].surfacePartsModelHandle);


			field[Bottom][LeftBottom].surfacePartsModelTrans.TransUpdate(camera);


		}

		{
			std::string Map = DefaultModelName + map24;
			//右下
			handl = TextureManager::Load("Resources/FoldPlaneImg/MateMap\\Map10.png");
			field[Bottom][RightBottom].textureData = TextureManager::GetTextureData(handl);
			field[Bottom][RightBottom].field = Field::y;

			field[Bottom][RightBottom].surfacePartsModelTrans.Initialize();
			field[Bottom][RightBottom].surfacePartsModelTrans.translation = { -20.0f,-50.0f,-20.0f };
			field[Bottom][RightBottom].surfacePartsModelTrans.rotation = { 180.0f * AliceMathF::Deg2Rad,angle * AliceMathF::Deg2Rad ,0.0f };
			field[Bottom][RightBottom].surfacePartsModelTrans.scale = { 40.0f,40.0f,40.0f };
			field[Bottom][RightBottom].angle_ = angle;

			field[Bottom][RightBottom].surfacePartsModelHandle = Model::CreateObjModel(Map);

			field[Bottom][RightBottom].surfacePartsModel = std::make_unique<Model>();
			field[Bottom][RightBottom].surfacePartsModel->SetModel(field[Bottom][RightBottom].surfacePartsModelHandle);


			field[Bottom][RightBottom].surfacePartsModelTrans.TransUpdate(camera);


		}
	}

	int meshColliderCount = 0;

	for (size_t i = 0; i < field.size(); i++)
	{
		for (size_t j = 0; j < field[Top].size(); j++)
		{
			field[i][j].surfacePartsModelTrans.TransUpdate(camera);
			SetCollider(static_cast<FieldIndex>(i), static_cast<FieldElementIndex>(j), meshColliderCount);
			meshColliderCount++;
		}
	}

#pragma endregion

}

void Stage::FieldPlaneFoldStart(FieldIndex fieldIndex, FoldIndex foldIndex)
{
	foldDirection = foldIndex;

	FieldSurfaceIndex = fieldIndex;

	switch (foldIndex)
	{
	case FoldIndex::Surface:

		surfaceFold_->Start(field, FieldSurfaceIndex, standardAngle_);
		break;

	default:
		break;
	}

}

void Stage::Update(Camera* camera)
{
	surfaceFold_->Update(camera, field, FieldSurfaceIndex, fieldPlaneDrawFlag);

	BlockTrans.TransUpdate(camera);

	for (size_t i = 0; i < field.size(); i++)
	{
		for (size_t j = 0; j < field[Top].size(); j++)
		{
			field[i][j].surfacePartsModelTrans.TransUpdate(camera);

		}
	}

	int meshColliderCount = 0;

	for (size_t i = 0; i < field.size(); i++)
	{
		for (size_t j = 0; j < field[Top].size(); j++)
		{
			field[i][j].surfacePartsModelTrans.TransUpdate(camera);
			ChangeCollider(static_cast<FieldIndex>(i), static_cast<FieldElementIndex>(j), meshColliderCount);
			meshColliderCount++;
		}
	}


	// 当たり判定更新
	/*for (int i = 0; i < 23; i++) {
		if (collider[i]) {
			collider[i]->Update(field[Top][RightTop].surfacePartsModelTrans.matWorld);
		}
	}
	
	*/


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
	BlockCollider->Draw(BlockTrans);
	if (fieldPlaneDrawFlag)
	{
		switch (foldDirection)
		{
		case FoldIndex::Surface:

			surfaceFold_->Draw();

			break;

		default:
			break;
		}


	}
}


void Stage::SetCollider(FieldIndex fieldIndex, FieldElementIndex fieldElementIndex, int meshNumber)
{
	// コリジョンマネージャに追加
	meshCollider[meshNumber] = std::make_unique<MeshCollider>();
	CollisionManager::GetInstance()->AddCollider(meshCollider[meshNumber].get());
	meshCollider[meshNumber]->Update(field[fieldIndex][fieldElementIndex].surfacePartsModelTrans.matWorld);
	meshCollider[meshNumber]->ConstructTriangles(field[fieldIndex][fieldElementIndex].surfacePartsModel, field[fieldIndex][fieldElementIndex].surfacePartsModelTrans.matWorld);
	meshCollider[meshNumber]->SetAttribute(COLLISION_ATTR_LANDSHAPE);
}



void Stage::ChangeCollider(FieldIndex fieldIndex, FieldElementIndex fieldElementIndex, int meshNumber)
{
	// コリジョンマネージャに追加
	meshCollider[meshNumber]->ConstructTriangles(field[fieldIndex][fieldElementIndex].surfacePartsModel, field[fieldIndex][fieldElementIndex].surfacePartsModelTrans.matWorld);
	meshCollider[meshNumber]->SetAttribute(COLLISION_ATTR_LANDSHAPE);
}

void Stage::GoodbyeStage(int meshNumber)
{
	CollisionManager::GetInstance()->RemoveCollider(meshCollider[meshNumber].get());
}

void Stage::SetStageObjScale(const AliceMathF::Vector3& scale)
{
	field[Top][RightTop].surfacePartsModelTrans.scale = scale;
	field[Top][RightBottom].surfacePartsModelTrans.scale = scale;
	field[Top][LeftTop].surfacePartsModelTrans.scale = scale;
	field[Top][LeftBottom].surfacePartsModelTrans.scale = scale;

	field[Left][LeftTop].surfacePartsModelTrans.scale = scale;
	field[Left][RightTop].surfacePartsModelTrans.scale = scale;
	field[Left][LeftBottom].surfacePartsModelTrans.scale = scale;
	field[Left][RightBottom].surfacePartsModelTrans.scale = scale;

	field[CenterLeft][LeftTop].surfacePartsModelTrans.scale = scale;
	field[CenterLeft][RightTop].surfacePartsModelTrans.scale = scale;
	field[CenterLeft][LeftBottom].surfacePartsModelTrans.scale = scale;
	field[CenterLeft][RightBottom].surfacePartsModelTrans.scale = scale;

	field[CenterRight][LeftTop].surfacePartsModelTrans.scale = scale;
	field[CenterRight][RightTop].surfacePartsModelTrans.scale = scale;
	field[CenterRight][LeftBottom].surfacePartsModelTrans.scale = scale;
	field[CenterRight][RightBottom].surfacePartsModelTrans.scale = scale;

	field[Right][LeftTop].surfacePartsModelTrans.scale = scale;
	field[Right][RightTop].surfacePartsModelTrans.scale = scale;
	field[Right][LeftBottom].surfacePartsModelTrans.scale = scale;
	field[Right][RightBottom].surfacePartsModelTrans.scale = scale;

	field[Bottom][LeftTop].surfacePartsModelTrans.scale = scale;
	field[Bottom][RightTop].surfacePartsModelTrans.scale = scale;
	field[Bottom][LeftBottom].surfacePartsModelTrans.scale = scale;
	field[Bottom][RightBottom].surfacePartsModelTrans.scale = scale;
}

void Stage::SetStageFrameScale(const AliceMathF::Vector3& scale)
{
	BlockTrans.scale = scale;
}

void Stage::SetStageFrameTrans(const AliceMathF::Vector3& trans)
{
	BlockTrans.translation = trans;

}

void Stage::SetStageTopTrans(const AliceMathF::Vector3& trans)
{
	field[Top][RightTop].surfacePartsModelTrans.translation = { -trans.x,-trans.y,trans.z };
	field[Top][RightBottom].surfacePartsModelTrans.translation = { -trans.x,-trans.y,-trans.z };
	field[Top][LeftTop].surfacePartsModelTrans.translation = { -trans.x,trans.y,trans.z };
	field[Top][LeftBottom].surfacePartsModelTrans.translation = { -trans.x,trans.y,-trans.z };
}

void Stage::SetStageLeftTrans(const AliceMathF::Vector3& trans)
{
	field[Left][RightTop].surfacePartsModelTrans.translation = { -trans.x,trans.y,trans.z };
	field[Left][RightBottom].surfacePartsModelTrans.translation = { -trans.x,trans.y,-trans.z };
	field[Left][LeftTop].surfacePartsModelTrans.translation = { trans.x,trans.y,trans.z };
	field[Left][LeftBottom].surfacePartsModelTrans.translation = { trans.x,trans.y,-trans.z };
}

void Stage::SetStageCenterLeftTrans(const AliceMathF::Vector3& trans)
{
	field[CenterLeft][RightTop].surfacePartsModelTrans.translation = { -trans.x,trans.y,-trans.z };
	field[CenterLeft][RightBottom].surfacePartsModelTrans.translation = { trans.x,trans.y,-trans.z };
	field[CenterLeft][LeftTop].surfacePartsModelTrans.translation = { -trans.x,-trans.y,-trans.z };
	field[CenterLeft][LeftBottom].surfacePartsModelTrans.translation = { trans.x,-trans.y,-trans.z };
}

void Stage::SetStageCenterRightTrans(const AliceMathF::Vector3& trans)
{
	field[CenterRight][RightTop].surfacePartsModelTrans.translation = { trans.x,trans.y,-trans.z };
	field[CenterRight][RightBottom].surfacePartsModelTrans.translation = { trans.x,trans.y,trans.z };
	field[CenterRight][LeftTop].surfacePartsModelTrans.translation = { trans.x,-trans.y,-trans.z };
	field[CenterRight][LeftBottom].surfacePartsModelTrans.translation = { trans.x,-trans.y,trans.z };
}

void Stage::SetStageRightTrans(const AliceMathF::Vector3& trans)
{
	field[Right][RightTop].surfacePartsModelTrans.translation = { trans.x,trans.y,trans.z };
	field[Right][RightBottom].surfacePartsModelTrans.translation = { -trans.x,trans.y,trans.z };
	field[Right][LeftTop].surfacePartsModelTrans.translation = { trans.x,-trans.y,trans.z };
	field[Right][LeftBottom].surfacePartsModelTrans.translation = { -trans.x,-trans.y,trans.z };
}

void Stage::SetStageBottomTrans(const AliceMathF::Vector3& trans)
{
	field[Bottom][RightTop].surfacePartsModelTrans.translation = { trans.x,-trans.y,trans.z };
	field[Bottom][RightBottom].surfacePartsModelTrans.translation = { -trans.x,-trans.y,trans.z };
	field[Bottom][LeftTop].surfacePartsModelTrans.translation = { trans.x,-trans.y,-trans.z };
	field[Bottom][LeftBottom].surfacePartsModelTrans.translation = { -trans.x,-trans.y,-trans.z };
}

Transform Stage::GetStageTransform(FieldIndex fieldIndex, FieldElementIndex fieldElementIndex)
{
	return field[fieldIndex][fieldElementIndex].surfacePartsModelTrans;
}

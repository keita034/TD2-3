#include "Sprite3D.h"


Sprite3D::Sprite3D()
{
}

Sprite3D::~Sprite3D()
{
}

void Sprite3D::Initialize(const uint32_t handle)
{
	texture = TextureManager::GetTextureData(handle);

	SpriteInitialize();

	CreatVertexIndexBuffer();

	trimmingRange.z = static_cast<float>(texture->width);
	trimmingRange.w = static_cast<float>(texture->height);
}

void Sprite3D::Draw(Transform& transform, Camera* camera, BlendMode blend, BillboardFlag flag, Material* material)
{
	AliceMathF::Matrix4 mTrans, mRot, mScale;

	//???s????s??
	mTrans.MakeTranslation(transform.translation);
	//??]?s??
	mRot.MakeRotation(transform.rotation);
	//?X?P?[???s??
	mScale.MakeScaling(transform.scale);

	switch (flag)
	{
	case NonBillboard:
		transform.matWorld = mScale * mRot * mTrans * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
		break;
	case AllBillboard:
	{
		AliceMathF::Matrix4 mat = camera->GetViewMatrix();

		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;

		transform.matWorld = mScale * mRot * mat * mTrans * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
		break;
	}
	case XBillboard:
	{
		AliceMathF::Matrix4 mat = camera->GetViewMatrix();

		mat.m[1][0] = 0;
		mat.m[1][1] = 1;
		mat.m[1][2] = 0;
		mat.m[1][3] = 0;

		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;

		transform.matWorld = mScale * mRot * mat * mTrans * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
		break;
	}
	case YBillboard:
	{
		AliceMathF::Matrix4 mat = camera->GetViewMatrix();

		mat.m[0][0] = 1;
		mat.m[0][1] = 0;
		mat.m[0][2] = 0;
		mat.m[0][3] = 0;

		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;


		transform.matWorld = mScale * mRot * mat * mTrans * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
		break;
	}
	case XYBillboard:
	{
		AliceMathF::Matrix4 mat = camera->GetViewMatrix();

		mat.m[2][0] = 0;
		mat.m[2][1] = 0;
		mat.m[2][2] = 1;
		mat.m[2][3] = 0;

		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;

		transform.matWorld = mScale * mRot * mat * mTrans * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
		break;
	}
	default:
		assert(0);
		break;
	}

	switch (blend)
	{
	case BlendMode::AX_BLENDMODE_NOBLEND:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[0].get();
		break;
	case BlendMode::AX_BLENDMODE_ALPHA:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[1].get();
		break;
	case BlendMode::AX_BLENDMODE_ADD:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[2].get();
		break;
	case BlendMode::AX_BLENDMODE_SUB:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[3].get();
		break;
	case BlendMode::AX_BLENDMODE_MULA:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[4].get();
		break;
	case BlendMode::AX_BLENDMODE_INVSRC:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[5].get();
		break;
	case BlendMode::AX_BLENDMODE_MAX:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[0].get();
		printf("?u?????h???????????????");
		break;
	case BlendMode::AX_BLENDMODE_CUSTOM:
		if (material)
		{
			spriteMaterial = material;
		}
		else
		{
			printf("?}?e???A????null???");
			spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[0].get();
		}
		break;
	default:
		printf("?u?????h????O??????????");
		assert(0);
		break;

	}

	transform.Update();

	SpriteDraw(transform, spriteMaterial);
}

void Sprite3D::Draw(Transform& transform, BlendMode blend, Material* material)
{

	float isFlipX, isFlipY;
	isFlipX = flipX ? -1.0f : 1.0f;
	isFlipY = flipY ? -1.0f : 1.0f;

	float left = ((0.0f - anchorPoint.x) * (static_cast<float>(texture->width) * 0.0625f)) * isFlipX;
	float right = ((1.0f - anchorPoint.x) * (static_cast<float>(texture->width) * 0.0625f)) * isFlipX;
	float top = ((0.0f - anchorPoint.y) * (static_cast<float>(texture->height) * 0.0625f)) * isFlipY;
	float bottom = ((1.0f - anchorPoint.y) * (static_cast<float>(texture->height) * 0.0625f)) * isFlipY;

	float texLeft = trimmingRange.x / static_cast<float>(texture->width);
	float texTop = trimmingRange.y / static_cast<float>(texture->height);
	float texRight = trimmingRange.z / static_cast<float>(texture->width);
	float texBottom = trimmingRange.w / static_cast<float>(texture->height);

	// ???_?f?[?^
	PosUvColor vertices[] =
	{//		x		y		z		u	v
		{{left,top,0.0f},{texLeft,texTop},{texture->color.x,texture->color.y,texture->color.z,texture->color.w}},//????C???f?b?N?X0
		{{left,bottom,0.0f},{texLeft,texBottom},{texture->color.x,texture->color.y,texture->color.z,texture->color.w}},//?????C???f?b?N?X1
		{{right,top,0.0f},{texRight,texTop},{texture->color.x,texture->color.y,texture->color.z,texture->color.w}},//?E??C???f?b?N?X2
		{{right,bottom,0.0f},{texRight,texBottom},{texture->color.x,texture->color.y,texture->color.z,texture->color.w}},//?E???C???f?b?N?X3
	};

	// ?C???f?b?N?X?f?[?^
	uint32_t indices[] =
	{
		1, 0, 3, // ?O?p?`1???
		2, 3, 0, // ?O?p?`2???
	};

	//???_?o?b?t?@???f?[?^?]??
	vertexBuffer->Update(vertices);

	//?C???f?b?N?X?o?b?t?@???f?[?^?]??
	indexBuffer->Update(indices);

	switch (blend)
	{
	case BlendMode::AX_BLENDMODE_NOBLEND:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[0].get();
		break;
	case BlendMode::AX_BLENDMODE_ALPHA:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[1].get();
		break;
	case BlendMode::AX_BLENDMODE_ADD:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[2].get();
		break;
	case BlendMode::AX_BLENDMODE_SUB:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[3].get();
		break;
	case BlendMode::AX_BLENDMODE_MULA:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[4].get();
		break;
	case BlendMode::AX_BLENDMODE_INVSRC:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[5].get();
		break;
	case BlendMode::AX_BLENDMODE_MAX:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[0].get();
		printf("?u?????h???????????????");
		break;
	case BlendMode::AX_BLENDMODE_CUSTOM:
		if (material)
		{
			spriteMaterial = material;
		}
		else
		{
			printf("?}?e???A????null???");
			spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[0].get();
		}
		break;
	default:
		printf("?u?????h????O??????????");
		assert(0);
		break;

	}

	SpriteDraw(transform, spriteMaterial);
}

void Sprite3D::AnimationDraw(Transform& transform, uint16_t radiusX, uint16_t radiusY, float& frame, float frameDiv, BlendMode blend, Material* material)
{
	size_t animeFrame = static_cast<size_t>(frame / frameDiv);

	size_t width = static_cast<size_t>(radiusX) * 2;
	size_t height = static_cast<size_t>(radiusY) * 2;
	float texTop = trimmingRange.y / static_cast<float>(texture->height);
	float texRight = trimmingRange.z / static_cast<float>(texture->width);

	float widthU = static_cast<float>(width) / (texRight * static_cast<float>(texture->width));

	//?????????T?C?Y

	if (texture->width / width < animeFrame + 1)
	{
		frame = 0;
	}

	float isFlipX, isFlipY;
	isFlipX = flipX ? -1.0f : 1.0f;
	isFlipY = flipY ? -1.0f : 1.0f;

	float left = ((0.0f - anchorPoint.x) * (static_cast<float>(width / 10))) * isFlipX;
	float right = ((1.0f - anchorPoint.x) * (static_cast<float>(width / 10))) * isFlipX;
	float top = ((0.0f - anchorPoint.y) * static_cast<float>(height / 10)) * isFlipY;
	float bottom = ((1.0f - anchorPoint.y) * static_cast<float>(height / 10)) * isFlipY;

	// ???_?f?[?^
	PosUvColor vertices[] =
	{//		x		y		z		u	v
		{{left, top, 0.0f},{widthU * static_cast<float>(animeFrame),texTop},{texture->color.x,texture->color.y,texture->color.z,texture->color.w}},//????C???f?b?N?X0
		{{left, bottom, 0.0f},{widthU * static_cast<float>(animeFrame),texRight},{texture->color.x,texture->color.y,texture->color.z,texture->color.w}},//?????C???f?b?N?X1
		{{right, top, 0.0f},{widthU * static_cast<float>((animeFrame + 1)),texTop},{texture->color.x,texture->color.y,texture->color.z,texture->color.w}},//?E??C???f?b?N?X2
		{{right, bottom, 0.0f},{widthU * static_cast<float>((animeFrame + 1)),texRight},{texture->color.x,texture->color.y,texture->color.z,texture->color.w}},//?E???C???f?b?N?X3
	};

	// ?C???f?b?N?X?f?[?^
	uint32_t indices[] =
	{
		1, 0, 3, // ?O?p?`1???
		2, 3, 0, // ?O?p?`2???
	};

	//???_?o?b?t?@???f?[?^?]??
	vertexBuffer->Update(vertices);

	//?C???f?b?N?X?o?b?t?@???f?[?^?]??
	indexBuffer->Update(indices);

	switch (blend)
	{
	case BlendMode::AX_BLENDMODE_NOBLEND:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE3D_MATERIAL[0].get();
		break;
	case BlendMode::AX_BLENDMODE_ALPHA:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE3D_MATERIAL[1].get();
		break;
	case BlendMode::AX_BLENDMODE_ADD:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE3D_MATERIAL[2].get();
		break;
	case BlendMode::AX_BLENDMODE_SUB:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE3D_MATERIAL[3].get();
		break;
	case BlendMode::AX_BLENDMODE_MULA:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE3D_MATERIAL[4].get();
		break;
	case BlendMode::AX_BLENDMODE_INVSRC:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE3D_MATERIAL[5].get();
		break;
	case BlendMode::AX_BLENDMODE_MAX:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE3D_MATERIAL[0].get();
		printf("?u?????h???????????????");
		break;
	case BlendMode::AX_BLENDMODE_CUSTOM:
		if (material)
		{
			spriteMaterial = material;
		}
		else
		{
			printf("?}?e???A????null???");
			spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[0].get();
		}
		break;
	default:
		printf("?u?????h????O??????????");
		assert(0);
		break;
	}

	transform.Update();


	SpriteDraw(transform, spriteMaterial);
}

void Sprite3D::AnimationDraw(Transform& transform, uint16_t radiusX, uint16_t radiusY, float& frame, float frameDiv, Camera* camera, BlendMode blend, BillboardFlag flag, Material* material)
{
	AliceMathF::Matrix4 mTrans, mRot, mScale;

	//???s????s??
	mTrans.MakeTranslation(transform.translation);
	//??]?s??
	mRot.MakeRotation(transform.rotation);
	//?X?P?[???s??
	mScale.MakeScaling(transform.scale);

	switch (flag)
	{
	case NonBillboard:
		transform.matWorld = mScale * mRot * mTrans * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
		break;
	case AllBillboard:
	{
		AliceMathF::Matrix4 mat = camera->GetViewMatrix();

		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;

		transform.matWorld = mScale * mRot * mat * mTrans * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
		break;
	}
	case XBillboard:
	{
		AliceMathF::Matrix4 mat = camera->GetViewMatrix();

		mat.m[1][0] = 0;
		mat.m[1][1] = 1;
		mat.m[1][2] = 0;
		mat.m[1][3] = 0;

		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;

		transform.matWorld = mScale * mRot * mat * mTrans * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
		break;
	}
	case YBillboard:
	{
		AliceMathF::Matrix4 mat = camera->GetViewMatrix();

		mat.m[0][0] = 1;
		mat.m[0][1] = 0;
		mat.m[0][2] = 0;
		mat.m[0][3] = 0;

		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;


		transform.matWorld = mScale * mRot * mat * mTrans * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
		break;
	}
	case XYBillboard:
	{
		AliceMathF::Matrix4 mat = camera->GetViewMatrix();

		mat.m[2][0] = 0;
		mat.m[2][1] = 0;
		mat.m[2][2] = 1;
		mat.m[2][3] = 0;

		mat.m[3][0] = 0;
		mat.m[3][1] = 0;
		mat.m[3][2] = 0;
		mat.m[3][3] = 1;

		transform.matWorld = mScale * mRot * mat * mTrans * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
		break;
	}
	default:
		assert(0);
		break;
	}

	transform.Update();

	AnimationDraw(transform, radiusX, radiusY, frame, frameDiv, blend, material);
}

#include "Sprite2D.h"
#include"WindowsApp.h"

Sprite2D::Sprite2D()
{
}

Sprite2D::~Sprite2D()
{
}

void Sprite2D::Initialize(uint32_t handle)
{
	SpriteInitialize();

	float width = static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().width);
	float height = static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().height);

	AliceMathF::MakeOrthogonalL(0.0f, width, height, 0.0f, 0.0f, 1.0f, matProjection);

	texture = TextureManager::GetTextureData(handle);

	trimmingRange.z = static_cast<float>(texture->width);
	trimmingRange.w = static_cast<float>(texture->height);

	spriteSize.x = static_cast<float>(texture->width);
	spriteSize.y = static_cast<float>(texture->height);

	CreatVertexIndexBuffer();
}

//�`��
void Sprite2D::Draw(Transform& transform, BlendMode blend, Material* material)
{
	float isFlipX, isFlipY;
	isFlipX = flipX ? -1.0f : 1.0f;
	isFlipY = flipY ? -1.0f : 1.0f;

	float left = ((0.0f - anchorPoint.x) * static_cast<float>(spriteSize.x)) * isFlipX;
	float right = ((1.0f - anchorPoint.x) * static_cast<float>(spriteSize.x)) * isFlipX;
	float top = ((0.0f - anchorPoint.y) * static_cast<float>(spriteSize.y)) * isFlipY;
	float bottom = ((1.0f - anchorPoint.y) * static_cast<float>(spriteSize.y)) * isFlipY;

	float texLeft = trimmingRange.x / static_cast<float>(texture->width);
	float texTop = trimmingRange.y / static_cast<float>(texture->height);
	float texRight = trimmingRange.z / static_cast<float>(texture->width);
	float texBottom = trimmingRange.w / static_cast<float>(texture->height);

	// ���_�f�[�^
	PosUvColor vertices[] =
	{//		x		y		z		u	v
		{{left,top,0.0f},{texLeft,texTop},{texture->color.x,texture->color.y,texture->color.z,texture->color.w}},//����C���f�b�N�X0
		{{left,bottom,0.0f},{texLeft,texBottom},{texture->color.x,texture->color.y,texture->color.z,texture->color.w}},//�����C���f�b�N�X1
		{{right,top,0.0f},{texRight,texTop},{texture->color.x,texture->color.y,texture->color.z,texture->color.w}},//�E��C���f�b�N�X2
		{{right,bottom,0.0f},{texRight,texBottom},{texture->color.x,texture->color.y,texture->color.z,texture->color.w}},//�E���C���f�b�N�X3
	};

	// �C���f�b�N�X�f�[�^
	uint32_t indices[] =
	{
		1, 0, 3, // �O�p�`1��
		2, 3, 0, // �O�p�`2��
	};

	//���_�o�b�t�@�ւ̃f�[�^�]��
	vertexBuffer->Update(vertices);

	//�C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	indexBuffer->Update(indices);

	AliceMathF::Matrix4 mTrans, mRot, mScale, matWorld;
	//���s�ړ��s��
	mTrans.MakeTranslation(transform.translation);
	//��]�s��
	mRot.MakeRotation(transform.rotation);
	//�X�P�[���s��
	mScale.MakeScaling(transform.scale);
	//���[���h�s��
	matWorld = mScale * mRot * mTrans;

	transform.matWorld = matWorld * matProjection;

	transform.GetWorldViewpojCamera()->matWorld = transform.matWorld;

	transform.Update();

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
		printf("�u�����h�̎�ސ������Ă��܂�");
		break;
	case BlendMode::AX_BLENDMODE_CUSTOM:
		if (material)
		{
			spriteMaterial = material;
		}
		else
		{
			printf("�}�e���A����null�ł�");
			spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[0].get();
		}
		break;
	default:
		printf("�u�����h�͈̔͊O�����Ă��܂�");
		assert(0);
		break;
	}

	SpriteDraw(transform, spriteMaterial);
}

void Sprite2D::AnimationDraw(Transform& transform, uint16_t radiusX, uint16_t radiusY, float& frame, float frameDiv, BlendMode blend, Material* material)
{
	size_t animeFrame = static_cast<size_t>(frame / frameDiv);

	size_t width = static_cast<size_t>(radiusX) * 2;
	size_t height = static_cast<size_t>(radiusY) * 2;

	float texTop = trimmingRange.y / static_cast<float>(texture->height);
	float texRight = trimmingRange.z / static_cast<float>(texture->width);

	float widthU = static_cast<float>(width) / (texRight * static_cast<float>(texture->width));

	//�摜�̔����̃T�C�Y

	if (texture->width / width < animeFrame + 1)
	{
		frame = 0;
	}

	float isFlipX, isFlipY;
	isFlipX = flipX ? -1.0f : 1.0f;
	isFlipY = flipY ? -1.0f : 1.0f;

	float left = ((0.0f - anchorPoint.x) * static_cast<float>(width)) * isFlipX;
	float right = ((1.0f - anchorPoint.x) * static_cast<float>(width)) * isFlipX;
	float top = ((0.0f - anchorPoint.y) * static_cast<float>(height)) * isFlipY;
	float bottom = ((1.0f - anchorPoint.y) * static_cast<float>(height)) * isFlipY;

	// ���_�f�[�^
	PosUvColor vertices[] =
	{//		x		y		z		u	v
		{{left, top, 0.0f},{widthU * static_cast<float>(animeFrame),texTop},{texture->color.x,texture->color.y,texture->color.z,texture->color.w}},//����C���f�b�N�X0
		{{left, bottom, 0.0f},{widthU * static_cast<float>(animeFrame),texRight},{texture->color.x,texture->color.y,texture->color.z,texture->color.w}},//�����C���f�b�N�X1
		{{right, top, 0.0f},{widthU * static_cast<float>((animeFrame + 1)),texTop},{texture->color.x,texture->color.y,texture->color.z,texture->color.w}},//�E��C���f�b�N�X2
		{{right, bottom, 0.0f},{widthU * static_cast<float>((animeFrame + 1)),texRight},{texture->color.x,texture->color.y,texture->color.z,texture->color.w}},//�E���C���f�b�N�X3
	};

	// �C���f�b�N�X�f�[�^
	uint32_t indices[] =
	{
		1, 0, 3, // �O�p�`1��
		2, 3, 0, // �O�p�`2��
	};

	//���_�o�b�t�@�ւ̃f�[�^�]��
	vertexBuffer->Update(vertices);

	//�C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	indexBuffer->Update(indices);

	AliceMathF::Matrix4 mTrans, mRot, mScale, matWorld;
	//���s�ړ��s��
	mTrans.MakeTranslation(transform.translation);
	//��]�s��
	mRot.MakeRotation(transform.rotation);
	//�X�P�[���s��
	mScale.MakeScaling(transform.scale);
	//���[���h�s��
	matWorld = mScale * mRot * mTrans;

	transform.matWorld = matWorld * matProjection;

	transform.GetWorldViewpojCamera()->matWorld = transform.matWorld;
	transform.Update();

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
		printf("�u�����h�̎�ސ������Ă��܂�");
		break;
	case BlendMode::AX_BLENDMODE_CUSTOM:
		if (material)
		{
			spriteMaterial = material;
		}
		else
		{
			printf("�}�e���A����null�ł�");
			spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[0].get();
		}
		break;
	default:
		printf("�u�����h�͈̔͊O�����Ă��܂�");
		assert(0);
		break;
	}

	SpriteDraw(transform, spriteMaterial);
}

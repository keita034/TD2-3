#include "SurfaceFold.h"

void SurfaceFold::Initialize()
{
	//�ʐ܂胂�f��
	surfaceFoldFbxmodel_ = std::make_unique<fbxModel>();
	surfaceFoldFbxmodel_->Initialize();
	surfaceFoldFbxmodel_->Create("Resources/SurfaceFold", false, false, true, false);
	surfaceFoldFbxmodelAnime_ = std::make_unique<fbxAnimation>();
	FbxLoader::GetInstance()->LoadAnimation(surfaceFoldFbxmodelAnime_.get(), "Resources/SurfaceFold", "");


	fieldPlaneTrans_.Initialize();
	fieldPlaneTrans_.scale = { 0.4f,0.4f ,0.4f };
	fieldPlaneTrans_.translation = { 0,-10,0 };
}

void SurfaceFold::Start(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	surfaceFoldFbxmodel_->InitializeVertex();

	switch (fieldIndex)
	{
	case TopToLeft:
	case TopToCenterLeft:
	case TopToCenterRight:
	case TopToRight:

		StartTopTo(field, fieldIndex);

		break;

	case LeftToTop:
	case LeftToCenterLeft:
	case LeftToRight:
	case LeftToBottom:

		StartLeftTo(field, fieldIndex);

		break;

	case CenterLeftToTop:
	case CenterLeftToLeft:
	case CenterLeftToCenterRight:
	case CenterLeftToBottom:

		StartCenterLeftTo(field, fieldIndex);

		break;

	case CenterRightToTop:
	case CenterRightToCenterLeft:
	case CenterRightToRight:
	case CenterRightToBottom:

		StartCenterRightTo(field, fieldIndex);

		break;

	case RightToTop:
	case RightToLeft:
	case RightToCenterRight:
	case RightToBottom:

		StartRightTo(field, fieldIndex);

		break;

	case BottomToLeft:
	case BottomToCenterLeft:
	case BottomToCenterRight:
	case BottomToRight:

		StartBottomTo(field, fieldIndex);

		break;

	default:
		break;
	}

}

void SurfaceFold::Update(Camera* camera, std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, bool& fieldPlaneDrawFlag)
{
	fieldPlaneAnimeFlam_ += 0.02f;

	fieldPlaneTrans_.TransUpdate(camera);

	if (fieldPlaneAnimeFlam_ >= surfaceFoldFbxmodelAnime_->GetAnimeMaxflame() / 2 && !fieldReplaceFlag_)
	{
		Replace(field, fieldIndex);
		fieldReplaceFlag_ = true;
	}

	if (fieldPlaneAnimeFlam_ >= surfaceFoldFbxmodelAnime_->GetAnimeMaxflame())
	{
		fieldPlaneDrawFlag = false;
		fieldPlaneAnimeFlam_ = 0.0f;
		fieldReplaceFlag_ = false;

		switch (fieldIndex)
		{
		case TopToLeft:
		case TopToCenterLeft:
		case TopToCenterRight:
		case TopToRight:

			EndTopTo(field, fieldIndex);

			break;

		case LeftToTop:
		case LeftToCenterLeft:
		case LeftToRight:
		case LeftToBottom:

			EndLeftTo(field, fieldIndex);

			break;

		case CenterLeftToTop:
		case CenterLeftToLeft:
		case CenterLeftToCenterRight:
		case CenterLeftToBottom:

			EndCenterLeftTo(field, fieldIndex);

			break;

		case CenterRightToTop:
		case CenterRightToCenterLeft:
		case CenterRightToRight:
		case CenterRightToBottom:

			EndCenterRightTo(field, fieldIndex);

			break;

		case RightToTop:
		case RightToLeft:
		case RightToCenterRight:
		case RightToBottom:

			EndRightTo(field, fieldIndex);

			break;

		case BottomToLeft:
		case BottomToCenterLeft:
		case BottomToCenterRight:
		case BottomToRight:

			EndBottomTo(field, fieldIndex);

			break;

		default:
			break;
		}
	}

	surfaceFoldFbxmodel_->AnimationUpdate(surfaceFoldFbxmodelAnime_.get(), fieldPlaneAnimeFlam_);
}

void SurfaceFold::Replace(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	switch (fieldIndex)
	{
	case TopToLeft:
	case TopToCenterLeft:
	case TopToCenterRight:
	case TopToRight:

		ReplaceTopTo(field, fieldIndex);

		break;

	case LeftToTop:
	case LeftToCenterLeft:
	case LeftToRight:
	case LeftToBottom:

		ReplaceLeftTo(field, fieldIndex);

		break;

	case CenterLeftToTop:
	case CenterLeftToLeft:
	case CenterLeftToCenterRight:
	case CenterLeftToBottom:

		ReplaceCenterLeftTo(field, fieldIndex);

		break;

	case CenterRightToTop:
	case CenterRightToCenterLeft:
	case CenterRightToRight:
	case CenterRightToBottom:

		ReplaceCenterRightTo(field, fieldIndex);

		break;

	case RightToTop:
	case RightToLeft:
	case RightToCenterRight:
	case RightToBottom:

		ReplaceRightTo(field, fieldIndex);

		break;

	case BottomToLeft:
	case BottomToCenterLeft:
	case BottomToCenterRight:
	case BottomToRight:

		ReplaceBottomTo(field, fieldIndex);

		break;

	default:
		break;
	}
}

void SurfaceFold::Draw()
{
	surfaceFoldFbxmodel_->Draw(&fieldPlaneTrans_);
}

void SurfaceFold::StartTopTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	field[Top][LeftTop].isDraw = false;
	field[Top][RightTop].isDraw = false;
	field[Top][LeftBottom].isDraw = false;
	field[Top][RightBottom].isDraw = false;

	switch (fieldIndex)
	{
	case TopToLeft:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Top][RightBottom].textureData);

		//���UV��]
		surfaceFoldFbxmodel_->rotationUV("Map03", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map01", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map04", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map02", -90.0f * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[Left][RightBottom].textureData);

		//��]
		fieldPlaneTrans_.rotation = { 0.0f * AliceMathF::Deg2Rad,-90.0f * AliceMathF::Deg2Rad,0.0f * AliceMathF::Deg2Rad };

		field[Left][LeftTop].isDraw = false;
		field[Left][RightTop].isDraw = false;
		field[Left][LeftBottom].isDraw = false;
		field[Left][RightBottom].isDraw = false;

		break;

	case TopToCenterLeft:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Top][RightBottom].textureData);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[CenterLeft][RightBottom].textureData);

		//��]
		fieldPlaneTrans_.rotation = { 0.0f,180.0f * AliceMathF::Deg2Rad,0.0f };

		field[CenterLeft][LeftTop].isDraw = false;
		field[CenterLeft][RightTop].isDraw = false;
		field[CenterLeft][LeftBottom].isDraw = false;
		field[CenterLeft][RightBottom].isDraw = false;

		break;

	case TopToCenterRight:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Top][RightBottom].textureData);

		//���UV��]
		surfaceFoldFbxmodel_->rotationUV("Map03", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map01", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map04", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map02", 90.0f * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[CenterRight][RightBottom].textureData);

		fieldPlaneTrans_.rotation = { 0.0f,90.0f * AliceMathF::Deg2Rad,0.0f };

		field[CenterRight][LeftTop].isDraw = false;
		field[CenterRight][RightTop].isDraw = false;
		field[CenterRight][LeftBottom].isDraw = false;
		field[CenterRight][RightBottom].isDraw = false;

		break;

	case TopToRight:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Top][RightBottom].textureData);

		//���UV��]
		surfaceFoldFbxmodel_->rotationUV("Map04", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map03", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map02", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map01", 180.0f * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[Right][RightBottom].textureData);

		fieldPlaneTrans_.rotation = { 0.0f,0.0f,0.0f };

		field[Right][LeftTop].isDraw = false;
		field[Right][RightTop].isDraw = false;
		field[Right][LeftBottom].isDraw = false;
		field[Right][RightBottom].isDraw = false;

		break;
	default:
		break;
	}
}

void SurfaceFold::ReplaceTopTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	FieldElement element;
	Transform transform1;
	Transform transform2;

	switch (fieldIndex)
	{
	case TopToLeft:
		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[Top][LeftTop].surfacePartsModelTrans;
		transform2 = field[Left][LeftTop].surfacePartsModelTrans;
		element = std::move(field[Top][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[Top][LeftTop] = std::move(field[Left][LeftTop]);
		field[Top][LeftTop].surfacePartsModelTrans = transform1;

		field[Left][LeftTop] = std::move(element);
		field[Left][LeftTop].surfacePartsModelTrans = transform2;

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Top][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Left][RightTop].surfacePartsModelTrans;
		element = std::move(field[Top][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[Top][LeftBottom] = std::move(field[Left][RightTop]);
		field[Top][LeftBottom].surfacePartsModelTrans = transform1;

		field[Left][RightTop] = std::move(element);
		field[Left][RightTop].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[Top][RightTop].surfacePartsModelTrans;
		transform2 = field[Left][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[Top][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[Top][RightTop] = std::move(field[Left][LeftBottom]);
		field[Top][RightTop].surfacePartsModelTrans = transform1;

		field[Left][LeftBottom] = std::move(element);
		field[Left][LeftBottom].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[Top][RightBottom].surfacePartsModelTrans;
		transform2 = field[Left][RightBottom].surfacePartsModelTrans;
		element = std::move(field[Top][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Left][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[Top][RightBottom] = std::move(field[Left][RightBottom]);
		field[Top][RightBottom].surfacePartsModelTrans = transform1;

		field[Left][RightBottom] = std::move(element);
		field[Left][RightBottom].surfacePartsModelTrans = transform2;

		break;

	case TopToCenterLeft:

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[Top][LeftTop].surfacePartsModelTrans;
		transform2 = field[CenterLeft][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[Top][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[Top][LeftTop] = std::move(field[CenterLeft][LeftBottom]);
		field[Top][LeftTop].surfacePartsModelTrans = transform1;

		field[CenterLeft][LeftBottom] = std::move(element);
		field[CenterLeft][LeftBottom].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[Top][RightTop].surfacePartsModelTrans;
		transform2 = field[CenterLeft][RightBottom].surfacePartsModelTrans;
		element = std::move(field[Top][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[CenterLeft][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[Top][RightTop] = std::move(field[CenterLeft][RightBottom]);
		field[Top][RightTop].surfacePartsModelTrans = transform1;

		field[CenterLeft][RightBottom] = std::move(element);
		field[CenterLeft][RightBottom].surfacePartsModelTrans = transform2;

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[Top][LeftBottom].surfacePartsModelTrans;
		transform2 = field[CenterLeft][LeftTop].surfacePartsModelTrans;
		element = std::move(field[Top][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[Top][LeftBottom] = std::move(field[CenterLeft][LeftTop]);
		field[Top][LeftBottom].surfacePartsModelTrans = transform1;

		field[CenterLeft][LeftTop] = std::move(element);
		field[CenterLeft][LeftTop].surfacePartsModelTrans = transform2;

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Top][RightBottom].surfacePartsModelTrans;
		transform2 = field[CenterLeft][RightTop].surfacePartsModelTrans;
		element = std::move(field[Top][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[Top][RightBottom] = std::move(field[CenterLeft][RightTop]);
		field[Top][RightBottom].surfacePartsModelTrans = transform1;

		field[CenterLeft][RightTop] = std::move(element);
		field[CenterLeft][RightTop].surfacePartsModelTrans = transform2;

		break;

	case TopToCenterRight:

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[Top][LeftTop].surfacePartsModelTrans;
		transform2 = field[CenterRight][RightBottom].surfacePartsModelTrans;
		element = std::move(field[Top][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[CenterRight][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[Top][LeftTop] = std::move(field[CenterRight][RightBottom]);
		field[Top][LeftTop].surfacePartsModelTrans = transform1;

		field[CenterRight][RightBottom] = std::move(element);
		field[CenterRight][RightBottom].surfacePartsModelTrans = transform2;

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Top][RightTop].surfacePartsModelTrans;
		transform2 = field[CenterRight][RightTop].surfacePartsModelTrans;
		element = std::move(field[Top][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[Top][RightTop] = std::move(field[CenterRight][RightTop]);
		field[Top][RightTop].surfacePartsModelTrans = transform1;

		field[CenterRight][RightTop] = std::move(element);
		field[CenterRight][RightTop].surfacePartsModelTrans = transform2;

		//1�Ԃ�5�Ԃ����ւ���
		transform1 = field[Top][LeftBottom].surfacePartsModelTrans;
		transform2 = field[CenterRight][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[Top][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[Top][LeftBottom] = std::move(field[CenterRight][LeftBottom]);
		field[Top][LeftBottom].surfacePartsModelTrans = transform1;

		field[CenterRight][LeftBottom] = std::move(element);
		field[CenterRight][LeftBottom].surfacePartsModelTrans = transform2;

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Top][RightBottom].surfacePartsModelTrans;
		transform2 = field[CenterRight][LeftTop].surfacePartsModelTrans;
		element = std::move(field[Top][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[Top][RightBottom] = std::move(field[CenterRight][LeftTop]);
		field[Top][RightBottom].surfacePartsModelTrans = transform1;

		field[CenterRight][LeftTop] = std::move(element);
		field[CenterRight][LeftTop].surfacePartsModelTrans = transform2;

		break;

	case TopToRight:

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Top][LeftTop].surfacePartsModelTrans;
		transform2 = field[Right][RightTop].surfacePartsModelTrans;
		element = std::move(field[Top][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[Top][LeftTop] = std::move(field[Right][RightTop]);
		field[Top][LeftTop].surfacePartsModelTrans = transform1;

		field[Right][RightTop] = std::move(element);
		field[Right][RightTop].surfacePartsModelTrans = transform2;

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[Top][RightTop].surfacePartsModelTrans;
		transform2 = field[Right][LeftTop].surfacePartsModelTrans;
		element = std::move(field[Top][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[Top][RightTop] = std::move(field[Right][LeftTop]);
		field[Top][RightTop].surfacePartsModelTrans = transform1;

		field[Right][LeftTop] = std::move(element);
		field[Right][LeftTop].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[Top][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Right][RightBottom].surfacePartsModelTrans;
		element = std::move(field[Top][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Right][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[Top][LeftBottom] = std::move(field[Right][RightBottom]);
		field[Top][LeftBottom].surfacePartsModelTrans = transform1;

		field[Right][RightBottom] = std::move(element);
		field[Right][RightBottom].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[Top][RightBottom].surfacePartsModelTrans;
		transform2 = field[Right][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[Top][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[Top][RightBottom] = std::move(field[Right][LeftBottom]);
		field[Top][RightBottom].surfacePartsModelTrans = transform1;

		field[Right][LeftBottom] = std::move(element);
		field[Right][LeftBottom].surfacePartsModelTrans = transform2;

		break;

	default:
		break;
	}
}

void SurfaceFold::EndTopTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	field[Top][LeftTop].isDraw = true;
	field[Top][RightTop].isDraw = true;
	field[Top][LeftBottom].isDraw = true;
	field[Top][RightBottom].isDraw = true;

	switch (fieldIndex)
	{
	case TopToLeft:

		field[Left][LeftTop].isDraw = true;
		field[Left][RightTop].isDraw = true;
		field[Left][LeftBottom].isDraw = true;
		field[Left][RightBottom].isDraw = true;

		break;

	case TopToCenterLeft:

		field[CenterLeft][LeftTop].isDraw = true;
		field[CenterLeft][RightTop].isDraw = true;
		field[CenterLeft][LeftBottom].isDraw = true;
		field[CenterLeft][RightBottom].isDraw = true;

		break;

	case TopToCenterRight:

		field[CenterRight][LeftTop].isDraw = true;
		field[CenterRight][RightTop].isDraw = true;
		field[CenterRight][LeftBottom].isDraw = true;
		field[CenterRight][RightBottom].isDraw = true;

		break;

	case TopToRight:

		field[Right][LeftTop].isDraw = true;
		field[Right][RightTop].isDraw = true;
		field[Right][LeftBottom].isDraw = true;
		field[Right][RightBottom].isDraw = true;

		break;

	default:
		break;
	}
}

void SurfaceFold::StartLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	field[Left][LeftTop].isDraw = false;
	field[Left][RightTop].isDraw = false;
	field[Left][LeftBottom].isDraw = false;
	field[Left][RightBottom].isDraw = false;

	switch (fieldIndex)
	{
	case LeftToTop:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Left][RightBottom].textureData);

		//���UV��]
		surfaceFoldFbxmodel_->rotationUV("Map04", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map03", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map02", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map01", 180.0f * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[Top][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Map06", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map05", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map08", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map07", 90.0f * AliceMathF::Deg2Rad);

		//��]�p
		fieldPlaneTrans_.rotation = { -90.0f * AliceMathF::Deg2Rad,0.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[Top][LeftTop].isDraw = false;
		field[Top][RightTop].isDraw = false;
		field[Top][LeftBottom].isDraw = false;
		field[Top][RightBottom].isDraw = false;

		break;
	case LeftToCenterLeft:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Left][RightBottom].textureData);

		//���UV��]
		surfaceFoldFbxmodel_->rotationUV("Map04", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map03", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map02", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map01", 90.0f * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[CenterLeft][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Map06", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map05", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map08", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map07", 90.0f * AliceMathF::Deg2Rad);

		//��]�p
		fieldPlaneTrans_.rotation = { 180.0f * AliceMathF::Deg2Rad,0.0f,90.0f * AliceMathF::Deg2Rad };

		field[CenterLeft][LeftTop].isDraw = false;
		field[CenterLeft][RightTop].isDraw = false;
		field[CenterLeft][LeftBottom].isDraw = false;
		field[CenterLeft][RightBottom].isDraw = false;

		break;

	case LeftToRight:
		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Left][RightBottom].textureData);

		//���UV��]
		surfaceFoldFbxmodel_->rotationUV("Map04", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map03", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map02", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map01", -90.0f * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[Right][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Map06", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map05", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map08", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map07", -90.0f * AliceMathF::Deg2Rad);

		//��]�p
		fieldPlaneTrans_.rotation = { 0.0f * AliceMathF::Deg2Rad,0.0f,90.0f * AliceMathF::Deg2Rad };

		field[Right][LeftTop].isDraw = false;
		field[Right][RightTop].isDraw = false;
		field[Right][LeftBottom].isDraw = false;
		field[Right][RightBottom].isDraw = false;

		break;

	case LeftToBottom:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Left][RightBottom].textureData);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[Bottom][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Map06", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map05", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map08", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map07", -90.0f * AliceMathF::Deg2Rad);

		//��]�p
		fieldPlaneTrans_.rotation = { 90.0f * AliceMathF::Deg2Rad,0.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[Bottom][LeftTop].isDraw = false;
		field[Bottom][RightTop].isDraw = false;
		field[Bottom][LeftBottom].isDraw = false;
		field[Bottom][RightBottom].isDraw = false;

		break;

	default:
		break;
	}
}

void SurfaceFold::ReplaceLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	FieldElement element;
	Transform transform1;
	Transform transform2;

	switch (fieldIndex)
	{

	case LeftToTop:
		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Left][LeftTop].surfacePartsModelTrans;
		transform2 = field[Top][LeftTop].surfacePartsModelTrans;
		element = std::move(field[Left][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[Left][LeftTop] = std::move(field[Top][LeftTop]);
		field[Left][LeftTop].surfacePartsModelTrans = transform1;

		field[Top][LeftTop] = std::move(element);
		field[Top][LeftTop].surfacePartsModelTrans = transform2;

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[Left][RightTop].surfacePartsModelTrans;
		transform2 = field[Top][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[Left][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[Left][RightTop] = std::move(field[Top][LeftBottom]);
		field[Left][RightTop].surfacePartsModelTrans = transform1;

		field[Top][LeftBottom] = std::move(element);
		field[Top][LeftBottom].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[Left][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Top][RightTop].surfacePartsModelTrans;
		element = std::move(field[Left][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[Left][LeftBottom] = std::move(field[Top][RightTop]);
		field[Left][LeftBottom].surfacePartsModelTrans = transform1;

		field[Top][RightTop] = std::move(element);
		field[Top][RightTop].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[Left][RightBottom].surfacePartsModelTrans;
		transform2 = field[Top][RightBottom].surfacePartsModelTrans;
		element = std::move(field[Left][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Top][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[Left][RightBottom] = std::move(field[Top][RightBottom]);
		field[Left][RightBottom].surfacePartsModelTrans = transform1;

		field[Top][RightBottom] = std::move(element);
		field[Top][RightBottom].surfacePartsModelTrans = transform2;

		break;

	case LeftToCenterLeft:

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[Left][LeftTop].surfacePartsModelTrans;
		transform2 = field[CenterLeft][RightTop].surfacePartsModelTrans;
		element = std::move(field[Left][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[Left][LeftTop] = std::move(field[CenterLeft][RightTop]);
		field[Left][LeftTop].surfacePartsModelTrans = transform1;

		field[CenterLeft][RightTop] = std::move(element);
		field[CenterLeft][RightTop].surfacePartsModelTrans = transform2;

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Left][RightTop].surfacePartsModelTrans;
		transform2 = field[CenterLeft][LeftTop].surfacePartsModelTrans;
		element = std::move(field[Left][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[Left][RightTop] = std::move(field[CenterLeft][LeftTop]);
		field[Left][RightTop].surfacePartsModelTrans = transform1;

		field[CenterLeft][LeftTop] = std::move(element);
		field[CenterLeft][LeftTop].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[Left][LeftBottom].surfacePartsModelTrans;
		transform2 = field[CenterLeft][RightBottom].surfacePartsModelTrans;
		element = std::move(field[Left][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[CenterLeft][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[Left][LeftBottom] = std::move(field[CenterLeft][RightBottom]);
		field[Left][LeftBottom].surfacePartsModelTrans = transform1;

		field[CenterLeft][RightBottom] = std::move(element);
		field[CenterLeft][RightBottom].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[Left][RightBottom].surfacePartsModelTrans;
		transform2 = field[CenterLeft][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[Left][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[Left][RightBottom] = std::move(field[CenterLeft][LeftBottom]);
		field[Left][RightBottom].surfacePartsModelTrans = transform1;

		field[CenterLeft][LeftBottom] = std::move(element);
		field[CenterLeft][LeftBottom].surfacePartsModelTrans = transform2;

		break;

	case LeftToRight:

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[Left][LeftTop].surfacePartsModelTrans;
		transform2 = field[Right][RightTop].surfacePartsModelTrans;
		element = std::move(field[Left][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[Left][LeftTop] = std::move(field[Right][RightTop]);
		field[Left][LeftTop].surfacePartsModelTrans = transform1;

		field[Right][RightTop] = std::move(element);
		field[Right][RightTop].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[Left][RightTop].surfacePartsModelTrans;
		transform2 = field[Right][LeftTop].surfacePartsModelTrans;
		element = std::move(field[Left][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[Left][RightTop] = std::move(field[Right][LeftTop]);
		field[Left][RightTop].surfacePartsModelTrans = transform1;

		field[Right][LeftTop] = std::move(element);
		field[Right][LeftTop].surfacePartsModelTrans = transform2;

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Left][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Right][RightBottom].surfacePartsModelTrans;
		element = std::move(field[Left][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Right][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[Left][LeftBottom] = std::move(field[Right][RightBottom]);
		field[Left][LeftBottom].surfacePartsModelTrans = transform1;

		field[Right][RightBottom] = std::move(element);
		field[Right][RightBottom].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[Left][RightBottom].surfacePartsModelTrans;
		transform2 = field[Right][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[Left][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[Left][RightBottom] = std::move(field[Right][LeftBottom]);
		field[Left][RightBottom].surfacePartsModelTrans = transform1;

		field[Right][LeftBottom] = std::move(element);
		field[Right][LeftBottom].surfacePartsModelTrans = transform2;

		break;

	case LeftToBottom:

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[Left][LeftTop].surfacePartsModelTrans;
		transform2 = field[Bottom][LeftTop].surfacePartsModelTrans;
		element = std::move(field[Left][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[Left][LeftTop] = std::move(field[Bottom][LeftTop]);
		field[Left][LeftTop].surfacePartsModelTrans = transform1;

		field[Bottom][LeftTop] = std::move(element);
		field[Bottom][LeftTop].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[Left][RightTop].surfacePartsModelTrans;
		transform2 = field[Bottom][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[Left][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[Left][RightTop] = std::move(field[Bottom][LeftBottom]);
		field[Left][RightTop].surfacePartsModelTrans = transform1;

		field[Bottom][LeftBottom] = std::move(element);
		field[Bottom][LeftBottom].surfacePartsModelTrans = transform2;

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[Left][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Bottom][RightTop].surfacePartsModelTrans;
		element = std::move(field[Left][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[Left][LeftBottom] = std::move(field[Bottom][RightTop]);
		field[Left][LeftBottom].surfacePartsModelTrans = transform1;

		field[Bottom][RightTop] = std::move(element);
		field[Bottom][RightTop].surfacePartsModelTrans = transform2;

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Left][RightBottom].surfacePartsModelTrans;
		transform2 = field[Bottom][RightBottom].surfacePartsModelTrans;
		element = std::move(field[Left][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Bottom][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[Left][RightBottom] = std::move(field[Bottom][RightBottom]);
		field[Left][RightBottom].surfacePartsModelTrans = transform1;

		field[Bottom][RightBottom] = std::move(element);
		field[Bottom][RightBottom].surfacePartsModelTrans = transform2;

		break;

	default:
		break;

	}
}

void SurfaceFold::EndLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	field[Left][LeftTop].isDraw = true;
	field[Left][RightTop].isDraw = true;
	field[Left][LeftBottom].isDraw = true;
	field[Left][RightBottom].isDraw = true;

	switch (fieldIndex)
	{

	case LeftToTop:

		field[Top][LeftTop].isDraw = true;
		field[Top][RightTop].isDraw = true;
		field[Top][LeftBottom].isDraw = true;
		field[Top][RightBottom].isDraw = true;
		break;

	case LeftToCenterLeft:

		field[CenterLeft][LeftTop].isDraw = true;
		field[CenterLeft][RightTop].isDraw = true;
		field[CenterLeft][LeftBottom].isDraw = true;
		field[CenterLeft][RightBottom].isDraw = true;
		break;

	case LeftToRight:

		field[Right][LeftTop].isDraw = true;
		field[Right][RightTop].isDraw = true;
		field[Right][LeftBottom].isDraw = true;
		field[Right][RightBottom].isDraw = true;
		break;

	case LeftToBottom:

		field[Bottom][LeftTop].isDraw = true;
		field[Bottom][RightTop].isDraw = true;
		field[Bottom][LeftBottom].isDraw = true;
		field[Bottom][RightBottom].isDraw = true;
		break;

	default:
		break;
	}
}

void SurfaceFold::StartCenterLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	field[CenterLeft][LeftTop].isDraw = false;
	field[CenterLeft][RightTop].isDraw = false;
	field[CenterLeft][LeftBottom].isDraw = false;
	field[CenterLeft][RightBottom].isDraw = false;

	switch (fieldIndex)
	{
	case CenterLeftToTop:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[CenterLeft][RightBottom].textureData);

		//���UV��]
		surfaceFoldFbxmodel_->rotationUV("Map04", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map03", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map02", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map01", 180.0f * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[Top][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Map08", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map07", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map06", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map05", 180.0f * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { -90.0f * AliceMathF::Deg2Rad,-90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[Top][LeftTop].isDraw = false;
		field[Top][RightTop].isDraw = false;
		field[Top][LeftBottom].isDraw = false;
		field[Top][RightBottom].isDraw = false;

		break;
	case CenterLeftToLeft:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[CenterLeft][RightBottom].textureData);

		////���UV��]
		surfaceFoldFbxmodel_->rotationUV("Map03", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map01", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map04", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map02", -90.0f * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[Left][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Map08", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map07", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map06", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map05", -90.0f * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 0.0f,-90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[Left][LeftTop].isDraw = false;
		field[Left][RightTop].isDraw = false;
		field[Left][LeftBottom].isDraw = false;
		field[Left][RightBottom].isDraw = false;

		break;
	case CenterLeftToCenterRight:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[CenterLeft][RightBottom].textureData);

		////���UV��]
		surfaceFoldFbxmodel_->rotationUV("Map02", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map04", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map01", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map03", 90.0f * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[CenterRight][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Map06", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map08", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map05", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map07", 90.0f * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 180.0f * AliceMathF::Deg2Rad,-90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[CenterRight][LeftTop].isDraw = false;
		field[CenterRight][RightTop].isDraw = false;
		field[CenterRight][LeftBottom].isDraw = false;
		field[CenterRight][RightBottom].isDraw = false;

		break;
	case CenterLeftToBottom:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[CenterLeft][RightBottom].textureData);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[Bottom][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Map08", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map07", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map06", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map05", 180.0f * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 90.0f * AliceMathF::Deg2Rad,-90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[Bottom][LeftTop].isDraw = false;
		field[Bottom][RightTop].isDraw = false;
		field[Bottom][LeftBottom].isDraw = false;
		field[Bottom][RightBottom].isDraw = false;

		break;

	default:
		break;
	}
}

void SurfaceFold::ReplaceCenterLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	FieldElement element;
	Transform transform1;
	Transform transform2;

	switch (fieldIndex)
	{
	case CenterLeftToTop:

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[CenterLeft][LeftTop].surfacePartsModelTrans;
		transform2 = field[Top][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[CenterLeft][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[CenterLeft][LeftTop] = std::move(field[Top][LeftBottom]);
		field[CenterLeft][LeftTop].surfacePartsModelTrans = transform1;

		field[Top][LeftBottom] = std::move(element);
		field[Top][LeftBottom].surfacePartsModelTrans = transform2;

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[CenterLeft][RightTop].surfacePartsModelTrans;
		transform2 = field[Top][RightBottom].surfacePartsModelTrans;
		element = std::move(field[CenterLeft][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Top][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[CenterLeft][RightTop] = std::move(field[Top][RightBottom]);
		field[CenterLeft][RightTop].surfacePartsModelTrans = transform1;

		field[Top][RightBottom] = std::move(element);
		field[Top][RightBottom].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[CenterLeft][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Top][LeftTop].surfacePartsModelTrans;
		element = std::move(field[CenterLeft][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[CenterLeft][LeftBottom] = std::move(field[Top][LeftTop]);
		field[CenterLeft][LeftBottom].surfacePartsModelTrans = transform1;

		field[Top][LeftTop] = std::move(element);
		field[Top][LeftTop].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[CenterLeft][RightBottom].surfacePartsModelTrans;
		transform2 = field[Top][RightTop].surfacePartsModelTrans;
		element = std::move(field[CenterLeft][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[CenterLeft][RightBottom] = std::move(field[Top][RightTop]);
		field[CenterLeft][RightBottom].surfacePartsModelTrans = transform1;

		field[Top][RightTop] = std::move(element);
		field[Top][RightTop].surfacePartsModelTrans = transform2;

		break;

	case CenterLeftToLeft:

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[CenterLeft][LeftTop].surfacePartsModelTrans;
		transform2 = field[Left][RightTop].surfacePartsModelTrans;
		element = std::move(field[CenterLeft][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[CenterLeft][LeftTop] = std::move(field[Left][RightTop]);
		field[CenterLeft][LeftTop].surfacePartsModelTrans = transform1;

		field[Left][RightTop] = std::move(element);
		field[Left][RightTop].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[CenterLeft][RightTop].surfacePartsModelTrans;
		transform2 = field[Left][LeftTop].surfacePartsModelTrans;
		element = std::move(field[CenterLeft][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[CenterLeft][RightTop] = std::move(field[Left][LeftTop]);
		field[CenterLeft][RightTop].surfacePartsModelTrans = transform1;

		field[Left][LeftTop] = std::move(element);
		field[Left][LeftTop].surfacePartsModelTrans = transform2;

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[CenterLeft][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Left][RightBottom].surfacePartsModelTrans;
		element = std::move(field[CenterLeft][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Left][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[CenterLeft][LeftBottom] = std::move(field[Left][RightBottom]);
		field[CenterLeft][LeftBottom].surfacePartsModelTrans = transform1;

		field[Left][RightBottom] = std::move(element);
		field[Left][RightBottom].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[CenterLeft][RightBottom].surfacePartsModelTrans;
		transform2 = field[Left][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[CenterLeft][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[CenterLeft][RightBottom] = std::move(field[Left][LeftBottom]);
		field[CenterLeft][RightBottom].surfacePartsModelTrans = transform1;

		field[Left][LeftBottom] = std::move(element);
		field[Left][LeftBottom].surfacePartsModelTrans = transform2;

		break;
	case CenterLeftToCenterRight:
		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[CenterLeft][LeftTop].surfacePartsModelTrans;
		transform2 = field[CenterRight][RightTop].surfacePartsModelTrans;
		element = std::move(field[CenterLeft][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[CenterLeft][LeftTop] = std::move(field[CenterRight][RightTop]);
		field[CenterLeft][LeftTop].surfacePartsModelTrans = transform1;

		field[CenterRight][RightTop] = std::move(element);
		field[CenterRight][RightTop].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[CenterLeft][RightTop].surfacePartsModelTrans;
		transform2 = field[CenterRight][LeftTop].surfacePartsModelTrans;
		element = std::move(field[CenterLeft][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[CenterLeft][RightTop] = std::move(field[CenterRight][LeftTop]);
		field[CenterLeft][RightTop].surfacePartsModelTrans = transform1;

		field[CenterRight][LeftTop] = std::move(element);
		field[CenterRight][LeftTop].surfacePartsModelTrans = transform2;

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[CenterLeft][LeftBottom].surfacePartsModelTrans;
		transform2 = field[CenterRight][RightBottom].surfacePartsModelTrans;
		element = std::move(field[CenterLeft][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[CenterRight][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[CenterLeft][LeftBottom] = std::move(field[CenterRight][RightBottom]);
		field[CenterLeft][LeftBottom].surfacePartsModelTrans = transform1;

		field[CenterRight][RightBottom] = std::move(element);
		field[CenterRight][RightBottom].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[CenterLeft][RightBottom].surfacePartsModelTrans;
		transform2 = field[CenterRight][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[CenterLeft][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[CenterLeft][RightBottom] = std::move(field[CenterRight][LeftBottom]);
		field[CenterLeft][RightBottom].surfacePartsModelTrans = transform1;

		field[CenterRight][LeftBottom] = std::move(element);
		field[CenterRight][LeftBottom].surfacePartsModelTrans = transform2;

		break;
	case CenterLeftToBottom:

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[CenterLeft][LeftTop].surfacePartsModelTrans;
		transform2 = field[Bottom][RightTop].surfacePartsModelTrans;
		element = std::move(field[CenterLeft][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[CenterLeft][LeftTop] = std::move(field[Bottom][RightTop]);
		field[CenterLeft][LeftTop].surfacePartsModelTrans = transform1;

		field[Bottom][RightTop] = std::move(element);
		field[Bottom][RightTop].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[CenterLeft][RightTop].surfacePartsModelTrans;
		transform2 = field[Bottom][LeftTop].surfacePartsModelTrans;
		element = std::move(field[CenterLeft][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[CenterLeft][RightTop] = std::move(field[Bottom][LeftTop]);
		field[CenterLeft][RightTop].surfacePartsModelTrans = transform1;

		field[Bottom][LeftTop] = std::move(element);
		field[Bottom][LeftTop].surfacePartsModelTrans = transform2;

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[CenterLeft][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Bottom][RightBottom].surfacePartsModelTrans;
		element = std::move(field[CenterLeft][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Bottom][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[CenterLeft][LeftBottom] = std::move(field[Bottom][RightBottom]);
		field[CenterLeft][LeftBottom].surfacePartsModelTrans = transform1;

		field[Bottom][RightBottom] = std::move(element);
		field[Bottom][RightBottom].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[CenterLeft][RightBottom].surfacePartsModelTrans;
		transform2 = field[Bottom][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[CenterLeft][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[CenterLeft][RightBottom] = std::move(field[Bottom][LeftBottom]);
		field[CenterLeft][RightBottom].surfacePartsModelTrans = transform1;

		field[Bottom][LeftBottom] = std::move(element);
		field[Bottom][LeftBottom].surfacePartsModelTrans = transform2;

		break;
	default:
		break;
	}
}

void SurfaceFold::EndCenterLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	field[CenterLeft][LeftTop].isDraw = true;
	field[CenterLeft][RightTop].isDraw = true;
	field[CenterLeft][LeftBottom].isDraw = true;
	field[CenterLeft][RightBottom].isDraw = true;

	switch (fieldIndex)
	{
	case CenterLeftToTop:

		field[Top][LeftTop].isDraw = true;
		field[Top][RightTop].isDraw = true;
		field[Top][LeftBottom].isDraw = true;
		field[Top][RightBottom].isDraw = true;

		break;

	case CenterLeftToLeft:

		field[Left][LeftTop].isDraw = true;
		field[Left][RightTop].isDraw = true;
		field[Left][LeftBottom].isDraw = true;
		field[Left][RightBottom].isDraw = true;

		break;

	case CenterLeftToCenterRight:

		field[CenterRight][LeftTop].isDraw = true;
		field[CenterRight][RightTop].isDraw = true;
		field[CenterRight][LeftBottom].isDraw = true;
		field[CenterRight][RightBottom].isDraw = true;

		break;

	case CenterLeftToBottom:

		field[Bottom][LeftTop].isDraw = true;
		field[Bottom][RightTop].isDraw = true;
		field[Bottom][LeftBottom].isDraw = true;
		field[Bottom][RightBottom].isDraw = true;

		break;

	default:
		break;
	}
}

void SurfaceFold::StartCenterRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	field[CenterRight][LeftTop].isDraw = false;
	field[CenterRight][RightTop].isDraw = false;
	field[CenterRight][LeftBottom].isDraw = false;
	field[CenterRight][RightBottom].isDraw = false;

	switch (fieldIndex)
	{

	case CenterRightToTop:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[CenterRight][RightBottom].textureData);

		//���UV��]
		surfaceFoldFbxmodel_->rotationUV("Map04", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map03", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map02", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map01", 180.0f * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[Top][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Map06", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map08", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map05", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map07", -90.0f * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { -90.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[Top][LeftTop].isDraw = false;
		field[Top][RightTop].isDraw = false;
		field[Top][LeftBottom].isDraw = false;
		field[Top][RightBottom].isDraw = false;

		break;

	case CenterRightToCenterLeft:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[CenterRight][RightBottom].textureData);

		//���UV��]
		surfaceFoldFbxmodel_->rotationUV("Map03", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map01", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map04", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map02", -90.0f * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[CenterLeft][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Map07", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map05", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map08", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map06", -90.0f * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 0.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[CenterLeft][LeftTop].isDraw = false;
		field[CenterLeft][RightTop].isDraw = false;
		field[CenterLeft][LeftBottom].isDraw = false;
		field[CenterLeft][RightBottom].isDraw = false;

		break;

	case CenterRightToRight:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[CenterRight][RightBottom].textureData);

		//���UV��]
		surfaceFoldFbxmodel_->rotationUV("Map02", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map04", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map01", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map03", 90.0f * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[Right][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Map06", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map08", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map05", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map07", 90.0f * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 180.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[Right][LeftTop].isDraw = false;
		field[Right][RightTop].isDraw = false;
		field[Right][LeftBottom].isDraw = false;
		field[Right][RightBottom].isDraw = false;

		break;

	case CenterRightToBottom:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[CenterRight][RightBottom].textureData);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[Bottom][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Map06", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map08", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map05", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map07", 90.0f * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 90.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[Bottom][LeftTop].isDraw = false;
		field[Bottom][RightTop].isDraw = false;
		field[Bottom][LeftBottom].isDraw = false;
		field[Bottom][RightBottom].isDraw = false;

		break;

	default:
		break;
	}
}

void SurfaceFold::ReplaceCenterRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	FieldElement element;
	Transform transform1;
	Transform transform2;

	switch (fieldIndex)
	{
	case CenterRightToTop:

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[CenterRight][LeftTop].surfacePartsModelTrans;
		transform2 = field[Top][RightBottom].surfacePartsModelTrans;
		element = std::move(field[CenterRight][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Top][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[CenterRight][LeftTop] = std::move(field[Top][RightBottom]);
		field[CenterRight][LeftTop].surfacePartsModelTrans = transform1;

		field[Top][RightBottom] = std::move(element);
		field[Top][RightBottom].surfacePartsModelTrans = transform2;

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[CenterRight][RightTop].surfacePartsModelTrans;
		transform2 = field[Top][RightTop].surfacePartsModelTrans;
		element = std::move(field[CenterRight][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[CenterRight][RightTop] = std::move(field[Top][RightTop]);
		field[CenterRight][RightTop].surfacePartsModelTrans = transform1;

		field[Top][RightTop] = std::move(element);
		field[Top][RightTop].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[CenterRight][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Top][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[CenterRight][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[CenterRight][LeftBottom] = std::move(field[Top][LeftBottom]);
		field[CenterRight][LeftBottom].surfacePartsModelTrans = transform1;

		field[Top][LeftBottom] = std::move(element);
		field[Top][LeftBottom].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[CenterRight][RightBottom].surfacePartsModelTrans;
		transform2 = field[Top][LeftTop].surfacePartsModelTrans;
		element = std::move(field[CenterRight][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[CenterRight][RightBottom] = std::move(field[Top][LeftTop]);
		field[CenterRight][RightBottom].surfacePartsModelTrans = transform1;

		field[Top][LeftTop] = std::move(element);
		field[Top][LeftTop].surfacePartsModelTrans = transform2;

		break;

	case CenterRightToCenterLeft:

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[CenterRight][LeftTop].surfacePartsModelTrans;
		transform2 = field[CenterLeft][RightTop].surfacePartsModelTrans;
		element = std::move(field[CenterRight][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[CenterRight][LeftTop] = std::move(field[CenterLeft][RightTop]);
		field[CenterRight][LeftTop].surfacePartsModelTrans = transform1;

		field[CenterLeft][RightTop] = std::move(element);
		field[CenterLeft][RightTop].surfacePartsModelTrans = transform2;

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[CenterRight][RightTop].surfacePartsModelTrans;
		transform2 = field[CenterLeft][LeftTop].surfacePartsModelTrans;
		element = std::move(field[CenterRight][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[CenterRight][RightTop] = std::move(field[CenterLeft][LeftTop]);
		field[CenterRight][RightTop].surfacePartsModelTrans = transform1;

		field[CenterLeft][LeftTop] = std::move(element);
		field[CenterLeft][LeftTop].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[CenterRight][LeftBottom].surfacePartsModelTrans;
		transform2 = field[CenterLeft][RightBottom].surfacePartsModelTrans;
		element = std::move(field[CenterRight][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[CenterLeft][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[CenterRight][LeftBottom] = std::move(field[CenterLeft][RightBottom]);
		field[CenterRight][LeftBottom].surfacePartsModelTrans = transform1;

		field[CenterLeft][RightBottom] = std::move(element);
		field[CenterLeft][RightBottom].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[CenterRight][RightBottom].surfacePartsModelTrans;
		transform2 = field[CenterLeft][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[CenterRight][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[CenterRight][RightBottom] = std::move(field[CenterLeft][LeftBottom]);
		field[CenterRight][RightBottom].surfacePartsModelTrans = transform1;

		field[CenterLeft][LeftBottom] = std::move(element);
		field[CenterLeft][LeftBottom].surfacePartsModelTrans = transform2;

		break;

	case CenterRightToRight:

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[CenterRight][LeftTop].surfacePartsModelTrans;
		transform2 = field[Right][RightTop].surfacePartsModelTrans;
		element = std::move(field[CenterRight][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[CenterRight][LeftTop] = std::move(field[Right][RightTop]);
		field[CenterRight][LeftTop].surfacePartsModelTrans = transform1;

		field[Right][RightTop] = std::move(element);
		field[Right][RightTop].surfacePartsModelTrans = transform2;

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[CenterRight][RightTop].surfacePartsModelTrans;
		transform2 = field[Right][LeftTop].surfacePartsModelTrans;
		element = std::move(field[CenterRight][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[CenterRight][RightTop] = std::move(field[Right][LeftTop]);
		field[CenterRight][RightTop].surfacePartsModelTrans = transform1;

		field[Right][LeftTop] = std::move(element);
		field[Right][LeftTop].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[CenterRight][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Right][RightBottom].surfacePartsModelTrans;
		element = std::move(field[CenterRight][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Right][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[CenterRight][LeftBottom] = std::move(field[Right][RightBottom]);
		field[CenterRight][LeftBottom].surfacePartsModelTrans = transform1;

		field[Right][RightBottom] = std::move(element);
		field[Right][RightBottom].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[CenterRight][RightBottom].surfacePartsModelTrans;
		transform2 = field[Right][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[CenterRight][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[CenterRight][RightBottom] = std::move(field[Right][LeftBottom]);
		field[CenterRight][RightBottom].surfacePartsModelTrans = transform1;

		field[Right][LeftBottom] = std::move(element);
		field[Right][LeftBottom].surfacePartsModelTrans = transform2;

		break;

	case CenterRightToBottom:

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[CenterRight][LeftTop].surfacePartsModelTrans;
		transform2 = field[Bottom][RightBottom].surfacePartsModelTrans;
		element = std::move(field[CenterRight][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Bottom][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[CenterRight][LeftTop] = std::move(field[Bottom][RightBottom]);
		field[CenterRight][LeftTop].surfacePartsModelTrans = transform1;

		field[Bottom][RightBottom] = std::move(element);
		field[Bottom][RightBottom].surfacePartsModelTrans = transform2;

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[CenterRight][RightTop].surfacePartsModelTrans;
		transform2 = field[Bottom][RightTop].surfacePartsModelTrans;
		element = std::move(field[CenterRight][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[CenterRight][RightTop] = std::move(field[Bottom][RightTop]);
		field[CenterRight][RightTop].surfacePartsModelTrans = transform1;

		field[Bottom][RightTop] = std::move(element);
		field[Bottom][RightTop].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[CenterRight][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Bottom][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[CenterRight][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[CenterRight][LeftBottom] = std::move(field[Bottom][LeftBottom]);
		field[CenterRight][LeftBottom].surfacePartsModelTrans = transform1;

		field[Bottom][LeftBottom] = std::move(element);
		field[Bottom][LeftBottom].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[CenterRight][RightBottom].surfacePartsModelTrans;
		transform2 = field[Bottom][LeftTop].surfacePartsModelTrans;
		element = std::move(field[CenterRight][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[CenterRight][RightBottom] = std::move(field[Bottom][LeftTop]);
		field[CenterRight][RightBottom].surfacePartsModelTrans = transform1;

		field[Bottom][LeftTop] = std::move(element);
		field[Bottom][LeftTop].surfacePartsModelTrans = transform2;

		break;

	default:
		break;
	}
}

void SurfaceFold::EndCenterRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	field[CenterRight][LeftTop].isDraw = true;
	field[CenterRight][RightTop].isDraw = true;
	field[CenterRight][LeftBottom].isDraw = true;
	field[CenterRight][RightBottom].isDraw = true;

	switch (fieldIndex)
	{

	case CenterRightToTop:

		field[Top][LeftTop].isDraw = true;
		field[Top][RightTop].isDraw = true;
		field[Top][LeftBottom].isDraw = true;
		field[Top][RightBottom].isDraw = true;

		break;

	case CenterRightToCenterLeft:

		field[CenterLeft][LeftTop].isDraw = true;
		field[CenterLeft][RightTop].isDraw = true;
		field[CenterLeft][LeftBottom].isDraw = true;
		field[CenterLeft][RightBottom].isDraw = true;

		break;

	case CenterRightToRight:

		field[Right][LeftTop].isDraw = true;
		field[Right][RightTop].isDraw = true;
		field[Right][LeftBottom].isDraw = true;
		field[Right][RightBottom].isDraw = true;

		break;

	case CenterRightToBottom:

		field[Bottom][LeftTop].isDraw = true;
		field[Bottom][RightTop].isDraw = true;
		field[Bottom][LeftBottom].isDraw = true;
		field[Bottom][RightBottom].isDraw = true;

		break;

	default:
		break;
	}
}

void SurfaceFold::StartRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	
	field[Right][LeftTop].isDraw = false;
	field[Right][RightTop].isDraw = false;
	field[Right][LeftBottom].isDraw = false;
	field[Right][RightBottom].isDraw = false;

	switch (fieldIndex)
	{
	case RightToTop:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Right][RightBottom].textureData);

		//���UV��]
		surfaceFoldFbxmodel_->rotationUV("Map02", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map04", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map01", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map03", 180.0f * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[Top][RightBottom].textureData);

		fieldPlaneTrans_.rotation = { -90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[Top][LeftTop].isDraw = false;
		field[Top][RightTop].isDraw = false;
		field[Top][LeftBottom].isDraw = false;
		field[Top][RightBottom].isDraw = false;

		break;

	case RightToLeft:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Right][RightBottom].textureData);

		//���UV��]
		surfaceFoldFbxmodel_->rotationUV("Map02", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map04", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map01", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map03", 90.0f * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[Left][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Map06", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map08", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map05", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map07", 90.0f * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 180.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[Left][LeftTop].isDraw = false;
		field[Left][RightTop].isDraw = false;
		field[Left][LeftBottom].isDraw = false;
		field[Left][RightBottom].isDraw = false;

		break;

	case RightToCenterRight:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Right][RightBottom].textureData);

		//���UV��]
		surfaceFoldFbxmodel_->rotationUV("Map03", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map01", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map04", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map02", -90.0f * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[CenterRight][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Map07", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map05", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map08", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map06", -90.0f * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 0.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[CenterRight][LeftTop].isDraw = false;
		field[CenterRight][RightTop].isDraw = false;
		field[CenterRight][LeftBottom].isDraw = false;
		field[CenterRight][RightBottom].isDraw = false;

		break;

	case RightToBottom:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Right][RightBottom].textureData);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[Bottom][RightBottom].textureData);

		fieldPlaneTrans_.rotation = { 90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad };

		field[Bottom][LeftTop].isDraw = false;
		field[Bottom][RightTop].isDraw = false;
		field[Bottom][LeftBottom].isDraw = false;
		field[Bottom][RightBottom].isDraw = false;

		break;

	default:
		break;
	}
}

void SurfaceFold::ReplaceRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	FieldElement element;
	Transform transform1;
	Transform transform2;

	switch (fieldIndex)
	{
	case RightToTop:

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Right][LeftTop].surfacePartsModelTrans;
		transform2 = field[Top][RightTop].surfacePartsModelTrans;
		element = std::move(field[Right][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Top][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[Right][LeftTop] = std::move(field[Top][RightTop]);
		field[Right][LeftTop].surfacePartsModelTrans = transform1;

		field[Top][RightTop] = std::move(element);
		field[Top][RightTop].surfacePartsModelTrans = transform2;

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[Right][RightTop].surfacePartsModelTrans;
		transform2 = field[Top][LeftTop].surfacePartsModelTrans;
		element = std::move(field[Right][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Top][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[Right][RightTop] = std::move(field[Top][LeftTop]);
		field[Right][RightTop].surfacePartsModelTrans = transform1;

		field[Top][LeftTop] = std::move(element);
		field[Top][LeftTop].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[Right][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Top][RightBottom].surfacePartsModelTrans;
		element = std::move(field[Right][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Top][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[Right][LeftBottom] = std::move(field[Top][RightBottom]);
		field[Right][LeftBottom].surfacePartsModelTrans = transform1;

		field[Top][RightBottom] = std::move(element);
		field[Top][RightBottom].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[Right][RightBottom].surfacePartsModelTrans;
		transform2 = field[Top][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[Right][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Top][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[Right][RightBottom] = std::move(field[Top][LeftBottom]);
		field[Right][RightBottom].surfacePartsModelTrans = transform1;

		field[Top][LeftBottom] = std::move(element);
		field[Top][LeftBottom].surfacePartsModelTrans = transform2;

		break;

	case RightToLeft:

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Right][LeftTop].surfacePartsModelTrans;
		transform2 = field[Left][RightTop].surfacePartsModelTrans;
		element = std::move(field[Right][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[Right][LeftTop] = std::move(field[Left][RightTop]);
		field[Right][LeftTop].surfacePartsModelTrans = transform1;

		field[Left][RightTop] = std::move(element);
		field[Left][RightTop].surfacePartsModelTrans = transform2;

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[Right][RightTop].surfacePartsModelTrans;
		transform2 = field[Left][LeftTop].surfacePartsModelTrans;
		element = std::move(field[Right][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[Right][RightTop] = std::move(field[Left][LeftTop]);
		field[Right][RightTop].surfacePartsModelTrans = transform1;

		field[Left][LeftTop] = std::move(element);
		field[Left][LeftTop].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[Right][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Left][RightBottom].surfacePartsModelTrans;
		element = std::move(field[Right][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Left][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[Right][LeftBottom] = std::move(field[Left][RightBottom]);
		field[Right][LeftBottom].surfacePartsModelTrans = transform1;

		field[Left][RightBottom] = std::move(element);
		field[Left][RightBottom].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[Right][RightBottom].surfacePartsModelTrans;
		transform2 = field[Left][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[Right][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[Right][RightBottom] = std::move(field[Left][LeftBottom]);
		field[Right][RightBottom].surfacePartsModelTrans = transform1;

		field[Left][LeftBottom] = std::move(element);
		field[Left][LeftBottom].surfacePartsModelTrans = transform2;

		break;

	case RightToCenterRight:

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Right][LeftTop].surfacePartsModelTrans;
		transform2 = field[CenterRight][RightTop].surfacePartsModelTrans;
		element = std::move(field[Right][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[Right][LeftTop] = std::move(field[CenterRight][RightTop]);
		field[Right][LeftTop].surfacePartsModelTrans = transform1;

		field[CenterRight][RightTop] = std::move(element);
		field[CenterRight][RightTop].surfacePartsModelTrans = transform2;

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[Right][RightTop].surfacePartsModelTrans;
		transform2 = field[CenterRight][LeftTop].surfacePartsModelTrans;
		element = std::move(field[Right][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[Right][RightTop] = std::move(field[CenterRight][LeftTop]);
		field[Right][RightTop].surfacePartsModelTrans = transform1;

		field[CenterRight][LeftTop] = std::move(element);
		field[CenterRight][LeftTop].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[Right][LeftBottom].surfacePartsModelTrans;
		transform2 = field[CenterRight][RightBottom].surfacePartsModelTrans;
		element = std::move(field[Right][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[CenterRight][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[Right][LeftBottom] = std::move(field[CenterRight][RightBottom]);
		field[Right][LeftBottom].surfacePartsModelTrans = transform1;

		field[CenterRight][RightBottom] = std::move(element);
		field[CenterRight][RightBottom].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[Right][RightBottom].surfacePartsModelTrans;
		transform2 = field[CenterRight][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[Right][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[Right][RightBottom] = std::move(field[CenterRight][LeftBottom]);
		field[Right][RightBottom].surfacePartsModelTrans = transform1;

		field[CenterRight][LeftBottom] = std::move(element);
		field[CenterRight][LeftBottom].surfacePartsModelTrans = transform2;

		break;

	case RightToBottom:

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Right][LeftTop].surfacePartsModelTrans;
		transform2 = field[Bottom][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[Right][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[Right][LeftTop] = std::move(field[Bottom][LeftBottom]);
		field[Right][LeftTop].surfacePartsModelTrans = transform1;

		field[Bottom][LeftBottom] = std::move(element);
		field[Bottom][LeftBottom].surfacePartsModelTrans = transform2;

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[Right][RightTop].surfacePartsModelTrans;
		transform2 = field[Bottom][RightBottom].surfacePartsModelTrans;
		element = std::move(field[Right][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Bottom][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[Right][RightTop] = std::move(field[Bottom][RightBottom]);
		field[Right][RightTop].surfacePartsModelTrans = transform1;

		field[Bottom][RightBottom] = std::move(element);
		field[Bottom][RightBottom].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[Right][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Bottom][LeftTop].surfacePartsModelTrans;
		element = std::move(field[Right][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[Right][LeftBottom] = std::move(field[Bottom][LeftTop]);
		field[Right][LeftBottom].surfacePartsModelTrans = transform1;

		field[Bottom][LeftTop] = std::move(element);
		field[Bottom][LeftTop].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[Right][RightBottom].surfacePartsModelTrans;
		transform2 = field[Bottom][RightTop].surfacePartsModelTrans;
		element = std::move(field[Right][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[Right][RightBottom] = std::move(field[Bottom][RightTop]);
		field[Right][RightBottom].surfacePartsModelTrans = transform1;

		field[Bottom][RightTop] = std::move(element);
		field[Bottom][RightTop].surfacePartsModelTrans = transform2;

		break;

	default:
		break;
	}
}

void SurfaceFold::EndRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	field[Right][LeftTop].isDraw = true;
	field[Right][RightTop].isDraw = true;
	field[Right][LeftBottom].isDraw = true;
	field[Right][RightBottom].isDraw = true;

	switch (fieldIndex)
	{
	case RightToTop:

		field[Top][LeftTop].isDraw = true;
		field[Top][RightTop].isDraw = true;
		field[Top][LeftBottom].isDraw = true;
		field[Top][RightBottom].isDraw = true;

		break;

	case RightToLeft:

		field[Left][LeftTop].isDraw = true;
		field[Left][RightTop].isDraw = true;
		field[Left][LeftBottom].isDraw = true;
		field[Left][RightBottom].isDraw = true;

		break;

	case RightToCenterRight:

		field[CenterRight][LeftTop].isDraw = true;
		field[CenterRight][RightTop].isDraw = true;
		field[CenterRight][LeftBottom].isDraw = true;
		field[CenterRight][RightBottom].isDraw = true;

		break;

	case RightToBottom:

		field[Bottom][LeftTop].isDraw = true;
		field[Bottom][RightTop].isDraw = true;
		field[Bottom][LeftBottom].isDraw = true;
		field[Bottom][RightBottom].isDraw = true;

		break;

	default:
		break;
	}
}

void SurfaceFold::StartBottomTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	field[Bottom][LeftTop].isDraw = false;
	field[Bottom][RightTop].isDraw = false;
	field[Bottom][LeftBottom].isDraw = false;
	field[Bottom][RightBottom].isDraw = false;

	switch (fieldIndex)
	{
	case BottomToLeft:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Bottom][RightBottom].textureData);

		////���UV��]
		surfaceFoldFbxmodel_->rotationUV("Map03", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map01", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map04", 90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map02", 90.0f * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[Left][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Map07", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map05", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map08", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map06", 180.0f * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 180.0f * AliceMathF::Deg2Rad,90.0f * AliceMathF::Deg2Rad,0.0f * AliceMathF::Deg2Rad };

		field[Left][LeftTop].isDraw = false;
		field[Left][RightTop].isDraw = false;
		field[Left][LeftBottom].isDraw = false;
		field[Left][RightBottom].isDraw = false;

		break;

	case BottomToCenterLeft:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Bottom][RightBottom].textureData);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[CenterLeft][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Map07", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map05", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map08", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map06", 180.0f * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 180.0f * AliceMathF::Deg2Rad,0.0f * AliceMathF::Deg2Rad,0.0f * AliceMathF::Deg2Rad };

		field[CenterLeft][LeftTop].isDraw = false;
		field[CenterLeft][RightTop].isDraw = false;
		field[CenterLeft][LeftBottom].isDraw = false;
		field[CenterLeft][RightBottom].isDraw = false;

		break;

	case BottomToCenterRight:

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Bottom][RightBottom].textureData);

		//���UV��]
		surfaceFoldFbxmodel_->rotationUV("Map03", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map01", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map04", -90.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map02", -90.0f * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[CenterRight][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Map07", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map05", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map08", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map06", 180.0f * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 180.0f * AliceMathF::Deg2Rad,-90.0f * AliceMathF::Deg2Rad,0.0f * AliceMathF::Deg2Rad };

		field[CenterRight][LeftTop].isDraw = false;
		field[CenterRight][RightTop].isDraw = false;
		field[CenterRight][LeftBottom].isDraw = false;
		field[CenterRight][RightBottom].isDraw = false;

		break;
	case BottomToRight:

			//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Bottom][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Bottom][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Bottom][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Bottom][RightBottom].textureData);

		//���UV��]
		surfaceFoldFbxmodel_->rotationUV("Map03", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map01", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map04", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map02", 180.0f * AliceMathF::Deg2Rad);

		//�e�N�X�`�����Z�b�g
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, field[Right][RightBottom].textureData);

		//����UV��]
		surfaceFoldFbxmodel_->rotationUV("Map07", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map05", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map08", 180.0f * AliceMathF::Deg2Rad);
		surfaceFoldFbxmodel_->rotationUV("Map06", 180.0f * AliceMathF::Deg2Rad);

		fieldPlaneTrans_.rotation = { 180.0f * AliceMathF::Deg2Rad,180.0f * AliceMathF::Deg2Rad,0.0f * AliceMathF::Deg2Rad };

		field[Right][LeftTop].isDraw = false;
		field[Right][RightTop].isDraw = false;
		field[Right][LeftBottom].isDraw = false;
		field[Right][RightBottom].isDraw = false;

		break;

	default:
		break;
	}

}

void SurfaceFold::ReplaceBottomTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	FieldElement element;
	Transform transform1;
	Transform transform2;

	switch (fieldIndex)
	{
	case BottomToLeft:

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Bottom][LeftTop].surfacePartsModelTrans;
		transform2 = field[Left][LeftTop].surfacePartsModelTrans;
		element = std::move(field[Bottom][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Left][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[Bottom][LeftTop] = std::move(field[Left][LeftTop]);
		field[Bottom][LeftTop].surfacePartsModelTrans = transform1;

		field[Left][LeftTop] = std::move(element);
		field[Left][LeftTop].surfacePartsModelTrans = transform2;

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[Bottom][RightTop].surfacePartsModelTrans;
		transform2 = field[Left][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[Bottom][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Left][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[Bottom][RightTop] = std::move(field[Left][LeftBottom]);
		field[Bottom][RightTop].surfacePartsModelTrans = transform1;

		field[Left][LeftBottom] = std::move(element);
		field[Left][LeftBottom].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[Bottom][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Left][RightTop].surfacePartsModelTrans;
		element = std::move(field[Bottom][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Left][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[Bottom][LeftBottom] = std::move(field[Left][RightTop]);
		field[Bottom][LeftBottom].surfacePartsModelTrans = transform1;

		field[Left][RightTop] = std::move(element);
		field[Left][RightTop].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[Bottom][RightBottom].surfacePartsModelTrans;
		transform2 = field[Left][RightBottom].surfacePartsModelTrans;
		element = std::move(field[Bottom][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Left][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[Bottom][RightBottom] = std::move(field[Left][RightBottom]);
		field[Bottom][RightBottom].surfacePartsModelTrans = transform1;

		field[Left][RightBottom] = std::move(element);
		field[Left][RightBottom].surfacePartsModelTrans = transform2;

		break;

	case BottomToCenterLeft:

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Bottom][LeftTop].surfacePartsModelTrans;
		transform2 = field[CenterLeft][RightTop].surfacePartsModelTrans;
		element = std::move(field[Bottom][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[CenterLeft][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[Bottom][LeftTop] = std::move(field[CenterLeft][RightTop]);
		field[Bottom][LeftTop].surfacePartsModelTrans = transform1;

		field[CenterLeft][RightTop] = std::move(element);
		field[CenterLeft][RightTop].surfacePartsModelTrans = transform2;

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[Bottom][RightTop].surfacePartsModelTrans;
		transform2 = field[CenterLeft][LeftTop].surfacePartsModelTrans;
		element = std::move(field[Bottom][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[CenterLeft][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[Bottom][RightTop] = std::move(field[CenterLeft][LeftTop]);
		field[Bottom][RightTop].surfacePartsModelTrans = transform1;

		field[CenterLeft][LeftTop] = std::move(element);
		field[CenterLeft][LeftTop].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[Bottom][LeftBottom].surfacePartsModelTrans;
		transform2 = field[CenterLeft][RightBottom].surfacePartsModelTrans;
		element = std::move(field[Bottom][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[CenterLeft][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[Bottom][LeftBottom] = std::move(field[CenterLeft][RightBottom]);
		field[Bottom][LeftBottom].surfacePartsModelTrans = transform1;

		field[CenterLeft][RightBottom] = std::move(element);
		field[CenterLeft][RightBottom].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[Bottom][RightBottom].surfacePartsModelTrans;
		transform2 = field[CenterLeft][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[Bottom][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[CenterLeft][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[Bottom][RightBottom] = std::move(field[CenterLeft][LeftBottom]);
		field[Bottom][RightBottom].surfacePartsModelTrans = transform1;

		field[CenterLeft][LeftBottom] = std::move(element);
		field[CenterLeft][LeftBottom].surfacePartsModelTrans = transform2;

		break;

	case BottomToCenterRight:

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Bottom][LeftTop].surfacePartsModelTrans;
		transform2 = field[CenterRight][RightBottom].surfacePartsModelTrans;
		element = std::move(field[Bottom][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[CenterRight][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[Bottom][LeftTop] = std::move(field[CenterRight][RightBottom]);
		field[Bottom][LeftTop].surfacePartsModelTrans = transform1;

		field[CenterRight][RightBottom] = std::move(element);
		field[CenterRight][RightBottom].surfacePartsModelTrans = transform2;

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[Bottom][RightTop].surfacePartsModelTrans;
		transform2 = field[CenterRight][RightTop].surfacePartsModelTrans;
		element = std::move(field[Bottom][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[CenterRight][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[Bottom][RightTop] = std::move(field[CenterRight][RightTop]);
		field[Bottom][RightTop].surfacePartsModelTrans = transform1;

		field[CenterRight][RightTop] = std::move(element);
		field[CenterRight][RightTop].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[Bottom][LeftBottom].surfacePartsModelTrans;
		transform2 = field[CenterRight][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[Bottom][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[CenterRight][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[Bottom][LeftBottom] = std::move(field[CenterRight][LeftBottom]);
		field[Bottom][LeftBottom].surfacePartsModelTrans = transform1;

		field[CenterRight][LeftBottom] = std::move(element);
		field[CenterRight][LeftBottom].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[Bottom][RightBottom].surfacePartsModelTrans;
		transform2 = field[CenterRight][LeftTop].surfacePartsModelTrans;
		element = std::move(field[Bottom][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[CenterRight][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[Bottom][RightBottom] = std::move(field[CenterRight][LeftTop]);
		field[Bottom][RightBottom].surfacePartsModelTrans = transform1;

		field[CenterRight][LeftTop] = std::move(element);
		field[CenterRight][LeftTop].surfacePartsModelTrans = transform2;

		break;

	case BottomToRight:

		//4�Ԃ�6�Ԃ����ւ���
		transform1 = field[Bottom][LeftTop].surfacePartsModelTrans;
		transform2 = field[Right][LeftBottom].surfacePartsModelTrans;
		element = std::move(field[Bottom][LeftTop]);

		surfaceFoldFbxmodel_->TransTexture("Map04", 0, field[Right][LeftBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map06", 0, element.textureData);

		field[Bottom][LeftTop] = std::move(field[Right][LeftBottom]);
		field[Bottom][LeftTop].surfacePartsModelTrans = transform1;

		field[Right][LeftBottom] = std::move(element);
		field[Right][LeftBottom].surfacePartsModelTrans = transform2;

		//3�Ԃ�5�Ԃ����ւ���
		transform1 = field[Bottom][RightTop].surfacePartsModelTrans;
		transform2 = field[Right][RightBottom].surfacePartsModelTrans;
		element = std::move(field[Bottom][RightTop]);

		surfaceFoldFbxmodel_->TransTexture("Map03", 0, field[Right][RightBottom].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map05", 0, element.textureData);

		field[Bottom][RightTop] = std::move(field[Right][RightBottom]);
		field[Bottom][RightTop].surfacePartsModelTrans = transform1;

		field[Right][RightBottom] = std::move(element);
		field[Right][RightBottom].surfacePartsModelTrans = transform2;

		//2�Ԃ�8�Ԃ����ւ���
		transform1 = field[Bottom][LeftBottom].surfacePartsModelTrans;
		transform2 = field[Right][LeftTop].surfacePartsModelTrans;
		element = std::move(field[Bottom][LeftBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map02", 0, field[Right][LeftTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map08", 0, element.textureData);

		field[Bottom][LeftBottom] = std::move(field[Right][LeftTop]);
		field[Bottom][LeftBottom].surfacePartsModelTrans = transform1;

		field[Right][LeftTop] = std::move(element);
		field[Right][LeftTop].surfacePartsModelTrans = transform2;

		//1�Ԃ�7�Ԃ����ւ���
		transform1 = field[Bottom][RightBottom].surfacePartsModelTrans;
		transform2 = field[Right][RightTop].surfacePartsModelTrans;
		element = std::move(field[Bottom][RightBottom]);

		surfaceFoldFbxmodel_->TransTexture("Map01", 0, field[Right][RightTop].textureData);
		surfaceFoldFbxmodel_->TransTexture("Map07", 0, element.textureData);

		field[Bottom][RightBottom] = std::move(field[Right][RightTop]);
		field[Bottom][RightBottom].surfacePartsModelTrans = transform1;

		field[Right][RightTop] = std::move(element);
		field[Right][RightTop].surfacePartsModelTrans = transform2;

		break;

	default:
		break;
	}
}

void SurfaceFold::EndBottomTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	field[Bottom][LeftTop].isDraw = true;
	field[Bottom][RightTop].isDraw = true;
	field[Bottom][LeftBottom].isDraw = true;
	field[Bottom][RightBottom].isDraw = true;

	switch (fieldIndex)
	{
	case BottomToLeft:

		field[Left][LeftTop].isDraw = true;
		field[Left][RightTop].isDraw = true;
		field[Left][LeftBottom].isDraw = true;
		field[Left][RightBottom].isDraw = true;

		break;

	case BottomToCenterLeft:

		field[CenterLeft][LeftTop].isDraw = true;
		field[CenterLeft][RightTop].isDraw = true;
		field[CenterLeft][LeftBottom].isDraw = true;
		field[CenterLeft][RightBottom].isDraw = true;

		break;

	case BottomToCenterRight:

		field[CenterRight][LeftTop].isDraw = true;
		field[CenterRight][RightTop].isDraw = true;
		field[CenterRight][LeftBottom].isDraw = true;
		field[CenterRight][RightBottom].isDraw = true;

		break;

	case BottomToRight:

		field[Right][LeftTop].isDraw = true;
		field[Right][RightTop].isDraw = true;
		field[Right][LeftBottom].isDraw = true;
		field[Right][RightBottom].isDraw = true;

		break;

	default:
		break;
	}
}


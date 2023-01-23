#include "SurfaceFold.h"
#include "SurfaceFoldTop2.h"
#include "SurfaceFoldLeft2.h"
#include "SurfaceFoldCenterLeft2.h"
#include "SurfaceFoldCenterRight2.h"
#include "SurfaceFoldRight2.h"
#include "SurfaceFoldBottom2.h"

void SurfaceFold::Initialize()
{
	//面折りモデル
	surfaceFoldFbxmodel_ = std::make_unique<fbxModel>();
	surfaceFoldFbxmodel_->Initialize();
	surfaceFoldFbxmodel_->Create("Resources/SurfaceFold/FBX 2013", false, false, true, false);
	surfaceFoldFbxmodelAnime_ = std::make_unique<fbxAnimation>();
	FbxLoader::GetInstance()->LoadAnimation(surfaceFoldFbxmodelAnime_.get(), "Resources/SurfaceFold/FBX 2013", "");


	fieldPlaneTrans_.Initialize();
	fieldPlaneTrans_.scale = { 0.4f,0.4f ,0.4f };
	fieldPlaneTrans_.translation = { 0,-10,0 };
}

void SurfaceFold::Start(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, float standardAngle)
{
	surfaceFoldFbxmodel_->InitializeVertex();

	shrinkAnimeFlag_ = true;

	scale_ = 40.0f;
}

void SurfaceFold::Update(Camera* camera, std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, bool& fieldPlaneDrawFlag)
{
	if (shrinkAnimeFlag_)
	{
		scale_ -= 4.0f;

		if (scale_ <= 0.1f)
		{
			shrinkAnimeFlag_ = false;
			scale_ = 0.1f;
			fieldPlaneDrawFlag = true;

			//入れ替える準備
			FoldPreparation(field, fieldIndex);

			replaceAnimeFlag_ = true;
		}

		//縮むアニメーション
		ExtendShrinkAnime(field, fieldIndex);

	}

	if (replaceAnimeFlag_)
	{

		fieldPlaneAnimeFlam_ += 0.02f;

		fieldPlaneTrans_.TransUpdate(camera);

		if (surfaceFoldFbxmodelAnime_->GetTickTimes(fieldPlaneAnimeFlam_) >= surfaceFoldFbxmodelAnime_->GetAnimeMaxflame() / 2 && !fieldReplaceFlag_)
		{
			//入れ替え
			Replace(field, fieldIndex);
			fieldReplaceFlag_ = true;
		}

		if (surfaceFoldFbxmodelAnime_->GetTickTimes(fieldPlaneAnimeFlam_) >= surfaceFoldFbxmodelAnime_->GetAnimeMaxflame())
		{
			fieldPlaneDrawFlag = false;
			extendAnimeFlag_ = true;
			replaceAnimeFlag_ = false;

			//後処理
			FoldEnd(field, fieldIndex);
		}

		//FBXアニメーションアップデート
		surfaceFoldFbxmodel_->AnimationUpdate(surfaceFoldFbxmodelAnime_.get(), fieldPlaneAnimeFlam_);
	}

	if (extendAnimeFlag_)
	{
		scale_ += 4.0f;

		if (scale_ >= 40.0f)
		{
			scale_ = 40.0f;
			extendAnimeFlag_ = false;
			animeEnd = true;
		}

		//伸びるアニメーション
		ExtendShrinkAnime(field, fieldIndex);
	}

	if (animeEnd)
	{
		fieldPlaneAnimeFlam_ = 0.0f;
		fieldReplaceFlag_ = false;
		animeEnd = false;
	}
}

void SurfaceFold::Replace(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	switch (fieldIndex)
	{
	case TopToLeft:
	case TopToCenterLeft:
	case TopToCenterRight:
	case TopToRight:

		SurfaceFoldTop2::ReplaceTopTo(field, fieldIndex, fieldPlaneTrans_, surfaceFoldFbxmodel_.get());

		break;

	case LeftToTop:
	case LeftToCenterLeft:
	case LeftToRight:
	case LeftToBottom:

		SurfaceFoldLeft2::ReplaceLeftTo(field, fieldIndex, fieldPlaneTrans_, surfaceFoldFbxmodel_.get());

		break;

	case CenterLeftToTop:
	case CenterLeftToLeft:
	case CenterLeftToCenterRight:
	case CenterLeftToBottom:

		SurfaceFoldCenterLeft2::ReplaceCenterLeftTo(field, fieldIndex, fieldPlaneTrans_, surfaceFoldFbxmodel_.get());

		break;

	case CenterRightToTop:
	case CenterRightToCenterLeft:
	case CenterRightToRight:
	case CenterRightToBottom:

		SurfaceFoldCenterRight2::ReplaceCenterRightTo(field, fieldIndex, fieldPlaneTrans_, surfaceFoldFbxmodel_.get());
		break;

	case RightToTop:
	case RightToLeft:
	case RightToCenterRight:
	case RightToBottom:

		SurfaceFoldRight2::ReplaceRightTo(field, fieldIndex, fieldPlaneTrans_, surfaceFoldFbxmodel_.get());

		break;

	case BottomToLeft:
	case BottomToCenterLeft:
	case BottomToCenterRight:
	case BottomToRight:

		SurfaceFoldBottom2::ReplaceBottomTo(field, fieldIndex, fieldPlaneTrans_, surfaceFoldFbxmodel_.get());

		break;

	default:
		break;
	}
}

void SurfaceFold::Draw()
{
	surfaceFoldFbxmodel_->Draw(&fieldPlaneTrans_);
}

void SurfaceFold::ExtendShrinkAnime(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	switch (fieldIndex)
	{
	case TopToLeft:
	case TopToCenterLeft:
	case TopToCenterRight:
	case TopToRight:

		SurfaceFoldTop2::ShrinkAnimeTopTo(field, fieldIndex, scale_);

		break;

	case LeftToTop:
	case LeftToCenterLeft:
	case LeftToRight:
	case LeftToBottom:

		SurfaceFoldLeft2::ShrinkAnimeLeftTo(field, fieldIndex, scale_);
		break;

	case CenterLeftToTop:
	case CenterLeftToLeft:
	case CenterLeftToCenterRight:
	case CenterLeftToBottom:

		SurfaceFoldCenterLeft2::ShrinkAnimeCenterLeftTo(field, fieldIndex, scale_);
		break;

	case CenterRightToTop:
	case CenterRightToCenterLeft:
	case CenterRightToRight:
	case CenterRightToBottom:

		SurfaceFoldCenterRight2::ShrinkAnimeCenterRightTo(field, fieldIndex, scale_);
		break;

	case RightToTop:
	case RightToLeft:
	case RightToCenterRight:
	case RightToBottom:

		SurfaceFoldRight2::ShrinkAnimeRightTo(field, fieldIndex, scale_);
		break;

	case BottomToLeft:
	case BottomToCenterLeft:
	case BottomToCenterRight:
	case BottomToRight:

		SurfaceFoldBottom2::ShrinkAnimeBottomTo(field, fieldIndex, scale_);
		break;

	default:
		break;
	}
}

void SurfaceFold::FoldPreparation(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	switch (fieldIndex)
	{
	case TopToLeft:
	case TopToCenterLeft:
	case TopToCenterRight:
	case TopToRight:

		SurfaceFoldTop2::StartTopTo(field, fieldIndex, fieldPlaneTrans_, surfaceFoldFbxmodel_.get());
		break;

	case LeftToTop:
	case LeftToCenterLeft:
	case LeftToRight:
	case LeftToBottom:

		SurfaceFoldLeft2::StartLeftTo(field, fieldIndex, fieldPlaneTrans_, surfaceFoldFbxmodel_.get());

		break;

	case CenterLeftToTop:
	case CenterLeftToLeft:
	case CenterLeftToCenterRight:
	case CenterLeftToBottom:

		SurfaceFoldCenterLeft2::StartCenterLeftTo(field, fieldIndex, fieldPlaneTrans_, surfaceFoldFbxmodel_.get());

		break;

	case CenterRightToTop:
	case CenterRightToCenterLeft:
	case CenterRightToRight:
	case CenterRightToBottom:

		SurfaceFoldCenterRight2::StartCenterRightTo(field, fieldIndex, fieldPlaneTrans_, surfaceFoldFbxmodel_.get());

		break;

	case RightToTop:
	case RightToLeft:
	case RightToCenterRight:
	case RightToBottom:

		SurfaceFoldRight2::StartRightTo(field, fieldIndex, fieldPlaneTrans_, surfaceFoldFbxmodel_.get());

		break;

	case BottomToLeft:
	case BottomToCenterLeft:
	case BottomToCenterRight:
	case BottomToRight:

		SurfaceFoldBottom2::StartBottomTo(field, fieldIndex, fieldPlaneTrans_, surfaceFoldFbxmodel_.get());

		break;

	default:
		break;
	}
}

void SurfaceFold::FoldEnd(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex)
{
	switch (fieldIndex)
	{
	case TopToLeft:
	case TopToCenterLeft:
	case TopToCenterRight:
	case TopToRight:

		SurfaceFoldTop2::EndTopTo(field, fieldIndex);

		break;

	case LeftToTop:
	case LeftToCenterLeft:
	case LeftToRight:
	case LeftToBottom:

		SurfaceFoldLeft2::EndLeftTo(field, fieldIndex);
		break;

	case CenterLeftToTop:
	case CenterLeftToLeft:
	case CenterLeftToCenterRight:
	case CenterLeftToBottom:

		SurfaceFoldCenterLeft2::EndCenterLeftTo(field, fieldIndex);
		break;

	case CenterRightToTop:
	case CenterRightToCenterLeft:
	case CenterRightToRight:
	case CenterRightToBottom:

		SurfaceFoldCenterRight2::EndCenterRightTo(field, fieldIndex);
		break;

	case RightToTop:
	case RightToLeft:
	case RightToCenterRight:
	case RightToBottom:

		SurfaceFoldRight2::EndRightTo(field, fieldIndex);
		break;

	case BottomToLeft:
	case BottomToCenterLeft:
	case BottomToCenterRight:
	case BottomToRight:

		SurfaceFoldBottom2::EndBottomTo(field, fieldIndex);

		break;

	default:
		break;
	}
}
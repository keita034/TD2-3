#pragma once
#include"SurfaceFold.h"

class SurfaceFoldRight2
{
public:
	static void StartRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, fbxModel* surfaceFoldFbxmodel_);

	static void ShrinkAnimeRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, float scale);

	static void ReplaceRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, fbxModel* surfaceFoldFbxmodel_);

	static void EndRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);
};



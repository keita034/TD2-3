#pragma once
#include"SurfaceFold.h"

class SurfaceFoldBottom2
{
public:
	static void StartBottomTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, fbxModel* surfaceFoldFbxmodel_);

	static void ShrinkAnimeBottomTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, float scale);

	static void ReplaceBottomTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, fbxModel* surfaceFoldFbxmodel_);

	static void EndBottomTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);


};


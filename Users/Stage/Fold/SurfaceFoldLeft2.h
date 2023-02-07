#pragma once
#include"SurfaceFold.h"

class SurfaceFoldLeft2
{
public:
	static void StartLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, AliceModel* surfaceFoldFbxmodel_);

	static void ShrinkAnimeLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, float scale);

	static void ReplaceLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, AliceModel* surfaceFoldFbxmodel_);

	static void EndLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);
};


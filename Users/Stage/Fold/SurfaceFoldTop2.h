#pragma once
#include "SurfaceFold.h"

class SurfaceFoldTop2
{
public:
	static void StartTopTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex,Transform& fieldPlaneTrans_, AliceModel* surfaceFoldFbxmodel_);

	static void ShrinkAnimeTopTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, float scale);

	static void ReplaceTopTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, AliceModel* surfaceFoldFbxmodel_);

	static void EndTopTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);
};


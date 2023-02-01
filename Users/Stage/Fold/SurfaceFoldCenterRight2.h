#pragma once
#include"SurfaceFold.h"

class SurfaceFoldCenterRight2
{
public:
	static void StartCenterRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, fbxModel* surfaceFoldFbxmodel_);

	static void ShrinkAnimeCenterRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, float scale);

	static void ReplaceCenterRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, fbxModel* surfaceFoldFbxmodel_);

	static void EndCenterRightTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);
};


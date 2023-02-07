#pragma once
#include"SurfaceFold.h"

class SurfaceFoldCenterLeft2
{
public:
	static void StartCenterLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, AliceModel* surfaceFoldFbxmodel_);

	static void ShrinkAnimeCenterLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, float scale);

	static void ReplaceCenterLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, Transform& fieldPlaneTrans_, AliceModel* surfaceFoldFbxmodel_);

	static void EndCenterLeftTo(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex);
};


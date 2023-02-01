#include "FieldConstant.h"

void FieldElement::Draw()
{
	if (isDraw)
	{
		surfacePartsModel->Draw(surfacePartsModelTrans);
	}
}

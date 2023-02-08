#include "ChangeCollider.h"
#include "MeshCollider.h"
#include "CollisionAttribute.h"
#include "CollisionManager.h"


void SetCollider(std::array<std::array<FieldElement, 4>, 6>& field, FieldIndex fieldIndex, FieldElementIndex fieldElementIndex, int changeNumber)
{
	// コリジョンマネージャに追加
	MeshCollider* meshCollider = new MeshCollider;
	CollisionManager::GetInstance()->ChangeCollider(changeNumber, meshCollider);
	meshCollider->Update(field[fieldIndex][fieldElementIndex].surfacePartsModelTrans.matWorld);
	meshCollider->ConstructTriangles(field[fieldIndex][fieldElementIndex].surfacePartsModel, field[fieldIndex][fieldElementIndex].surfacePartsModelTrans.matWorld);
	meshCollider->SetAttribute(COLLISION_ATTR_LANDSHAPE);
}

#include "MeshCollider.h"
#include "Collision.h"

using namespace DirectX;

void MeshCollider::ConstructTriangles(Model* model)
{
	triangles.clear();

	const std::vector<Mesh*>& meshes = model->GetMeshes();

	int start = 0;

	std::vector<Mesh*>::const_iterator it = meshes.cbegin();
	for (; it != meshes.cend(); ++it) {
		Mesh* mesh = *it;
		const std::vector<Mesh::VertexPosNormalUv>& vertices = mesh->GetVertices();
		const std::vector<unsigned short>& indices = mesh->GetIndices();

		size_t triangleNum = indices.size() / 3;

		triangles.resize(triangles.size() + triangleNum);

		for (int i = 0; i < triangleNum; i++) {

			Triangle& tri = triangles[start + i];
			int idx0 = indices[i * 3 + 0];
			int idx1 = indices[i * 3 + 1];
			int idx2 = indices[i * 3 + 2];

			tri.p0 = {
				vertices[idx0].pos.x,
				vertices[idx0].pos.y,
				vertices[idx0].pos.z,
				1 };

			tri.p1 = {
				vertices[idx1].pos.x,
				vertices[idx1].pos.y,
				vertices[idx1].pos.z,
				1 };

			tri.p2 = {
				vertices[idx2].pos.x,
				vertices[idx2].pos.y,
				vertices[idx2].pos.z,
				1 };

			tri.ComputeNormal();
		}
	}
}

void MeshCollider::Update(const AliceMathF::Matrix4& worldPos)
{
	AliceMathF::Matrix4 tmp = AliceMathF::MakeIdentity();
	invMatWorld = AliceMathF::MakeInverse(&tmp);
}

bool MeshCollider::CheckCollisionSphere(const Sphere& sphere, AliceMathF::Vector4* inter, AliceMathF::Vector4* reject)
{
	// オブジェクトのローカル座標系での球を得る（半径はXスケールを参照)
	Sphere localSphere;
	localSphere.center = AliceMathF::Vec4Mat4Mul( sphere.center, invMatWorld);
	localSphere.radius *= AliceMathF::Vector4(invMatWorld.m[0][0], invMatWorld.m[0][1], invMatWorld.m[0][2], invMatWorld.m[0][3]).Vector3Length();

	std::vector<Triangle>::const_iterator it = triangles.cbegin();

	for (; it != triangles.cend(); ++it) {
		const Triangle& triangle = *it;

		if (Collision::CheckSphere2Triangle(localSphere, triangle, inter,reject)) {
			if (inter) {
				const AliceMathF::Matrix4& matWorld = XMMatrixIdentity();

				*inter = AliceMathF::Vec4Mat4Mul(*inter, matWorld);
			}
			if (reject) {
				const AliceMathF::Matrix4& matWorld = XMMatrixIdentity();
				//ワールド座標系で排斥ベクトルに変換
				*reject = AliceMathF::Vec4Mat4Mul(*reject, matWorld);
			}
			return true;
		}
	}

	return false;
}

bool MeshCollider::CheckCollisionRay(const Ray& ray, float* distance, AliceMathF::Vector4* inter)
{
	// オブジェクトのローカル座標系でのレイを得る
	Ray localRay;
	localRay.start = AliceMathF::Vec4Mat4Mul(ray.start, invMatWorld);
	localRay.dir = AliceMathF::Vec4Mat4Mul(ray.dir, invMatWorld).Vector3Normal();

	std::vector<Triangle>::const_iterator it = triangles.cbegin();

	for (; it != triangles.cend(); ++it) {
		const Triangle& triangle = *it;

		AliceMathF::Vector4 tempInter;

		if (Collision::CheckRay2Triangle(localRay, triangle, nullptr, &tempInter)) {

			const AliceMathF::Matrix4& matWorld = AliceMathF::MakeIdentity();

			tempInter = AliceMathF::Vec4Mat4Mul(tempInter, matWorld);

			if (distance) {
				AliceMathF::Vector4 sub = tempInter - ray.start;
				*distance = sub.Vector3Dot(ray.dir);
			}

			if (inter) {
				*inter = tempInter;
			}

			return true;
		}
	}

	return false;
}

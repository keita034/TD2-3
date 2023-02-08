#pragma once
#include"ErrorException.h"
#include"AliceModel.h"
#include"AliceFunctionUtility.h"

class AliceFileStream
{

	static std::string buff;

	static std::istringstream lineData;

	static char buffC[256];

	static std::string directoryPath;
public:
	static bool LoadAlicePolygonData(const std::string& path, AliceModelData* model);

	static bool LoadAlicePolygonBinaryData(const std::string& path, AliceModelData* model);

	static bool LoadAliceMotionBinaryData(const std::string& path, MotionData* motion);
	

private:
	static void ReadModelData(std::stringstream& data, std::string& str, AliceModelData* model);

	static void ReadMeshsData(std::stringstream& data, std::string& str, AliceModelData* model);

	static void ReadMeshData(std::stringstream& data, std::string& str, ModelMesh& mesh, std::vector<Node>& nodes);

	static void ReadHesderData(std::stringstream& data, std::string& str, AliceModelData* model);

	static void ReadMatrix(const std::string& strMat,AliceMathF::Matrix4& mat);

	static void ReadString(const std::string& strData, std::string& str);

	static void ReadFlag(const std::string& strFlag, bool& flag);

	static void ReadNumber(const std::string& strNum, float& num);
	static void ReadNumber(const std::string& strNum, uint32_t& num);

	static void ReadVertex(const std::string& strVer, PosNormUvTangeColSkin& ver);

	static void ReadVector3(const std::string& strVec, AliceMathF::Vector3& ver);
	static void ReadVector3(const std::string& strVec, AliceMathF::Vector4& ver);

	static void ReadVector2(const std::string& strVec, AliceMathF::Vector2& ver);

	static void ReadVector4(const std::string& strVec, AliceMathF::Vector4& ver);

	static float Atof(const std::string& str);

	static void ReadBoneIndex(const std::string& strInd, std::array<UINT, MAX_BONE_INDICES>& boneIndex);

	static void ReadBoneWeight(const std::string& strWei, std::array<float, MAX_BONE_INDICES>& boneWeight);

	static void ReadBoneData(const std::string& strbone, Bone& bone, ModelMesh* model);

	static void ReadMaterial(const std::string& strMate, ModelMaterial& modelMaterial);

	static void ReadNodesData(std::stringstream& data, std::string& str, AliceModelData* model);

	static void ReadNodeData(std::stringstream& data, std::string& str, Node& node, AliceModelData* model);

	static void ReadParentData(const std::string& name, Node& node, std::vector<Node>& nodes);

	static bool ReadHesderBinaryData(AliceModelData* model, FILE* fp);

	static bool ReadNodesBinaryData(AliceModelData* model, FILE* fp);

	static bool ReadMeshBinaryData(AliceModelData* model, FILE* fp);

	static bool ReadMotionNodeBinaryData(MotionNode* node, FILE* fp);
};


#include "AliceFileStream.h"
#include "TextureManager.h"

std::string AliceFileStream::buff;
std::string AliceFileStream::directoryPath;
std::istringstream AliceFileStream::lineData;
char  AliceFileStream::buffC[256];


bool AliceFileStream::LoadAlicePolygonData(const std::string& path, AliceModelData* model)
{
	//モデルデータ
	std::stringstream modelData;
	//1行分も文字列を入れる変数
	std::string line;

	//ファイルを開く
	std::ifstream file(path);
	if (file.fail())
	{
		return false;
	}

	//ファイルの内容を文字列をストリームにコピー
	modelData << file.rdbuf();

	//ファイルを閉じる
	file.close();

	//一行取得
	getline(modelData, line, '\n');

	if (line == "<MODEL>")
	{
		ReadModelData(modelData, line, model);
	}

	return true;
}

void AliceFileStream::ReadModelData(std::stringstream& data, std::string& str, AliceModelData* model)
{
	//1行分の文字列を入れる変数
	std::string line;

	//一行取得
	while (getline(data, line, '\n'))
	{
		if (line == "")
		{
			continue;
		}

		if (str == line)
		{
			return;
		}

		if (line == "<HEADER>")
		{
			ReadHesderData(data, line, model);
		}

		if (line == "<NODES>")
		{
			ReadNodesData(data, line, model);
		}

		if (line == "<MESHS>")
		{
			ReadMeshsData(data, line, model);
		}

	}

}

void AliceFileStream::ReadMeshsData(std::stringstream& data, std::string& str, AliceModelData* model)
{
	//1行分の文字列を入れる変数
	std::string line;

	//一行取得
	while (getline(data, line, '\n'))
	{
		if (line == "")
		{
			continue;
		}

		std::istringstream stream(line);

		for (size_t i = 0; i < model->meshes.size(); i++)
		{
			ReadMeshData(data, line, model->meshes[i], model->nodes);
		}

		if (str == line)
		{
			return;
		}
	}

}

void AliceFileStream::ReadMeshData(std::stringstream& data, std::string& str, ModelMesh& mesh, std::vector<Node>& nodes)
{
	//1行分の文字列を入れる変数
	std::string line;

	//一行取得
	while (getline(data, line, '\n'))
	{
		std::istringstream stream(line);


		if (line == "")
		{
			continue;
		}

		if (std::equal(line.begin(), line.end(), ""))
		{
			continue;
		}

		if (str == line)
		{
			getline(data, line, '\n');
			getline(data, str, '\n');
			return;
		}

		getline(stream, line, ':');

		if (std::equal(line.begin(), line.end(), "Name"))
		{
			getline(stream, line, ':');

			ReadString(line, mesh.name);

			continue;
		}

		if (std::equal(line.begin(), line.end(), "NodeName"))
		{
			getline(stream, line, ':');

			ReadString(line, mesh.nodeName);

			std::vector<Node>::iterator itr;
			itr = std::find_if(nodes.begin(), nodes.end(), [&](Node& p)
				{
					return p.name == mesh.nodeName;
				});

			if (itr != nodes.end())
			{
				mesh.node = &*itr;
				continue;
			}
			else
			{
				mesh.node = nullptr;
			}

			continue;
		}

		if (std::equal(line.begin(), line.end(), "VertexNum"))
		{
			getline(stream, line, ':');

			float vertexNum;
			ReadNumber(line, vertexNum);
			mesh.vertices.resize(vertexNum);

			for (size_t i = 0; i < mesh.vertices.size(); i++)
			{
				getline(data, line, '\n');
				line = line.substr(8, line.size() - 9);

				ReadVertex(line, mesh.vertices[i]);
			}

			continue;
		}

		if (std::equal(line.begin(), line.end(), "IndexNum"))
		{
			getline(stream, line, ':');

			float indexNum;
			ReadNumber(line, indexNum);
			mesh.indices.resize(indexNum);

			for (size_t i = 0; i < mesh.indices.size(); i++)
			{
				getline(data, line, '\n');
				line = line.substr(6, line.size() - 6);

				ReadNumber(line, mesh.indices[i]);
			}

			continue;
		}

		if (std::equal(line.begin(), line.end(), "TextureNum"))
		{
			getline(stream, line, ':');

			float textureNum;
			ReadNumber(line, textureNum);
			mesh.textures.resize(textureNum);

			for (size_t i = 0; i < mesh.textures.size(); i++)
			{
				getline(data, line, '\n');
				line = line.substr(8, line.size() - 8);

				std::string filepath;
				ReadString(line, filepath);

				mesh.textures[i] = TextureManager::GetTextureData(TextureManager::Load(filepath));
			}

			continue;
		}

		if (std::equal(line.begin(), line.end(), "TextureNormalNum"))
		{
			getline(stream, line, ':');

			float texturesNormalNum;
			ReadNumber(line, texturesNormalNum);
			mesh.texturesNormal.resize(texturesNormalNum);

			for (size_t i = 0; i < mesh.texturesNormal.size(); i++)
			{
				getline(data, line, '\n');
				line = line.substr(14, line.size() - 14);

				std::string filepath;
				ReadString(line, filepath);

				mesh.texturesNormal[i] = TextureManager::GetTextureData(TextureManager::Load(filepath));
			}

			continue;
		}

		if (std::equal(line.begin(), line.end(), "BoneNum"))
		{
			getline(stream, line, ':');

			float boneNum;
			ReadNumber(line, boneNum);
			mesh.vecBones.resize(boneNum);

			for (size_t i = 0; i < mesh.vecBones.size(); i++)
			{
				getline(data, line, '\n');
				line = line.substr(6, line.size() - 7);

				ReadBoneData(line, mesh.vecBones[i], &mesh);
			}

			continue;
		}

		if (std::equal(line.begin(), line.end(), "Material"))
		{
			getline(stream, line, ':');

			line = line.substr(1, line.size() - 2);

			ReadMaterial(line, mesh.material);

		}
	}
}

void AliceFileStream::ReadHesderData(std::stringstream& data, std::string& str, AliceModelData* model)
{
	//1行分の文字列を入れる変数
	std::string line;

	//一行取得
	while (getline(data, line, '\n'))
	{
		if (line == "")
		{
			continue;
		}
		std::istringstream stream(line);

		if (str == stream.str())
		{
			return;
		}

		getline(stream, line, ':');

		if (std::equal(line.begin(), line.end(), "Name"))
		{
			getline(stream, line, ':');

			ReadString(line, model->name);

			continue;
		}

		if (std::equal(line.begin(), line.end(), "CanAnimation"))
		{
			getline(stream, line, '\n');
			ReadFlag(line, model->canAnimation);
			continue;
		}

		if (std::equal(line.begin(), line.end(), "IsAnime"))
		{
			getline(stream, line, '\n');
			ReadFlag(line, model->IsAnime);
			continue;
		}

		if (std::equal(line.begin(), line.end(), "GlobalInverseTransform"))
		{
			getline(stream, line, ':');
			ReadMatrix(line, model->globalInverseTransform);
			continue;
		}

		if (std::equal(line.begin(), line.end(), "NodeNun"))
		{
			getline(stream, line, ':');

			float nodeNun;
			ReadNumber(line, nodeNun);
			model->nodes.resize(nodeNun);
			continue;
		}

		if (std::equal(line.begin(), line.end(), "MeshNum"))
		{
			getline(stream, line, ':');

			float meshNum;
			ReadNumber(line, meshNum);
			model->meshes.resize(meshNum);
			continue;
		}
	}
}

void AliceFileStream::ReadVertex(const std::string& strVer, PosNormUvTangeColSkin& ver)
{
	std::istringstream stream(strVer);
	std::string str;

	getline(stream, str, '|');
	ReadVector3(str, ver.position);

	getline(stream, str, '|');
	ReadVector3(str, ver.normal);

	getline(stream, str, '|');
	ReadVector2(str, ver.uv);

	getline(stream, str, '|');
	ReadVector3(str, ver.tangent);

	getline(stream, str, '|');
	ReadVector4(str, ver.color);

	getline(stream, str, '|');
	ReadBoneIndex(str, ver.boneIndex);

	getline(stream, str, '|');
	ReadBoneWeight(str, ver.boneWeight);
}

void AliceFileStream::ReadMaterial(const std::string& strMate, ModelMaterial& modelMaterial)
{
	std::istringstream stream(strMate);
	std::string str;

	getline(stream, str, '|');
	ReadString(str, modelMaterial.name);

	getline(stream, str, '|');
	ReadVector3(str, modelMaterial.ambient);

	getline(stream, str, '|');
	ReadVector3(str, modelMaterial.diffuse);

	getline(stream, str, '|');
	ReadVector3(str, modelMaterial.specular);

	getline(stream, str, '|');
	ReadVector3(str, modelMaterial.emission);

	getline(stream, str, '|');
	ReadNumber(str, modelMaterial.shininess);

	getline(stream, str, '|');
	ReadNumber(str, modelMaterial.alpha);

	getline(stream, str, '|');
	ReadString(str, modelMaterial.textureFiename);
}

void AliceFileStream::ReadNodesData(std::stringstream& data, std::string& str, AliceModelData* model)
{
	//1行分の文字列を入れる変数
	std::string line;

	//一行取得
	while (getline(data, line, '\n'))
	{
		if (line == "")
		{
			continue;
		}

		std::istringstream stream(line);

		for (size_t i = 0; i < model->nodes.size(); i++)
		{
			ReadNodeData(data, line, model->nodes[i], model);
		}

		if (str == line)
		{
			return;
		}
	}
}

void AliceFileStream::ReadNodeData(std::stringstream& data, std::string& str, Node& node, AliceModelData* model)
{
	//1行分の文字列を入れる変数
	std::string line;

	//一行取得
	while (getline(data, line, '\n'))
	{
		if (line == "")
		{
			continue;
		}

		std::istringstream stream(line);

		if (str == line)
		{
			getline(data, line, '\n');
			getline(data, str, '\n');
			return;
		}

		getline(stream, line, ':');

		if (line == "Name")
		{
			getline(stream, line, ':');

			ReadString(line, node.name);

			continue;
		}

		if (line == "Transform")
		{
			getline(stream, line, ':');
			ReadMatrix(line, node.transform);
			continue;
		}

		if (line == "GlobalTransform")
		{
			getline(stream, line, ':');
			ReadMatrix(line, node.globalTransform);
			continue;
		}

		if (line == "Parent")
		{
			getline(stream, line, ':');
			std::string nodeName;
			ReadString(line, nodeName);

			ReadParentData(nodeName, node, model->nodes);
			continue;
		}
	}
}

void AliceFileStream::ReadParentData(const std::string& name, Node& node, std::vector<Node>& nodes)
{
	if (name == "")
	{
		node.parent = nullptr;
		return;
	}

	std::vector<Node>::iterator itr;
	itr = std::find_if(nodes.begin(), nodes.end(), [&](Node& p)
		{
			return p.name == name;
		});

	if (itr != nodes.end())
	{
		node.parent = &*itr;
		return;
	}
	else
	{
		node.parent = nullptr;
	}
}

void AliceFileStream::ReadBoneData(const std::string& strbone, Bone& bone, ModelMesh* model)
{
	std::istringstream stream(strbone);
	std::string str;

	getline(stream, str, '|');
	ReadString(str, bone.name);

	getline(stream, str, '|');
	ReadMatrix(str, bone.offsetMatirx);

	getline(stream, str, '|');
	ReadNumber(str, bone.index);

	model->bones[bone.name] = &bone;
}

void AliceFileStream::ReadBoneIndex(const std::string& strInd, std::array<UINT, MAX_BONE_INDICES>& boneIndex)
{
	lineData.str(strInd.substr(1, strInd.size() - 2));
	lineData.clear();

	getline(lineData, buff, ',');
	boneIndex[0] = Atof(buff);

	getline(lineData, buff, ',');
	boneIndex[1] = Atof(buff);

	getline(lineData, buff, ',');
	boneIndex[2] = Atof(buff);

	getline(lineData, buff, ',');
	boneIndex[3] = Atof(buff);
}

void AliceFileStream::ReadMatrix(const std::string& strMat, AliceMathF::Matrix4& mat)
{
	lineData.str(strMat.substr(1, strMat.size() - 2));
	lineData.clear();

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			getline(lineData, buff, ',');
			mat.m[i][j] = Atof(buff);
		}
	}
}

void AliceFileStream::ReadString(const std::string& strData, std::string& str)
{
	str = strData.substr(1, strData.size() - 2);

}

void AliceFileStream::ReadFlag(const std::string& strFlag, bool& flag)
{
	flag = std::equal(strFlag.begin(), strFlag.end(), "true") ? true : false;
}

void AliceFileStream::ReadNumber(const std::string& strNum, float& num)
{
	num = std::atof(strNum.substr(1, strNum.size() - 2).c_str());
}

void AliceFileStream::ReadNumber(const std::string& strNum, uint32_t& num)
{
	num = static_cast<uint32_t>(std::atof(strNum.substr(1, strNum.size() - 2).c_str()));
}

float AliceFileStream::Atof(const std::string& str)
{
	return static_cast<float>(atof(str.c_str()));
}

void AliceFileStream::ReadBoneWeight(const std::string& strWei, std::array<float, MAX_BONE_INDICES>& boneWeight)
{
	lineData.str(strWei.substr(1, strWei.size() - 2));
	lineData.clear();

	getline(lineData, buff, ',');
	boneWeight[0] = Atof(buff);

	getline(lineData, buff, ',');
	boneWeight[1] = Atof(buff);

	getline(lineData, buff, ',');
	boneWeight[2] = Atof(buff);

	getline(lineData, buff, ',');
	boneWeight[3] = Atof(buff);
}

void AliceFileStream::ReadVector3(const std::string& strVec, AliceMathF::Vector3& ver)
{
	lineData.str(strVec.substr(1, strVec.size() - 2));
	lineData.clear();

	getline(lineData, buff, ',');
	ver.x = Atof(buff);

	getline(lineData, buff, ',');
	ver.y = Atof(buff);

	getline(lineData, buff, ',');
	ver.z = Atof(buff);
}

void AliceFileStream::ReadVector3(const std::string& strVec, AliceMathF::Vector4& ver)
{
	lineData.str(strVec.substr(1, strVec.size() - 2));
	lineData.clear();

	getline(lineData, buff, ',');
	ver.x = Atof(buff);

	getline(lineData, buff, ',');
	ver.y = Atof(buff);

	getline(lineData, buff, ',');
	ver.z = Atof(buff);

	ver.w = 1.0f;
}

void AliceFileStream::ReadVector2(const std::string& strVec, AliceMathF::Vector2& ver)
{
	lineData.str(strVec.substr(1, strVec.size() - 2));
	lineData.clear();

	getline(lineData, buff, ',');
	ver.x = Atof(buff);

	getline(lineData, buff, ',');
	ver.y = Atof(buff);
}

void AliceFileStream::ReadVector4(const std::string& strVec, AliceMathF::Vector4& ver)
{
	lineData.str(strVec.substr(1, strVec.size() - 2));
	lineData.clear();

	getline(lineData, buff, ',');
	ver.x = Atof(buff);

	getline(lineData, buff, ',');
	ver.y = Atof(buff);

	getline(lineData, buff, ',');
	ver.z = Atof(buff);

	getline(lineData, buff, ',');
	ver.w = Atof(buff);
}


bool AliceFileStream::LoadAlicePolygonBinaryData(const std::string& path, AliceModelData* model)
{
	//ファイルを開く
	FILE* fp = NULL;
	fopen_s(&fp, path.data(), "rb");

	directoryPath = AliceFunctionUtility::GetDirectoryPath(path);

	if (!fp)
	{
		return false;
	}

	if (!ReadHesderBinaryData(model, fp))
	{
		fclose(fp);
		return false;

	}


	if (!ReadNodesBinaryData(model, fp))
	{
		fclose(fp);
		return false;

	}

	if (!ReadMeshBinaryData(model, fp))
	{
		fclose(fp);
		return false;

	}

	fclose(fp);
	return true;

}

bool AliceFileStream::ReadHesderBinaryData(AliceModelData* model, FILE* fp)
{
	//名前
	{
		size_t nameNum;
		fread(&nameNum, sizeof(size_t), 1, fp);
		if (nameNum < 256)
		{
			fread(buffC, sizeof(char), nameNum, fp);
			model->name = std::string(buffC, nameNum);
		}
		else
		{
			return false;
		}

	}

	//アニメーションできるか
	{
		fread(&model->canAnimation, sizeof(bool), 1, fp);
	}

	//アニメーションするか
	{
		fread(&model->IsAnime, sizeof(bool), 1, fp);
	}

	//rootNodeの逆行列
	{
		fread(&model->globalInverseTransform, sizeof(float), 16, fp);
	}

	//ノードの数
	{
		size_t nodeNum;
		fread(&nodeNum, sizeof(size_t), 1, fp);
		model->nodes.resize(nodeNum);
	}

	//メッシュの数
	{
		size_t meshNum;
		fread(&meshNum, sizeof(size_t), 1, fp);
		model->meshes.resize(meshNum);
	}

	return true;
}

bool AliceFileStream::ReadNodesBinaryData(AliceModelData* model, FILE* fp)
{

	for (size_t i = 0; i < model->nodes.size(); i++)
	{

		//ノードの名前
		{
			size_t nameNum;
			fread(&nameNum, sizeof(size_t), 1, fp);
			if (nameNum < 256)
			{
				fread(buffC, sizeof(char), nameNum, fp);
				model->nodes[i].name = std::string(buffC, nameNum);
			}
			else
			{
				return false;
			}
		}

		//ローカル変形行列
		{
			fread(&model->nodes[i].transform, sizeof(float), 16, fp);
		}

		//グローバル変形行列
		{
			fread(&model->nodes[i].globalTransform, sizeof(float), 16, fp);
		}

		//親ノード
		{
			size_t nameNum;
			fread(&nameNum, sizeof(size_t), 1, fp);
			if (nameNum < 256)
			{
				if (nameNum != 0)
				{
					fread(buffC, sizeof(char), nameNum, fp);
				}

			}
			else
			{
				return false;
			}

			std::string parentName(buffC, nameNum);

			if (parentName.size() == 0)
			{
				model->nodes[i].parent = nullptr;
				continue;
			}

			//親ノード探索
			std::vector<Node>::iterator itr;
			itr = std::find_if(model->nodes.begin(), model->nodes.end(), [&](Node& p)
				{
					return p.name == parentName;
				});

			if (itr != model->nodes.end())
			{
				model->nodes[i].parent = &*itr;
				continue;
			}
			else
			{
				model->nodes[i].parent = nullptr;
			}
		}

		
	}
	
	return true;
}

bool AliceFileStream::ReadMeshBinaryData(AliceModelData* model, FILE* fp)
{
	for (size_t i = 0; i < model->meshes.size(); i++)
	{

		//名前
		{
			size_t nameNum;
			fread(&nameNum, sizeof(size_t), 1, fp);
			if (nameNum < 256)
			{
				fread(buffC, sizeof(char), nameNum, fp);
				model->meshes[i].name = std::string(buffC, nameNum);
			}
			else
			{
				return false;
			}
		}

		//ノードの名前
		{
			size_t nameNum;
			fread(&nameNum, sizeof(size_t), 1, fp);
			if (nameNum < 256)
			{
				fread(buffC, sizeof(char), nameNum, fp);
				model->meshes[i].nodeName = std::string(buffC, nameNum);
			}
			else
			{
				return false;
			}

			std::vector<Node>::iterator itr;
			itr = std::find_if(model->nodes.begin(), model->nodes.end(), [&](Node& p)
				{
					return p.name == model->meshes[i].nodeName;
				});

			if (itr != model->nodes.end())
			{
				model->meshes[i].node = &*itr;
			}
			else
			{
				model->meshes[i].node = nullptr;
			}
		}

		//頂点データ
		{
			size_t vertexNum;
			fread(&vertexNum, sizeof(size_t), 1, fp);
			model->meshes[i].vertices.resize(vertexNum);

			fread(model->meshes[i].vertices.data(), sizeof(model->meshes[i].vertices[0]), vertexNum, fp);
		}

		//インデックスデータ
		{
			size_t indexNum;
			fread(&indexNum, sizeof(size_t), 1, fp);
			model->meshes[i].indices.resize(indexNum);

			fread(model->meshes[i].indices.data(), sizeof(model->meshes[i].indices[0]), indexNum, fp);
		}

		//テクスチャファイルパス
		{
			size_t TextureNum;
			fread(&TextureNum, sizeof(size_t), 1, fp);

			model->meshes[i].textures.resize(TextureNum);
			for (size_t j = 0; j < TextureNum; j++)
			{
				size_t nameNum;
				fread(&nameNum, sizeof(size_t), 1, fp);
				if (nameNum < 256)
				{
					fread(buffC, sizeof(char), nameNum, fp);
					std::string filepath = std::string(buffC, nameNum);
					filepath = directoryPath + filepath;
					model->meshes[i].textures[j] = TextureManager::GetTextureData(TextureManager::Load(filepath));
				}
				else
				{
					return false;
				}
			}
		}

		//ノーマルテクスチャファイルパス
		{
			size_t TextureNum ;
			fread(&TextureNum, sizeof(size_t), 1, fp);
			model->meshes[i].texturesNormal.resize(TextureNum);
			for (size_t i = 0; i < TextureNum; i++)
			{
				size_t nameNum ;
				fread(&nameNum, sizeof(size_t), 1, fp);
				if (nameNum < 256)
				{
					fread(buffC, sizeof(char), nameNum, fp);

					std::string filepath= std::string(buffC, nameNum);
					filepath = directoryPath + filepath;
					model->meshes[i].texturesNormal[i] = TextureManager::GetTextureData(TextureManager::Load(filepath));
				}
				else
				{
					return false;
				}
			}
		}

		//ボーン
		{
			size_t bonesNum = model->meshes[i].vecBones.size();
			fread(&bonesNum, sizeof(size_t), 1, fp);
			model->meshes[i].vecBones.resize(bonesNum);

			for (size_t j = 0; j < bonesNum; j++)
			{
				size_t nameNum;
				fread(&nameNum, sizeof(size_t), 1, fp);
				if (nameNum < 256)
				{
					fread(buffC, sizeof(char), nameNum, fp);
					model->meshes[i].vecBones[j].name = std::string(buffC, nameNum);
				}
				else
				{
					return false;
				}

				fread(&model->meshes[i].vecBones[j].offsetMatirx, sizeof(float), 16, fp);

				fread(&model->meshes[i].vecBones[j].index, sizeof(UINT), 1, fp);

				model->meshes[i].bones[model->meshes[i].vecBones[j].name] = &model->meshes[i].vecBones[j];
			}
		}

		//マテリアル
		{
			size_t nameNum = model->meshes[i].material.name.size();
			fread(&nameNum, sizeof(size_t), 1, fp);
			if (nameNum < 256)
			{
				fread(buffC, sizeof(char), nameNum, fp);
				model->meshes[i].material.name = std::string(buffC, nameNum);
			}
			else
			{
				return false;
			}

			fread(&model->meshes[i].material.ambient, sizeof(float), 3, fp);

			fread(&model->meshes[i].material.diffuse, sizeof(float), 3, fp);

			fread(&model->meshes[i].material.specular, sizeof(float), 3, fp);

			fread(&model->meshes[i].material.emission, sizeof(float), 3, fp);

			fread(&model->meshes[i].material.shininess, sizeof(float), 1, fp);

			fread(&model->meshes[i].material.alpha, sizeof(float), 1, fp);

			fread(&nameNum, sizeof(size_t), 1, fp);
			if (nameNum < 256)
			{
				fread(buffC, sizeof(char), nameNum, fp);
				model->meshes[i].material.textureFiename = std::string(buffC, nameNum);
			}
			else
			{
				return false;
			}
		}
	}

	return true;
}


bool AliceFileStream::LoadAliceMotionBinaryData(const std::string& path, MotionData* motion)
{
	//ファイルを開く
	FILE* fp = NULL;
	fopen_s(&fp, path.data(), "rb");

	if (!fp)
	{
		return false;
	}

	//名前
	{
		size_t nameNum;
		fread(&nameNum, sizeof(size_t), 1, fp);
		if (nameNum < 256)
		{
			fread(buffC, sizeof(char), nameNum, fp);
			motion->name = std::string(buffC, nameNum);
		}
		else
		{
			fclose(fp);
			return false;
		}

	}

	//一秒あたりのアニメーション継続時間
	{
		float ticks;
		fread(&ticks, sizeof(float), 1, fp);
		motion->ticksPerSecond = ticks;
	}

	//アニメーション時間
	{
		float duration;
		fread(&duration, sizeof(float), 1, fp);
		motion->duration = duration;
	}

	//チャンネル数
	{
		size_t channelNum;
		fread(&channelNum, sizeof(size_t), 1, fp);
		motion->channels.resize(channelNum);
	}

	//チャンネル
	for (size_t i = 0; i < motion->channels.size(); i++)
	{
		if (!ReadMotionNodeBinaryData(&motion->channels[i], fp))
		{
			fclose(fp);
			return false;
		}
	}

	fclose(fp);

	return true;
}

bool AliceFileStream::ReadMotionNodeBinaryData(MotionNode* node, FILE* fp)
{
	//名前
	{
		size_t nameNum;
		fread(&nameNum, sizeof(size_t), 1, fp);
		if (nameNum < 256)
		{
			fread(buffC, sizeof(char), nameNum, fp);
			node->name = std::string(buffC, nameNum);
		}
		else
		{
			return false;
		}
	}

	//スケーリング
	{
		size_t scalingNum;
		fread(&scalingNum, sizeof(size_t), 1, fp);
		node->scalingKeys.resize(scalingNum);

		for (size_t i = 0; i < scalingNum; i++)
		{
			fread(&node->scalingKeys[i], sizeof(node->scalingKeys[0]), 1, fp);
		}

	}

	//回転角
	{
		size_t rotationNum;
		fread(&rotationNum, sizeof(size_t), 1, fp);
		node->rotationKeys.resize(rotationNum);

		for (size_t i = 0; i < rotationNum; i++)
		{
			fread(&node->rotationKeys[i], sizeof(node->rotationKeys[0]), 1, fp);
		}
	}

	//位置
	{
		size_t positionNum;
		fread(&positionNum, sizeof(size_t), 1, fp);
		node->positionKeys.resize(positionNum);

		for (size_t i = 0; i < positionNum; i++)
		{
			fread(&node->positionKeys[i], sizeof(node->positionKeys[0]), 1, fp);
		}

	}

	return true;
}
#pragma once
#include"Model.h"
#include"DefaultMaterial.h"

class objModel
{

public:

	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	static void Create(const char* filePath, bool smoothing, ModelData* data);

private:

	static void LoadMaterial(const std::string& directoryPath,const std::string& filename, ModelData* data);
	static void LoadTexture(const std::string& directoryPath, const std::string& filename, ModelData* data);

	//�X���[�W���O���_����
	static void CalculateSmoothedVertexNormals(ModelData* data);
};
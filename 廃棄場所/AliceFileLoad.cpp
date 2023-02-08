#include "AliceFileLoad.h"
#include"AliceFileStream.h"
#include"AliceFunctionUtility.h"

bool AliceFileLoad::ModelLoad(const std::string& fileDirectoryPath, AliceModel* model)
{

	std::vector<std::string> files;

	std::string filePath;

	/*if (AliceFunctionUtility::FileIsExist(fileDirectoryPath))
	{
		assert(0);
	}*/

	files = AliceFunctionUtility::getFileNames(fileDirectoryPath);

	//ディレクトリからFBXファイルを探す
	for (std::string file : files)
	{
		if (file.find(".alpb") != std::string::npos || file.find(".alp") != std::string::npos)
		{
			filePath = file;
		}
	}

	std::string fileExtension = AliceFunctionUtility::FileExtension(filePath);

	if (fileExtension == "alpb")
	{
		AliceFileStream::LoadAlicePolygonBinaryData(filePath, model);
	}
	else if (fileExtension == "alp")
	{
		AliceFileStream::LoadAlicePolygonData(filePath, model);
	}
	else
	{
		return false;
	}

	for (size_t i = 0; i < model->meshes.size(); i++)
	{
		for (size_t j = 0; j < model->meshes[i].vecBones.size(); j++)
		{
			model->meshes[i].bones[model->meshes[i].vecBones[j].name] = model->meshes[i].vecBones[j];
		}
	}


	return true;
}

AliceFileLoad* AliceFileLoad::GetInstance()
{
	static AliceFileLoad instance;
	return &instance;
}

AliceFileLoad::AliceFileLoad()
{

}

AliceFileLoad::~AliceFileLoad()
{
}

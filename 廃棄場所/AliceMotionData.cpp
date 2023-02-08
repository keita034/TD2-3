#include "AliceMotionData.h"
#include "AliceFileStream.h"

void AliceMotionData::Create(const std::string& fileDirectoryPath)
{
	std::vector<std::string> files;

	std::string filePath;

	files = AliceFunctionUtility::getFileNames(fileDirectoryPath);

	//ディレクトリからFBXファイルを探す
	for (std::string file : files)
	{
		if (file.find(".almb") != std::string::npos || file.find(".alm") != std::string::npos)
		{
			filePath = file;
		}
	}

	std::string fileExtension = AliceFunctionUtility::FileExtension(filePath);

	if (fileExtension == "almb")
	{
		if (!AliceFileStream::LoadAliceMotionBinaryData(filePath, this))
		{
			assert(0);
		}
	}
	else if (fileExtension == "alm")
	{

	}
	else
	{
		assert(0);
	}
}

float AliceMotionData::GetAnimeMaxflame()
{
	return duration;
}

float AliceMotionData::GetTickTimes(float frame)
{
	float TicksPerSecond = ticksPerSecond != 0 ? ticksPerSecond : 25.0f;

	return  frame * TicksPerSecond;
}

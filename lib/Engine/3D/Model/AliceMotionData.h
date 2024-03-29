#pragma once
#include"ErrorException.h"
#include"AliceMathUtility.h"

//Vector3のアニメーションキー
struct VectorKey
{
	//キーの時間
	double time;

	//キーの値
	AliceMathF::Vector3 value;
};

//Quaternionのアニメーションキー
struct QuaternionKey
{
	//キーの時間
	double time;

	//キーの値
	AliceMathF::Quaternion value;
};

struct MotionNode
{
	//名前
	std::string name;

	//スケーリング
	std::vector<VectorKey>scalingKeys;

	//回転角
	std::vector<QuaternionKey>rotationKeys;

	//位置
	std::vector<VectorKey>positionKeys;
};

class MotionData
{
private:
	friend class AliceMotionData;
	friend class AliceFileStream;
	friend class AliceModel;

	std::string filePath;

	uint32_t modelHandle;

	//名前
	std::string name;

	//一秒あたりのアニメーション継続時間(指定されてなかったら0)
	float ticksPerSecond;

	//アニメーション時間
	float duration;

	//ノードアニメーションチャンネル
	std::vector<MotionNode> channels;

};

class AliceMotionData
{
private:
	friend class AliceFileStream;
	friend class AliceModel;

	static std::vector<std::string>filePaths;

	static std::unordered_map<std::string, std::unique_ptr<MotionData>> motionDatas;

	static uint32_t modelCount;

	static const uint32_t maxMotion = 1024;

	MotionData* motionData = nullptr;

public:

	float GetAnimeMaxflame();

	float GetTickTimes(float frame);

	void SetMotion(uint32_t motionHandle);

	/// <summary>
	/// モーション生成
	/// </summary>
	/// <param name="filePath">ファイルディレクトリ</param>
	/// <returns>ハンドル</returns>
	static uint32_t CreateMotion(const std::string& fileDirectoryPath);

	/// <summary>
	/// 共通初期化
	/// </summary>
	static void CommonInitialize();
};


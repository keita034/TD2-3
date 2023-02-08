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

class AliceMotionData
{
private:
	friend class AliceFileStream;
	friend class AliceModel;

	//名前
	std::string name;

	//一秒あたりのアニメーション継続時間(指定されてなかったら0)
	float ticksPerSecond;

	//アニメーション時間
	float duration;

	//ノードアニメーションチャンネル
	std::vector<MotionNode> channels;

public:

	void Create(const std::string& fileDirectoryPath);

	float GetAnimeMaxflame();

	float GetTickTimes(float frame);

};


#pragma once
#include"ErrorException.h"
#include"AliceMathUtility.h"

//Vector3�̃A�j���[�V�����L�[
struct VectorKey
{
	//�L�[�̎���
	double time;

	//�L�[�̒l
	AliceMathF::Vector3 value;
};

//Quaternion�̃A�j���[�V�����L�[
struct QuaternionKey
{
	//�L�[�̎���
	double time;

	//�L�[�̒l
	AliceMathF::Quaternion value;
};

struct MotionNode
{
	//���O
	std::string name;

	//�X�P�[�����O
	std::vector<VectorKey>scalingKeys;

	//��]�p
	std::vector<QuaternionKey>rotationKeys;

	//�ʒu
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

	//���O
	std::string name;

	//��b������̃A�j���[�V�����p������(�w�肳��ĂȂ�������0)
	float ticksPerSecond;

	//�A�j���[�V��������
	float duration;

	//�m�[�h�A�j���[�V�����`�����l��
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
	/// ���[�V��������
	/// </summary>
	/// <param name="filePath">�t�@�C���f�B���N�g��</param>
	/// <returns>�n���h��</returns>
	static uint32_t CreateMotion(const std::string& fileDirectoryPath);

	/// <summary>
	/// ���ʏ�����
	/// </summary>
	static void CommonInitialize();
};


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

class AliceMotionData
{
private:
	friend class AliceFileStream;
	friend class AliceModel;

	//���O
	std::string name;

	//��b������̃A�j���[�V�����p������(�w�肳��ĂȂ�������0)
	float ticksPerSecond;

	//�A�j���[�V��������
	float duration;

	//�m�[�h�A�j���[�V�����`�����l��
	std::vector<MotionNode> channels;

public:

	void Create(const std::string& fileDirectoryPath);

	float GetAnimeMaxflame();

	float GetTickTimes(float frame);

};


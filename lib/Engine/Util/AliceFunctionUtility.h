#pragma once
#include"ErrorException.h"

namespace AliceFunctionUtility
{
	/// <summary>
	/// ����������C�h������ɕϊ�
	/// </summary>
	/// <param name="string">�ϊ�������������</param>
	std::wstring StringToWstring(const std::string& string);

	/// <summary>
	/// �f�B���N�g������t�@�C�����ꗗ������
	/// </summary>
	/// <param name="folderPath">�f�B���N�g���p�X</param>
	/// <returns>�t�@�C�����ꗗ</returns>
	std::vector<std::string> getFileNames(const std::string& folderPath);

	/// <summary>
	/// �t�@�C���p�X����t�@�C���������o��
	/// </summary>
	/// <param name="path">�t�@�C���p�X</param>
	/// <returns>�t�@�C����</returns>
	std::string GetFileName(std::string& path);

	/// <summary>
	/// �t�@�C���p�X����t�@�C���������o��(�g���q����)
	/// </summary>
	/// <param name="path">�t�@�C���p�X</param>
	/// <returns>�t�@�C����</returns>
	std::string ExtractFileName(const std::string& path);

	/// <summary>
	/// �t�@�C���p�X����f�B���N�g���p�X�����o��
	/// </summary>
	/// <param name="path">�t�@�C���p�X</param>
	/// <returns>�f�B���N�g���p�X</returns>
	std::string GetDirectoryPath(const std::string& filePath);

	/// <summary>
	/// �t�@�C���p�X����g���q�����o��
	/// </summary>
	/// <param name="path">�t�@�C���p�X</param>
	/// <returns>�g���q</returns>
	std::string FileExtension(const std::string& path);

	// �g���q��u�������鏈��
	
	/// <summary>
	/// �t�@�C���̊g���q��u��������
	/// </summary>
	/// <param name="path">�t�@�C���p�X</param>
	/// <param name="ext">�u��������g���q</param>
	std::string ReplaceExtension(const std::string& path, const char* ext);
};


#pragma once
#include"AliceMathF.h"
#include"AliceMath.h"

namespace AliceMathUtility
{
#pragma region ��Βl�̌v�Z

	//��Βl�̌v�Z
	int Abs(int abs);

	//��Βl�̌v�Z
	long AbsL(long abs);

	//��Βl�̌v�Z
	long long AbsLL(long long abs);

#pragma endregion ��Βl�̌v�Z

#pragma region ��r�֐�

	/// <summary>
	/// �l���傫������Ԃ�
	/// </summary>
	template<typename T>
	T Max(T a, T b)
	{
		return (a > b) ? a : b;
	}

	/// <summary>
	/// �l���傫���z��Ԃ�(vector)
	/// </summary>
	template<typename T>
	T Max(std::vector<T> values)
	{
		int num = values.size() - 1;

		if (num == 0)
		{
			return static_cast<T>(0);
		}

		float num2 = values[0];

		for (int i = 1; i < num; i++)
		{
			if (values[i] > num2)
			{
				num2 = values[i];
			}
		}

		return num2;
	}

	/// <summary>
	/// �l������������Ԃ�
	/// </summary>
	template<typename T>
	T Min(T a, T b)
	{
		return (a < b) ? a : b;
	}

	/// <summary>
	/// �l���������z��Ԃ�(vector)
	/// </summary>
	template<typename T>
	T Min(std::vector<T> values)
	{
		int num = values.size() - 1;

		if (num == 0)
		{
			return static_cast<T>(0);
		}

		float num2 = values[0];

		for (int i = 1; i < num; i++)
		{
			if (values[i] < num2)
			{
				num2 = values[i];
			}
		}

		return num2;
	}

#pragma endregion ��r�֐�
};
#pragma once

class DebugText
{
private:
	static DebugText* instance;

public:

	/// <summary>
	/// �C���X�^���X������
	/// </summary>
	static DebugText* GetInstance();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

private:

	DebugText() = default;
	~DebugText() = default;

};


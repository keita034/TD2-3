#pragma once
#include"BaseScene.h"

class TitleScene : public BaseScene
{
private:

public:

	TitleScene();
	~TitleScene();

	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// XVˆ—
	/// </summary>
	void Update() override;

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw() override;

	/// <summary>
	/// Œãn––
	/// </summary>
	void Finalize() override;
};


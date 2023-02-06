#pragma once
#include"BaseScene.h"
#include "ErrorException.h"
#include "TextureManager.h"
#include "Sprite.h"

class TitleScene : public BaseScene
{
private:
	std::unique_ptr<Sprite> spriteTitle_;
	TextureData titleTex_;

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


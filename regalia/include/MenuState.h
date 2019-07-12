#pragma once

#include <State.h>
#include "Sprite.h"
#include "Music.h"
#include "Timer.h"
#include "Sound.h"

class MenuState : public State {
public:
	MenuState();

	~MenuState();

	void LoadAssets() override;

	void Update(unsigned dt) override;

	void Render() override;

	void Start() override;

	void Pause() override;

	void Resume() override;

private:
	enum class MenuModes {
		Initial,
		SelectOptions
	};

	enum {
		Play,
		Story,
		Credits,
		Exit,
		MAX_OPTION
	};

	int SelectedOption = Play;

	MenuModes mode = MenuModes::Initial;

	std::map<int, Sprite*> OptionSprite;

	Music music;

	Sound* sound = nullptr;

	void ChangeMode();

	void CreateBackground();

	void CreateOptions();

	void CreateOption(int option, const SpriteSheetData* spriteSheetData, Vec2 position);

	void CreateSound();
};

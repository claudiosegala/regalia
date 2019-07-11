#pragma once

#include <State.h>
#include "Sprite.h"
#include "Timer.h"

class SelectPersonaState : public State {
public:
	SelectPersonaState();

	~SelectPersonaState();

	void LoadAssets() override;

	void Update(unsigned dt) override;

	void Render() override;

	void Start() override;

	void Pause() override;

	void Resume() override;

private:
	Constants::PersonaType nextPersona(Constants::PersonaType persona);
	Constants::PersonaType previousPersona(Constants::PersonaType persona);

	struct PersonaInfo {
		bool isAvailable;
		const SpriteSheetData* spriteSheetData;
	};

	std::map<Constants::PersonaType, PersonaInfo> personas = {
		{ Constants::PersonaType::MISTER_N_RED, { true, &Constants::Player::MisterNRed } },
		{ Constants::PersonaType::MISTER_N_BLUE, { true, &Constants::Player::MisterNBlue } },
		{ Constants::PersonaType::GOTICA_PURPLE, { true, &Constants::Player::GoticaPurple } },
		{ Constants::PersonaType::GOTICA_RED, { true, &Constants::Player::GoticaRed } },
	};

	std::vector<bool> personaConfirmed;

	std::vector<Constants::PersonaType> currentPersona;

	std::vector<GameObject*> players;

	std::vector<std::pair<GameObject*, GameObject*>> arrows;

	std::vector<Timer> timers;

	const Vec2 positions[4] = {
		{ 300, 110 },
		{ 640, 110 },
		{ 300, 380 },
		{ 640, 380 },
	};
};

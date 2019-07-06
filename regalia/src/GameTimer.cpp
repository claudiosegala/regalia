#include "pch.h"
#include "GameTimer.h"
#include "Game.h"
#include "PlayState.h"
#include "GameData.h"

GameTimer::GameTimer(GameObject& go)
    : Component(go) {}

void GameTimer::Update(unsigned dt) {
	animationTimer.Update(dt);
}

void GameTimer::Render() {
	auto renderer = Game::GetInstance()->GetRenderer();

	SDL_Rect topBar = {
		0,
		0,
		Constants::Window::Width,
		5
	};

	if (GameData::CurrentRoundTimer.Get() < Constants::Game::MillisecondsPerRound) {

		auto timePercentage = float(GameData::CurrentRoundTimer.Get()) / float(Constants::Game::MillisecondsPerRound);
		auto barWidth = Constants::Window::Width - Constants::Window::Width * timePercentage;

		SDL_Rect timeBar = {
			(Constants::Window::Width - int(barWidth)) / 2,
			0,
			int(barWidth),
			5
		};

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &topBar);

		auto red = 255.0f * timePercentage;
		auto green = 255 - 255.0f * timePercentage;
		SDL_SetRenderDrawColor(renderer, Uint8(red), Uint8(green), 0, 255);
		SDL_RenderFillRect(renderer, &timeBar);

	} else {

		const static int animationTime = 1000;

		if (animationTimer.Get() > animationTime) {
			animationTimer.Restart();
		}

		auto red = abs(255 * float(int(animationTimer.Get()) - (animationTime / 2)) / (animationTime / 2));

		SDL_SetRenderDrawColor(renderer, Uint8(red), 0, 0, 255);

		SDL_RenderFillRect(renderer, &topBar);
	}
}

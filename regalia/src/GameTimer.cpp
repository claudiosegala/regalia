#include "pch.h"
#include "GameTimer.h"
#include "Game.h"

GameTimer::GameTimer(GameObject& go)
    : Component(go) {}

void GameTimer::Update(unsigned dt) {
	gameTimer.Update(dt);
	animationTimer.Update(dt);
}

void GameTimer::Render() {
	auto renderer = Game::GetInstance()->GetRenderer();

	if (gameTimer.Get() < Constants::Game::SecondsPerRound * 1000) {

		auto timePercentage = float(gameTimer.Get()) / float(Constants::Game::SecondsPerRound * 1000);
		auto barWidth = Constants::Window::Width - Constants::Window::Width * timePercentage;

		auto red = 255.0f * timePercentage;
		auto green = 255 - 255.0f * timePercentage;
		SDL_SetRenderDrawColor(renderer, Uint8(red), Uint8(green), 0, 255);

		SDL_Rect rect = {
			(Constants::Window::Width - int(barWidth)) / 2,
			0,
			int(barWidth),
			5
		};

		SDL_RenderFillRect(renderer, &rect);

	} else {

		if (animationTimer.Get() > 1000) {
			animationTimer.Restart();
		}

		auto barSize = int(10.0f * float(animationTimer.Get()) / 1000.0f);

		SDL_Rect rectTop = {
			0,
			0,
			Constants::Window::Width,
			barSize
		};

		SDL_Rect rectLeft = {
			0,
			0,
			barSize,
			Constants::Window::Height
		};

		SDL_Rect rectRight = {
			Constants::Window::Width - barSize,
			0,
			barSize,
			Constants::Window::Height
		};

		SDL_Rect rectBottom = {
			0,
			Constants::Window::Height - barSize,
			Constants::Window::Width,
			barSize
		};

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		SDL_RenderFillRect(renderer, &rectTop);
		SDL_RenderFillRect(renderer, &rectLeft);
		SDL_RenderFillRect(renderer, &rectRight);
		SDL_RenderFillRect(renderer, &rectBottom);
	}
}

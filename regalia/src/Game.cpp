#include <pch.h>
#include <Game.h>
#include <Constants.h>
#include <InputManager.h>
#include <Logger.h>
#include <Resources.h>
#include "GameData.h"

Game* Game::instance;

Game::Game(const std::string& title, int width, int height) {
	if (instance != nullptr) {
		throw std::runtime_error("There should be only one instance!\n");
	}

	instance = this;
	frameStart = 0;
	dt = 0.0f;
	storedState = nullptr;
	window = nullptr;
	renderer = nullptr;

	Init_SDL();
	Init_IMG();
	Init_MIX();
	Init_TTF();
	Init_WDW(title, width, height);
	Init_RDR();

	Logger::Info("Created the game instance");
}

Game::~Game() {
	// Clean SDL instances
	Logger::Info("Destroying Renderer");
	SDL_DestroyRenderer(renderer);

	Logger::Info("Destroying Window");
	SDL_DestroyWindow(window);

	Logger::Info("Quiting SDL TTF");
	TTF_Quit();

	Logger::Info("Quiting SDL Mix Audio");
	Mix_CloseAudio();

	Logger::Info("Quiting SDL Mixer");
	while (Mix_Init(0)) {
		Mix_Quit(); // The best way (by documentation)
	}

	Logger::Info("Quiting SDL Image");
	IMG_Quit();

	Logger::Info("Quiting SDL");
	SDL_Quit();
}

void Game::Run() {
	Logger::Info("Running");
	if (storedState == nullptr) {
		return;
	}

	Start();
	Loop();
	End();
}

void Game::Push(State* state) {
	storedState = state;
}

Game* Game::GetInstance() {
	if (Game::instance != nullptr) {
		return Game::instance;
	}

	return Game::instance = new Game(Constants::Window::Name, Constants::Window::Width, Constants::Window::Height);
}

State* Game::GetCurrentState() {
	return stateStack.top().get();
}

SDL_Renderer* Game::GetRenderer() const {
	return renderer;
}

SDL_Window* Game::GetWindow() const {
	return window;
}

float Game::GetDeltaTime() const {
	return dt;
}


void Game::Start() {
	Logger::Info("Starting Game");

	stateStack.emplace(storedState);

	storedState->Start();

	storedState = nullptr;
}

void Game::Loop() {
	Logger::Info("Initting Loop");
	auto& in = InputManager::GetInstance();

	while (!stateStack.empty()) {
		auto state = stateStack.top().get();

		if (state->QuitRequested()) {
			Logger::Info("Quitting");
			break;
		}

		if (state->PopRequested()) {
			Logger::Info("Popping State");
			stateStack.pop();

			Resources::Prune();

			if (!stateStack.empty()) {
				Logger::Info("Changing State");
				state = stateStack.top().get();
				state->Resume();
			}
		}

		if (storedState != nullptr) {
			Logger::Info("Adding State");
			if (state != nullptr) {
				state->Pause();
			}

			stateStack.emplace(storedState);

			storedState = nullptr;

			Logger::Info("Changing State");

			state = stateStack.top().get();

			state->Start();
		}

		if (stateStack.empty()) {
			break;
		}

		CalculateDeltaTime();

		in.Update();

		if (in.KeyPress(SDLK_f)) {
			GameData::WindowFullscreen = !GameData::WindowFullscreen;
			SDL_SetWindowFullscreen(window, GameData::WindowFullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
		}

		state->Update(dt);
		state->Render();

		SDL_RenderPresent(renderer);

		SDL_Delay(16);
	}
}

void Game::End() {
	Logger::Info("Ended Game");

	if (storedState != nullptr) {
		Logger::Info("Erasing Stored State");
		delete storedState;
	}

	Logger::Info("Cleaning Stack of States");
	while (!stateStack.empty()) {
		stateStack.pop();
	}

	Logger::Info("Destroying Resources");
	Resources::Prune();
}

void Game::CalculateDeltaTime() {
	auto newFrameStart = (float)SDL_GetTicks();
	auto oldFrameStart = (float)frameStart;

	dt = (newFrameStart - oldFrameStart) / 1000.0f;
	frameStart = (unsigned int)newFrameStart;
}

void Game::Init_SDL() const {
	/* 
        Available Flags:
        SDL_INIT_TIMER
        SDL_INIT_GAMECONTROLLER,
        SDL_INIT_AUDIO
        SDL_INIT_EVENTS
        SDL_INIT_VIDEO
        SDL_INIT_EVERYTHING
        SDL_INIT_JOYSTICK
        SDL_INIT_NOPARACHUTE
        SDL_INIT_HAPTIC
    */
	auto flags = (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK);

	Logger::Info("Initing SDL");
	auto err = SDL_Init(flags);

	if (err < 0) {
		auto msg = "SDLError: " + std::string(SDL_GetError()) + "\n";
		throw std::runtime_error(msg);
	}
}

void Game::Init_IMG() const {
	/*
        Available Flags:
        IMG_INIT_JPG
        IMG_INIT_PNG
        IMG_INIT_TIF
    */
	auto flags = (IMG_INIT_JPG | IMG_INIT_PNG);

	Logger::Info("Initing SDL Image");
	auto res = IMG_Init(flags);

	if (res != flags) {
		auto msg = "ImageError: " + std::string(IMG_GetError()) + "\nThe flag sent was " + std::to_string(flags) + ", but the result of initing image was " + std::to_string(res) + "\n";
		throw std::runtime_error(msg);
	}
}

void Game::Init_MIX() const {
	/*
        Available Flags:
        MIX_INIT_FLAC
        MIX_INIT_MP3
        MIX_INIT_OGG
        MIX_INIT_MOD
        MIX_INIT_FLUIDSYNTH
        MIX_INIT_MODPLUG
    */
	auto flags = (MIX_INIT_OGG);

	Logger::Info("Initing Mixer");
	auto res = Mix_Init(flags);

	if (res != flags) {
		auto msg = "MixError: " + std::string(Mix_GetError()) + "\nThe flag sent was " + std::to_string(flags) + ", but the result of initing mixer was " + std::to_string(res) + "\n";
		throw std::runtime_error(msg);
	}

	Logger::Info("Configuring Audio");
	res = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	if (res < 0) {
		auto msg = "MixError: " + std::string(Mix_GetError()) + "\n";
		throw std::runtime_error(msg);
	}

	Logger::Info("Allocating Channels");
	res = Mix_AllocateChannels(32);

	if (res < 0) {
		auto msg = "MixError: " + std::string(Mix_GetError()) + "\n";
		throw std::runtime_error(msg);
	}
}

void Game::Init_TTF() const {
	Logger::Info("Initing TTF");
	auto res = TTF_Init();

	if (res == -1) {
		auto msg = "TTFError: " + std::string(TTF_GetError()) + "\n";
		throw std::runtime_error(msg);
	}
}

void Game::Init_WDW(const std::string& title, int width, int height) {
	auto pos = SDL_WINDOWPOS_CENTERED;
	uint32_t flags = SDL_WINDOW_RESIZABLE;

	Logger::Info("Creating Window");
	window = SDL_CreateWindow(title.c_str(), (int)pos, (int)pos, width, height, flags);

	if (window == nullptr) {
		auto msg = "SDLError: " + std::string(SDL_GetError()) + "\n";
		throw std::runtime_error(msg);
	}
}

void Game::Init_RDR() {
	auto index = -1; // SDL will choose the best for us

	/*
        Available flags:
        SDL_RENDERER_SOFTWARE
        SDL_RENDERER_PRESENTVSYNC
        SDL_RENDERER_ACCELERATED
        SDL_RENDERER_TARGETTEXTURE
    */
	uint32_t flags = (SDL_RENDERER_ACCELERATED);

	Logger::Info("Creating Renderer");
	renderer = SDL_CreateRenderer(window, index, flags);

	if (renderer == nullptr) {
		SDL_GetNumRenderDrivers(); // TODO: WTF is this?

		auto msg = "SDLError: " + std::string(SDL_GetError()) + "\n";
		throw std::runtime_error(msg);
	}

	auto result = SDL_RenderSetLogicalSize(renderer, Constants::Window::Width, Constants::Window::Height);
	if (result != 0) {
		auto msg = "SDL_RenderSetLogicalSize: " + std::string(SDL_GetError()) + "\n";
		throw std::runtime_error(msg);
	}
}
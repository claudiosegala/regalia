#include <pch.h>
#include <Logger.h>
#include <Music.h>
#include <Resources.h>

Music::Music()
    : music() {}

Music::Music(const std::string& file) {
	Open(file);
}

Music::~Music() {}

void Music::Play(int times) {
	if (this->music == nullptr)
		return;

	Logger::Info("Start Playing Music");
	auto err = Mix_PlayMusic(this->music.get(), times);

	if (err < 0) {
		auto msg = "MixError: " + std::string(Mix_GetError()) + "\n";
		throw std::runtime_error(msg);
	}
}

void Music::Stop(int msToStop) {
	Logger::Info("Fading Out Music");
	auto err = Mix_FadeOutMusic(msToStop);

	if (err != 1) {
		auto msg = "MixError: " + std::string(Mix_GetError()) + "\n";
		throw std::runtime_error(msg);
	}
}

void Music::Open(const std::string& file) {
	this->music = Resources::GetMusic(file);
}

bool Music::IsOpen() {
	return (this->music != nullptr);
}
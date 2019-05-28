#include <pch.h>
#include <Logger.h>
#include <Resources.h>
#include <Sound.h>
#include <Util.h>

Sound::Sound(GameObject& go)
    : Component(go)
    , chunk() {
	this->channel = -1;
}

Sound::Sound(GameObject& go, const std::string& file)
    : Component(go) {
	Open(file);
}

Sound::~Sound() {}

void Sound::Play(int times) {
	this->channel = Mix_PlayChannel(-1, this->chunk.get(), times - 1);

	if (this->channel < 0) {
		auto msg = "MixError: " + std::string(Mix_GetError()) + "\n";
		throw std::runtime_error(msg);
	} else {
		Logger::Info("Music is playing on channel " + std::to_string(this->channel));
	}
}

void Sound::Stop() {
	Logger::Info("Halting the channel " + std::to_string(this->channel));
	if (this->chunk != nullptr && this->channel >= 0) {
		Mix_HaltChannel(this->channel);
		Logger::Info("Halting the channel " + std::to_string(this->channel));
	}
}

void Sound::Open(const std::string& file) {
	this->chunk = Resources::GetSound(file);
}

bool Sound::IsOpen() {
	return (this->chunk == nullptr);
}

void Sound::Update(float dt) {
	UNUSED(dt);
}

void Sound::Render() {}

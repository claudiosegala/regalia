#include <pch.h>
#include <Logger.h>
#include <Resources.h>
#include <Sound.h>
#include <Util.h>

Sound::Sound(GameObject& go)
    : Component(go)
    , chunk() {
	channel = -1;
}

Sound::Sound(GameObject& go, const std::string& file)
    : Component(go) {
	Open(file);
}

Sound::~Sound() {}

void Sound::Play(int times) {
	channel = Mix_PlayChannel(-1, chunk.get(), times - 1);

	if (channel < 0) {
		auto msg = "MixError: " + std::string(Mix_GetError()) + "\n";
		throw std::runtime_error(msg);
	} else {
		Logger::Info("Music is playing on channel " + std::to_string(channel));
	}
}

void Sound::Stop() {
	Logger::Info("Halting the channel " + std::to_string(channel));
	if (chunk != nullptr && channel >= 0) {
		Mix_HaltChannel(channel);
		Logger::Info("Halting the channel " + std::to_string(channel));
	}
}

void Sound::Open(const std::string& file) {
	chunk = Resources::GetSound(file);
}

bool Sound::IsOpen() {
	return (chunk == nullptr);
}

void Sound::Update(unsigned dt) {
	UNUSED(dt);
}

void Sound::Render() {}

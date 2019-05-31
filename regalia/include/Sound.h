#pragma once

#include <Component.h>
#include <GameObject.h>

class Sound : public Component {
public:
	Sound(GameObject& go);

	Sound(GameObject& go, const std::string& file);

	~Sound();

	void Play(int times = 1);

	void Stop();

	void Open(const std::string& file);

	bool IsOpen();

	void Update(float dt) override;

	void Render() override;

private:
	int channel = -1;

	std::shared_ptr<Mix_Chunk> chunk;
};
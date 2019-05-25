#pragma once

#include <Component.h>
#include <Timer.h>
#include <Vec2.h>

class Sprite : public Component {
public:
	// TODO: see if every animation has the same frameCount
	Sprite(GameObject&, const std::string&, int frameCount = 1, float frameTime = 1.0f, float secondsToSelfDestruct = 0);

	~Sprite();

	void Open(const std::string&);

	void SetClip(int, int, int, int);

	void SetClip();

	void SetBox();

	void SetScale(float, float);

	Vec2 GetScale();

	void SetFrame(int);

	void SetFrameCount(int);

	void SetFrameTime(float);

	void Update(float) override;

	void Render() override;

	void Render(int, int);

	void Render(float, float);

	int GetWidth();

	int GetHeight();

	bool IsOpen();

private:
	int width;

	int height;

	Vec2 scale;

	int frameCount;

	int currentFrame;

	float timeElapsed;

	float frameTime;

	float secondsToSelfDestruct;

	Timer selfDestructCount;

	std::shared_ptr<SDL_Texture> texture;

	SDL_Rect clipRect;
};
